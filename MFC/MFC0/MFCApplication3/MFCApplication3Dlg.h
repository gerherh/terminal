
// MFCApplication3Dlg.h: 헤더 파일
//

#pragma once
#include <vector>
#include <string>
#include <cstring>

using namespace std;
// CMFCApplication3Dlg 대화 상자
class CMFCApplication3Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication3Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION3_DIALOG };
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

public:
	CEdit m_editc;
	CEdit m_editc2;
	afx_msg void OnBnClickedButton1();
	CListCtrl list_ctrl;
	afx_msg void OnBnClickedButton2();
	void print_whole_data();
	void ptrint_to_list_ctrl(CString _si, CString _gu);
	void ptrint_to_list_ctrl(CString _si);
	void clear_list_control();
	vector<std::string> all_data;
	vector <CString> si;
	vector <CString> gu;

	struct each_accident_num_row
	{
		int data[11];
	};
	vector <each_accident_num_row> whole_accident_num_row;
	

	afx_msg void OnBnClickedButton3();
};

