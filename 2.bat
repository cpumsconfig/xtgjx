@echo off

:menu
echo ============================
echo 系统工具箱
echo ============================
echo 1. 系统信息
echo 2. 清理磁盘
echo 3. 检查磁盘 (CHKDSK)
echo 4. 任务管理器
echo 5. 退出
echo 6. 修复系统
echo 7. 重装系统（第三方）
echo 8. 签名
echo 9. 创建用户
echo 10. 更新软件
echo ============================

set /p choice=请输入你的选择：

if "%choice%"=="1" goto system_info
if "%choice%"=="2" goto disk_cleanup
if "%choice%"=="3" goto check_disk
if "%choice%"=="4" goto task_manager
if "%choice%"=="5" goto exit
if "%choice%"=="6" goto repair_system
if "%choice%"=="7" goto rts
if "%choice%"=="8" goto signature
if "%choice%"=="9" goto user_1
if "%choice%"=="10" goto update

echo 无效的选择，请重新尝试。
echo.
goto menu

:system_info
echo 系统信息：
systeminfo
echo.
pause
goto menu

:disk_cleanup
echo 正在运行磁盘清理...
cleanmgr
echo.
pause
goto menu

:check_disk
echo 正在运行磁盘检查 (CHKDSK)...
chkdsk
echo.
pause
goto menu

:task_manager
echo 打开任务管理器...
taskmgr
echo.
pause
goto menu

:exit
echo 退出系统工具箱...
exit

:repair_system
Dism /online /cleanup-image /restorehealth
SFC /scannow
pause
goto menu

:rts
start data/rts/CmzPrep.exe
goto menu

:signature
set /p n=请设置证书中创建者的名称：
data/signature/makecert.exe -sv 证书.pvk -r -n "CN=%n%" 证书.cer
:: 创建 X.509 证书
data/signature/certmgr.exe -add -c 证书.cer -s -r localMachine root
data/signature/cert2spc.exe 证书.cer 证书.spc
:: 创建发行者证书
set /p p=请输入你刚才设置的密码：
data/signature/pvk2pfx.exe -pvk 证书.pvk -pi %p% -spc 证书.spc -pfx 证书.pfx -f
 :: 提取 pfx 证书
set /p e=请输入你要签名的可执行文件名称：
data/signature/signtool.exe sign /f 证书.pfx /p %p% "%e%"
:: 签名
data/signature/signtool.exe timestamp /t http://timestamp.wosign.com/timestamp "%e%"
:: 加盖时间戳（可选）
pause
goto menu
:user_1
start bin/user/user.bat add
goto menu
:update
start dt/update.exe
goto menu
