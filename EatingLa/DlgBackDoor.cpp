// DLGTemp.cpp : 實作檔
//

#include "stdafx.h"
#include "EatingLa.h"
#include "DlgBackDoor.h"
#include "afxdialogex.h"
#include "EatingLaDlg.h"
#include "RstFunction.h"
#include "CurrentState.h"


// DLGTemp 對話方塊

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


// DLGTemp 訊息處理常式



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

    //設定頁籤上面的文字
    BackDoorPageList.SetExtendedStyle(BackDoorPageList.GetExtendedStyle() | LVS_EX_GRIDLINES);//LVS_EX_GRIDLINES顯示網格
    BackDoorPageList.InsertColumn(0, _T("Restaurant"), LVCFMT_LEFT, 100, -1);//插入標題名稱
    BackDoorPageList.InsertColumn(1, _T("Weight"), LVCFMT_LEFT, 50, -1);
    BackDoorPageList.InsertColumn(2, _T("Deny"), LVCFMT_LEFT, 40, -1);


    //讀入BackDoorRst資料
    CString StrPath = _T("");
    GetCurrentDirectoryW(MAX_PATH, StrPath.GetBuffer(MAX_PATH));
    StrPath.Format(_T("%s\\BackDoorRst.ini"), StrPath);

    int i = GetRstFunPtr()->ReadRstIni(StrPath);
    TotalRestarantBackDoor = i;


    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION:  OCX 屬性頁應傳回 FALSE
}




void DlgBackDoor::OnNMClickBackdoorlist(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

    POSITION pp;
    pp = BackDoorPageList.GetFirstSelectedItemPosition();//取得滑鼠按到的位置

    int i = -1;
    if (pp != NULL)
    {
        i = BackDoorPageList.GetNextSelectedItem(pp);//取得 滑鼠按到的位置 轉換成第幾項

        SwitchYesNo(i);//把第i項 yes換成no ， no換成yes

        //當餐廳被更改後
        //CurrentState的ini要更改為 可被吃 or 不可被吃
        pEatDlgPtr->pCurrentState->AdjustRestaurant(GetRstFunPtr(), GetGlobalRstIndex(i));
    }


    *pResult = 0;



    ////////各種筆記//////////////////////////////////////////////////////////////////

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
    //         if (nFlag == 1)	//判斷是否為目錄	
    //         {
    //             //獲取完整的目錄信息
    //             CString csFoder = BackDoorPageList.GetItemText(nItem, 0);
    //             csFoder += "\\";
    //獲取目錄
    //             m_CurDir += csFoder;
    //             DisplayPath(m_CurDir);
    //        }
    //         else			//如果是文件，則打開文件
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
        BackDoorPageList.InsertItem(i, GetRstFunPtr()->AllRst[r].RstName);//插入行 餐廳名稱
        CString oo; oo.Format(_T("%.3lf"), GetRstFunPtr()->AllRst[r].RstWeight);//權重
        BackDoorPageList.SetItemText(i, 1, oo);

        if (GetRstFunPtr()->IsRstCanEat(r) == TRUE)
            oo = L"Yes";
        else
            oo = L"No";
        BackDoorPageList.SetItemText(i, 2, oo);//可被吃
    }
}
