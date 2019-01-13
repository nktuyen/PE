#pragma once
#include "PE_Entity.h"
class PE_FileHeader : public PE_Entity
{
	friend class PE_NtHeader;
private:
	IMAGE_FILE_HEADER	m_FileHeader;
	static std::map<DWORD, CString> m_mapMachine;
	static std::map<DWORD, CString> m_mapCharacteristic;
private:
	PE_FileHeader(IMAGE_FILE_HEADER* pFileHdr = nullptr);
	virtual ~PE_FileHeader();
protected:
	static CString MachineName_Get(DWORD dwID);
	static CString CharacteristicString_Get(DWORD dw);
public:
	inline WORD  Machine() { return m_FileHeader.Machine; }
	inline WORD  NumberOfSections() { return m_FileHeader.NumberOfSections; }
	inline DWORD  TimeDateStamp() { return m_FileHeader.TimeDateStamp; }
	inline DWORD  PointerToSymbolTable() { return m_FileHeader.PointerToSymbolTable; }
	inline DWORD  NumberOfSymbols() { return m_FileHeader.NumberOfSymbols; }
	inline WORD  SizeOfOptionalHeader() { return m_FileHeader.SizeOfOptionalHeader; }
	inline WORD  Characteristics() { return m_FileHeader.Characteristics; }

	virtual void Present(HWND hTreeCtrl, HTREEITEM hParentNode, PE_PresentOptions* opt = nullptr);
};

