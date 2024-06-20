[IN PROGRESS]

I build with these steps (Windows 11 mingw64 from MSYS2):
- cd build
- cmake -S .. -B ../build -G "MinGW Makefiles"
- mingw32-make
- ../bin/craftmine.exe