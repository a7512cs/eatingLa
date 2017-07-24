#pragma once
#include "afxcmn.h"

class RstFunction;
class CEatingLaDlg;

// DLGTemp ��ܤ��

class DlgBackDoor : public CDialogEx
{
    DECLARE_DYNAMIC(DlgBackDoor)

public:
    DlgBackDoor(CWnd* pParent = NULL);   // �зǫغc�禡
    virtual ~DlgBackDoor();

    // ��ܤ�����
    enum { IDD = IDD_DLGBACKDOOR };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

    DECLARE_MESSAGE_MAP()

    CEatingLaDlg* pEatDlgPtr;
    RstFunction* GetRstFunPtr();
public:
    void SetEatDlgPtr(CEatingLaDlg* dlgPtr);
    virtual BOOL OnInitDialog();


public:
    CListCtrl BackDoorPageList;
    int TotalRestarantBackDoor;//BackDoor���`�\�U��
    afx_msg void OnNMClickBackdoorlist(NMHDR *pNMHDR, LRESULT *pResult);//�ƹ������涵�خɪ��ʧ@
    int GetGlobalRstIndex(int i);//���o�ഫ���C�����\�U�s�� �b �`�s�����ĴX��
    int GetGlobalTotalRst();//���o�ഫ���b �`�s�����`�\�U��
    void SwitchYesNo(int i); // ���i�� yes����no �A no����yes
    void ShowRstOnList();//�N�����ܦA�\�Ulist�W��
};
