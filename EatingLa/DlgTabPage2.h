#pragma once


// CDlgTabPage2 ��ܤ��

class CDlgTabPage2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTabPage2)

public:
	CDlgTabPage2(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CDlgTabPage2();

// ��ܤ�����
	enum { IDD = IDD_EATINGLA_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
};
