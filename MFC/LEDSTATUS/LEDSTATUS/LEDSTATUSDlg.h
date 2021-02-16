
// LEDSTATUSDlg.h: 헤더 파일
//

#pragma once
#include "afxwin.h"

#include "SerialCom.h"	//추가 MrKang.


// CLEDSTATUSDlg 대화 상자
class CLEDSTATUSDlg : public CDialogEx
{
// 생성입니다.
public:
	CLEDSTATUSDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CSerialComm* m_comm;
	LRESULT		OnThreadClosed(WPARAM length, LPARAM lpara);
	LRESULT		OnReceive(WPARAM length, LPARAM lpara);
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LEDSTATUS_DIALOG };
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
	CComboBox m_combo_port;
	CComboBox m_combo_baudrate;
	CString m_selected_port;
	CString m_selected_baudrate;
	CEdit m_edit_led0;
	CEdit m_edit_led1;
	CEdit m_edit_led2;
	BOOL comport_state;
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedLed0();
	afx_msg void OnBnClickedLed1();
	afx_msg void OnBnClickedLed2();
	afx_msg void OnBnClickedLed3();

	afx_msg void OnCbnSelchangeComboComport();
	afx_msg void OnCbnSelchangeComboBaudrate();
};
