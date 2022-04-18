
// MFCApplication11Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication11.h"
#include "MFCApplication11Dlg.h"
#include "afxdialogex.h"

#include "Accident.h"
#include "SubDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication11Dlg 대화 상자



CMFCApplication11Dlg::CMFCApplication11Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION11_DIALOG, pParent)
	, m_edit(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_radio = 0;
}

void CMFCApplication11Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_myUserList);
	DDX_Text(pDX, IDC_EDIT1, m_edit);
}

BEGIN_MESSAGE_MAP(CMFCApplication11Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication11Dlg::OnBnClickedButton2)
	
	ON_COMMAND(IDC_RADIO1, &CMFCApplication11Dlg::OnRadio1)
	ON_COMMAND(IDC_RADIO2, &CMFCApplication11Dlg::OnRadio2)

	
	
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMFCApplication11Dlg::OnItemchangedList1)
ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication11Dlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication11Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMFCApplication11Dlg 메시지 처리기

BOOL CMFCApplication11Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	m_myUserList.DeleteAllItems();
	

	m_myUserList.InsertColumn(0, _T("시도"), LVCFMT_CENTER, 100);
	m_myUserList.InsertColumn(1, _T("시군구"), LVCFMT_CENTER, 100);
	m_myUserList.InsertColumn(2, _T("횡단보도상"), LVCFMT_CENTER, 100);
	m_myUserList.InsertColumn(3, _T("횡단보도부근"), LVCFMT_CENTER, 100);
	m_myUserList.InsertColumn(4, _T("터널안"), LVCFMT_CENTER, 100);
	m_myUserList.InsertColumn(5, _T("교량위"), LVCFMT_CENTER, 100);
	m_myUserList.InsertColumn(6, _T("기타단일로"), LVCFMT_CENTER, 100);
	m_myUserList.InsertColumn(7, _T("교차로내"), LVCFMT_CENTER, 100);
	m_myUserList.InsertColumn(8, _T("교차로부근"), LVCFMT_CENTER, 100);
	m_myUserList.InsertColumn(9, _T("건널목"), LVCFMT_CENTER, 100);
	m_myUserList.InsertColumn(10, _T("기타불명"), LVCFMT_CENTER, 100);
	m_myUserList.InsertColumn(11, _T("고가도로위"), LVCFMT_CENTER, 100);
	m_myUserList.InsertColumn(12, _T("지하도로내"), LVCFMT_CENTER, 100);
	m_myUserList.SetExtendedStyle(m_myUserList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);




	ifstream  data("data.csv");
	string input;
	string input1;
	string line;
	string cell;
	Accident info[229];
	int count = 0;
	int sum[17][11] = { 0, };
	int total_sum = 0;
	int choice = 0;
	int adf = 0;


	LPCSTR Mystring = { 0 };
	int j = 0;
	while (std::getline(data, line)) // getline(stream, line) 
	{

		stringstream  lineStream(line); //한줄의 데이터를 가지고 사용
		string        cell;

		LPCSTR Mystring = cell.c_str();


		for (int i = 0; i < 13; i++)
		{
			std::getline(lineStream, cell, ',');
			if (i == 0)
			{
				info[j].sido = Mystring;
			}
			else if (i == 1)
			{
				info[j].sigoongu = Mystring;
			}
			else
			{

				info[j].cnt[i - 2] = Mystring;

			}
		}

		j++;

	}


	for (int j = 0; j < 229; j++)
	{
		adf = m_myUserList.InsertItem(0, info[j].sido);
		m_myUserList.SetItemText(adf, 1, info[j].sigoongu);
		for (int i = 0; i < 11; i++)
		{
			m_myUserList.SetItemText(adf, i + 2, info[j].cnt[i]);
		}


	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication11Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication11Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication11Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication11Dlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	

	ifstream  data("data.csv");
	string line;
	string cell;
	Accident info[229];
	int sum[11] = { 0, };
	int adf = 0;


	LPCSTR Mystring = { 0 };
	int j = 0;
	while (std::getline(data, line)) // getline(stream, line) 
	{

		stringstream  lineStream(line); //한줄의 데이터를 가지고 사용
		string        cell;

		LPCSTR Mystring = cell.c_str();


		for (int i = 0; i < 13; i++)
		{
			std::getline(lineStream, cell, ',');
			if (i == 0)
			{
				info[j].sido = Mystring;
			}
			else if (i == 1)
			{
				info[j].sigoongu = Mystring;
			}
			else
			{

				info[j].cnt[i - 2] = Mystring;

			}
		}

		j++;

	}

	if (m_radio == 1)
	{

		for (int j = 0; j < 229; j++)
		{
			if (info[j].sido == m_edit)
			{
				adf = m_myUserList.InsertItem(0, info[j].sido);
				m_myUserList.SetItemText(adf, 1, info[j].sigoongu);
				for (int i = 0; i < 11; i++)
				{
					m_myUserList.SetItemText(adf, i + 2, info[j].cnt[i]);
				}
			}


		}
		CSubDlg* Search = new CSubDlg();
		Search->SetMainPtr(this);
		Search->Create(IDD_DIALOG1, this);
		Search->ShowWindow(SW_SHOW);
		Search->SetTextBox(m_edit, m_radio);
	}
	else if (m_radio == 2)
	{
		for (int j = 0; j < 229; j++)
		{
			if (info[j].sigoongu == m_edit)
			{
				adf = m_myUserList.InsertItem(0, info[j].sido);
				m_myUserList.SetItemText(adf, 1, info[j].sigoongu);
				for (int i = 0; i < 11; i++)
				{
					m_myUserList.SetItemText(adf, i + 2, info[j].cnt[i]);
				}
			}


		}
		CSubDlg* Search = new CSubDlg();
		Search->SetMainPtr(this);
		Search->Create(IDD_DIALOG1, this);
		Search->ShowWindow(SW_SHOW);
		Search->SetTextBox(m_edit, m_radio);
	}
	else if (m_radio == 0)
	{
		AfxMessageBox(_T("1번 또는 2번을 선택해주세요."));
	}
	
	

	

	UpdateData(false);
}





void CMFCApplication11Dlg::OnRadio1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_radio = 1;
}


void CMFCApplication11Dlg::OnRadio2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_radio = 2;
}


void CMFCApplication11Dlg::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CMFCApplication11Dlg::OnBnClickedButton1() //통계 버튼
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(true);
	

	ifstream  data("data.csv");
	string line;
	string cell;
	Accident info[229];
	int sum[11] = { 0, };
	int adf = 0;


	LPCSTR Mystring = { 0 };
	int j = 0;
	while (std::getline(data, line)) // getline(stream, line) 
	{

		stringstream  lineStream(line); //한줄의 데이터를 가지고 사용
		string        cell;

		LPCSTR Mystring = cell.c_str();


		for (int i = 0; i < 13; i++)
		{
			std::getline(lineStream, cell, ',');
			if (i == 0)
			{
				info[j].sido = Mystring;
			}
			else if (i == 1)
			{
				info[j].sigoongu = Mystring;
			}
			else
			{

				info[j].cnt[i - 2] = Mystring;

			}
		}

		j++;

	}

	if (m_radio == 1)
	{

		for (int j = 0; j < 229; j++)
		{
			if (info[j].sido == m_edit)
			{
				adf = m_myUserList.InsertItem(0, info[j].sido);
				m_myUserList.SetItemText(adf, 1, info[j].sigoongu);
				for (int i = 0; i < 11; i++)
				{
					m_myUserList.SetItemText(adf, i + 2, info[j].cnt[i]);
				}
			}


		}
	}
	else if (m_radio == 2)
	{
		for (int j = 0; j < 229; j++)
		{
			if (info[j].sigoongu == m_edit)
			{
				adf = m_myUserList.InsertItem(0, info[j].sido);
				m_myUserList.SetItemText(adf, 1, info[j].sigoongu);
				for (int i = 0; i < 11; i++)
				{
					m_myUserList.SetItemText(adf, i + 2, info[j].cnt[i]);
				}
			}


		}
	}

	
	//m_myUserList.DeleteAllItems();
	
	CSubDlg* Search = new CSubDlg();
	Search->SetMainPtr(this);
	Search->Create(IDD_DIALOG1, this);
	Search->ShowWindow(SW_SHOW);
	Search->SetTextBox2(m_edit, m_radio);



	UpdateData(false);


}


void CMFCApplication11Dlg::OnBnClickedButton3() //종료 버튼
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();


}
