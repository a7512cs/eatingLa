#pragma once
#include "afxcmn.h"
#include "DlgBackDoor.h"
#include "DLGLadyStreet.h"
#include "DlgMember.h"

class RstFunction;
class CurrentState;


// CEatingLaDlg 對話方塊
class CEatingLaDlg : public CDialogEx
{
    // 建構
public:
    CEatingLaDlg(CWnd* pParent = NULL);	// 標準建構函式

    // 對話方塊資料
    enum { IDD = IDD_EATINGLA_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


    // 程式碼實作
protected:
    HICON m_hIcon;

    // 產生的訊息對應函式
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedExit();
    afx_msg void OnBnClickedEatingLa();//按下rand的按鈕



    afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
    CString RestaurantName;//顯示的TEXT

    RstFunction* pRstFunction;//共用函式的指標 和資料的指標
    RstFunction* GetRstFunPtr();
    CurrentState* pCurrentState;//記錄目前狀態 的指標
    CurrentState* GetCurStatePtr();
    void ShowAllRestaurantOnList();//將新的資料顯示再餐廳list上面
    int SwapTab();//按下Tab顯示切換 回傳按到第幾頁


    //顯示rand到的餐廳資訊到對話框上
    void ShowResultOnText(int RestaurantIndex, BOOL FinishR = FALSE);

    /*
    === Tab活頁夾結構 ===
    在main DLG上有tab control
    tab裡面要包新的DLG
    DLG再包 要顯示的東西 list etc...
    */
    CTabCtrl RestaurantTab;//main DLG 的 tab
    DlgBackDoor BackDoorPage;//後門的 Dlg
    DLGLadyStreet LadyStreetPage;//宵夜街的 Dlg
    DlgMember MemberPage;//吃的成員的 Dlg
};
