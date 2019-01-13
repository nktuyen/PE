#pragma once
#include "PE_Entity.h"

class PE_DosHeader : public PE_Entity
{
	friend class PE_File;
private:
	IMAGE_DOS_HEADER	m_header;
private:
	PE_DosHeader(IMAGE_DOS_HEADER* pDosHdr = nullptr);
	virtual ~PE_DosHeader();
public:
	inline WORD Magic() { return m_header.e_magic; }
	inline WORD BytesOnLastPage() { return m_header.e_cblp; }
	inline WORD PagesInFile() { return m_header.e_cp; }
	inline WORD Relocations() { return m_header.e_crlc; }
	inline WORD SizeOfHeader() { return m_header.e_cparhdr; }
	inline WORD MinimumExtra() { return m_header.e_minalloc; }
	inline WORD MaximumExtra() { return m_header.e_maxalloc; }
	inline WORD InitSSValue() { return m_header.e_ss; }
	inline WORD InitSPValue() { return m_header.e_sp; }
	inline WORD Checksum() { return m_header.e_csum; }
	inline WORD InitIPValue() { return m_header.e_ip; }
	inline WORD InitCSValue() { return m_header.e_cs; }
	inline WORD RelocationTableAddr() { return m_header.e_lfarlc; }
	inline WORD OverlayNumber() { return m_header.e_ovno; }
	inline WORD OEMId() { return m_header.e_oemid; }
	inline WORD OEMInfo() { return m_header.e_oeminfo; }
	inline LONG PEHeaderAddr() { return m_header.e_lfanew; }
	inline PWORD Reserved1() { return m_header.e_res; }
	inline PWORD Reserved2() { return m_header.e_res2; }

	virtual void Present(HWND hTreeCtrl, HTREEITEM hParentNode, PE_PresentOptions* opt = nullptr);
};

