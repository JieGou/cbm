#pragma once

#include "aced.h"

/*
 * ���ڴ���LinkedGEͼԪ�ıպ�����
 * ���磬�����ִ���ƶ��������ƶ���
 * �������ԭʼλ�õ����ӵ�պ�
 * �Լ������������λ�õ����ӵ�պ�
 */
class LinkedGEEditorReactor : public AcEditorReactor {

protected:
	bool mbAutoInitAndRelease ;

public:
	LinkedGEEditorReactor (const bool autoInitAndRelease =true) ;
	virtual ~LinkedGEEditorReactor () ;

	virtual void Attach () ;
	virtual void Detach () ;
	virtual AcEditor *Subject () const ;
	virtual bool IsAttached () const ;

	// ������ִ�н����������ӵ�պ�
	virtual void commandEnded(const ACHAR * cmdStr);
} ;
