@echo off

REM Required variables
set ROOT=%~dp0..\..\
set ScriptsDir=%ROOT%\Scripts
set BuildDir=%ROOT%\Build
set ConanDir=%ROOT%\Conan
set ConanProfilesDir=%ConanDir%\Profiles

REM Conan setup
cd "%ConanDir%"
conan install . --output-folder=%BuildDir% --build=missing --profile:host=%ConanProfilesDir%\Windows\windows-release --profile:build=%ConanProfilesDir%\Windows\windows-release

REM CMake generation
cd "%ScriptsDir%"
python Automation.py --format_all --WIN64 --VS2022 --config release --gen_build

pause