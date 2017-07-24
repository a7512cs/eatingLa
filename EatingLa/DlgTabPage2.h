#pragma once


// CDlgTabPage2 對話方塊

class CDlgTabPage2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTabPage2)

public:
	CDlgTabPage2(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CDlgTabPage2();

// 對話方塊資料
	enum { IDD = IDD_EATINGLA_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
};
