
// MFCSerialCommDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include "SerialCom.h"	//추가 MrKang.

// CMFCSerialCommDlg dialog
class CMFCSerialCommDlg : public CDialogEx
{
// Construction
public:
	CMFCSerialCommDlg(CWnd* pParent = NULL);	// standard constructor

	/* 추가 부분  MrKang*/
	CSerialComm* m_comm;
	LRESULT		OnThreadClosed(WPARAM length, LPARAM lpara);
	
	
	/* 추가 부분 끝 MrKang*/

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSERIALCOMM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	/*MrKang 추가*/
	BOOL comport_state;

	CComboBox m_combo_comport_list;
	CString m_str_comport;
	CComboBox m_combo_baudrate_list;
	CString m_combo_baudrate;

	afx_msg void OnBnClickedBtConnect();
	afx_msg void OnCbnSelchangeComboComport();
	afx_msg void OnCbnSelchangeComboBaudrate();


	CImage m_image;
	CBrush m_brush;
	int m_Answer;
	CString m_ID;
	CListBox m_listbox;
	int m_myStatic;
	int m_Step;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedStartbtn();
	CStatic m_Picture;
	afx_msg void OnBnClickedInputbtn();
	afx_msg void OnBnClickedNewbtn();
	afx_msg void OnBnClickedRegbtn();
	afx_msg void OnBnClickedDelbtn();
	afx_msg void OnStnClickedMystatic();
	afx_msg void OnBnClickedButton6();
	
	CImage m_image2;

	
};
