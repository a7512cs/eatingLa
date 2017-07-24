#pragma once
class RstFunction;

class CurrentState
{
public:
    CurrentState();
    ~CurrentState();
    CString StrPath;//CurrentState.ini 的路徑

    void GetIniPath();//取得CurrentState.ini 的路徑
    void LoadCurrentState(RstFunction* AllDataPtr);//讀取目前狀態
    void LoadMemberStat(RstFunction* AllDataPtr);//讀取 去的人員
    void LoadRstStat(RstFunction* AllDataPtr);//讀取 不吃的餐廳
    void AdjustMember(RstFunction* AllDataPtr, int i);//更動人不要去
    void AdjustRestaurant(RstFunction* AllDataPtr, int i);//更動不吃餐廳
private:

};
