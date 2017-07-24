// DLGTemp.cpp : ��@��
//

#include "stdafx.h"
#include "EatingLa.h"
#include "DlgBackDoor.h"
#include "afxdialogex.h"
#include "EatingLaDlg.h"
#include "RstFunction.h"
#include "CurrentState.h"


// DLGTemp ��ܤ��

IMPLEMENT_DYNAMIC(DlgBackDoor, CDialogEx)

DlgBackDoor::DlgBackDoor(CWnd* pParent /*=NULL*/)
    : CDialogEx(DlgBackDoor::IDD, pParent)
{
}

DlgBackDoor::~DlgBackDoor()
{
}

void DlgBackDoor::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BackDoorLIST, BackDoorPageList);
}

BEGIN_MESSAGE_MAP(DlgBackDoor, CDialogEx)
    ON_NOTIFY(NM_CLICK, IDC_BackDoorLIST, &DlgBackDoor::OnNMClickBackdoorlist)
END_MESSAGE_MAP()


// DLGTemp �T���B�z�`��



RstFunction* DlgBackDoor::GetRstFunPtr()
{
    return pEatDlgPtr->pRstFunction;
}

void DlgBackDoor::SetEatDlgPtr(CEatingLaDlg* dlgPtr)
{
    pEatDlgPtr = dlgPtr;
}

BOOL DlgBackDoor::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    //�]�w���ҤW������r
    BackDoorPageList.SetExtendedStyle(BackDoorPageList.GetExtendedStyle() | LVS_EX_GRIDLINES);//LVS_EX_GRIDLINES��ܺ���
    BackDoorPageList.InsertColumn(0, _T("Restaurant"), LVCFMT_LEFT, 100, -1);//���J���D�W��
    BackDoorPageList.InsertColumn(1, _T("Weight"), LVCFMT_LEFT, 50, -1);
    BackDoorPageList.InsertColumn(2, _T("Deny"), LVCFMT_LEFT, 40, -1);


    //Ū�JBackDoorRst���
    CString StrPath = _T("");
    GetCurrentDirectoryW(MAX_PATH, StrPath.GetBuffer(MAX_PATH));
    StrPath.Format(_T("%s\\BackDoorRst.ini"), StrPath);

    int i = GetRstFunPtr()->ReadRstIni(StrPath);
    TotalRestarantBackDoor = i;


    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION:  OCX �ݩʭ����Ǧ^ FALSE
}




void DlgBackDoor::OnNMClickBackdoorlist(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

    POSITION pp;
    pp = BackDoorPageList.GetFirstSelectedItemPosition();//���o�ƹ����쪺��m

    int i = -1;
    if (pp != NULL)
    {
        i = BackDoorPageList.GetNextSelectedItem(pp);//���o �ƹ����쪺��m �ഫ���ĴX��

        SwitchYesNo(i);//���i�� yes����no �A no����yes

        //���\�U�Q����
        //CurrentState��ini�n��אּ �i�Q�Y or ���i�Q�Y
        pEatDlgPtr->pCurrentState->AdjustRestaurant(GetRstFunPtr(), GetGlobalRstIndex(i));
    }


    *pResult = 0;



    ////////�U�ص��O//////////////////////////////////////////////////////////////////

    //int nItem = GetItemCount();
    //CItemData* pItem = (CItemData*)(CListCtrl::
    //     int nItem = 0;
    //     BackDoorPageList.GetItemData(nItem);
    // return pItem->m_dwData;
    //     {
    //         NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    //         int nColumn = pNMListView->iSubItem;
    //         Sort(nColumn, nColumn == m_nSortColumn ? !m_bAscend : TRUE);
    //         *pResult = 0;
    //     }
    //     POSITION pp1;
    //     pp1 = BackDoorPageList.GetFirstSelectedItemPosition();
    // nItem = BackDoorPageList.GetpoPosition();
    //SetItemText(i, 1, oo);
    //     CString csFoder = BackDoorPageList.GetItemText(nItem, 0);
    //     if (nItem != -1)
    //     {
    // 
    //         int nFlag = BackDoorPageList.GetItemData(nItem);
    //         if (nFlag == 1)	//�P�_�O�_���ؿ�	
    //         {
    //             //������㪺�ؿ��H��
    //             CString csFoder = BackDoorPageList.GetItemText(nItem, 0);
    //             csFoder += "\\";
    //����ؿ�
    //             m_CurDir += csFoder;
    //             DisplayPath(m_CurDir);
    //        }
    //         else			//�p�G�O���A�h���}���
    //         {
    //             CString csFileName = m_CurDir + BackDoorPageList.GetItemText(nItem, 0);
    //             ShellExecute(NULL, "open", csFileName, 0, 0, SW_SHOWNORMAL);
    //         }
    //     }
    //     *pResult = 0;


    //_AFXCMN_INLINE POSITION CListCtrl::GetFirstSelectedItemPosition() const{ ... }

    //     CString csLabel = _T("");
    // 
    //     csLabel = BackDoorPageList.GetItemText(i, 0);

    //return csLabel;

}

int DlgBackDoor::GetGlobalRstIndex(int i)
{
    return i;
}

int DlgBackDoor::GetGlobalTotalRst()
{
    return TotalRestarantBackDoor;
}

void DlgBackDoor::SwitchYesNo(int i)
{
    CString oo;
    CString tmp = BackDoorPageList.GetItemText(i, 2);
    if (i >= 0 && i < (int)GetRstFunPtr()->AllRst.size())
    {
        if (!tmp.Compare(L"No"))
        {
            oo = L"Yes";
            GetRstFunPtr()->AllRst[GetGlobalRstIndex(i)].CanEat = TRUE;
        }
        else
        {
            oo = L"No";
            GetRstFunPtr()->AllRst[GetGlobalRstIndex(i)].CanEat = FALSE;
        }
        BackDoorPageList.SetItemText(i, 2, oo);
    }
}

void DlgBackDoor::ShowRstOnList()
{
    for (int i = 0; i < TotalRestarantBackDoor; i++)
    {
        int r = GetGlobalRstIndex(i);
        BackDoorPageList.InsertItem(i, GetRstFunPtr()->AllRst[r].RstName);//���J�� �\�U�W��
        CString oo; oo.Format(_T("%.3lf"), GetRstFunPtr()->AllRst[r].RstWeight);//�v��
        BackDoorPageList.SetItemText(i, 1, oo);

        if (GetRstFunPtr()->IsRstCanEat(r) == TRUE)
            oo = L"Yes";
        else
            oo = L"No";
        BackDoorPageList.SetItemText(i, 2, oo);//�i�Q�Y
    }
}
