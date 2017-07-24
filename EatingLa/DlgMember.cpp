// DlgMember.cpp : 實作檔
//

#include "stdafx.h"
#include "EatingLa.h"
#include "DlgMember.h"
#include "afxdialogex.h"
#include "EatingLaDlg.h"
#include "RstFunction.h"
#include "CurrentState.h"


// DlgMember 對話方塊

IMPLEMENT_DYNAMIC(DlgMember, CDialogEx)

DlgMember::DlgMember(CWnd* pParent /*=NULL*/)
: CDialogEx(DlgMember::IDD, pParent)
{

}

DlgMember::~DlgMember()
{
}

void DlgMember::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MemberList, MemberList);
}


RstFunction* DlgMember::GetRstFunPtr()
{
    return pEatDlgPtr->pRstFunction;
}

BEGIN_MESSAGE_MAP(DlgMember, CDialogEx)
    ON_NOTIFY(NM_CLICK, IDC_MemberList, &DlgMember::OnNMClickMemberlist)
END_MESSAGE_MAP()


// DlgMember 訊息處理常式


void DlgMember::SetEatDlgPtr(CEatingLaDlg* dlgPtr)
{
    pEatDlgPtr = dlgPtr;
}

BOOL DlgMember::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    //設定頁籤上面的文字
    MemberList.SetExtendedStyle(MemberList.GetExtendedStyle() | LVS_EX_GRIDLINES);//LVS_EX_GRIDLINES顯示網格
    MemberList.InsertColumn(0, _T("Member"), LVCFMT_LEFT, 80, -1);//插入標題名稱
    MemberList.InsertColumn(1, _T("Go"), LVCFMT_LEFT, 40, -1);


    CString StrPath = _T("");
    GetCurrentDirectoryW(MAX_PATH, StrPath.GetBuffer(MAX_PATH));
    StrPath.Format(_T("%s\\Member.ini"), StrPath);


    CString RData = L"";
    CString StrTmp = _T("");


    //抓第幾比資料
    int i = 0;
    for (i = 0;; i++)
    {
        RData.Format(L"M%d", i);
        GetPrivateProfileString(RData, L"Name", L"Unknown",
            StrTmp.GetBuffer(MAX_PATH), MAX_PATH,//抓人員Name資料
            StrPath);

        if (StrTmp == L"Unknown")//沒人員資料了 返回
            break;

        Member *m = new Member();
        m->MemberName = StrTmp;//儲存人員資料


        for (int j = 0;; j++)
        {
            //抓討厭餐廳資料
            CString StrName = _T("");
            int IntWeight = 0;
            if (FALSE == GetHateRstList(StrPath, RData, j, StrName, IntWeight))
                break;


            if (IntWeight < -1)
            {//如果抓不到資料 回傳錯誤位置
                CString StrLog = _T("");
                StrLog.Format(_T("Your data type wrong!\npath:%s\n in the %s data"), StrPath, RData);
                AfxMessageBox(StrLog);
                IntWeight = 5;
            }
            if (IntWeight > 10 && IntWeight != 666)//限制最大只能填10
                IntWeight = 10;


            //存入餐廳資料
            HateRestaurant HateRsts;
            int RstInd = GetRstFunPtr()->SearchRstIndex(StrName);
            if (RstInd == -1)
                continue;

            HateRsts.index = RstInd;
            HateRsts.HatWeight = IntWeight;
            m->HateRsts.push_back(HateRsts);
        }
        GetRstFunPtr()->MemberList.push_back(m);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION:  OCX 屬性頁應傳回 FALSE
}


void DlgMember::OnNMClickMemberlist(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

    POSITION pp;
    pp = MemberList.GetFirstSelectedItemPosition();

    int i = -1;
    if (pp != NULL)
    {
        i = MemberList.GetNextSelectedItem(pp);

        SwitchYesNo(i);//把第i項 yes換成no ， no換成yes

        //把點到的人 有-1的改成 yes
        //若有其他人有-1 CalculateRestaurantWeightFromMember()會在改成no
        GetRstFunPtr()->RecoveryRstDenyInOneMember(i);


        /* 程式步驟
        當人員被更改後
        CurrentState的ini要更改為 去 or 不去
        人員的討厭餐廳權重要重算
        刷新餐廳list
        */
        pEatDlgPtr->pCurrentState->AdjustMember(GetRstFunPtr(), i);
        GetRstFunPtr()->CalculateRestaurantWeightFromMember();

        //刷新list
        pEatDlgPtr->BackDoorPage.BackDoorPageList.DeleteAllItems();
        pEatDlgPtr->BackDoorPage.ShowRstOnList();

        pEatDlgPtr->LadyStreetPage.LadyStreetList.DeleteAllItems();
        pEatDlgPtr->LadyStreetPage.ShowRstOnList();
    }


    *pResult = 0;
}

void DlgMember::SwitchYesNo(int i)
{
    CString oo;
    CString tmp = MemberList.GetItemText(i, 1);
    if (i >= 0 && i < (int)GetRstFunPtr()->MemberList.size())
    {
        if (!tmp.Compare(L"No"))
        {
            oo = L"Yes";
            GetRstFunPtr()->MemberList[i]->IsGo = TRUE;
        }
        else
        {
            oo = L"No";
            GetRstFunPtr()->MemberList[i]->IsGo = FALSE;
        }
        MemberList.SetItemText(i, 1, oo);
    }
}

void DlgMember::ShowMemberOnList()
{
    for (int i = 0; i < (int)GetRstFunPtr()->MemberList.size(); i++)
    {
        MemberList.InsertItem(i, GetRstFunPtr()->MemberList[i]->MemberName);//插入行
        CString oo;
        if (GetRstFunPtr()->MemberList[i]->IsGo == TRUE)
            oo = L"Yes";
        else
            oo = L"No";
        MemberList.SetItemText(i, 1, oo);
    }//f2
}

BOOL DlgMember::GetHateRstList(CString StrPath, CString RData, int j, CString &StrName, int &IntWeight)
{
    CString StrTmp = _T("");
    //抓討厭餐廳資料
    StrTmp.Format(L"R%dName", j);
    GetPrivateProfileString(RData, StrTmp, L"NoMoreRst",
        StrName.GetBuffer(MAX_PATH), MAX_PATH,//抓討厭餐廳 名稱
        StrPath);

    if (StrName == L"NoMoreRst")//如果找完討厭餐廳 返回
        return FALSE;

    StrTmp.Format(L"R%dWeight", j);
    IntWeight = GetPrivateProfileInt(RData, StrTmp, -2, StrPath);

    return TRUE;
}
