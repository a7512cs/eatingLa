#pragma once
#include "afxcmn.h"

class RstFunction;
class CEatingLaDlg;

// DLGLadyStreet ��ܤ��

class DLGLadyStreet : public CDialogEx
{
    DECLARE_DYNAMIC(DLGLadyStreet)

public:
    DLGLadyStreet(CWnd* pParent = NULL);   // �зǫغc�禡
    virtual ~DLGLadyStreet();

    // ��ܤ�����
    enum { IDD = IDD_DLGLADYSTREET };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

    DECLARE_MESSAGE_MAP()

    CEatingLaDlg* pEatDlgPtr;
    RstFunction* GetRstFunPtr();
public:
    void SetEatDlgPtr(CEatingLaDlg* dlgPtr);
    virtual BOOL OnInitDialog();


public:
    CListCtrl LadyStreetList;
    int TotalRestarantLadyStreet;//�d�]���`�\�U��
    afx_msg void OnNMClickLasystreetlist(NMHDR *pNMHDR, LRESULT *pResult);//�ƹ������涵�خɪ��ʧ@
    int GetGlobalRstIndex(int i);//���o�ഫ���C�����\�U�s�� �b �`�s�����ĴX��
    int GetGlobalTotalRst();//���o�ഫ���b �`�s�����`�\�U��
    void SwitchYesNo(int i); // ���i�� yes����no �A no����yes
    void ShowRstOnList();//�N�����ܦA�\�Ulist�W��
};
