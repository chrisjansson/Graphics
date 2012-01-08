::cmake.exe -G "NMake Makefiles" -D CMAKE_BUILD_TYPE=Debug -D BUILD_SHARED_LIBS=FALSE -D STATIC_STD_LIBS=FALSE -D CMAKE_INSTALL_PREFIX="%CD%/../../SFML_INSTALL" %CD%/../
::nmake install

::cmake.exe -G "NMake Makefiles" -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=FALSE -D STATIC_STD_LIBS=FALSE -D CMAKE_INSTALL_PREFIX="%CD%/../../SFML_INSTALL" %CD%/../
::nmake install

cd SFML2

::Set environment variables
set vsPath=C:\Program Files (x86)\Microsoft Visual Studio 10.0
call "%vsPath%\VC\vcvarsall.bat"

rmdir /s /q build
mkdir build
cd build

set arg=Debug
call :build %arg%
set arg=Release
call :build %arg%
pause
goto :EOF

:build
cmake.exe -G "NMake Makefiles" -D CMAKE_BUILD_TYPE=%1 -D BUILD_SHARED_LIBS=FALSE -D STATIC_STD_LIBS=FALSE -D CMAKE_INSTALL_PREFIX="%CD%/../../SFML_INSTALL" %CD%/../
nmake install
goto :EOF