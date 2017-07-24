#pragma once
#include "afxcmn.h"

class RstFunction;
class CEatingLaDlg;

// DLGLadyStreet 對話方塊

class DLGLadyStreet : public CDialogEx
{
    DECLARE_DYNAMIC(DLGLadyStreet)

public:
    DLGLadyStreet(CWnd* pParent = NULL);   // 標準建構函式
    virtual ~DLGLadyStreet();

    // 對話方塊資料
    enum { IDD = IDD_DLGLADYSTREET };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

    DECLARE_MESSAGE_MAP()

    CEatingLaDlg* pEatDlgPtr;
    RstFunction* GetRstFunPtr();
public:
    void SetEatDlgPtr(CEatingLaDlg* dlgPtr);
    virtual BOOL OnInitDialog();


public:
    CListCtrl LadyStreetList;
    int TotalRestarantLadyStreet;//宵夜街的總餐廳數
    afx_msg void OnNMClickLasystreetlist(NMHDR *pNMHDR, LRESULT *pResult);//滑鼠按到表單項目時的動作
    int GetGlobalRstIndex(int i);//取得轉換成每頁的餐廳編號 在 總編號的第幾個
    int GetGlobalTotalRst();//取得轉換成在 總編號的總餐廳數
    void SwitchYesNo(int i); // 把第i項 yes換成no ， no換成yes
    void ShowRstOnList();//將資料顯示再餐廳list上面
};
