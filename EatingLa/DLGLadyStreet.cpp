// DLGLadyStreet.cpp : ��@��
//

#include "stdafx.h"
#include "EatingLa.h"
#include "DLGLadyStreet.h"
#include "afxdialogex.h"
#include "EatingLaDlg.h"
#include "RstFunction.h"
#include "CurrentState.h"


// DLGLadyStreet ��ܤ��

IMPLEMENT_DYNAMIC(DLGLadyStreet, CDialogEx)

DLGLadyStreet::DLGLadyStreet(CWnd* pParent /*=NULL*/)
    : CDialogEx(DLGLadyStreet::IDD, pParent)
{

}

DLGLadyStreet::~DLGLadyStreet()
{
}

void DLGLadyStreet::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LasyStreetLIST, LadyStreetList);
}

BEGIN_MESSAGE_MAP(DLGLadyStreet, CDialogEx)
    ON_NOTIFY(NM_CLICK, IDC_LasyStreetLIST, &DLGLadyStreet::OnNMClickLasystreetlist)
END_MESSAGE_MAP()


// DLGLadyStreet �T���B�z�`��

RstFunction* DLGLadyStreet::GetRstFunPtr()
{
    return pEatDlgPtr->pRstFunction;
}

void DLGLadyStreet::SetEatDlgPtr(CEatingLaDlg* dlgPtr)
{
    pEatDlgPtr = dlgPtr;
}

BOOL DLGLadyStreet::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    //�]�w���ҤW������r
    LadyStreetList.SetExtendedStyle(LadyStreetList.GetExtendedStyle() | LVS_EX_GRIDLINES);//LVS_EX_GRIDLINES��ܺ���
    LadyStreetList.InsertColumn(0, _T("Restaurant"), LVCFMT_LEFT, 100, -1);//���J���D�W��
    LadyStreetList.InsertColumn(1, _T("Weight"), LVCFMT_LEFT, 50, -1);
    LadyStreetList.InsertColumn(2, _T("Deny"), LVCFMT_LEFT, 40, -1);


    //Ū�JLadyStreetRst���
    CString StrPath = _T("");
    GetCurrentDirectoryW(MAX_PATH, StrPath.GetBuffer(MAX_PATH));
    StrPath.Format(_T("%s\\LadyStreetRst.ini"), StrPath);

    int i = GetRstFunPtr()->ReadRstIni(StrPath);
    TotalRestarantLadyStreet = i;


    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION:  OCX �ݩʭ����Ǧ^ FALSE
}




void DLGLadyStreet::OnNMClickLasystreetlist(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

    POSITION pp;
    pp = LadyStreetList.GetFirstSelectedItemPosition();//���o�ƹ����쪺��m

    int i = -1;
    if (pp != NULL)
    {
        i = LadyStreetList.GetNextSelectedItem(pp);//���o �ƹ����쪺��m �ഫ���ĴX��

        SwitchYesNo(i);//���i�� yes����no �A no����yes

        //���\�U�Q����
        //CurrentState��ini�n��אּ �i�Q�Y or ���i�Q�Y
        pEatDlgPtr->pCurrentState->AdjustRestaurant(GetRstFunPtr(), GetGlobalRstIndex(i));
    }
    

    *pResult = 0;
}

int DLGLadyStreet::GetGlobalRstIndex(int i)
{
    return i + pEatDlgPtr->BackDoorPage.TotalRestarantBackDoor;
}

int DLGLadyStreet::GetGlobalTotalRst()
{
    return pEatDlgPtr->BackDoorPage.TotalRestarantBackDoor + TotalRestarantLadyStreet;
}

void DLGLadyStreet::SwitchYesNo(int i)
{
    CString oo;
    CString tmp = LadyStreetList.GetItemText(i, 2);//���o �ĴX������r
    if (i >= 0 && i < (int)GetRstFunPtr()->AllRst.size())
    {
        if (!tmp.Compare(L"No"))//is no
        {
            oo = L"Yes";
            GetRstFunPtr()->AllRst[GetGlobalRstIndex(i)].CanEat = TRUE;
        }
        else
        {//is yes
            oo = L"No";
            GetRstFunPtr()->AllRst[GetGlobalRstIndex(i)].CanEat = FALSE;
        }
        LadyStreetList.SetItemText(i, 2, oo);
    }
}

void DLGLadyStreet::ShowRstOnList()
{
    for (int i = 0; i < TotalRestarantLadyStreet; i++)
    {
        int r = GetGlobalRstIndex(i);
        LadyStreetList.InsertItem(i, GetRstFunPtr()->AllRst[r].RstName);//���J�� �\�U�W��
        CString oo; oo.Format(_T("%.3lf"), GetRstFunPtr()->AllRst[r].RstWeight);//�v��
        LadyStreetList.SetItemText(i, 1, oo);

        if (GetRstFunPtr()->IsRstCanEat(r) == TRUE)
            oo = L"Yes";
        else
            oo = L"No";
        LadyStreetList.SetItemText(i, 2, oo);//�i�Q�Y
    }
}
