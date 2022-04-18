#pragma once
#include "MFCApplication11Dlg.h"


// CSubDlg 대화 상자

class CSubDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSubDlg)

public:
	CSubDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSubDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	
	void SetTextBox(CString str, int m_radio);
	CListCtrl m_myUserList2;
	void SetMainPtr(CMFCApplication11Dlg* ptr);
	CMFCApplication11Dlg* pMain;
	virtual BOOL OnInitDialog();
	CString m_mystatic;
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	void SetTextBox2(CString str, int m_radio);
	afx_msg void OnBnClickedButton1();
};
