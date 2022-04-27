@echo off
cl /Os /GS- include_windows.h /link /SUBSYSTEM:console /NODEFAULTLIB kernel32.lib
REM TODO
REM del main.obj
