
// PEDlg.h : header file
//

#pragma once

#include "PE_Entity.h"

class CPEDlgAutoProxy;


// CPEDlg dialog
class PE_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(PE_Dlg);
	friend class CPEDlgAutoProxy;

// Construction
public:
	PE_Dlg(CWnd* pParent = nullptr);	// standard constructor
	virtual ~PE_Dlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	CPEDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;
	HANDLE m_hPEFile;
	HANDLE m_hMapViewOfFile;
	BOOL CanExit();
	PE_PresentOptions	m_option;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_tvwStructure;
	afx_msg void OnBnClickedBtnBrowse();
private:
	BOOL Open(LPCTSTR lpszFilename);
public:
	afx_msg void OnBnClickedChbHexa();
};
