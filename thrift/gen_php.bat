@echo off

rem thrift -gen php:server Hello.thrift  ����php�ķ������Ҫ��server
thrift.exe -r --gen php:server msis.thrift
rem����php�ͻ��˴���
rem thrift.exe -r --gen php msis.thrift
