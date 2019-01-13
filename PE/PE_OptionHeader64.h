#pragma once
#include "PE_OptionHeader.h"
class PE_OptionHeader64 : public PE_OptionHeader
{
	friend class PE_NtHeader;
private:
	IMAGE_OPTIONAL_HEADER64	m_header;
protected:
	PE_OptionHeader64(IMAGE_OPTIONAL_HEADER64* pOptHdr = nullptr);
	virtual ~PE_OptionHeader64();
public:
	inline WORD        Magic() { return m_header.Magic; }
	inline BYTE        MajorLinkerVersion(){ return m_header.MajorLinkerVersion;}
	inline BYTE        MinorLinkerVersion(){ return m_header.MinorLinkerVersion;}
	inline DWORD       SizeOfCode(){return m_header.SizeOfCode;}
	inline DWORD       SizeOfInitializedData(){return m_header.SizeOfInitializedData;}
	inline DWORD       SizeOfUninitializedData(){return m_header.SizeOfUninitializedData;}
	inline DWORD       AddressOfEntryPoint(){return m_header.AddressOfEntryPoint;}
	inline DWORD       BaseOfCode(){return m_header.BaseOfCode;}
	inline ULONGLONG   ImageBase(){return m_header.ImageBase;}
	inline DWORD       SectionAlignment(){return m_header.SectionAlignment;}
	inline DWORD       FileAlignment(){return m_header.FileAlignment;}
	inline WORD        MajorOperatingSystemVersion(){return m_header.MajorOperatingSystemVersion;}
	inline WORD        MinorOperatingSystemVersion(){return m_header.MinorOperatingSystemVersion;}
	inline WORD        MajorImageVersion(){return m_header.MajorImageVersion;}
	inline WORD        MinorImageVersion(){return m_header.MinorImageVersion;}
	inline WORD        MajorSubsystemVersion(){return m_header.MajorSubsystemVersion;}
	inline WORD        MinorSubsystemVersion(){return m_header.MinorSubsystemVersion;}
	inline DWORD       Win32VersionValue(){return m_header.Win32VersionValue;}
	inline DWORD       SizeOfImage(){return m_header.SizeOfImage;}
	inline DWORD       SizeOfHeaders(){return m_header.SizeOfHeaders;}
	inline DWORD       CheckSum(){return m_header.CheckSum;}
	inline WORD        Subsystem(){return m_header.Subsystem;}
	inline WORD        DllCharacteristics(){return m_header.DllCharacteristics;}
	inline ULONGLONG   SizeOfStackReserve(){return m_header.SizeOfStackReserve;}
	inline ULONGLONG   SizeOfStackCommit(){return m_header.SizeOfStackCommit;}
	inline ULONGLONG   SizeOfHeapReserve(){return m_header.SizeOfHeapReserve;}
	inline ULONGLONG   SizeOfHeapCommit(){return m_header.SizeOfHeapCommit;}
	inline DWORD       LoaderFlags(){return m_header.LoaderFlags;}
	inline DWORD       NumberOfRvaAndSizes(){return m_header.NumberOfRvaAndSizes;}
};

