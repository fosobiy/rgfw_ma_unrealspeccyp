g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\file_type.cpp -c -o obj\speccy\file_type.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI -Isrc\3rdparty\minizip -Isrc\3rdparty\zlib src\file_type_zip.cpp -c -o obj\speccy\file_type_zip.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\options_common.cpp -c -o obj\speccy\options_common.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\speccy.cpp -c -o obj\speccy\speccy.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\speccy_handler.cpp -c -o obj\speccy\speccy_handler.o
::pause
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\devices\device.cpp -c -o obj\speccy\devices\device.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\devices\memory.cpp -c -o obj\speccy\devices\memory.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\devices\ula.cpp -c -o obj\speccy\devices\ula.o
::pause
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\devices\fdd\fdd.cpp -c -o obj\speccy\devices\fdd\fdd.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\devices\fdd\fdd_fdi.cpp -c -o obj\speccy\devices\fdd\fdd_fdi.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\devices\fdd\fdd_scl.cpp -c -o obj\speccy\devices\fdd\fdd_scl.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\devices\fdd\fdd_td0.cpp -c -o obj\speccy\devices\fdd\fdd_td0.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\devices\fdd\fdd_td0_lzh.cpp -c -o obj\speccy\devices\fdd\fdd_td0_lzh.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\devices\fdd\fdd_trd.cpp -c -o obj\speccy\devices\fdd\fdd_trd.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\devices\fdd\fdd_udi.cpp -c -o obj\speccy\devices\fdd\fdd_udi.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\devices\fdd\wd1793.cpp -c -o obj\speccy\devices\fdd\wd1793.o
::pause
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\devices\input\kempston_joy.cpp -c -o obj\speccy\devices\input\kempston_joy.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\devices\input\kempston_mouse.cpp -c -o obj\speccy\devices\input\kempston_mouse.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\devices\input\keyboard.cpp -c -o obj\speccy\devices\input\keyboard.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\devices\input\tape.cpp -c -o obj\speccy\devices\input\tape.o
::pause
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\devices\sound\ay.cpp -c -o obj\speccy\devices\sound\ay.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\devices\sound\beeper.cpp -c -o obj\speccy\devices\sound\beeper.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\devices\sound\device_sound.cpp -c -o obj\speccy\devices\sound\device_sound.o
::pause
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI -Isrc\3rdparty\zlib src\snapshot\rzx.cpp -c -o obj\speccy\snapshot\rzx.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI -Isrc\3rdparty\zlib -Isrc\3rdparty\libpng src\snapshot\screenshot.cpp -c -o obj\speccy\snapshot\screenshot.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\snapshot\snapshot.cpp -c -o obj\speccy\snapshot\snapshot.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI -Isrc\3rdparty\zlib src\snapshot\snapshot_szx.cpp -c -o obj\speccy\snapshot\snapshot_szx.o
::pause
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI -Isrc\3rdparty\minizip -Isrc\3rdparty\zlib src\tools\io_select_zip.cpp -c -o obj\speccy\tools\io_select_zip.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\tools\log.cpp -c -o obj\speccy\tools\log.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI -Isrc\3rdparty\tinyxml2 src\tools\options.cpp -c -o obj\speccy\tools\options.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\tools\profiler.cpp -c -o obj\speccy\tools\profiler.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\tools\sound_mixer.cpp -c -o obj\speccy\tools\sound_mixer.o
::pause
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\ui\ui.cpp -c -o obj\speccy\ui\ui.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\ui\ui_button.cpp -c -o obj\speccy\ui\ui_button.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\ui\ui_control.cpp -c -o obj\speccy\ui\ui_control.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\ui\ui_desktop.cpp -c -o obj\speccy\ui\ui_desktop.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\ui\ui_dialog.cpp -c -o obj\speccy\ui\ui_dialog.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\ui\ui_list.cpp -c -o obj\speccy\ui\ui_list.o
::pause
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\z80\z80.cpp -c -o obj\speccy\z80\z80.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\z80\z80_opcodes.cpp -c -o obj\speccy\z80\z80_opcodes.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\z80\z80_op_tables.cpp -c -o obj\speccy\z80\z80_op_tables.o
::pause
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\platform\custom_ui\ui_file_open.cpp -c -o obj\speccy\platform\custom_ui\ui_file_open.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\platform\custom_ui\ui_keyboard.cpp -c -o obj\speccy\platform\custom_ui\ui_keyboard.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\platform\custom_ui\ui_main.cpp -c -o obj\speccy\platform\custom_ui\ui_main.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\platform\custom_ui\ui_menu.cpp -c -o obj\speccy\platform\custom_ui\ui_menu.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\platform\custom_ui\ui_profiler.cpp -c -o obj\speccy\platform\custom_ui\ui_profiler.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\platform\custom_ui\ui_web_browse.cpp -c -o obj\speccy\platform\custom_ui\ui_web_browse.o
::pause
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\platform\io.cpp -c -o obj\speccy\platform\io.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\platform\platform.cpp -c -o obj\speccy\platform\platform.o
::pause
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\platform\gl\draw.cpp -c -o obj\speccy\platform\gl\draw.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\platform\gl\vsync.cpp -c -o obj\speccy\platform\gl\vsync.o
::pause
::g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI -DFREEGLUT_STATIC -Ilibs\freeglut\include src\platform\glut\main_glut.cpp -c -o obj\speccy\platform\glut\main_glut.o
::pause
::g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI -DAL_LIBTYPE_STATIC -Ilibs\openal\include\AL src\platform\oal\oal.cpp -c -o obj\speccy\platform\oal\oal.o
::pause
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI src\platform\win\io_select_win.cpp -c -o obj\speccy\platform\win\io_select_win.o
pause
