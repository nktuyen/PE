#pragma once
#include "PE_Entity.h"
#include "PE_DataDirectory.h"

class PE_OptionHeader : public PE_Entity
{
private:
	BOOL				m_bIsX64;
	SIZE_T				m_nDataDirectoriesOffset;
	PE_DataDirectory*	m_pDataDirectories[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
	static std::map<DWORD, CString>	m_mapOptMagic;
	static std::map<DWORD, CString>	m_mapOptSubsystem;
	static std::map<DWORD, CString>	m_mapOptDirEntries;
protected:
	PE_OptionHeader( BOOL bIsX64 = FALSE);
	virtual ~PE_OptionHeader();
	void Initialize(LPCVOID pOptHdr = nullptr);
	void Finalize();
	static CString	OptionMagicName_Get(DWORD dwID);
	static CString	OptionSubsystemName_Get(DWORD dwID);
	static CString	OptionDirectoryName_Get(DWORD dwID);
public:
	virtual WORD        Magic() = 0;
	virtual BYTE        MajorLinkerVersion() = 0;
	virtual BYTE        MinorLinkerVersion() = 0;
	virtual DWORD       SizeOfCode() = 0;
	virtual DWORD       SizeOfInitializedData() = 0;
	virtual DWORD       SizeOfUninitializedData() = 0;
	virtual DWORD       AddressOfEntryPoint() = 0;
	virtual DWORD       BaseOfCode() = 0;
	virtual ULONGLONG   ImageBase() = 0;
	virtual DWORD       SectionAlignment() = 0;
	virtual DWORD       FileAlignment() = 0;
	virtual WORD        MajorOperatingSystemVersion() = 0;
	virtual WORD        MinorOperatingSystemVersion() = 0;
	virtual WORD        MajorImageVersion() = 0;
	virtual WORD        MinorImageVersion() = 0;
	virtual WORD        MajorSubsystemVersion() = 0;
	virtual WORD        MinorSubsystemVersion() = 0;
	virtual DWORD       Win32VersionValue() = 0;
	virtual DWORD       SizeOfImage() = 0;
	virtual DWORD       SizeOfHeaders() = 0;
	virtual DWORD       CheckSum() = 0;
	virtual WORD        Subsystem() = 0;
	virtual WORD        DllCharacteristics() = 0;
	virtual ULONGLONG   SizeOfStackReserve() = 0;
	virtual ULONGLONG   SizeOfStackCommit() = 0;
	virtual ULONGLONG   SizeOfHeapReserve() = 0;
	virtual ULONGLONG   SizeOfHeapCommit() = 0;
	virtual DWORD       LoaderFlags() = 0;
	virtual DWORD       NumberOfRvaAndSizes() = 0;

	PE_DataDirectory**	DataDirectory() { return m_pDataDirectories; }
	virtual void Present(HWND hTreeCtrl, HTREEITEM hParentNode, PE_PresentOptions* opt = nullptr);
};

