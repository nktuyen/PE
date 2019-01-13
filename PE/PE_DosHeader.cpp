#include "stdafx.h"
#include "PE_DosHeader.h"


PE_DosHeader::PE_DosHeader(IMAGE_DOS_HEADER* pDosHdr)
	: PE_Entity()
{
	CopyMemory(&m_header, pDosHdr, sizeof(IMAGE_DOS_HEADER));
}


PE_DosHeader::~PE_DosHeader()
{
}


void PE_DosHeader::Present(HWND hTreeCtrl, HTREEITEM hParentNode, PE_PresentOptions* opt)
{
	HTREEITEM hDosHdrNode = InsertTreeItem(hTreeCtrl, hParentNode, _T("IMAGE_DOS_HEADER"));
	CString s;

	s.Format(_T("Magic number (e_magic) = {%s:%s}"), HexaString(m_header.e_magic, opt), MagicName_Get(m_header.e_magic));
	InsertTreeItem(hTreeCtrl, hDosHdrNode, s);

	s.Format(_T("Bytes on last page of file (e_cblp) = {%s}"), HexaString( m_header.e_cblp, opt));
	InsertTreeItem(hTreeCtrl, hDosHdrNode, s);

	s.Format(_T("Pages in file (e_cp) = {%s}"), HexaString(m_header.e_cp, opt));
	InsertTreeItem(hTreeCtrl, hDosHdrNode, s);

	s.Format(_T("Relocations (e_crlc) = {%s}"), HexaString(m_header.e_crlc, opt));
	InsertTreeItem(hTreeCtrl, hDosHdrNode, s);

	s.Format(_T("Size of header in paragraphs (e_cparhdr) = {%s}"), HexaString(m_header.e_cparhdr, opt));
	InsertTreeItem(hTreeCtrl, hDosHdrNode, s);

	s.Format(_T("Minimum extra paragraphs needed (e_minalloc) = {%s}"), HexaString(m_header.e_minalloc, opt));
	InsertTreeItem(hTreeCtrl, hDosHdrNode, s);

	s.Format(_T("Maximum extra paragraphs needed (e_maxalloc) = {%s}"), HexaString(m_header.e_maxalloc, opt));
	InsertTreeItem(hTreeCtrl, hDosHdrNode, s);

	s.Format(_T("Initial (relative) SS value (e_ss) = {%s}"), HexaString(m_header.e_ss, opt));
	InsertTreeItem(hTreeCtrl, hDosHdrNode, s);

	s.Format(_T("Initial SP value (e_sp) = {%s}"), HexaString(m_header.e_sp, opt));
	InsertTreeItem(hTreeCtrl, hDosHdrNode, s);

	s.Format(_T("Checksum (e_csum) = {%s}"), HexaString(m_header.e_csum, opt));
	InsertTreeItem(hTreeCtrl, hDosHdrNode, s);

	s.Format(_T("Initial IP value (e_ip) = {%s}"), HexaString(m_header.e_ip, opt));
	InsertTreeItem(hTreeCtrl, hDosHdrNode, s);

	s.Format(_T("Initial (relative) CS value (e_cs) = {%s}"), HexaString(m_header.e_cs, opt));
	InsertTreeItem(hTreeCtrl, hDosHdrNode, s);

	s.Format(_T("File address of relocation table (e_lfarlc) = {%s}"), HexaString( m_header.e_lfarlc, opt ));
	InsertTreeItem(hTreeCtrl, hDosHdrNode, s);

	s.Format(_T("Overlay number (e_ovno) = {%s}"), HexaString(m_header.e_ovno, opt));
	InsertTreeItem(hTreeCtrl, hDosHdrNode, s);

	s.Format(_T("Reserved words (e_res[4]) = {%s, %s, %s, %s}"), 
				HexaString(m_header.e_res[0], opt), 
				HexaString(m_header.e_res[1], opt),
				HexaString(m_header.e_res[2], opt),
				HexaString(m_header.e_res[3], opt));
	InsertTreeItem(hTreeCtrl, hDosHdrNode, s);

	s.Format(_T("OEM identifier (e_oemid) = {%s}"), HexaString(m_header.e_oemid, opt));
	InsertTreeItem(hTreeCtrl, hDosHdrNode, s);

	s.Format(_T("OEM information (e_oeminfo) = {%s}"), HexaString(m_header.e_oeminfo, opt));
	InsertTreeItem(hTreeCtrl, hDosHdrNode, s);

	s.Format(_T("Reserved words (e_res2[10) = {%s, %s, %s, %s, %s, %s, %s, %s, %s, %s}")
		, HexaString(m_header.e_res2[0], opt)
		, HexaString(m_header.e_res2[1], opt)
		, HexaString(m_header.e_res2[2], opt)
		, HexaString(m_header.e_res2[3], opt)
		, HexaString(m_header.e_res2[4], opt)
		, HexaString(m_header.e_res2[5], opt)
		, HexaString(m_header.e_res2[6], opt)
		, HexaString(m_header.e_res2[7], opt)
		, HexaString(m_header.e_res2[8], opt)
		, HexaString(m_header.e_res2[9], opt));
	InsertTreeItem(hTreeCtrl, hDosHdrNode, s);

	s.Format(_T("File address of new exe header (e_lfanew) = {%s}"), HexaString(m_header.e_lfanew, opt));
	InsertTreeItem(hTreeCtrl, hDosHdrNode, s);
}