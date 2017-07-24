#include "stdafx.h"
#include "CurrentState.h"
#include "RstFunction.h"

CurrentState::CurrentState()
{
    StrPath = _T("");
    GetIniPath();
}

CurrentState::~CurrentState()
{
  
}

void CurrentState::GetIniPath()
{
    GetCurrentDirectoryW(MAX_PATH, StrPath.GetBuffer(MAX_PATH));
    StrPath.Format(_T("%s\\CurrentState.ini"), StrPath);
}

void CurrentState::LoadCurrentState(RstFunction* AllDataPtr)
{
    //讀取 去的人員
    LoadMemberStat(AllDataPtr);


    //讀取 不吃的餐廳
    LoadRstStat(AllDataPtr);
}

void CurrentState::LoadMemberStat(RstFunction* AllDataPtr)
{
    //load member data
    //check if he no go and record
    int mem = AllDataPtr->MemberList.size();
    for (int i = 0; i < mem; i++)
    {
        CString memName = AllDataPtr->MemberList[i]->MemberName;
        int Go = GetPrivateProfileInt(L"MemberGo", memName, -1, StrPath);

        if (Go == 1)
        {//yes
            AllDataPtr->MemberList[i]->IsGo = TRUE;//去
        }
        else if (Go == -1)
        {//-1
            AllDataPtr->MemberList[i]->IsGo = TRUE;//也把它設定 一起去吧
        }
        else
        {
            AllDataPtr->MemberList[i]->IsGo = FALSE;//不去
        }
    }
}

void CurrentState::LoadRstStat(RstFunction* AllDataPtr)
{
    //load R data
    //check if it no wanted  and record
    int rst = AllDataPtr->AllRst.size();
    for (int i = 0; i < rst; i++)
    {
        CString RName = AllDataPtr->AllRst[i].RstName;
        int Go = GetPrivateProfileInt(L"RestaurantGo", RName, -1, StrPath);

        if (Go == 1)
        {//yes
            AllDataPtr->AllRst[i].CanEat = TRUE;
        }
        else if (Go == -1)
        {//-1
            AllDataPtr->AllRst[i].CanEat = TRUE;
        }
        else
        {
            AllDataPtr->AllRst[i].CanEat = FALSE;
        }
    }
}

void CurrentState::AdjustMember(RstFunction* AllDataPtr, int i)
{
    CString memName = AllDataPtr->MemberList[i]->MemberName;

    CString MemGo;
    MemGo.Format(_T("%d"), AllDataPtr->MemberList[i]->IsGo);

    WritePrivateProfileString(L"MemberGo", memName, MemGo, StrPath);
}

void CurrentState::AdjustRestaurant(RstFunction* AllDataPtr, int i)
{
    CString StrName = AllDataPtr->AllRst[i].RstName;

    CString RstGo;
    RstGo.Format(_T("%d"), AllDataPtr->AllRst[i].CanEat);

    WritePrivateProfileString(L"RestaurantGo", StrName, RstGo, StrPath);
}
