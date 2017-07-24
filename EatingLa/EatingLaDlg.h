#pragma once
#include "afxcmn.h"
#include "DlgBackDoor.h"
#include "DLGLadyStreet.h"
#include "DlgMember.h"

class RstFunction;
class CurrentState;


// CEatingLaDlg ��ܤ��
class CEatingLaDlg : public CDialogEx
{
    // �غc
public:
    CEatingLaDlg(CWnd* pParent = NULL);	// �зǫغc�禡

    // ��ܤ�����
    enum { IDD = IDD_EATINGLA_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


    // �{���X��@
protected:
    HICON m_hIcon;

    // ���ͪ��T�������禡
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedExit();
    afx_msg void OnBnClickedEatingLa();//���Urand�����s



    afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
    CString RestaurantName;//��ܪ�TEXT

    RstFunction* pRstFunction;//�@�Ψ禡������ �M��ƪ�����
    RstFunction* GetRstFunPtr();
    CurrentState* pCurrentState;//�O���ثe���A ������
    CurrentState* GetCurStatePtr();
    void ShowAllRestaurantOnList();//�N�s�������ܦA�\�Ulist�W��
    int SwapTab();//���UTab��ܤ��� �^�ǫ���ĴX��


    //���rand�쪺�\�U��T���ܮؤW
    void ShowResultOnText(int RestaurantIndex, BOOL FinishR = FALSE);

    /*
    === Tab���������c ===
    �bmain DLG�W��tab control
    tab�̭��n�]�s��DLG
    DLG�A�] �n��ܪ��F�� list etc...
    */
    CTabCtrl RestaurantTab;//main DLG �� tab
    DlgBackDoor BackDoorPage;//����� Dlg
    DLGLadyStreet LadyStreetPage;//�d�]�� Dlg
    DlgMember MemberPage;//�Y�������� Dlg
};
