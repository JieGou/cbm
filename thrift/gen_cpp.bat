@echo off

rem ����c++����
call gen_code.bat cpp

rd /s /q "..\RpcDao\gen-cpp\"
md "..\RpcDao\gen-cpp\"

rem ����ͨ��IDL���ɵ�cpp����
xcopy "gen-cpp" "..\RpcDao\gen-cpp\"  /c /e /y

rem ��ͣ
pause