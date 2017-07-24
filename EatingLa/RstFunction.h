#pragma once
#include "stdafx.h"
#include <vector>

class HateRestaurant
{
public:
    HateRestaurant();
    ~HateRestaurant();
    int index;
    int HatWeight;//�v��
    BOOL IsDeny();
private:

};

class Member
{
public:
    Member();
    ~Member();
    CString MemberName;//�H���W��
    BOOL IsGo;//�O�_�n�@�_�h�Y
    std::vector<HateRestaurant> HateRsts;//�Q�����\�U
private:

};


class RestaurantData
{
public:
    RestaurantData();
    ~RestaurantData();
    int index;
    CString RstName;//�W��
    double RstWeight;//�v��

    BOOL CanEat;// �O�_�Q��h�Y (�ڵ��X��)
    std::vector<double> Hate_Weight;//�x�s���H�Q�����v�����
private:

};

class RstFunction
{
public:
    RstFunction();
    ~RstFunction();
    int TotalRestaurants;//�����\�U��
    int LastRstIndex;//�W��rand���\�U���G
    std::vector<RestaurantData> AllRst; //�����\�U   
    std::vector<Member*> MemberList;//�����n�Y���H��


    int GetARandomRestaurant();//���o�üƪ��\�U
    int CalculateRandRst(double TotalWeightNum);//�p��ü� �^���\�Uindex
    int SearchRstIndex(CString StrName);//��ۦP�ۦP�\�U�W�� �^��index
    void CalculateRestaurantWeightFromMember();//�έp�C���\�U���v��
    void RecoveryRstDenyInOneMember(int i);

    BOOL IsRstCanEat(int i);//�P�_���\�U�O�_��Y
    int ReadRstIni(CString &StrPath);//Ū��StrPath���g���\�U�ɮ� �æ^�Ǧ@Ū��X���\�U
private:

};


