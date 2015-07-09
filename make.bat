@echo off
%NACL%/tools/make
IF %ERRORLEVEL% EQU 0 goto success

:fail
echo Make Failed... Exiting
pause
exit

:success
xcopy app.pexe ..\www\app.pexe /Y
xcopy app.bc ..\www\app.bc /Y
pause
