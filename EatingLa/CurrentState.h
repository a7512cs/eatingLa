#pragma once
class RstFunction;

class CurrentState
{
public:
    CurrentState();
    ~CurrentState();
    CString StrPath;//CurrentState.ini �����|

    void GetIniPath();//���oCurrentState.ini �����|
    void LoadCurrentState(RstFunction* AllDataPtr);//Ū���ثe���A
    void LoadMemberStat(RstFunction* AllDataPtr);//Ū�� �h���H��
    void LoadRstStat(RstFunction* AllDataPtr);//Ū�� ���Y���\�U
    void AdjustMember(RstFunction* AllDataPtr, int i);//��ʤH���n�h
    void AdjustRestaurant(RstFunction* AllDataPtr, int i);//��ʤ��Y�\�U
private:

};
