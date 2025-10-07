/*
Portable ZX-Spectrum emulator.
Copyright (C) 2001-2017 SMT, Dexus, Alone Coder, deathsoft, djdron, scor

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// based on SDL2 implementation.

// FOS

#define RGFW_BUFFER
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#include "src/platform/platform.h"
#include "src/tools/options.h"

#include "src/ui/ui.h"
#include "src/options_common.h"

#include "src/tools/tick.h"
#include "src/platform/io.h"

#ifdef USE_RGFW

namespace xPlatform {
	
	// === video ===
	
	dword RGBX (byte r, byte g, byte b) { return (b << 16) | (g << 8) | r; }
	
	static struct eCachedColors {
		void Init() {
			const byte brightness = 200;
			const byte bright_intensity = 55;
			for(int c = 0; c < 16; ++c)
			{
				byte i = c&8 ? brightness + bright_intensity : brightness;
				byte b = c&1 ? i : 0;
				byte r = c&2 ? i : 0;
				byte g = c&4 ? i : 0;
				items[c] = RGBX(r, g, b);
				items_rgbx[c] = RGBX(r, g, b);
			}
		}
		dword items[16];
		dword items_rgbx[16];
	} color_cache;
	
	RGFW_window* window = NULL;
	RGFW_surface* surface;
	u8 * vidBuffer;
	
	bool InitVideo() {
		
		RGFW_windowFlags flags = RGFW_windowCenter | RGFW_windowNoResize | RGFW_windowAllowDND;
		window = RGFW_createWindow(Handler()->WindowCaption(), 100, 100, 320 * 2, 240 * 2, flags);
		if (!window) return false;
		
		color_cache.Init();
		
		vidBuffer = (u8*)RGFW_ALLOC((u32)(window->w * window->h * 3));
		surface = RGFW_createSurface(vidBuffer, window->w, window->h, RGFW_formatRGB8);
		return true;
	}
	
	void DoneVideo() {
		RGFW_surface_free(surface);
		RGFW_window_close(window);
	}
	
	void drawPoint (u8 * scr, int x, int y, dword c) {
		scr[(y * 640 * 3 + x * 3    ) % (window->w * window->h * 3)] = c & 0xFF;
		scr[(y * 640 * 3 + x * 3 + 1) % (window->w * window->h * 3)] = (c >> 8) & 0xFF;
		scr[(y * 640 * 3 + x * 3 + 2) % (window->w * window->h * 3)] = (c >> 16) & 0xFF;
	}
	
	void drawPoint2x (u8 * scr, int x, int y, dword c) {
		drawPoint(scr, x    , y    , c);
		drawPoint(scr, x + 1, y    , c);
		drawPoint(scr, x    , y + 1, c);
		drawPoint(scr, x + 1, y + 1, c);
	}
	
	void UpdateScreen() {
		
		byte* data = (byte*)Handler()->VideoData();
		byte* data_ui = (byte*)Handler()->VideoDataUI();
		
		if (data_ui) {
			for (int y = 0; y < 240; ++y)
			{
				for (int x = 0; x < 320; ++x)
				{
					xUi::eRGBAColor c_ui = xUi::palette[*data_ui++];
					xUi::eRGBAColor c = color_cache.items_rgbx[*data++];
					dword pix = RGBX( 
						(c.r >> c_ui.a) + c_ui.r, 
						(c.g >> c_ui.a) + c_ui.g, 
						(c.b >> c_ui.a) + c_ui.b
					);
					
					drawPoint2x(vidBuffer, x * 2, y * 2, pix);
				}
			}
		}
		else {
			for (int y = 0; y < 240; ++y)
			{
				for (int x = 0; x < 320; ++x)
				{
					dword pix = color_cache.items[*data++];
					drawPoint2x(vidBuffer, x * 2, y * 2, pix);
				}
			}
		}
		
		RGFW_window_blitSurface(window, surface);
	}
	
	// === keys events ===
	
	static struct eOptionSpeed : public xOptions::eOptionInt {
		virtual const char* Name() const { return "speed"; }
		virtual const char** Values() const {
			static const char* values[] = { "1x", "2x", "3x", "4x", "5x", "6x", "7x", "8x", "9x", "10x", NULL };
			return values;
		}
		virtual void Change(bool next = true) {
			eOptionInt::Change(0, 10, next);
		}
		virtual int Order() const { return 69; }
	} op_speed;
	
	int OpSpeed() { return op_speed; }
	void OpSpeed(int v) { op_speed.Set(v); }
	
	static bool PreProcessKey (RGFW_event * e) {
		if (e->key.value) return false;
		switch (e->key.value) {
			case RGFW_F8:
				OpSpeed(e->type == RGFW_keyPressed ? 5 : 0);
				return true;
		}
		if (e->type != RGFW_keyReleased) return false;
		switch (e->key.value) {
			case RGFW_F2: {
				using namespace xOptions;
				eOptionB* o = eOptionB::Find("save state");
				SAFE_CALL(o)->Change();
			}
			return true;
			case RGFW_F3: {
				using namespace xOptions;
				eOptionB* o = eOptionB::Find("load state");
				SAFE_CALL(o)->Change();
			}
			return true;
			case RGFW_F5:
				Handler()->OnAction(A_TAPE_TOGGLE);
				return true;
			case RGFW_F7: {
				using namespace xOptions;
				eOptionB* o = eOptionB::Find("pause");
				SAFE_CALL(o)->Change();
			}
			return true;
			case RGFW_F12:
				Handler()->OnAction(A_RESET);
				return true;
			default: return false;
		}
	}
	
	static byte TranslateKey (RGFW_key _key, dword & _flags) {
		switch(_key) {
			case RGFW_backtick:
			case RGFW_escape:	return 'm';
			case RGFW_shiftL:	return 'c';
			case RGFW_shiftR:	return 'c';
			case RGFW_altL:		return 's';
			case RGFW_altR:		return 's';
			case RGFW_return:	return 'e';
			case RGFW_backSpace:
				_flags |= KF_SHIFT;
				return '0';
			case RGFW_apostrophe:
				_flags |= KF_ALT;
				if(_flags&KF_SHIFT)
				{
					_flags &= ~KF_SHIFT;
					return 'P';
				}
				else
					return '7';
			case RGFW_comma:
				_flags |= KF_ALT;
				if(_flags&KF_SHIFT)
				{
					_flags &= ~KF_SHIFT;
					return 'R';
				}
				else
					return 'N';
			case RGFW_period:
				_flags |= KF_ALT;
				if(_flags&KF_SHIFT)
				{
					_flags &= ~KF_SHIFT;
					return 'T';
				}
				else
					return 'M';
			case RGFW_semicolon:
				_flags |= KF_ALT;
				if(_flags&KF_SHIFT)
				{
					_flags &= ~KF_SHIFT;
					return 'Z';
				}
				else
					return 'O';
			case RGFW_slash:
				_flags |= KF_ALT;
				if(_flags&KF_SHIFT)
				{
					_flags &= ~KF_SHIFT;
					return 'C';
				}
				else
					return 'V';
			case RGFW_minus:
				_flags |= KF_ALT;
				if(_flags&KF_SHIFT)
				{
					_flags &= ~KF_SHIFT;
					return '0';
				}
				else return 'J';
			case RGFW_equals:
				_flags |= KF_ALT;
				if(_flags&KF_SHIFT)
				{
					_flags &= ~KF_SHIFT;
					return 'K';
				}
				else return 'L';
			case RGFW_tab:
				_flags |= KF_ALT;
				_flags |= KF_SHIFT;
				return 0;
			case RGFW_kp4: case RGFW_left:   return 'l';
			case RGFW_kp6: case RGFW_right:  return 'r';
			case RGFW_kp8: case RGFW_up:     return 'u';
			case RGFW_kp2: case RGFW_down:   return 'd';
			case RGFW_insert:
			case RGFW_controlR:
			case RGFW_controlL:	return 'f';
		}
		if(_key >= RGFW_0 && _key <= RGFW_9) return _key;
		if(_key >= RGFW_a && _key <= RGFW_z) return 'A' + _key - RGFW_a;
		if(_key == RGFW_space) return _key;
		return 0;
	}
	
	void ProcessKey (RGFW_event * e) {
		switch (e->type) {
			case RGFW_keyPressed: {
				if (!PreProcessKey(e)) {
					dword flags = KF_DOWN | OpJoyKeyFlags();
					if (e->key.mod & RGFW_modAlt) flags |= KF_ALT;
					if (e->key.mod & RGFW_modShift) flags |= KF_SHIFT;
					byte key = TranslateKey(e->key.value, flags);
					Handler()->OnKey(key, flags);
				}
			} break;
			case RGFW_keyReleased: {
				if(!PreProcessKey(e)) {
					dword flags = 0;
					if(e->key.mod&RGFW_modAlt)
						flags |= KF_ALT;
					if(e->key.mod&RGFW_modShift)
						flags |= KF_SHIFT;
					byte key = TranslateKey(e->key.value, flags);
					Handler()->OnKey(key, OpJoyKeyFlags());
				}
			} break;
		}
	}
	
	// === main ===
	
	bool InitAudio();
	void DoneAudio();
	void UpdateAudio();
	
	bool Init() {
		Handler()->OnInit();
		if (!InitVideo()) return false;
		if (!InitAudio()) return false;
		return true;
	}
	
	void Done() {
		DoneAudio();
		DoneVideo();
		Handler()->OnDone();
	}
	
	static bool quit = false;
	
	void Loop1() {
		RGFW_event event;
		while (RGFW_window_checkEvent(window, &event)) {
			switch(event.type) {
				case RGFW_quit:
					quit = true;
					break;
				case RGFW_keyPressed:
				case RGFW_keyReleased:
					ProcessKey(&event);
					break;
				case RGFW_dataDrop:
					Handler()->OnOpenFile(event.drop.files[0]);
					break;
			}
		}
		
		Handler()->OnLoop();
		UpdateScreen();
		UpdateAudio();
	}
	
	void Loop() {
		eTick last_tick;
		last_tick.SetCurrent();
		while (!quit) {
			for (int i = OpSpeed(); --i >= 0;) {
				Handler()->OnLoop();
			}
			Loop1();
			while (last_tick.Passed().Ms() < 15) {
				//Sleep(3); // maybe? or...
				RGFW_waitForEvent(3);
			}
			last_tick.SetCurrent();
			if(OpQuit()) quit = true;
		}
	}
	
} // namespace xPlatform

int main (int argc, char* argv[]) {
	
	if (!xPlatform::Init()) {
		xPlatform::Done();
		return 0;
	}
	
	if (argc > 1) xPlatform::Handler()->OnOpenFile(argv[1]);
	
	xPlatform::Loop();
	xPlatform::Done();
	return 0;
}

#endif // USE_RGFW

