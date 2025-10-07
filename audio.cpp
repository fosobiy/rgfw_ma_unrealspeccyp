/*
Portable ZX-Spectrum emulator.
Copyright (C) 2001-2013 SMT, Dexus, Alone Coder, deathsoft, djdron, scor

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

#include "src/platform/platform.h"

#ifdef USE_MINIAUDIO

#define MA_ENABLE_WINMM
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "src/options_common.h"
#include "src/tools/options.h"
#include "src/tools/sound_mixer.h"

namespace xPlatform {
	
	int OpSpeed();
	
	ma_device device;
	ma_mutex mtx;
	
	static eSoundMixer sound_mixer;
	
	int SampleRate = 44100;
	
	void AudioCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 len) {
		if ((dword)len * 2 * sizeof(short) <= sound_mixer.Ready()) {
			memcpy(pOutput, sound_mixer.Ptr(), len * 2 * sizeof(short));
			sound_mixer.Use(len * 2 * sizeof(short));
		}
		else {
			memcpy(pOutput, sound_mixer.Ptr(), sound_mixer.Ready());
			memset(
				(void *)(((char *)pOutput) + sound_mixer.Ready()), 
				0, 
				len * 2 * sizeof(short) - sound_mixer.Ready()
			);
			sound_mixer.Use(sound_mixer.Ready());
		}
	}
	
	bool InitAudio() {
		struct eOptionBX : public xOptions::eOptionB {
			void Unuse() { customizable = false; storeable = false; }
		};
		
		eOptionBX* o = (eOptionBX*)xOptions::eOptionB::Find("sound");
		SAFE_CALL(o)->Unuse();
		o = (eOptionBX*)xOptions::eOptionB::Find("volume");
		SAFE_CALL(o)->Unuse();
		
		ma_device_config deviceConfig;
		
		ma_mutex_init(&mtx);
		
		deviceConfig = ma_device_config_init(ma_device_type_playback);
		deviceConfig.playback.format   = ma_format_s16;
		deviceConfig.playback.channels = 2;
		deviceConfig.sampleRate        = SampleRate;
		deviceConfig.dataCallback      = AudioCallback;
		deviceConfig.pUserData         = 0;
		
		if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) return false;
		
		Handler()->AudioSetSampleRate(SampleRate);
		if (ma_device_start(&device) != MA_SUCCESS) {
			ma_device_uninit(&device);
			return false;
		}
		return true;
	}
	
	void DoneAudio() {
		ma_device_stop(&device);
		ma_device_uninit(&device);
		ma_mutex_uninit(&mtx);
	}
	
	void UpdateAudio() {
		sound_mixer.Update();
		static bool audio_filled = false;
		bool audio_filled_new = !OpSpeed() && sound_mixer.Ready() > (SampleRate * 2 * sizeof(short) / 50) * 7;
		// 7-frame data
		
		if(audio_filled != audio_filled_new) {
			audio_filled = audio_filled_new;
			Handler()->VideoPaused(audio_filled);
		}
	}
	
} // namespace xPlatform

#endif // USE_SDL2

