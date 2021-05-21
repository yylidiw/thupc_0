:loop
rand_mkdt.exe
std.exe > my_std.out
fla.exe > bf.out
fc my_std.out bf.out
if %errorlevel% ==0 goto loop
pause
