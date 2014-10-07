@rem build static library
@echo off
call "%VS120COMNTOOLS%\..\..\VC\bin\vcvars32.bat"
nmake.exe /F Makefile
pause