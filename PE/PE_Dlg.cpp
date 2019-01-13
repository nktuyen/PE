
// PEDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PE_App.h"
#include "PE_Dlg.h"
#include "afxdialogex.h"
#include "PE_File.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CPEDlg dialog


IMPLEMENT_DYNAMIC(PE_Dlg, CDialogEx);

PE_Dlg::PE_Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PE_DIALOG, pParent)
	, m_option()
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = nullptr;
	m_hPEFile = INVALID_HANDLE_VALUE;
	m_hMapViewOfFile = NULL;

	m_option.setHexa(true);
}

PE_Dlg::~PE_Dlg()
{
}

void PE_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TVW_STRUCTURE, m_tvwStructure);
}

BEGIN_MESSAGE_MAP(PE_Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BROWSE, &PE_Dlg::OnBnClickedBtnBrowse)
	ON_BN_CLICKED(IDC_CHB_HEXA, &PE_Dlg::OnBnClickedChbHexa)
END_MESSAGE_MAP()


// CPEDlg message handlers

BOOL PE_Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void PE_Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void PE_Dlg::OnPaint()
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
HCURSOR PE_Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void PE_Dlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void PE_Dlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void PE_Dlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL PE_Dlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != nullptr)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}



void PE_Dlg::OnBnClickedBtnBrowse()
{
	const TCHAR szFilter[] = {_T("All Files(*.*|*.*|EXE Files(*.exe)|*.exe|OBJ Files(*.obj)|*.obj|DLL Files(*.dll)|*.dll||")};
	CFileDialog dlg(TRUE, nullptr, nullptr, OFN_FILEMUSTEXIST | OFN_EXPLORER, szFilter);
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	SetDlgItemText(IDC_EDT_FILENAME, dlg.GetPathName());
	m_tvwStructure.DeleteAllItems();
	Open(dlg.GetPathName());
}


BOOL PE_Dlg::Open(LPCTSTR lpszFilename)
{
	ASSERT(m_hPEFile == INVALID_HANDLE_VALUE);
	m_hPEFile = ::CreateFile(lpszFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, nullptr);
	ASSERT(m_hPEFile != INVALID_HANDLE_VALUE);

	ASSERT(m_hMapViewOfFile == NULL);
	m_hMapViewOfFile = ::CreateFileMapping(m_hPEFile, NULL, PAGE_READONLY, 0, 0, NULL);
	ASSERT(m_hMapViewOfFile != NULL);

	LPVOID lpFileBase = ::MapViewOfFile(m_hMapViewOfFile, FILE_MAP_READ, 0, 0, 0);
	ASSERT(lpFileBase != NULL);
	
	HTREEITEM hRoot = m_tvwStructure.InsertItem(lpszFilename, TVI_ROOT);
	PE_File PEFile(lpFileBase);
	BOOL  bHexa = (IsDlgButtonChecked(IDC_CHB_HEXA) & BST_CHECKED) != 0;
	m_option.setHexa(bHexa ? true : false);
	PEFile.Present(m_tvwStructure.GetSafeHwnd(), hRoot, &m_option);

	if (::UnmapViewOfFile(lpFileBase))
		if (::CloseHandle(m_hMapViewOfFile))
			m_hMapViewOfFile = NULL;

	if (::CloseHandle(m_hPEFile))
		m_hPEFile = INVALID_HANDLE_VALUE;

	return TRUE;
}


void PE_Dlg::OnBnClickedChbHexa()
{
	CString strFilename;
	GetDlgItemText(IDC_EDT_FILENAME, strFilename);

	m_tvwStructure.DeleteAllItems();
	Open(strFilename);
}
