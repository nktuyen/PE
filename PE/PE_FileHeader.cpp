#include "stdafx.h"
#include "PE_FileHeader.h"

std::map<DWORD, CString> PE_FileHeader::m_mapMachine;

PE_FileHeader::PE_FileHeader(IMAGE_FILE_HEADER* pFileHdr)
{
	ZeroMemory(&m_FileHeader, sizeof(IMAGE_FILE_HEADER));
	if (nullptr != pFileHdr)
	{
		CopyMemory(&m_FileHeader, pFileHdr, sizeof(IMAGE_FILE_HEADER));
	}

	m_mapMachine[IMAGE_FILE_MACHINE_I386] = _T("IMAGE_FILE_MACHINE_I386");
	m_mapMachine[IMAGE_FILE_MACHINE_IA64] = _T("IMAGE_FILE_MACHINE_IA64");
	m_mapMachine[IMAGE_FILE_MACHINE_AMD64] = _T("IMAGE_FILE_MACHINE_AMD64");
}

CString PE_FileHeader::CharacteristicString_Get(DWORD dw)
{
	CString s;

	if ((dw & IMAGE_FILE_RELOCS_STRIPPED) != 0)
	{
		if (!s.IsEmpty())
			s += _T(" | ");
		s += _T("IMAGE_FILE_RELOCS_STRIPPED");
	}

	if ((dw & IMAGE_FILE_EXECUTABLE_IMAGE) != 0)
	{
		if (!s.IsEmpty())
			s += _T(" | ");
		s += _T("IMAGE_FILE_EXECUTABLE_IMAGE");
	}

	if ((dw & IMAGE_FILE_LINE_NUMS_STRIPPED) != 0)
	{
		if (!s.IsEmpty())
			s += _T(" | ");
		s += _T("IMAGE_FILE_LINE_NUMS_STRIPPED");
	}

	if ((dw & IMAGE_FILE_LOCAL_SYMS_STRIPPED) != 0)
	{
		if (!s.IsEmpty())
			s += _T(" | ");
		s += _T("IMAGE_FILE_LOCAL_SYMS_STRIPPED");
	}

	if ((dw & IMAGE_FILE_AGGRESIVE_WS_TRIM) != 0)
	{
		if (!s.IsEmpty())
			s += _T(" | ");
		s += _T("IMAGE_FILE_AGGRESIVE_WS_TRIM");
	}

	if ((dw & IMAGE_FILE_LARGE_ADDRESS_AWARE) != 0)
	{
		if (!s.IsEmpty())
			s += _T(" | ");
		s += _T("IMAGE_FILE_LARGE_ADDRESS_AWARE");
	}

	if ((dw & IMAGE_FILE_BYTES_REVERSED_LO) != 0)
	{
		if (!s.IsEmpty())
			s += _T(" | ");
		s += _T("IMAGE_FILE_BYTES_REVERSED_LO");
	}

	if ((dw & IMAGE_FILE_32BIT_MACHINE) != 0)
	{
		if (!s.IsEmpty())
			s += _T(" | ");
		s += _T("IMAGE_FILE_32BIT_MACHINE");
	}

	if ((dw & IMAGE_FILE_DEBUG_STRIPPED) != 0)
	{
		if (!s.IsEmpty())
			s += _T(" | ");
		s += _T("IMAGE_FILE_DEBUG_STRIPPED");
	}

	if ((dw & IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP) != 0)
	{
		if (!s.IsEmpty())
			s += _T(" | ");
		s += _T("IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP");
	}

	if ((dw & IMAGE_FILE_NET_RUN_FROM_SWAP) != 0)
	{
		if (!s.IsEmpty())
			s += _T(" | ");
		s += _T("IMAGE_FILE_NET_RUN_FROM_SWAP");
	}

	if ((dw & IMAGE_FILE_SYSTEM) != 0)
	{
		if (!s.IsEmpty())
			s += _T(" | ");
		s += _T("IMAGE_FILE_SYSTEM");
	}

	if ((dw & IMAGE_FILE_DLL) != 0)
	{
		if (!s.IsEmpty())
			s += _T(" | ");
		s += _T("IMAGE_FILE_DLL");
	}

	if ((dw & IMAGE_FILE_UP_SYSTEM_ONLY) != 0)
	{
		if (!s.IsEmpty())
			s += _T(" | ");
		s += _T("IMAGE_FILE_UP_SYSTEM_ONLY");
	}

	if ((dw & IMAGE_FILE_BYTES_REVERSED_HI) != 0)
	{
		if (!s.IsEmpty())
			s += _T(" | ");
		s += _T("IMAGE_FILE_BYTES_REVERSED_HI");
	}

	return s;
}

PE_FileHeader::~PE_FileHeader()
{
}

CString PE_FileHeader::MachineName_Get(DWORD dwID)
{
	std::map<DWORD, CString>::iterator it = m_mapMachine.find(dwID);
	if (m_mapMachine.end() == it)
	{
		return CString();
	}

	return it->second;
}

void PE_FileHeader::Present(HWND hTreeCtrl, HTREEITEM hParentNode, PE_PresentOptions* opt)
{
	HTREEITEM hFileHdrNode = InsertTreeItem(hTreeCtrl, hParentNode, _T("IMAGE_FILE_HEADER"));
	CString s;

	s.Format(_T("Machine = {%s:%s}"), HexaString(m_FileHeader.Machine, opt), MachineName_Get(m_FileHeader.Machine));
	InsertTreeItem(hTreeCtrl, hFileHdrNode, s);

	s.Format(_T("NumberOfSections = {%s}"), HexaString(m_FileHeader.NumberOfSections, opt));
	InsertTreeItem(hTreeCtrl, hFileHdrNode, s);


	COleDateTime dt(1970,1,1,0,0,0);
	COleDateTimeSpan ds(double(m_FileHeader.TimeDateStamp)/(60.0*60.0*24.0));
	dt += ds;
	s.Format(_T("TimeDateStamp = {%s:%.4d/%.2d/%.2d-%.2d:%.2d:%.2d}"), HexaString(m_FileHeader.TimeDateStamp, opt), dt.GetYear(),dt.GetMonth(),dt.GetDay(),dt.GetHour(),dt.GetMinute(),dt.GetSecond());
	InsertTreeItem(hTreeCtrl, hFileHdrNode, s);

	s.Format(_T("PointerToSymbolTable = {%s}"), HexaString(m_FileHeader.PointerToSymbolTable, opt));
	InsertTreeItem(hTreeCtrl, hFileHdrNode, s);

	s.Format(_T("NumberOfSymbols = {%s}"), HexaString(m_FileHeader.NumberOfSymbols, opt));
	InsertTreeItem(hTreeCtrl, hFileHdrNode, s);

	s.Format(_T("SizeOfOptionalHeader = {%s}"), HexaString(m_FileHeader.SizeOfOptionalHeader, opt));
	InsertTreeItem(hTreeCtrl, hFileHdrNode, s);

	s.Format(_T("Characteristics = {%s:%s}"), HexaString(m_FileHeader.Characteristics, opt), CharacteristicString_Get(m_FileHeader.Characteristics));
	InsertTreeItem(hTreeCtrl, hFileHdrNode, s);
}