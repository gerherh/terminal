
// MFCApplication3Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"
#include "accident_information.h"

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


// CMFCApplication3Dlg 대화 상자



CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION3_DIALOG, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editc);

	DDX_Control(pDX, IDC_EDIT2, m_editc2);

	DDX_Control(pDX, IDC_LIST1, list_ctrl);
}

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication3Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication3Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication3Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 메시지 처리기

BOOL CMFCApplication3Dlg::OnInitDialog()
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

	/*컬럼 헤드 설정*/
	list_ctrl.InsertColumn(0, _T("시"), LVCFMT_CENTER, 100, -1);
	list_ctrl.InsertColumn(1, _T("구"), LVCFMT_CENTER, 100, -1);
	list_ctrl.InsertColumn(2, _T("횡단보도 위"), LVCFMT_CENTER, 100, -1);
	list_ctrl.InsertColumn(3, _T("횡단보도 부근"), LVCFMT_CENTER, 100, -1);
	list_ctrl.InsertColumn(4, _T("터널 안"), LVCFMT_CENTER, 100, -1);
	list_ctrl.InsertColumn(5, _T("교량 위"), LVCFMT_CENTER, 100, -1);
	list_ctrl.InsertColumn(6, _T("기타 단일로"), LVCFMT_CENTER, 100, -1);
	list_ctrl.InsertColumn(7, _T("교차로 내"), LVCFMT_CENTER, 100, -1);
	list_ctrl.InsertColumn(8, _T("교차로 부근"), LVCFMT_CENTER, 100, -1);
	list_ctrl.InsertColumn(9, _T("건널목"), LVCFMT_CENTER, 100, -1);
	list_ctrl.InsertColumn(10, _T("기타 / 불명"), LVCFMT_CENTER, 100, -1);
	list_ctrl.InsertColumn(11, _T("고가도로 위"), LVCFMT_CENTER, 100, -1);
	list_ctrl.InsertColumn(12, _T("지하도로 내"), LVCFMT_CENTER, 100, -1);

	
	/*edit box에 텍스트 설정*/
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T("시"));
	GetDlgItem(IDC_EDIT2)->SetWindowText(_T("구"));
	
	/*밑의 insertitem 하고 나서야 setitem이 한 행에 뭘 입력하고 싶으면 일단 insertItem을 해야하는것 같음
	list_ctrl.InsertItem(0, _T("a"));
	list_ctrl.InsertItem(1, _T("b"));

	/*행, 열 위치에 삽입
	list_ctrl.SetItem(0, 0, LVIF_TEXT, _T("0행 0열"), 0, 0, 0, NULL);
	list_ctrl.SetItem(0, 1, LVIF_TEXT, _T("0행 1열"), 0, 0, 0, NULL);
	list_ctrl.SetItem(1, 0, LVIF_TEXT, _T("1행 0열"), 0, 0, 0, NULL);

	/*행, 열 부분 텍스트 삽입
	list_ctrl.SetItem(0, 0, LVIF_TEXT, _T("0행 0열"), 0, 0, 0, NULL);
	list_ctrl.SetItem(0, 1, LVIF_TEXT, _T("0행 1열"), 0, 0, 0, NULL);

	*/
	/*컬럼 너비 자동조정*/
	for (int i = 0; i < list_ctrl.GetHeaderCtrl()->GetItemCount(); ++i)
		list_ctrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

	AccidentInformation ai;
	ai.upload_all_data();
	all_data = ai.get_lines();
	

	// 전체 데이터를 CString 시, 구 , 숫자 배열에 저장
	string cell;
	int idx = 0;
	struct each_accident_num_row eanr;
	
	for (int i = 0; i < all_data.size(); i++)
	{
		list_ctrl.InsertItem(0, _T(" "));
		stringstream lineStream(all_data[i]);
		idx = 0;
		while (getline(lineStream, cell, ','))
		{
			CString csi(cell.c_str());
			CString cgu(cell.c_str());
			if (idx == 0) {
				si.push_back(csi);
			}
			else if (idx == 1) {
				gu.push_back(cgu);
			}
			else {
				eanr.data[idx-2] = stoi(cell);
			}
			idx++;
		}
		whole_accident_num_row.push_back(eanr);
	}

	print_whole_data();
	/*컬럼 너비 자동조정*/
	for (int i = 0; i < list_ctrl.GetHeaderCtrl()->GetItemCount(); ++i)
		list_ctrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication3Dlg::OnPaint()
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
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication3Dlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	clear_list_control();

	CString cstring_si, cstring_gu;
	m_editc.GetWindowTextW(cstring_si);
	m_editc2.GetWindowTextW(cstring_gu);
	ptrint_to_list_ctrl(cstring_si, cstring_gu);

	/*시,구에 해당하는 정보 출력*/

}


void CMFCApplication3Dlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	clear_list_control();

	CString cstring_si;
	m_editc.GetWindowTextW(cstring_si);
	ptrint_to_list_ctrl(cstring_si);
	
	/*시의 합계 정보 출력*/

}

void CMFCApplication3Dlg::ptrint_to_list_ctrl(CString _si)
{
	int sum_of_si[11] = {0,};
	CString cstr;
	/*시의 모든 숫자 각 컬럼별로 합*/
	for (int row = 0; row < all_data.size(); row++)
	{
		if (si[row] == _si)
		{
			for (int col = 0; col < 11; col++) {
				sum_of_si[col] += whole_accident_num_row[row].data[col];
			}
		}
	}
	list_ctrl.SetItem(0, 0, LVIF_TEXT, _si, 0, 0, 0, NULL);
	list_ctrl.SetItem(0, 1, LVIF_TEXT, _T("총 합"), 0, 0, 0, NULL);

	for (int col = 0; col < 11; col++)
	{
		cstr.Format(_T("%d"), sum_of_si[col]);
		list_ctrl.SetItem(0, col+2, LVIF_TEXT, cstr, 0, 0, 0, NULL);
	}
	

}
void CMFCApplication3Dlg::ptrint_to_list_ctrl(CString _si, CString _gu)
{
	CString cstr;
	list_ctrl.SetItem(0, 0, LVIF_TEXT, _si, 0, 0, 0, NULL);
	list_ctrl.SetItem(0, 1, LVIF_TEXT, _gu, 0, 0, 0, NULL);
	for (int row = 0; row < all_data.size(); row++)
	{
		if (si[row] == _si && gu[row] == _gu)
		{
			for (int col = 0; col < 11; col++) {
				cstr.Format(_T("%d"), whole_accident_num_row[row].data[col]);
				list_ctrl.SetItem(0, col+2, LVIF_TEXT, cstr, 0, 0, 0, NULL);
			}
			return;
		}
	}

}
void CMFCApplication3Dlg::clear_list_control()
{
	for (int row = 0; row < all_data.size(); row++)
	{
		for (int col = 0; col < 13; col++)
		{
			list_ctrl.SetItem(row, col, LVIF_TEXT, _T(" "), 0, 0, 0, NULL);
		}
	}
}

void CMFCApplication3Dlg::print_whole_data()
{
	// 전체 데이터 출력
	CString cstr;
	for (int row = 0; row < all_data.size(); row++)
	{
		for (int col = 0; col < 13; col++) {
			if (col == 0) {
				list_ctrl.SetItem(row, col, LVIF_TEXT, si[row], 0, 0, 0, NULL);
			}
			else if (col == 1) {
				list_ctrl.SetItem(row, col, LVIF_TEXT, gu[row], 0, 0, 0, NULL);
			}
			else {
				cstr.Format(_T("%d"), whole_accident_num_row[row].data[col - 2]);
				list_ctrl.SetItem(row, col, LVIF_TEXT, cstr, 0, 0, 0, NULL);
			}
		}
	}
}

void CMFCApplication3Dlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	print_whole_data();
}
