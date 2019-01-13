#pragma once

#include "PE_FileHeader.h"
#include "PE_OptionHeader64.h"
#include "PE_OptionHeader32.h"

class PE_NtHeader : public PE_Entity
{
	friend class PE_File;
private:
	DWORD				m_dwSignature;
	PE_FileHeader*		m_pFileHeader;
	PE_OptionHeader*	m_pOptionHeader;
private:
	PE_NtHeader(LPCVOID pNtHdr = nullptr);
	virtual ~PE_NtHeader();
public:
	inline DWORD Signature() { return m_dwSignature; }
	inline PE_FileHeader* const FileHeader() { return m_pFileHeader; }
	inline PE_OptionHeader* const OptionHeader() { return m_pOptionHeader; }

	virtual void Present(HWND hTreeCtrl, HTREEITEM hParentNode, PE_PresentOptions* = nullptr);
};

