
// EatingLa.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CEatingLaApp: 
// �аѾ\��@�����O�� EatingLa.cpp
//

class CEatingLaApp : public CWinApp
{
public:
	CEatingLaApp();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CEatingLaApp theApp;