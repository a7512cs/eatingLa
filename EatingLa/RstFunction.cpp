#include "stdafx.h"
#include "RstFunction.h"


HateRestaurant::HateRestaurant()
{
}

HateRestaurant::~HateRestaurant()
{
}

BOOL HateRestaurant::IsDeny()
{
    if (HatWeight == -1)
    {
        return TRUE;
    }
    return FALSE;
}

Member::Member()
{
    MemberName = _T("Unknown");
    IsGo = FALSE;
}

Member::~Member()
{
}

RestaurantData::RestaurantData()
{
    index = -1;
    RstName = _T("");
    RstWeight = 5;

    CanEat = TRUE;
}

RestaurantData::~RestaurantData()
{
}

//////////////////////////////////////////////////////////////////////////

RstFunction::RstFunction()
    : TotalRestaurants(0)
{
    LastRstIndex = -1;
}

RstFunction::~RstFunction()
{
}

int RstFunction::GetARandomRestaurant()
{
    double TotalWeightNum = 0.0;
    int TotalAccessedRst = 0;//�i���\�Q�Y���\�U�ƶq

    //���\�U���v�������[�i�h
    for (int i = 0; i < TotalRestaurants; i++)
    {
        if (IsRstCanEat(i) == TRUE)
        {
            TotalWeightNum += AllRst[i].RstWeight;
            TotalAccessedRst++;
        }
    }

    //�p�Grand�X�Ӫ��\�U�@�� ���N�b�]�@��
    int j = -1;
    do{
        j = CalculateRandRst(TotalWeightNum);
    } while (LastRstIndex == j && TotalAccessedRst > 1);

    LastRstIndex = j;
    return LastRstIndex;
}


int RstFunction::CalculateRandRst(double TotalWeightNum)
{
    double randnum;//�üƵ��G �ѪR��0.1
    int a, temp = (int)TotalWeightNum * 10;
    a = rand() % temp;
    randnum = a / 10.0;


    int j = 0;//�p��X�\�U�s���A j+1=�ĴX�a

    //�[�W�~�t ���F��0.699999999 �ܦ�0.7
    while (randnum + 0.0000001 >= AllRst[j].RstWeight || IsRstCanEat(j) == FALSE)
    {
        if (IsRstCanEat(j) == TRUE)
        {
            randnum = randnum - AllRst[j].RstWeight;
            if (j > TotalRestaurants)
                AfxMessageBox(_T("rand error!"));
        }
        j++;
    }
    return j;
}

int RstFunction::SearchRstIndex(CString StrName)
{
    for (int i = 0; i < (int)AllRst.size(); i++)
    {
        if (!AllRst[i].RstName.Compare(StrName))
        {
            return AllRst[i].index;
        }
    }
    return -1;
}

void RstFunction::CalculateRestaurantWeightFromMember()
{
    //�M���\�U�̪��v�����
    for (int r = 0; r < (int)AllRst.size(); r++)
    {
        AllRst[r].Hate_Weight.clear();
        AllRst[r].RstWeight = 5;
    }

    //�⦳�H�Q�����v���\�U �O�����`���AllRst
    int MList = (int)MemberList.size();
    for (int i = 0; i < MList; i++)
    {
        if (MemberList[i]->IsGo == TRUE)
        {
            int RSize = (int)MemberList[i]->HateRsts.size();
            for (int j = 0; j < RSize; j++)
            {
                int RN = MemberList[i]->HateRsts[j].index;
                for (int r = 0; r < (int)AllRst.size(); r++)
                {
                    if (RN == AllRst[r].index)
                    {
                        int HW = MemberList[i]->HateRsts[j].HatWeight;
                        if (HW == -1)
                            AllRst[r].CanEat = FALSE;
                        else
                            AllRst[r].Hate_Weight.push_back(HW);
                    }
                }
            }
        }
    }

    //�p��s���v�� ��s���`���AllRst
    for (int r = 0; r < (int)AllRst.size(); r++)
    {
        int HSize = (int)AllRst[r].Hate_Weight.size();
        if (HSize != 0)
        {
            double tmp = 0;
            for (int j = 0; j < HSize; j++)
            {
                tmp = tmp + AllRst[r].Hate_Weight[j];
            }
            AllRst[r].RstWeight = tmp / HSize;
        }
    }
}

void RstFunction::RecoveryRstDenyInOneMember(int i)
{
    //i = member
    int RSize = (int)MemberList[i]->HateRsts.size();
    for (int j = 0; j < RSize; j++)
    {
        if (MemberList[i]->HateRsts[j].IsDeny())
        {
            int RN = MemberList[i]->HateRsts[j].index;
            AllRst[RN].CanEat = TRUE;
        }
    }
}

BOOL RstFunction::IsRstCanEat(int i)
{
    if (AllRst[i].CanEat == TRUE)
        return TRUE;
    return FALSE;
}

int RstFunction::ReadRstIni(CString &StrPath)
{
    CString RSetName = L"";
    CString StrName = _T("");

    int i = 0;
    for (i = 0;; i++)
    {
        RSetName.Format(L"R%d", i);

        GetPrivateProfileString(RSetName, L"Name", L"DefaultName",
            StrName.GetBuffer(MAX_PATH), MAX_PATH,
            StrPath);

        if (StrName == L"DefaultName")
            break;


        //�s�J�\�U��ƨ�data
        RestaurantData RstTmp;
        RstTmp.index = TotalRestaurants + i;//�s�J�\�U�s��
        RstTmp.RstName = StrName; //�s�J�\�U�W��
        AllRst.push_back(RstTmp);
    }
    TotalRestaurants += i;//��s�`�\�U�ƶq

    return i;
}
