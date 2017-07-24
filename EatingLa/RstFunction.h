#pragma once
#include "stdafx.h"
#include <vector>

class HateRestaurant
{
public:
    HateRestaurant();
    ~HateRestaurant();
    int index;
    int HatWeight;//權重
    BOOL IsDeny();
private:

};

class Member
{
public:
    Member();
    ~Member();
    CString MemberName;//人員名稱
    BOOL IsGo;//是否要一起去吃
    std::vector<HateRestaurant> HateRsts;//討厭的餐廳
private:

};


class RestaurantData
{
public:
    RestaurantData();
    ~RestaurantData();
    int index;
    CString RstName;//名稱
    double RstWeight;//權重

    BOOL CanEat;// 是否被能去吃 (拒絕訪問)
    std::vector<double> Hate_Weight;//儲存有人討厭的權重資料
private:

};

class RstFunction
{
public:
    RstFunction();
    ~RstFunction();
    int TotalRestaurants;//全部餐廳數
    int LastRstIndex;//上次rand的餐廳結果
    std::vector<RestaurantData> AllRst; //全部餐廳   
    std::vector<Member*> MemberList;//全部要吃的人員


    int GetARandomRestaurant();//取得亂數的餐廳
    int CalculateRandRst(double TotalWeightNum);//計算亂數 回傳餐廳index
    int SearchRstIndex(CString StrName);//找相同相同餐廳名稱 回傳index
    void CalculateRestaurantWeightFromMember();//統計每個餐廳的權重
    void RecoveryRstDenyInOneMember(int i);

    BOOL IsRstCanEat(int i);//判斷此餐廳是否能吃
    int ReadRstIni(CString &StrPath);//讀取StrPath路經的餐廳檔案 並回傳共讀到幾個餐廳
private:

};


