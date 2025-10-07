g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI -DUSE_MINIAUDIO audio.cpp -c -o sdl2_audio.o
g++ -DUSE_UI -DUSE_RGFW -D_WINDOWS -D_WINAPI main.cpp -c -o sdl2_video.o
pause
