@echo off

rem ����php�ķ������Ҫ��server
call gen_code.bat php:server

rem ����php�ͻ��˴���
rem call gen_code.bat php

rem ����php����
xcopy "gen-php" "..\php\gen-php\"  /c /e /y

rem ��ͣ
pause