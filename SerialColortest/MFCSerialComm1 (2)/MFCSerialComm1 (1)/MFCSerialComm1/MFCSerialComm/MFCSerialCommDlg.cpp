
// MFCSerialCommDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSerialComm.h"
#include "MFCSerialCommDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int count = 1;
int state = 0;
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CMFCSerialCommDlg dialog



CMFCSerialCommDlg::CMFCSerialCommDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCSERIALCOMM_DIALOG, pParent)
	, m_str_comport(_T(""))
	, m_combo_baudrate(_T(""))
	, m_Answer(0)
	, m_ID(_T(""))
	, m_myStatic(0)
	, m_Step(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CMFCSerialCommDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COMPORT, m_combo_comport_list);
	DDX_CBString(pDX, IDC_COMBO_COMPORT, m_str_comport);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_combo_baudrate_list);
	DDX_CBString(pDX, IDC_COMBO_BAUDRATE, m_combo_baudrate);
	//  DDX_Control(pDX, IDC_EDIT_RCV_VIEW, m_edit_rcv_view);
	//  DDX_Control(pDX, IDC_EDIT_SEND_DATA, m_edit_send_data);
	DDX_Text(pDX, IDC_EDIT1, m_Answer);
	DDX_Text(pDX, IDC_EDIT2, m_ID);
	DDX_Control(pDX, IDC_LIST1, m_listbox);
	DDX_Text(pDX, IDC_MYSTATIC, m_myStatic);
	DDX_Text(pDX, IDC_MYSTATIC2, m_Step);
	DDX_Control(pDX, IDC_MY_PICTURE, m_Picture);
	
}

BEGIN_MESSAGE_MAP(CMFCSerialCommDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BT_CONNECT, &CMFCSerialCommDlg::OnBnClickedBtConnect)
	ON_CBN_SELCHANGE(IDC_COMBO_COMPORT, &CMFCSerialCommDlg::OnCbnSelchangeComboComport)
	ON_CBN_SELCHANGE(IDC_COMBO_BAUDRATE, &CMFCSerialCommDlg::OnCbnSelchangeComboBaudrate)
	


	/*MRKang 추가*/
	ON_MESSAGE(WM_MYCLOSE, &CMFCSerialCommDlg::OnThreadClosed)
	
	/*MRKang 추가 끝*/
	
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_STARTBTN, &CMFCSerialCommDlg::OnBnClickedStartbtn)
	ON_BN_CLICKED(IDC_INPUTBTN, &CMFCSerialCommDlg::OnBnClickedInputbtn)
	ON_BN_CLICKED(IDC_NEWBTN, &CMFCSerialCommDlg::OnBnClickedNewbtn)
	ON_BN_CLICKED(IDC_REGBTN, &CMFCSerialCommDlg::OnBnClickedRegbtn)
	ON_BN_CLICKED(IDC_DELBTN, &CMFCSerialCommDlg::OnBnClickedDelbtn)
	ON_STN_CLICKED(IDC_MYSTATIC, &CMFCSerialCommDlg::OnStnClickedMystatic)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCSerialCommDlg::OnBnClickedButton6)
	
END_MESSAGE_MAP()


// CMFCSerialCommDlg message handlers

BOOL CMFCSerialCommDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_combo_comport_list.AddString(_T("COM1"));
	m_combo_comport_list.AddString(_T("COM2"));
	m_combo_comport_list.AddString(_T("COM3"));
	m_combo_comport_list.AddString(_T("COM4"));
	m_combo_comport_list.AddString(_T("COM5"));
	m_combo_comport_list.AddString(_T("COM6"));
	m_combo_comport_list.AddString(_T("COM7"));
	m_combo_comport_list.AddString(_T("COM8"));
	m_combo_comport_list.AddString(_T("COM9"));
	m_combo_comport_list.AddString(_T("COM10"));

	m_combo_baudrate_list.AddString(_T("9600"));
	m_combo_baudrate_list.AddString(_T("19200"));
	m_combo_baudrate_list.AddString(_T("115200"));


	comport_state = false;
	GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("OPEN"));
	m_str_comport = _T("COM2");
	m_combo_baudrate = _T("115200");
	UpdateData(FALSE);
	
	m_brush.CreateSolidBrush(RGB(0, 0, 0));
	
	//if (m_image2.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
	//	m_image2.Load(L"eyes2.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
	//	((CStatic*)GetDlgItem(IDC_MY_PICTURE2))->SetBitmap(m_image2);
	//	GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
	//}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCSerialCommDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCSerialCommDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCSerialCommDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/* 추가 부분  MrKang*/
LRESULT	CMFCSerialCommDlg::OnThreadClosed(WPARAM length, LPARAM lpara)
{
	((CSerialComm*)lpara)->HandleClose();
	delete ((CSerialComm*)lpara);

	return 0;
}

/* 추가 부분 끝  MrKang*/


// 버튼 이벤트 추가
void CMFCSerialCommDlg::OnBnClickedBtConnect()
{
	// TODO: Add your control notification handler code here
	if (comport_state)
	{
		if (m_comm)        //컴포트가존재하면
		{
			m_comm->Close();
			m_comm = NULL;
			AfxMessageBox(_T("COM 포트닫힘"));
			comport_state = false;
			GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("OPEN"));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
		}
	}
	else
	{
		m_comm = new CSerialComm(_T("\\\\.\\") + m_str_comport, m_combo_baudrate, _T("None"), _T("8 Bit"), _T("1 Bit"));         // initial Comm port
		if (m_comm->Create(GetSafeHwnd()) != 0) //통신포트를열고윈도우의핸들을넘긴다.
		{
			AfxMessageBox(_T("COM 포트열림"));
			comport_state = true;
			GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("CLOSE"));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
		}
		else
		{
			AfxMessageBox(_T("ERROR!"));
		}

	}
}


void CMFCSerialCommDlg::OnCbnSelchangeComboComport()
{
	// TODO: Add your control notification handler code here
	UpdateData(); /* 추가 부분  MrKang*/
}


void CMFCSerialCommDlg::OnCbnSelchangeComboBaudrate()
{
	// TODO: Add your control notification handler code here
	UpdateData(); /* 추가 부분  MrKang*/
}

HBRUSH CMFCSerialCommDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	if (nCtlColor == CTLCOLOR_LISTBOX)
	{
		if (pWnd->GetDlgCtrlID() == IDC_LIST1)
		{
			pDC->SetTextColor(RGB(255, 255, 0));
			//pDC->SetBkColor(RGB(255, 255, 0));



			return m_brush;
		}
	}

	//
	//HBRUSH hbr =  NULL;
	//if (pWnd->m_hWnd == this->m_hWnd) hbr = HBRUSH(m_brush);
	//// 나머지 들은 기본 색상을유지한다.
	//else hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	//


	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CMFCSerialCommDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CMFCSerialCommDlg::OnBnClickedStartbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);



	if (count == 1)
	{
		if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
			m_image.Load(L"colortest1.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
			((CStatic*)GetDlgItem(IDC_MY_PICTURE))->SetBitmap(m_image);
			count++;
			m_Step = 1;
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
		}
		else
		{
			m_image.Detach();

		}
	}
	else if (count == 2)
	{
		if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
			m_image.Load(L"colortest2.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
			((CStatic*)GetDlgItem(IDC_MY_PICTURE))->SetBitmap(m_image);
			count++;
			m_Step = 2;
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
		}
		else
		{
			m_image.Detach();

		}
	}
	else if (count == 3)
	{
		if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
			m_image.Load(L"colortest3.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
			((CStatic*)GetDlgItem(IDC_MY_PICTURE))->SetBitmap(m_image);
			count++;
			m_Step = 3;
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
		}
		else
		{
			m_image.Detach();

		}
	}
	else if (count == 4)
	{
		if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
			m_image.Load(L"colortest4.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
			((CStatic*)GetDlgItem(IDC_MY_PICTURE))->SetBitmap(m_image);
			count++;
			m_Step = 4;
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
		}
		else
		{
			m_image.Destroy();


		}
	}
	else if (count == 5)
	{
		if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
			m_image.Load(L"colortest5.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
			((CStatic*)GetDlgItem(IDC_MY_PICTURE))->SetBitmap(m_image);
			count++;
			m_Step = 5;
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
		}
		else
		{
			m_image.Destroy();


		}
	}
	else if (count == 6)
	{
		if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
			m_image.Load(L"colortest6.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
			((CStatic*)GetDlgItem(IDC_MY_PICTURE))->SetBitmap(m_image);
			count++;
			m_Step = 6;
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
		}
		else
		{
			m_image.Destroy();


		}
	}
	else if (count == 7)
	{
		if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
			m_image.Load(L"colortest7.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
			((CStatic*)GetDlgItem(IDC_MY_PICTURE))->SetBitmap(m_image);
			count++;
			m_Step = 7;
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
		}
		else
		{
			m_image.Destroy();


		}
	}

	else if (count == 8)
	{
		if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
			m_image.Load(L"colortest8.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
			((CStatic*)GetDlgItem(IDC_MY_PICTURE))->SetBitmap(m_image);
			count++;
			m_Step = 8;
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
		}
		else
		{
			m_image.Destroy();


		}
	}
	else if (count == 9)
	{
		if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
			m_image.Load(L"colortest9.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
			((CStatic*)GetDlgItem(IDC_MY_PICTURE))->SetBitmap(m_image);
			count++;
			m_Step = 9;
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
		}
		else
		{
			m_image.Destroy();


		}
	}
	else if (count == 10)
	{
		if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
			m_image.Load(L"colortest10.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
			((CStatic*)GetDlgItem(IDC_MY_PICTURE))->SetBitmap(m_image);
			count++;
			m_Step = 10;
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
		}
		else
		{
			m_image.Destroy();


		}
	}
	else if (count == 11)
	{
		if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
			m_image.Load(L"colortest11.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
			((CStatic*)GetDlgItem(IDC_MY_PICTURE))->SetBitmap(m_image);
			count++;
			m_Step = 11;
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
		}
		else
		{
			m_image.Destroy();


		}
	}
	else if (count == 12)
	{
		if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
			m_image.Load(L"colortest12.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
			((CStatic*)GetDlgItem(IDC_MY_PICTURE))->SetBitmap(m_image);
			count++;
			m_Step = 12;
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
		}
		else
		{
			m_image.Destroy();


		}

	}
	else if (count == 13)
	{
		if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
			m_image.Load(L"colortest13.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
			((CStatic*)GetDlgItem(IDC_MY_PICTURE))->SetBitmap(m_image);
			count++;
			m_Step = 13;
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
		}
		else
		{
			m_image.Destroy();


		}
	}
	else if (count == 14)
	{
		if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
			m_image.Load(L"colortest14.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
			((CStatic*)GetDlgItem(IDC_MY_PICTURE))->SetBitmap(m_image);
			count++;
			m_Step = 14;
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
		}
		else
		{
			m_image.Destroy();


		}
	}
	else if (count == 15)
	{
		if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
			m_image.Load(L"colortest15.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
			((CStatic*)GetDlgItem(IDC_MY_PICTURE))->SetBitmap(m_image);
			count++;
			m_Step = 15;
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
		}
		else
		{
			m_image.Destroy();


		}
	}
	else if (count == 16)
	{
		if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
			m_image.Load(L"colortest16.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
			((CStatic*)GetDlgItem(IDC_MY_PICTURE))->SetBitmap(m_image);
			count++;
			m_Step = 16;
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
		}
		else
		{
			m_image.Destroy();


		}
	}
	else if (count == 17)
	{
		if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
			m_image.Load(L"colortest17.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
			((CStatic*)GetDlgItem(IDC_MY_PICTURE))->SetBitmap(m_image);
			count++;
			m_Step = 17;
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
		}
		else
		{
			m_image.Destroy();


		}
	}
	else if (count == 18)
	{
		if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
			m_image.Load(L"colortest18.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
			((CStatic*)GetDlgItem(IDC_MY_PICTURE))->SetBitmap(m_image);
			count++;
			m_Step = 18;
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
		}
		else
		{
			m_image.Destroy();


		}
	}
	else if (count == 19)
	{
		if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
			m_image.Load(L"colortest19.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
			((CStatic*)GetDlgItem(IDC_MY_PICTURE))->SetBitmap(m_image);
			count++;
			m_Step = 19;
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);
		}
		else
		{
			m_image.Destroy();


		}
	}
	else if (count == 20)
	{
		if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
			m_image.Load(L"colortest20.bmp"); // 파일을 읽어서 비트맵 객체를 구성한다.
			((CStatic*)GetDlgItem(IDC_MY_PICTURE))->SetBitmap(m_image);
			count++;
			m_Step = 20;
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(true);

		}
		else
		{
			m_image.Destroy();


		}
	}
	UpdateData(false);


}
void CMFCSerialCommDlg::OnBnClickedInputbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);


	if (count == 2)
	{
		if (m_Answer == 1)
		{
			AfxMessageBox(_T("정답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			if (m_myStatic <= 100) m_myStatic += 5;
			state = 1;
		}
		else
		{
			AfxMessageBox(_T("오답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			state = 2;
		}
	}
	else if (count == 3)
	{
		if (m_Answer == 2)
		{
			AfxMessageBox(_T("정답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			if (m_myStatic <= 100) m_myStatic += 5;
			state = 1;
		}
		else
		{
			AfxMessageBox(_T("오답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			state = 2;

		}
	}


	else if (count == 4)
	{
		if (m_Answer == 3)
		{
			AfxMessageBox(_T("정답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			if (m_myStatic <= 100) m_myStatic += 5;
			state = 1;
		}
		else
		{
			AfxMessageBox(_T("오답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			state = 2;

		}
	}


	else if (count == 5)
	{
		if (m_Answer == 4)
		{
			AfxMessageBox(_T("정답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			if (m_myStatic <= 100) m_myStatic += 5;
			state = 1;
		}
		else
		{
			AfxMessageBox(_T("오답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			state = 2;

		}
	}


	else if (count == 6)
	{
		if (m_Answer == 5)
		{
			AfxMessageBox(_T("정답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			if (m_myStatic <= 100) m_myStatic += 5;
			state = 1;
		}
		else
		{
			AfxMessageBox(_T("오답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			state = 2;

		}
	}


	else if (count == 7)
	{
		if (m_Answer == 6)
		{
			AfxMessageBox(_T("정답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			if (m_myStatic <= 100) m_myStatic += 5;
			state = 1;
		}
		else
		{
			AfxMessageBox(_T("오답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			state = 2;
		}
	}


	else if (count == 8)
	{
		if (m_Answer == 7)
		{
			AfxMessageBox(_T("정답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			if (m_myStatic <= 100) m_myStatic += 5;
			state = 1;
		}
		else
		{
			AfxMessageBox(_T("오답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			state = 2;
		}
	}
	else if (count == 9)
	{
		if (m_Answer == 8)
		{
			AfxMessageBox(_T("정답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			if (m_myStatic <= 100) m_myStatic += 5;
			state = 1;
		}
		else
		{
			AfxMessageBox(_T("오답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			state = 2;
		}
	}

	else if (count == 10)
	{
		if (m_Answer == 12)
		{
			AfxMessageBox(_T("정답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			if (m_myStatic <= 100) m_myStatic += 5;
			state = 1;
		}
		else
		{
			AfxMessageBox(_T("오답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			state = 2;
		}
	}


	else if (count == 11)
	{
		if (m_Answer == 15)
		{
			AfxMessageBox(_T("정답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			if (m_myStatic <= 100) m_myStatic += 5;
			state = 1;
		}
		else
		{
			AfxMessageBox(_T("오답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			state = 2;
		}
	}


	else if (count == 12)
	{
		if (m_Answer == 16)
		{
			AfxMessageBox(_T("정답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			if (m_myStatic <= 100) m_myStatic += 5;
			state = 1;
		}
		else
		{
			AfxMessageBox(_T("오답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			state = 2;
		}
	}


	else if (count == 13)
	{
		if (m_Answer == 29)
		{
			AfxMessageBox(_T("정답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			if (m_myStatic <= 100) m_myStatic += 5;
			state = 1;
		}
		else
		{
			AfxMessageBox(_T("오답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			state = 2;
		}
	}

	else if (count == 14)
	{
		if (m_Answer == 35)
		{
			AfxMessageBox(_T("정답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			if (m_myStatic <= 100) m_myStatic += 5;
			state = 1;
		}
		else
		{
			AfxMessageBox(_T("오답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			state = 2;
		}
	}

	else if (count == 15)
	{
		if (m_Answer == 42)
		{
			AfxMessageBox(_T("정답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			if (m_myStatic <= 100) m_myStatic += 5;
			state = 1;
		}
		else
		{
			AfxMessageBox(_T("오답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			state = 2;
		}
	}


	else if (count == 16)
	{
		if (m_Answer == 45)
		{
			AfxMessageBox(_T("정답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			if (m_myStatic <= 100) m_myStatic += 5;
			state = 1;
		}
		else
		{
			AfxMessageBox(_T("오답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			state = 2;
		}
	}


	else if (count == 17)
	{
		if (m_Answer == 57)
		{
			AfxMessageBox(_T("정답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			if (m_myStatic <= 100) m_myStatic += 5;
			state = 1;
		}
		else
		{
			AfxMessageBox(_T("오답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			state = 2;
		}
	}


	else if (count == 18)
	{
		if (m_Answer == 73)
		{
			AfxMessageBox(_T("정답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			if (m_myStatic <= 100) m_myStatic += 5;
			state = 1;
		}
		else
		{
			AfxMessageBox(_T("오답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			state = 2;
		}
	}

	else if (count == 19)
	{
		if (m_Answer == 74)
		{
			AfxMessageBox(_T("정답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			if (m_myStatic <= 100) m_myStatic += 5;
			state = 1;
		}
		else
		{
			AfxMessageBox(_T("오답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			state = 2;
		}
	}


	else if (count == 20)
	{
		if (m_Answer == 96)
		{
			AfxMessageBox(_T("정답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			if (m_myStatic <= 100) m_myStatic += 5;
			state = 1;
		}
		else
		{
			AfxMessageBox(_T("오답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			state = 2;
		}
	}


	else if (count == 21)
	{
		if (m_Answer == 97)
		{
			AfxMessageBox(_T("정답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			if (m_myStatic <= 100) m_myStatic += 5;
			state = 1;
		}
		else
		{
			AfxMessageBox(_T("오답입니다."));
			GetDlgItem(IDC_INPUTBTN)->EnableWindow(false);
			state = 2;
		}
	}

	if (state == 1)
	{
		CString str;
		str = _T("11");
		//GetDlgItem(IDC_EDIT_SEND_DATA)->GetWindowText(str);
		str += "\r\n";
		wchar_t* wchar_str;
		char* char_str;
		int char_str_len;
		wchar_str = str.GetBuffer(str.GetLength());
		char_str_len = WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, NULL, 0, NULL, NULL);
		char_str = new char(char_str_len);
		WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, char_str, char_str_len, 0, 0);

		m_comm->Send((LPCTSTR)char_str, char_str_len - 1);
	}
	else if (state == 2)
	{
		CString str;
		str = _T("22");
		//GetDlgItem(IDC_EDIT_SEND_DATA)->GetWindowText(str);
		str += "\r\n";
		wchar_t* wchar_str;
		char* char_str;
		int char_str_len;
		wchar_str = str.GetBuffer(str.GetLength());
		char_str_len = WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, NULL, 0, NULL, NULL);
		char_str = new char(char_str_len);
		WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, char_str, char_str_len, 0, 0);

		m_comm->Send((LPCTSTR)char_str, char_str_len - 1);
	}


	UpdateData(false);

}
void CMFCSerialCommDlg::OnBnClickedNewbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	count = 1;
	m_myStatic = 0;
	m_Answer = 0;
	m_ID = "";
	UpdateData(false);
}
void CMFCSerialCommDlg::OnBnClickedRegbtn()//등록 버튼
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	GetDlgItemText(IDC_EDIT2, m_ID);
	CString str;
	str.Format(_T("%d"), m_myStatic);
	m_listbox.InsertString(-1, m_ID + "  score : " + str);
	UpdateData(false);
}
void CMFCSerialCommDlg::OnBnClickedDelbtn()//삭제 버튼
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_listbox.GetCurSel();
	m_listbox.DeleteString(index);

}
void CMFCSerialCommDlg::OnStnClickedMystatic()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void CMFCSerialCommDlg::OnBnClickedButton6() //종료 버튼
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();

}



