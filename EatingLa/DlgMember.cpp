// DlgMember.cpp : ��@��
//

#include "stdafx.h"
#include "EatingLa.h"
#include "DlgMember.h"
#include "afxdialogex.h"
#include "EatingLaDlg.h"
#include "RstFunction.h"
#include "CurrentState.h"


// DlgMember ��ܤ��

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


// DlgMember �T���B�z�`��


void DlgMember::SetEatDlgPtr(CEatingLaDlg* dlgPtr)
{
    pEatDlgPtr = dlgPtr;
}

BOOL DlgMember::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    //�]�w���ҤW������r
    MemberList.SetExtendedStyle(MemberList.GetExtendedStyle() | LVS_EX_GRIDLINES);//LVS_EX_GRIDLINES��ܺ���
    MemberList.InsertColumn(0, _T("Member"), LVCFMT_LEFT, 80, -1);//���J���D�W��
    MemberList.InsertColumn(1, _T("Go"), LVCFMT_LEFT, 40, -1);


    CString StrPath = _T("");
    GetCurrentDirectoryW(MAX_PATH, StrPath.GetBuffer(MAX_PATH));
    StrPath.Format(_T("%s\\Member.ini"), StrPath);


    CString RData = L"";
    CString StrTmp = _T("");


    //��ĴX����
    int i = 0;
    for (i = 0;; i++)
    {
        RData.Format(L"M%d", i);
        GetPrivateProfileString(RData, L"Name", L"Unknown",
            StrTmp.GetBuffer(MAX_PATH), MAX_PATH,//��H��Name���
            StrPath);

        if (StrTmp == L"Unknown")//�S�H����ƤF ��^
            break;

        Member *m = new Member();
        m->MemberName = StrTmp;//�x�s�H�����


        for (int j = 0;; j++)
        {
            //��Q���\�U���
            CString StrName = _T("");
            int IntWeight = 0;
            if (FALSE == GetHateRstList(StrPath, RData, j, StrName, IntWeight))
                break;


            if (IntWeight < -1)
            {//�p�G�줣���� �^�ǿ��~��m
                CString StrLog = _T("");
                StrLog.Format(_T("Your data type wrong!\npath:%s\n in the %s data"), StrPath, RData);
                AfxMessageBox(StrLog);
                IntWeight = 5;
            }
            if (IntWeight > 10 && IntWeight != 666)//����̤j�u���10
                IntWeight = 10;


            //�s�J�\�U���
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
    // EXCEPTION:  OCX �ݩʭ����Ǧ^ FALSE
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

        SwitchYesNo(i);//���i�� yes����no �A no����yes

        //���I�쪺�H ��-1���令 yes
        //�Y����L�H��-1 CalculateRestaurantWeightFromMember()�|�b�令no
        GetRstFunPtr()->RecoveryRstDenyInOneMember(i);


        /* �{���B�J
        ��H���Q����
        CurrentState��ini�n��אּ �h or ���h
        �H�����Q���\�U�v���n����
        ��s�\�Ulist
        */
        pEatDlgPtr->pCurrentState->AdjustMember(GetRstFunPtr(), i);
        GetRstFunPtr()->CalculateRestaurantWeightFromMember();

        //��slist
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
        MemberList.InsertItem(i, GetRstFunPtr()->MemberList[i]->MemberName);//���J��
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
    //��Q���\�U���
    StrTmp.Format(L"R%dName", j);
    GetPrivateProfileString(RData, StrTmp, L"NoMoreRst",
        StrName.GetBuffer(MAX_PATH), MAX_PATH,//��Q���\�U �W��
        StrPath);

    if (StrName == L"NoMoreRst")//�p�G�䧹�Q���\�U ��^
        return FALSE;

    StrTmp.Format(L"R%dWeight", j);
    IntWeight = GetPrivateProfileInt(RData, StrTmp, -2, StrPath);

    return TRUE;
}
