@echo off

rem ����py����
call gen_code.bat py

rd /s /q "..\python\flask\gen-py\"
rd /s /q "..\python\flask\thrift\"
md "..\python\flask\gen-py\"
md "..\python\flask\thrift\"

rem ����thrift��pyģ��
xcopy "..\ThirdParty\thrift\py\thrift"  "..\python\flask\thrift\"  /c /e /y
rem ����ͨ��IDL���ɵ�py����
xcopy "gen-py" "..\python\flask\gen-py\"  /c /e /y

rem ����sqlacodegen���ߣ���msyql���ݿ��ж�ȡ����Ϣ���Զ���������sqlalchemy��ʽ��py����
sqlacodegen mysql+pymysql://root:@localhost/cbm --outfile sql.py

rem ����sql.py
copy /y sql.py "..\python\flask\"
copy /y SQLServerHelper.py "..\python\flask\"
copy /y SQLClientHelper.py "..\python\flask\"

rem ��ͣ
pause