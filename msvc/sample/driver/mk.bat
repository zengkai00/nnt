@echo OFF

cd ..\..\..\Classes\Core
build

cd ..\Kernel
build

cd ..\TL
build

cd ..\..\msvc\sample\driver
rem C:\WinDDK\7600.16385.1\tools\Chkinf\chkinf.bat driver.inf
build

copy driver.inf ..\..\..\exchange\ /Y
copy build\amd64\* ..\..\..\exchange\ /Y
copy x64\Release\*.exe ..\..\..\exchange\ /Y
copy x64\Release\*.dll ..\..\..\exchange\ /Y

cd ..\..\..\exchange
rem signtool sign /f ..\cert\root.pfx NntSampleDriver.sys
rem Inf2cat /driver:.\ /os:7_X64
rem signtool sign /f ..\cert\root.pfx driver.cat

cd ..\msvc\sample\driver