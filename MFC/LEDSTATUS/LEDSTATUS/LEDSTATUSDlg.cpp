
// LEDSTATUSDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "LEDSTATUS.h"
#include "LEDSTATUSDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
public:
	

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


// CLEDSTATUSDlg 대화 상자



CLEDSTATUSDlg::CLEDSTATUSDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LEDSTATUS_DIALOG, pParent)
	, m_selected_port(_T(""))
	, m_selected_baudrate(_T(""))

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLEDSTATUSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COMPORT, m_combo_port);
	DDX_CBString(pDX, IDC_COMBO_COMPORT, m_selected_port);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_combo_baudrate);
	DDX_CBString(pDX, IDC_COMBO_BAUDRATE, m_selected_baudrate);
	DDX_Control(pDX, IDC_EDIT_LED0, m_edit_led0);
	DDX_Control(pDX, IDC_EDIT_LED1, m_edit_led1);
	DDX_Control(pDX, IDC_EDIT_LED2, m_edit_led2);

}

BEGIN_MESSAGE_MAP(CLEDSTATUSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, &CLEDSTATUSDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_LED0, &CLEDSTATUSDlg::OnBnClickedLed0)
	ON_BN_CLICKED(IDC_LED1, &CLEDSTATUSDlg::OnBnClickedLed1)
	ON_BN_CLICKED(IDC_LED2, &CLEDSTATUSDlg::OnBnClickedLed2)
	ON_BN_CLICKED(IDC_LED3, &CLEDSTATUSDlg::OnBnClickedLed3)
	ON_CBN_SELCHANGE(IDC_COMBO_COMPORT, &CLEDSTATUSDlg::OnCbnSelchangeComboComport)
	ON_CBN_SELCHANGE(IDC_COMBO_BAUDRATE, &CLEDSTATUSDlg::OnCbnSelchangeComboBaudrate)

	ON_MESSAGE(WM_MYCLOSE, &CLEDSTATUSDlg::OnThreadClosed)
	ON_MESSAGE(WM_MYRECEIVE, &CLEDSTATUSDlg::OnReceive)
END_MESSAGE_MAP()


// CLEDSTATUSDlg 메시지 처리기

BOOL CLEDSTATUSDlg::OnInitDialog()
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
	m_combo_port.AddString(_T("COM1"));
	m_combo_port.AddString(_T("COM3"));
	

	m_combo_baudrate.AddString(_T("9600"));
	m_combo_baudrate.AddString(_T("19200"));
	m_combo_baudrate.AddString(_T("115200"));


	comport_state = false;
	GetDlgItem(IDC_CONNECT)->SetWindowText(_T("OPEN"));
	m_selected_port = _T("COM1");
	m_selected_baudrate = _T("115200");
	UpdateData(FALSE);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CLEDSTATUSDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLEDSTATUSDlg::OnPaint()
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
HCURSOR CLEDSTATUSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CLEDSTATUSDlg::OnBnClickedConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (comport_state)
	{
		if (m_comm)        //컴포트가존재하면
		{
			m_comm->Close();
			m_comm = NULL;
			AfxMessageBox(_T("COM 포트닫힘"));
			comport_state = false;
			GetDlgItem(IDC_CONNECT)->SetWindowText(_T("OPEN"));
		}
	}
	else
	{
		m_comm = new CSerialComm(_T("\\\\.\\") + m_selected_port, m_selected_baudrate, _T("None"), _T("8 Bit"), _T("1 Bit"));         // initial Comm port
		if (m_comm->Create(GetSafeHwnd()) != 0) //통신포트를열고윈도우의핸들을넘긴다.
		{
			AfxMessageBox(_T("COM 포트열림"));
			comport_state = true;
			GetDlgItem(IDC_CONNECT)->SetWindowText(_T("CLOSE"));
		}
		else
		{
			AfxMessageBox(_T("ERROR!"));
		}
	}
}

/* 추가 부분  MrKang*/
LRESULT	CLEDSTATUSDlg::OnThreadClosed(WPARAM length, LPARAM lpara)
{
	((CSerialComm*)lpara)->HandleClose();
	delete ((CSerialComm*)lpara);

	return 0;
}

LRESULT CLEDSTATUSDlg::OnReceive(WPARAM length, LPARAM lpara)
{
	CString str;
	char* data = new char[length + 1];
	if (m_comm)
	{
		m_comm->Receive(data, length);	// Length 길이만큼 데이터 받음.
		data[length] = _T('\0');
		if (length == 3)
		{

			if (data[0] == '0')
			{
				m_edit_led0.SetWindowTextW(_T("꺼져 있음"));
			}
			else
			{
				m_edit_led0.SetWindowTextW(_T("켜져 있음"));
			}
			if (data[1] == '0')
			{
				m_edit_led1.SetWindowTextW(_T("꺼져 있음"));
			}
			else
			{
				m_edit_led1.SetWindowTextW(_T("켜져 있음"));
			}
			if (data[2] == '0')
			{
				m_edit_led2.SetWindowTextW(_T("꺼져 있음"));
			}
			else
			{
				m_edit_led2.SetWindowTextW(_T("켜져 있음"));
			}
		}
	}
	delete data;
	return 0;
}

/* 추가 부분 끝  MrKang*/




void CLEDSTATUSDlg::OnBnClickedLed0()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("A");
	m_comm->Send(str, str.GetLength());
}


void CLEDSTATUSDlg::OnBnClickedLed1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("B");
	m_comm->Send(str, str.GetLength());
}


void CLEDSTATUSDlg::OnBnClickedLed2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("C");
	m_comm->Send(str, str.GetLength());
}


void CLEDSTATUSDlg::OnBnClickedLed3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("D");
	m_comm->Send(str, str.GetLength());
}


void CLEDSTATUSDlg::OnCbnSelchangeComboComport()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
}


void CLEDSTATUSDlg::OnCbnSelchangeComboBaudrate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
}
