@echo off & pushd "%~dp0"

set "ProjectDir=%CD%"
set "TmpDir=%ProjectDir%\..\Compiled\Debug.win32"
set "OutDir=%ProjectDir%\..\Compiled"

if not exist "%TmpDir%" mkdir "%TmpDir%"
copy /y "%COCOS_FRAMEWORKS%\cocos2d-x-3.6\prebuilt\win32\*.lib" "%TmpDir%\"
copy /y "%COCOS_FRAMEWORKS%\cocos2d-x-3.6\prebuilt\win32\*.dll" "%OutDir%\"
xcopy "%ProjectDir%\..\Resources" "%OutDir%" /D /E /I /F /Y

exit /b 0

