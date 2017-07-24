#pragma once
#include "afxcmn.h"
class RstFunction;
class CEatingLaDlg;

// DlgMember ��ܤ��

class DlgMember : public CDialogEx
{
    DECLARE_DYNAMIC(DlgMember)

public:
    DlgMember(CWnd* pParent = NULL);   // �зǫغc�禡
    virtual ~DlgMember();

    // ��ܤ�����
    enum { IDD = IDD_DLGMember };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

    DECLARE_MESSAGE_MAP()

    CEatingLaDlg* pEatDlgPtr;
    RstFunction* GetRstFunPtr();
public:
    void SetEatDlgPtr(CEatingLaDlg* dlgPtr);
    virtual BOOL OnInitDialog();


    CListCtrl MemberList;
    afx_msg void OnNMClickMemberlist(NMHDR *pNMHDR, LRESULT *pResult);
    void SwitchYesNo(int i); // ���i�� yes����no �A no����yes
    void ShowMemberOnList();//�N�����ܦAlist�W��
    BOOL GetHateRstList(CString StrPath, CString RData, int j, CString &StrName, int &IntWeight);

};
