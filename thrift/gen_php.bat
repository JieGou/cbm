@echo off

rem ����php�ķ������Ҫ��server
call gen_code.bat php:server

rem ����php�ͻ��˴���
rem call gen_code.bat php

rem ����thrift��phpģ��
xcopy "..\ThirdParty\thrift\php\Thrift"  "..\php\cbm\thrift\"  /c /e /y
rem ����ͨ��IDL���ɵ�php����
xcopy "gen-php" "..\php\gen-php\"  /c /e /y

rem ��ͣ
pause