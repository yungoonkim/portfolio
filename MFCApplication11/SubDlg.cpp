// SubDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication11.h"
#include "SubDlg.h"
#include "afxdialogex.h"
#include "Accident.h"

#include "MFCApplication11Dlg.h"

using namespace std;




IMPLEMENT_DYNAMIC(CSubDlg, CDialogEx)

CSubDlg::CSubDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_mystatic(_T(""))
{

}

CSubDlg::~CSubDlg()
{
}

void CSubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_myUserList2);
	DDX_Text(pDX, IDC_MYSTATIC, m_mystatic);
}


BEGIN_MESSAGE_MAP(CSubDlg, CDialogEx)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CSubDlg::OnItemchangedList1)
ON_BN_CLICKED(IDC_BUTTON1, &CSubDlg::OnBnClickedButton1)
END_MESSAGE_MAP()





void CSubDlg::SetTextBox(CString str, int m_radio)
{
	// TODO: 여기에 구현 코드 추가.
	UpdateData(true);
	m_mystatic = str;
	int radio = 0;

	radio = m_radio;
	
	ifstream  data("data.csv");
	string line;
	string cell;
	Accident info[229];
	int sum[17][11] = { 0, };
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
		if (radio == 1)
		{
			if (info[j].sido == m_mystatic)
			{
				adf = m_myUserList2.InsertItem(0, info[j].sido);
				m_myUserList2.SetItemText(adf, 1, info[j].sigoongu);
				for (int i = 0; i < 11; i++)
				{
					m_myUserList2.SetItemText(adf, i + 2, info[j].cnt[i]);
				}
			}
		}
		else if (radio == 2)
		{
			if (info[j].sigoongu == m_mystatic)
			{
				adf = m_myUserList2.InsertItem(0, info[j].sido);
				m_myUserList2.SetItemText(adf, 1, info[j].sigoongu);
				for (int i = 0; i < 11; i++)
				{
					m_myUserList2.SetItemText(adf, i + 2, info[j].cnt[i]);
				}
			}
		}


	}

	


	UpdateData(false);
}

void CSubDlg::SetMainPtr(CMFCApplication11Dlg* ptr)
{
	// TODO: 여기에 구현 코드 추가.
	pMain = ptr;
}


BOOL CSubDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_myUserList2.InsertColumn(0, _T("시도"), LVCFMT_CENTER, 100);
	m_myUserList2.InsertColumn(1, _T("시군구"), LVCFMT_CENTER, 100);
	m_myUserList2.InsertColumn(2, _T("횡단보도상"), LVCFMT_CENTER, 100);
	m_myUserList2.InsertColumn(3, _T("횡단보도부근"), LVCFMT_CENTER, 100);
	m_myUserList2.InsertColumn(4, _T("터널안"), LVCFMT_CENTER, 100);
	m_myUserList2.InsertColumn(5, _T("교량위"), LVCFMT_CENTER, 100);
	m_myUserList2.InsertColumn(6, _T("기타단일로"), LVCFMT_CENTER, 100);
	m_myUserList2.InsertColumn(7, _T("교차로내"), LVCFMT_CENTER, 100);
	m_myUserList2.InsertColumn(8, _T("교차로부근"), LVCFMT_CENTER, 100);
	m_myUserList2.InsertColumn(9, _T("건널목"), LVCFMT_CENTER, 100);
	m_myUserList2.InsertColumn(10, _T("기타불명"), LVCFMT_CENTER, 100);
	m_myUserList2.InsertColumn(11, _T("고가도로위"), LVCFMT_CENTER, 100);
	m_myUserList2.InsertColumn(12, _T("지하도로내"), LVCFMT_CENTER, 100);
	m_myUserList2.SetExtendedStyle(m_myUserList2.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	

	
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSubDlg::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CSubDlg::SetTextBox2(CString str, int m_radio)
{
	// TODO: 여기에 구현 코드 추가.

	UpdateData(true);
	m_mystatic = str;
	int radio = 0;
	radio = m_radio;
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
	for (int j = 0; j < 229; j++)
	{
		if (radio == 1)
		{
			if (info[j].sido == m_mystatic)
			{
				for (int i = 0; i < 11; i++)
				{
					sum[i] += _ttoi(info[j].cnt[i]);
				}
			}
		}
		else if (radio == 2)
		{
			if (info[j].sigoongu == m_mystatic)
			{
				for (int i = 0; i < 11; i++)
				{
					sum[i] += _ttoi(info[j].cnt[i]);
				}
			}
		}
	


	}
	adf = m_myUserList2.InsertItem(0, m_mystatic);
	m_myUserList2.SetItemText(adf, 1, L"통계");

	for (int i = 0; i < 11; i++)
	{
		CString str;
		str.Format(_T("%d"), sum[i]);
		m_myUserList2.SetItemText(adf, i + 2, str);
	}



	UpdateData(false);

}


void CSubDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
