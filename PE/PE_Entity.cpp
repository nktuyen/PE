#include "stdafx.h"
#include "PE_Entity.h"

std::map<DWORD, CString> PE_Entity::m_mapFileMagic;

PE_Entity::PE_Entity()
	: m_bValid(FALSE)
{
	m_mapFileMagic[IMAGE_DOS_SIGNATURE] = _T("IMAGE_DOS_SIGNATURE(MZ)");
	m_mapFileMagic[IMAGE_OS2_SIGNATURE] = _T("IMAGE_OS2_SIGNATURE(NE)");
	m_mapFileMagic[IMAGE_OS2_SIGNATURE_LE] = _T("IMAGE_OS2_SIGNATURE_LE(LE)");
	m_mapFileMagic[IMAGE_VXD_SIGNATURE] = _T("IMAGE_VXD_SIGNATURE(LE)");
	m_mapFileMagic[IMAGE_NT_SIGNATURE] = _T("IMAGE_NT_SIGNATURE(PE00)");

	m_mapFileMagic[IMAGE_NT_OPTIONAL_HDR32_MAGIC] = _T("IMAGE_NT_OPTIONAL_HDR32_MAGIC(PE32)");
	m_mapFileMagic[IMAGE_NT_OPTIONAL_HDR64_MAGIC] = _T("IMAGE_NT_OPTIONAL_HDR64_MAGIC(PE32+)");
	m_mapFileMagic[IMAGE_ROM_OPTIONAL_HDR_MAGIC] = _T("IMAGE_ROM_OPTIONAL_HDR_MAGIC(ROM)");
}


PE_Entity::~PE_Entity()
{
	
}

CString PE_Entity::MagicName_Get(DWORD w)
{
	std::map<DWORD, CString>::iterator it = m_mapFileMagic.find(w);
	if (m_mapFileMagic.end() == it)
		return CString();

	return it->second;
}

HTREEITEM PE_Entity::InsertTreeItem(HWND hTreeCtrl, HTREEITEM hParentNode, LPCTSTR lpszText)
{
	TVINSERTSTRUCT tvi = { 0 };
	tvi.hParent = hParentNode;
	tvi.item.mask = TVIF_TEXT;
	TCHAR szBuff[255] = { 0 };
	_tcscpy_s(szBuff, 255, lpszText);
	tvi.item.pszText = szBuff;
	return TreeView_InsertItem(hTreeCtrl, &tvi);
}

CString PE_Entity::HexaString(BYTE n, PE_PresentOptions* opt)
{
	CString str;

	if ((nullptr != opt) && (opt->Hexa()))
		str.Format(_T("0x%x"), n);
	else
		str.Format(_T("%d"));

	return str;
}

CString PE_Entity::HexaString(WORD n, PE_PresentOptions* opt)
{
	CString str;

	if ((nullptr != opt) && (opt->Hexa()))
		str.Format(_T("0x%X"), n);
	else
		str.Format(_T("%d"), n);

	return str;
}

CString PE_Entity::HexaString(DWORD n, PE_PresentOptions* opt)
{
	CString str;

	if ((nullptr != opt) && (opt->Hexa()))
		str.Format(_T("0x%X"), n);
	else
		str.Format(_T("%ld"), n);

	return str;
}

CString PE_Entity::HexaString(QWORD n, PE_PresentOptions* opt)
{
	CString str;

	if ((nullptr != opt) && (opt->Hexa()))
		str.Format(_T("0x%X"), n);
	else
		str.Format(_T("%I64d"), n);

	return str;
}

CString PE_Entity::HexaString(LONG n, PE_PresentOptions* opt)
{
	CString str;

	if ((nullptr != opt) && (opt->Hexa()))
		str.Format(_T("0x%X"), n);
	else
		str.Format(_T("%ld"), n);

	return str;
}