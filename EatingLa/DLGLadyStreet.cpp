// DLGLadyStreet.cpp : 實作檔
//

#include "stdafx.h"
#include "EatingLa.h"
#include "DLGLadyStreet.h"
#include "afxdialogex.h"
#include "EatingLaDlg.h"
#include "RstFunction.h"
#include "CurrentState.h"


// DLGLadyStreet 對話方塊

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


// DLGLadyStreet 訊息處理常式

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

    //設定頁籤上面的文字
    LadyStreetList.SetExtendedStyle(LadyStreetList.GetExtendedStyle() | LVS_EX_GRIDLINES);//LVS_EX_GRIDLINES顯示網格
    LadyStreetList.InsertColumn(0, _T("Restaurant"), LVCFMT_LEFT, 100, -1);//插入標題名稱
    LadyStreetList.InsertColumn(1, _T("Weight"), LVCFMT_LEFT, 50, -1);
    LadyStreetList.InsertColumn(2, _T("Deny"), LVCFMT_LEFT, 40, -1);


    //讀入LadyStreetRst資料
    CString StrPath = _T("");
    GetCurrentDirectoryW(MAX_PATH, StrPath.GetBuffer(MAX_PATH));
    StrPath.Format(_T("%s\\LadyStreetRst.ini"), StrPath);

    int i = GetRstFunPtr()->ReadRstIni(StrPath);
    TotalRestarantLadyStreet = i;


    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION:  OCX 屬性頁應傳回 FALSE
}




void DLGLadyStreet::OnNMClickLasystreetlist(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

    POSITION pp;
    pp = LadyStreetList.GetFirstSelectedItemPosition();//取得滑鼠按到的位置

    int i = -1;
    if (pp != NULL)
    {
        i = LadyStreetList.GetNextSelectedItem(pp);//取得 滑鼠按到的位置 轉換成第幾項

        SwitchYesNo(i);//把第i項 yes換成no ， no換成yes

        //當餐廳被更改後
        //CurrentState的ini要更改為 可被吃 or 不可被吃
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
    CString tmp = LadyStreetList.GetItemText(i, 2);//取得 第幾項的文字
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
        LadyStreetList.InsertItem(i, GetRstFunPtr()->AllRst[r].RstName);//插入行 餐廳名稱
        CString oo; oo.Format(_T("%.3lf"), GetRstFunPtr()->AllRst[r].RstWeight);//權重
        LadyStreetList.SetItemText(i, 1, oo);

        if (GetRstFunPtr()->IsRstCanEat(r) == TRUE)
            oo = L"Yes";
        else
            oo = L"No";
        LadyStreetList.SetItemText(i, 2, oo);//可被吃
    }
}
