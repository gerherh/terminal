#pragma once

// ODBC API 헤더
#include <odbcinst.h>
#include <sqlext.h>
#include <afxdb.h>
#include "LibraryMember.h"
#include "Books.h"
#include <vector>
// CLibraryMnagementProgramDlg 대화 상자
class CLibraryMnagementProgramDlg : public CDialogEx
{
	// 생성입니다.
public:
	CLibraryMnagementProgramDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIBRARYMNAGEMENTPROGRAM_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	// ODBC

public:
	CRect m_rcMinimumDialog;
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnBnClickedMemberRegistrationButton();
	afx_msg void OnBnClickedMemberDeleteButton();
	afx_msg void OnBnClickedInformationButton();
	afx_msg void OnBnClickedRentalButton();
	afx_msg void OnBnClickedReturnButton();
	afx_msg void OnBnClickedBookRegistrationButton();
	afx_msg void OnBnClickedSearchButton();
	afx_msg void OnBnClickedBookListButton();
	CListCtrl list_ctrl;
	afx_msg void OnDestroy();
	void clear_list_ctrl();
	CDatabase db;
	CEdit m_edit_member_name_registration;
	int get_last_member_num();
	int get_last_book_num();
	CEdit m_edit_delete_member;
	void get_all_data_from_member();
	void get_all_data_from_book();
	/*회원 번호 같은걸로 해당 행 업데이트 하는 함수 필요*/
	void update_at_member_num_row();
	vector<LibraryMember> members;
	vector<Book> book_vector;
	CString get_book_name_by_book_num(int book_number);
	int is_book_exist(int book_number);
	bool is_member_exist(int member_number);
	CEdit m_edit_rental_book_number;
	CEdit m_edit_rental_member_number;
	CEdit m_edit_return;
	CEdit m_edit_book_registration;
	CEdit m_edit_book_search;
	CString get_books_on_loan_by_member_num(int member_num);
	
	

	afx_msg void OnBnClickedBookDeleteButton();
	CEdit m_edit_button_number_to_delete;
};



