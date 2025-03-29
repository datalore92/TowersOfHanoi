@echo off
if not exist "build" mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
cd ..
echo Build complete! Run hanoi.exe from the build directory.
pause
