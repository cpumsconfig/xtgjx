@echo off

:menu
echo ============================
echo System Toolbox
echo ============================
echo 1. System Information
echo 2. Disk Cleanup
echo 3. Check Disk (CHKDSK)
echo 4. Task Manager
echo 5. Exit
echo ============================

set /p choice=Enter your choice:

if "%choice%"=="1" goto system_info
if "%choice%"=="2" goto disk_cleanup
if "%choice%"=="3" goto check_disk
if "%choice%"=="4" goto task_manager
if "%choice%"=="5" goto exit

echo Invalid choice. Please try again.
echo.
goto menu

:system_info
echo System Information:
systeminfo
echo.
pause
goto menu

:disk_cleanup
echo Running Disk Cleanup...
cleanmgr
echo.
pause
goto menu

:check_disk
echo Running Check Disk (CHKDSK)...
chkdsk
echo.
pause
goto menu

:task_manager
echo Opening Task Manager...
taskmgr
echo.
pause
goto menu

:exit
echo Exiting System Toolbox...
exit