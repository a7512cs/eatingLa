
// EatingLaDlg.cpp : ��@��
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


// CEatingLaDlg ��ܤ��



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


// CEatingLaDlg �T���B�z�`��

BOOL CEatingLaDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
    // �ج[�|�۰ʱq�Ʀ��@�~
    SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
    SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�


    ////////////////////////////////////////// �]�w�C�ӹ�ܮت��@�θ�ƫ���//////////////////////
    pRstFunction = new RstFunction();
    pCurrentState = new CurrentState();
    BackDoorPage.SetEatDlgPtr(this);
    LadyStreetPage.SetEatDlgPtr(this);
    MemberPage.SetEatDlgPtr(this);
    //pCurrentState->SetEatDlgPtr(this);
    srand((unsigned)time(NULL));//�üƧ�ü�

    ////////////////////////////////////////// Tab��������l�]�w//////////////////////
    // �إ�tab�W��
    RestaurantTab.InsertItem(0, _T("���"));
    RestaurantTab.InsertItem(1, _T("�d�]��"));
    RestaurantTab.InsertItem(2, _T("�H��GO"));



    /* ===== �{���y�{�B�J =====
     * Ū������Ҧ��\�U
     * Ū���d�]��Ҧ��\�U
     * Ū���H��
     * Ū���ثe�O�����A�G���h���H�B�����w�Y���\�U(weight)
     * �p���\�U�v�� ���x�s
     * ��ܩҦ���ƨ�list�W
     */


    //�إ߭��Ҥ��e��DLG
    BackDoorPage.Create(IDD_DLGBACKDOOR, GetDlgItem(IDC_TAB1));//initial����\�U
    LadyStreetPage.Create(IDD_DLGLADYSTREET, GetDlgItem(IDC_TAB1));//initial�d�]���\�U
    MemberPage.Create(IDD_DLGMember, GetDlgItem(IDC_TAB1));//initial�H���S��


    //Ū���ثe���A�����
    pCurrentState->LoadCurrentState(GetRstFunPtr());

    //�έp�C���\�U���v��
    GetRstFunPtr()->CalculateRestaurantWeightFromMember();


    //�N�s�������ܦA�\�Ulist�W��
    ShowAllRestaurantOnList();


    //���UTab��ܤ���
    SwapTab();


    return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CEatingLaDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // ø�s���˸m���e

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // �N�ϥܸm����Τ�ݯx��
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // �yø�ϥ�
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR CEatingLaDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}



void CEatingLaDlg::OnBnClickedExit()
{
    // TODO:  �b���[�J����i���B�z�`���{���X
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
        {//���u20��
            RestaurantIndex = rand() % GetRstFunPtr()->TotalRestaurants;
            ShowResultOnText(RestaurantIndex);
            UpdateData(FALSE);

            Sleep(70);
        }
        for (int i = 0; i < 5; i++)
        {//�A�u5��
            RestaurantIndex = rand() % GetRstFunPtr()->TotalRestaurants;
            ShowResultOnText(RestaurantIndex);
            UpdateData(FALSE);

            Sleep(400);
        }

        int a = rand() % 4 + 1;
        for (int i = 0; i < a; i++)
        {//�A�u�H���� (�̦h4��) 
            RestaurantIndex = GetRstFunPtr()->GetARandomRestaurant();//���ü� �p���\�U���G
            ShowResultOnText(RestaurantIndex);
            UpdateData(FALSE);

            Sleep(1000);
        }
        ShowResultOnText(RestaurantIndex, TRUE);


        ///////////////////////////////////////////////////Ū�Ϥ�///////////////////////////////
        //m_BMP.SetBitmap((HBITMAP)m_BmpNew3[j]);
        ///////////////////////////////////////////////////Ū�Ϥ�///////////////////////////////
    }
    UpdateData(FALSE);
}



void CEatingLaDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
    *pResult = 0;
    int tab = SwapTab();//��������
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
    //���BackDoor�\�U
    BackDoorPage.ShowRstOnList();


    //���LadyStreet�\�U
    LadyStreetPage.ShowRstOnList();


    //���Member
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
    FinalName.Format(_T("��%d�a%s�v����%.2lf")
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
