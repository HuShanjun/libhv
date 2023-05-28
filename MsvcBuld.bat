@echo off

rem Cleanup build directory
rem rmdir /s/q build & mkdir build & cd build &

rem Generate solution
if not exist build md build

cd build
cmake -G "Visual Studio 16 2019" ../

cd ..
rem build & install
rem cmake --build . --config Debug --target ALL_BUILD INSTALL
pause