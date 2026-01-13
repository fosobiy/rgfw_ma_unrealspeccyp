gcc src\3rdparty\zlib\adler32.c -c -o obj\zlib\adler32.o
gcc src\3rdparty\zlib\crc32.c -c -o obj\zlib\crc32.o
gcc src\3rdparty\zlib\deflate.c -c -o obj\zlib\deflate.o
gcc src\3rdparty\zlib\infback.c -c -o obj\zlib\infback.o
gcc src\3rdparty\zlib\inffast.c -c -o obj\zlib\inffast.o
gcc src\3rdparty\zlib\inflate.c -c -o obj\zlib\inflate.o
gcc src\3rdparty\zlib\inftrees.c -c -o obj\zlib\inftrees.o
gcc src\3rdparty\zlib\trees.c -c -o obj\zlib\trees.o
gcc src\3rdparty\zlib\uncompr.c -c -o obj\zlib\uncompr.o
gcc src\3rdparty\zlib\zutil.c -c -o obj\zlib\zutil.o
::pause
gcc -Isrc\3rdparty\zlib src\3rdparty\libpng\png.c -c -o obj\png\png.o
gcc -Isrc\3rdparty\zlib src\3rdparty\libpng\pngerror.c -c -o obj\png\pngerror.o
gcc -Isrc\3rdparty\zlib src\3rdparty\libpng\pngget.c -c -o obj\png\pngget.o
gcc -Isrc\3rdparty\zlib src\3rdparty\libpng\pngmem.c -c -o obj\png\pngmem.o
gcc -Isrc\3rdparty\zlib src\3rdparty\libpng\pngset.c -c -o obj\png\pngset.o
gcc -Isrc\3rdparty\zlib src\3rdparty\libpng\pngtrans.c -c -o obj\png\pngtrans.o
gcc -Isrc\3rdparty\zlib src\3rdparty\libpng\pngwio.c -c -o obj\png\pngwio.o
gcc -Isrc\3rdparty\zlib src\3rdparty\libpng\pngwrite.c -c -o obj\png\pngwrite.o
gcc -Isrc\3rdparty\zlib src\3rdparty\libpng\pngwtran.c -c -o obj\png\pngwtran.o
gcc -Isrc\3rdparty\zlib src\3rdparty\libpng\pngwutil.c -c -o obj\png\pngwutil.o
::pause
gcc -Isrc\3rdparty\zlib src\3rdparty\minizip\ioapi.c -c -o obj\mzip\ioapi.o
gcc -Isrc\3rdparty\zlib src\3rdparty\minizip\unzip.c -c -o obj\mzip\unzip.o
::pause
g++ src\3rdparty\tinyxml2\tinyxml2.cpp -c -o obj\xml\tinyxml2.o
pause
