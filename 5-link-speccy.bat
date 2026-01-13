g++ ^
	obj\zlib\*.o ^
	obj\png\*.o ^
	obj\mzip\*.o ^
	obj\xml\*.o ^
	obj\speccy\*.o ^
	obj\speccy\devices\*.o ^
	obj\speccy\devices\fdd\*.o ^
	obj\speccy\devices\input\*.o ^
	obj\speccy\devices\sound\*.o ^
	obj\speccy\snapshot\*.o ^
	obj\speccy\tools\*.o ^
	obj\speccy\ui\*.o ^
	obj\speccy\z80\*.o ^
	obj\speccy\platform\*.o ^
	obj\speccy\platform\custom_ui\*.o ^
	obj\speccy\platform\win\*.o ^
	*.o ^
	-Lobj\libs ^
	-lgdi32 -lopengl32 -lwinmm -lole32 -luuid ^
	-o speccy.exe

pause