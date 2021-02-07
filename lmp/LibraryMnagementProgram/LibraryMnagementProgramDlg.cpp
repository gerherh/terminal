﻿
// LibraryMnagementProgramDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "LibraryMnagementProgram.h"
#include "LibraryMnagementProgramDlg.h"
#include "afxdialogex.h"
#include "Books.h"
#include "LibraryMember.h"
#include <vector>
#include <atldbcli.h>
#include <afxdb.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define MAX_COUNT 100
// ODBC API 라이브러리

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


// CLibraryMnagementProgramDlg 대화 상자



CLibraryMnagementProgramDlg::CLibraryMnagementProgramDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIBRARYMNAGEMENTPROGRAM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//자신이 설정해주었던 DSN 이름을 쓰고 id,pass를 입력
	db.OpenEx(_T("DSN=test;UID=mfc;PWD==r2BH+*hkU5yPtpz"));
	get_all_data_from_member();
	get_all_data_from_book();
	
}

void CLibraryMnagementProgramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, LIST_CTRL, list_ctrl);
	DDX_Control(pDX, ENTERED_MEMBER_NAME_TO_REGISTRATION, m_edit_member_name_registration);
	DDX_Control(pDX, ENTERED_MEMBER_NUMBER_TO_DELETE, m_edit_delete_member);
}

BEGIN_MESSAGE_MAP(CLibraryMnagementProgramDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(MEMBER_REGISTRATION_BUTTON, &CLibraryMnagementProgramDlg::OnBnClickedMemberRegistrationButton)
	ON_BN_CLICKED(MEMBER_DELETE_BUTTON, &CLibraryMnagementProgramDlg::OnBnClickedMemberDeleteButton)
	ON_BN_CLICKED(MEMBER_INFORMATION_BUTTON, &CLibraryMnagementProgramDlg::OnBnClickedInformationButton)
	ON_BN_CLICKED(BOOK_RENTAL_BUTTON, &CLibraryMnagementProgramDlg::OnBnClickedRentalButton)
	ON_BN_CLICKED(BOOK_RETURN_BUTTON, &CLibraryMnagementProgramDlg::OnBnClickedReturnButton)
	ON_BN_CLICKED(BOOK_REGISTRATION_BUTTON, &CLibraryMnagementProgramDlg::OnBnClickedBookRegistrationButton)
	ON_BN_CLICKED(BOOK_SEARCH_BUTTON, &CLibraryMnagementProgramDlg::OnBnClickedSearchButton)
	ON_BN_CLICKED(BOOK_LIST_BUTTON, &CLibraryMnagementProgramDlg::OnBnClickedBookListButton)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CLibraryMnagementProgramDlg 메시지 처리기

BOOL CLibraryMnagementProgramDlg::OnInitDialog()
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

	/*처음 창 크기를 얻는 부분*/
	GetClientRect(&m_rcMinimumDialog);
	CalcWindowRect(m_rcMinimumDialog);
	
	GetDlgItem(ENTERED_MEMBER_NAME_TO_REGISTRATION)->SetWindowText(_T("이름 입력"));
	GetDlgItem(ENTERED_MEMBER_NUMBER_TO_DELETE)->SetWindowText(_T("회원 번호 입력"));
	GetDlgItem(INDIVIDUAL_MEMBER_INFORMATION)->SetWindowText(_T("회원 번호 입력"));
	GetDlgItem(ENTERED_MEMBER_REGISTRATION_NUMBER_TO_BORROW)->SetWindowText(_T("회원 번호"));
	GetDlgItem(ENTERED_BOOK_NUMBER_TO_BORROW)->SetWindowText(_T("책 번호"));
	GetDlgItem(ENTERED_BOOK_NUMBER_TO_RETURN)->SetWindowText(_T("책 번호"));
	GetDlgItem(ENTERED_BOOK_NAME_TO_REGISTRATION_BOOK)->SetWindowText(_T("책 이름"));
	GetDlgItem(ENTERED_BOOK_NAME_TO_SEARCH)->SetWindowText(_T("책 이름"));


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CLibraryMnagementProgramDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLibraryMnagementProgramDlg::OnPaint()
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
HCURSOR CLibraryMnagementProgramDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLibraryMnagementProgramDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//CDialogEx::OnGetMinMaxInfo(lpMMI);
	/*처음 크기 이상으로 줄어들지는 않게 하는 부분*/
	lpMMI->ptMinTrackSize.x = m_rcMinimumDialog.Width();
	lpMMI->ptMinTrackSize.y = m_rcMinimumDialog.Height();

}

/*회원 등록*/
void CLibraryMnagementProgramDlg::OnBnClickedMemberRegistrationButton()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString member_name_cstr;
	int new_member_num = get_last_member_number() + 1;
	CString cquery;
	m_edit_member_name_registration.GetWindowTextW(member_name_cstr);
	cquery.Format(_T("INSERT INTO [dbo].[member]([member_number], [member_name])VALUES(%d, '%s')"), new_member_num,member_name_cstr);

	/*입력 쿼리 실행*/
	try
	{
		db.ExecuteSQL(cquery);
	}
	catch (CDBException* e) //에러 확인.
	{
		int errCode = e->ReportError();
	}
	GetDlgItem(ENTERED_MEMBER_NAME_TO_REGISTRATION)->SetWindowText(_T("이름 입력"));
}


void CLibraryMnagementProgramDlg::OnBnClickedMemberDeleteButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString member_number_cstr;
	CString cquery;
	m_edit_delete_member.GetWindowTextW(member_number_cstr);
	cquery.Format(_T("DELETE FROM [dbo].[member]WHERE member_number = %d"), _ttoi(member_number_cstr));

	/*삭제 쿼리 실행*/
	try
	{
		db.ExecuteSQL(cquery);
	}
	catch (CDBException* e) //에러 확인.
	{
		int errCode = e->ReportError();
	}
	GetDlgItem(ENTERED_MEMBER_NUMBER_TO_DELETE)->SetWindowText(_T("회원 번호 입력"));

}

/*회원정보 출력*/
void CLibraryMnagementProgramDlg::OnBnClickedInformationButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	clear_list_ctrl();
	// 책 리스트 => 컬럽 4개
	list_ctrl.InsertColumn(0, _T("회원 번호"), LVCFMT_CENTER, 200, -1);
	list_ctrl.InsertColumn(1, _T("이름"), LVCFMT_CENTER, 200, -1);
	list_ctrl.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER); // => 리스트에 값을 다 넣고 실행해야한다고 함


	for (int row = 0; row < members.size(); row++)
	{
		/*행의 첫번째 열에 InsertItem을 해야 그 행의 나머지 열에도 입력할수 있음*/
		list_ctrl.InsertItem(row, _T(""));
		for (int col = 0; col < 4; col++)
		{
			switch (col)
			{
			case 0:
				/*행, 열 위치에 삽입*/
				//list_ctrl.SetItem(row, col, LVIF_TEXT, , 0, 0, 0, NULL);
				break;
			case 1:

				break;
			case 2:

				break;
			case 3:

				break;
			}
			
		}
	}
	
	

	

}


void CLibraryMnagementProgramDlg::OnBnClickedRentalButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CLibraryMnagementProgramDlg::OnBnClickedReturnButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CLibraryMnagementProgramDlg::OnBnClickedBookRegistrationButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CLibraryMnagementProgramDlg::OnBnClickedSearchButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}


void CLibraryMnagementProgramDlg::OnBnClickedBookListButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 리스트컨트롤 초기화
	clear_list_ctrl();
	// 책 리스트 => 컬럽 4개
	list_ctrl.InsertColumn(0, _T("책 번호"), LVCFMT_CENTER, 200, -1);
	list_ctrl.InsertColumn(1, _T("책 이름"), LVCFMT_CENTER, 200, -1);
	list_ctrl.InsertColumn(2, _T("대여 상태"), LVCFMT_CENTER, 200, -1);
	list_ctrl.InsertColumn(3, _T("대여중인 사람"), LVCFMT_CENTER, 200, -1);

	list_ctrl.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	//for (int i = 0; i < list_ctrl.GetHeaderCtrl()->GetItemCount(); ++i)
	//	list_ctrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

	
	

	CRecordset rs(&db);
	try
	{
		rs.Open(CRecordset::dynaset, _T("SELECT * FROM book"));        //테이블의모든내용선택
	}
	catch (CDBException* e)
	{
		e->ReportError();      //디폴트는 오류시에 메시지 박스를 띄워준다
	}

	

	//GetODBCFieldCount 함수는 필드수(열의수) 를 알려줌
	short col = rs.GetODBCFieldCount();

	//행
	while (!rs.IsEOF())
	{
		//열
		for (short i = 0; i < col; i++)
		{
			CString tmp;
			rs.GetFieldValue(i, tmp);
		}
		//다음 행으로 이동
		rs.MoveNext();
	}
}


void CLibraryMnagementProgramDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	/*db 연결 종료*/
	db.Close();


}

void CLibraryMnagementProgramDlg::clear_list_ctrl()
{
	list_ctrl.DeleteAllItems();
	for (int i = 0; i < 6; i++)
	{
		list_ctrl.DeleteColumn(0);
	}
}

int CLibraryMnagementProgramDlg::get_last_member_number()
{
	int i = 0;
	CRecordset rs(&db);
	try
	{
		rs.Open(CRecordset::dynaset, _T("SELECT * FROM member"));        //테이블의모든내용선택
	}
	catch (CDBException* e)
	{
		e->ReportError();      //디폴트는 오류시에 메시지 박스를 띄워준다
	}
	while (!rs.IsEOF())
	{
		rs.MoveNext();
		i++;
	}
	return i;
}

void CLibraryMnagementProgramDlg::get_all_data_from_member()
{
	CString tmp[4];
	CRecordset rs(&db);
	try
	{
		rs.Open(CRecordset::dynaset, _T("SELECT * FROM member"));        //테이블의모든내용선택
	}
	catch (CDBException* e)
	{
		e->ReportError();      //디폴트는 오류시에 메시지 박스를 띄워준다
	}

	//GetODBCFieldCount 함수는 필드수(열의수) 를 알려줌
	short col = rs.GetODBCFieldCount();
	
	//행
	while (!rs.IsEOF())
	{
		//열
		for (short i = 0; i < col; i++)
		{
			rs.GetFieldValue(i, tmp[i]);
			
		}
		LibraryMember library_member(_ttoi(tmp[0]), tmp[1], _ttoi(tmp[2]), tmp[3]);
		members.push_back(library_member);
		//다음 행으로 이동
		rs.MoveNext();
	}

}
void CLibraryMnagementProgramDlg::get_all_data_from_book()
{
	CString tmp[4];
	CRecordset rs(&db);
	try
	{
		rs.Open(CRecordset::dynaset, _T("SELECT * FROM book"));        //테이블의모든내용선택
	}
	catch (CDBException* e)
	{
		e->ReportError();      //디폴트는 오류시에 메시지 박스를 띄워준다
	}

	//GetODBCFieldCount 함수는 필드수(열의수) 를 알려줌
	short col = rs.GetODBCFieldCount();

	//행
	while (!rs.IsEOF())
	{
		//열
		for (short i = 0; i < col; i++)
		{
			rs.GetFieldValue(i, tmp[i]);
		}
		Book book(_ttoi(tmp[0]),tmp[1], _ttoi(tmp[2]), _ttoi(tmp[2]));
		book_vector.push_back(book);
		//다음 행으로 이동
		rs.MoveNext();
	}
}


