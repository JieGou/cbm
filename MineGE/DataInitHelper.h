#pragma once

#include "dlimexp.h"

/*
 * �ֶμ����ݳ�ʼ��������
 * ���ļ��ж�ȡ�ֶκ�����
 */
class MINEGE_DLLIMPEXP DataInitHelper
{
public:
	static void InitDataField(const CString& fileName);
	static void InitDataFieldWithMoreInfo(const CString& fileName);

	static void InitStrList(const CString& fileName);
	static void InitIntStrList(const CString& fileName);
	static void InitDataObjectList(const CString& fileName);
	static void InitSingleDataObject(const CString& fileName);
};
