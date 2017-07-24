#pragma once
#include "afxcmn.h"
class RstFunction;
class CEatingLaDlg;

// DlgMember 對話方塊

class DlgMember : public CDialogEx
{
    DECLARE_DYNAMIC(DlgMember)

public:
    DlgMember(CWnd* pParent = NULL);   // 標準建構函式
    virtual ~DlgMember();

    // 對話方塊資料
    enum { IDD = IDD_DLGMember };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

    DECLARE_MESSAGE_MAP()

    CEatingLaDlg* pEatDlgPtr;
    RstFunction* GetRstFunPtr();
public:
    void SetEatDlgPtr(CEatingLaDlg* dlgPtr);
    virtual BOOL OnInitDialog();


    CListCtrl MemberList;
    afx_msg void OnNMClickMemberlist(NMHDR *pNMHDR, LRESULT *pResult);
    void SwitchYesNo(int i); // 把第i項 yes換成no ， no換成yes
    void ShowMemberOnList();//將資料顯示再list上面
    BOOL GetHateRstList(CString StrPath, CString RData, int j, CString &StrName, int &IntWeight);

};
