#include "stdafx.h"
#include "PE_NtHeader.h"


PE_NtHeader::PE_NtHeader(LPCVOID pNtHdr)
	: PE_Entity()
{
	m_dwSignature = 0;
	CopyMemory(&m_dwSignature, pNtHdr, sizeof(DWORD));
	m_pFileHeader = new PE_FileHeader((IMAGE_FILE_HEADER*)((SIZE_T)pNtHdr + sizeof(DWORD)));
	switch (m_pFileHeader->Machine())
	{
	case IMAGE_FILE_MACHINE_AMD64:
		m_pOptionHeader = new PE_OptionHeader64((IMAGE_OPTIONAL_HEADER64*)((SIZE_T)pNtHdr + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER)));
	default:
		m_pOptionHeader = new PE_OptionHeader32((IMAGE_OPTIONAL_HEADER32*)((SIZE_T)pNtHdr + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER)));
		break;
	}
}


PE_NtHeader::~PE_NtHeader()
{
	if (nullptr != m_pFileHeader)
	{
		if (nullptr != m_pOptionHeader)
		{
			switch (m_pFileHeader->Machine())
			{
			case IMAGE_FILE_MACHINE_AMD64:
				delete (PE_OptionHeader64*)m_pOptionHeader;
			default:
				delete (PE_OptionHeader32*)m_pOptionHeader;
				break;
			}

			m_pOptionHeader = nullptr;
		}

		delete m_pFileHeader;
		m_pFileHeader = nullptr;
	}
}

void PE_NtHeader::Present(HWND hTreeCtrl, HTREEITEM hParentNode, PE_PresentOptions* opt)
{
	HTREEITEM hNtHdrNode = InsertTreeItem(hTreeCtrl, hParentNode, _T("IMAGE_NT_HEADER"));
	CString s;

	s.Format(_T("Signature = {%s:%s}"), HexaString(m_dwSignature, opt), MagicName_Get(m_dwSignature));
	InsertTreeItem(hTreeCtrl, hNtHdrNode, s);

	m_pFileHeader->Present(hTreeCtrl, hNtHdrNode, opt);
	m_pOptionHeader->Present(hTreeCtrl, hNtHdrNode, opt);
}