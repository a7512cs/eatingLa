
// EatingLaDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "EatingLa.h"
#include "EatingLaDlg.h"
#include "afxdialogex.h"
#include "RstFunction.h"
#include "CurrentState.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEatingLaDlg 對話方塊



CEatingLaDlg::CEatingLaDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CEatingLaDlg::IDD, pParent)
    , RestaurantName(_T(""))
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEatingLaDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_RestaurantName, RestaurantName);
    DDX_Control(pDX, IDC_TAB1, RestaurantTab);
}

BEGIN_MESSAGE_MAP(CEatingLaDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDCANCEL, &CEatingLaDlg::OnBnClickedExit)
    ON_BN_CLICKED(IDC_BUTTON1, &CEatingLaDlg::OnBnClickedEatingLa)
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CEatingLaDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CEatingLaDlg 訊息處理常式

BOOL CEatingLaDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
    // 框架會自動從事此作業
    SetIcon(m_hIcon, TRUE);			// 設定大圖示
    SetIcon(m_hIcon, FALSE);		// 設定小圖示


    ////////////////////////////////////////// 設定每個對話框的共用資料指標//////////////////////
    pRstFunction = new RstFunction();
    pCurrentState = new CurrentState();
    BackDoorPage.SetEatDlgPtr(this);
    LadyStreetPage.SetEatDlgPtr(this);
    MemberPage.SetEatDlgPtr(this);
    //pCurrentState->SetEatDlgPtr(this);
    srand((unsigned)time(NULL));//亂數更亂數

    ////////////////////////////////////////// Tab活頁夾初始設定//////////////////////
    // 建立tab名稱
    RestaurantTab.InsertItem(0, _T("後門"));
    RestaurantTab.InsertItem(1, _T("宵夜街"));
    RestaurantTab.InsertItem(2, _T("人員GO"));



    /* ===== 程式流程步驟 =====
     * 讀取後門所有餐廳
     * 讀取宵夜街所有餐廳
     * 讀取人員
     * 讀取目前記錄狀態：不去的人、不喜歡吃的餐廳(weight)
     * 計算餐廳權重 並儲存
     * 顯示所有資料到list上
     */


    //建立頁籤內容的DLG
    BackDoorPage.Create(IDD_DLGBACKDOOR, GetDlgItem(IDC_TAB1));//initial後門餐廳
    LadyStreetPage.Create(IDD_DLGLADYSTREET, GetDlgItem(IDC_TAB1));//initial宵夜街餐廳
    MemberPage.Create(IDD_DLGMember, GetDlgItem(IDC_TAB1));//initial人員特性


    //讀取目前狀態的資料
    pCurrentState->LoadCurrentState(GetRstFunPtr());

    //統計每個餐廳的權重
    GetRstFunPtr()->CalculateRestaurantWeightFromMember();


    //將新的資料顯示再餐廳list上面
    ShowAllRestaurantOnList();


    //按下Tab顯示切換
    SwapTab();


    return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CEatingLaDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 繪製的裝置內容

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 將圖示置中於用戶端矩形
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 描繪圖示
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CEatingLaDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}



void CEatingLaDlg::OnBnClickedExit()
{
    // TODO:  在此加入控制項告知處理常式程式碼
    CDialogEx::OnCancel();
}


void CEatingLaDlg::OnBnClickedEatingLa()
{
    UpdateData(TRUE);


    if (GetRstFunPtr()->TotalRestaurants == 0)
        AfxMessageBox(_T("At least input a restaurant!!"));
    else
    {
        int RestaurantIndex = 0;
        for (int i = 0; i < 20; i++)
        {//先滾20次
            RestaurantIndex = rand() % GetRstFunPtr()->TotalRestaurants;
            ShowResultOnText(RestaurantIndex);
            UpdateData(FALSE);

            Sleep(70);
        }
        for (int i = 0; i < 5; i++)
        {//再滾5次
            RestaurantIndex = rand() % GetRstFunPtr()->TotalRestaurants;
            ShowResultOnText(RestaurantIndex);
            UpdateData(FALSE);

            Sleep(400);
        }

        int a = rand() % 4 + 1;
        for (int i = 0; i < a; i++)
        {//再滾隨機次 (最多4次) 
            RestaurantIndex = GetRstFunPtr()->GetARandomRestaurant();//取亂數 計算餐廳結果
            ShowResultOnText(RestaurantIndex);
            UpdateData(FALSE);

            Sleep(1000);
        }
        ShowResultOnText(RestaurantIndex, TRUE);


        ///////////////////////////////////////////////////讀圖片///////////////////////////////
        //m_BMP.SetBitmap((HBITMAP)m_BmpNew3[j]);
        ///////////////////////////////////////////////////讀圖片///////////////////////////////
    }
    UpdateData(FALSE);
}



void CEatingLaDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
    *pResult = 0;
    int tab = SwapTab();//切換頁面
}

RstFunction* CEatingLaDlg::GetRstFunPtr()
{
    return pRstFunction;
}

CurrentState* CEatingLaDlg::GetCurStatePtr()
{
    return pCurrentState;
}

void CEatingLaDlg::ShowAllRestaurantOnList()
{
    //顯示BackDoor餐廳
    BackDoorPage.ShowRstOnList();


    //顯示LadyStreet餐廳
    LadyStreetPage.ShowRstOnList();


    //顯示Member
    MemberPage.ShowMemberOnList();
}

int CEatingLaDlg::SwapTab()
{
    CRect rTab, rItem;
    RestaurantTab.GetItemRect(0, &rItem);
    RestaurantTab.GetClientRect(&rTab);
    int x = rItem.left;
    int y = rItem.bottom + 1;
    int cx = rTab.right - rItem.left - 3;
    int cy = rTab.bottom - y - 2;
    int tab = RestaurantTab.GetCurSel();

    BackDoorPage.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
    LadyStreetPage.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
    MemberPage.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);

    switch (tab)
    {
    case 0:
        BackDoorPage.SetWindowPos(NULL, x, y, cx, cy, SWP_SHOWWINDOW);
        break;
    case 1:
        LadyStreetPage.SetWindowPos(NULL, x, y, cx, cy, SWP_SHOWWINDOW);
        break;
    case 2:
        MemberPage.SetWindowPos(NULL, x, y, cx, cy, SWP_SHOWWINDOW);
        break;
    }

    return tab;
}


void CEatingLaDlg::ShowResultOnText(int RestaurantIndex, BOOL FinishR)
{
    CString FinalName;
    FinalName.Format(_T("第%d家%s權重數%.2lf")
        , RestaurantIndex + 1
        , GetRstFunPtr()->AllRst[RestaurantIndex].RstName
        , GetRstFunPtr()->AllRst[RestaurantIndex].RstWeight);

    if (FinishR == TRUE)
    {
        CString F = _T("You Get!!!");
        FinalName = F + FinalName;
    }
    RestaurantName = FinalName;
}
