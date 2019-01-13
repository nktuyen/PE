#include "stdafx.h"
#include "PE_OptionHeader.h"

std::map<DWORD, CString>	PE_OptionHeader::m_mapOptMagic;
std::map<DWORD, CString>	PE_OptionHeader::m_mapOptSubsystem;

PE_OptionHeader::PE_OptionHeader(BOOL bIsX64)
	:	PE_Entity()
	,	m_bIsX64(bIsX64)
	,	m_nDataDirectoriesOffset(0)
{
	m_mapOptMagic[IMAGE_NT_OPTIONAL_HDR_MAGIC] = _T("IMAGE_NT_OPTIONAL_HDR_MAGIC");
	m_mapOptMagic[IMAGE_NT_OPTIONAL_HDR32_MAGIC] = _T("IMAGE_NT_OPTIONAL_HDR32_MAGIC");
	m_mapOptMagic[IMAGE_NT_OPTIONAL_HDR64_MAGIC] = _T("IMAGE_NT_OPTIONAL_HDR64_MAGIC");
	m_mapOptMagic[IMAGE_ROM_OPTIONAL_HDR_MAGIC] = _T("IMAGE_ROM_OPTIONAL_HDR_MAGIC");

	m_mapOptSubsystem[IMAGE_SUBSYSTEM_UNKNOWN] = _T("IMAGE_SUBSYSTEM_UNKNOWN");
	m_mapOptSubsystem[IMAGE_SUBSYSTEM_NATIVE] = _T("IMAGE_SUBSYSTEM_NATIVE");
	m_mapOptSubsystem[IMAGE_SUBSYSTEM_WINDOWS_GUI] = _T("IMAGE_SUBSYSTEM_WINDOWS_GUI");
	m_mapOptSubsystem[IMAGE_SUBSYSTEM_WINDOWS_CUI] = _T("IMAGE_SUBSYSTEM_WINDOWS_CUI");
	m_mapOptSubsystem[IMAGE_SUBSYSTEM_OS2_CUI] = _T("IMAGE_SUBSYSTEM_OS2_CUI");
	m_mapOptSubsystem[IMAGE_SUBSYSTEM_POSIX_CUI] = _T("IMAGE_SUBSYSTEM_POSIX_CUI");
	m_mapOptSubsystem[IMAGE_SUBSYSTEM_WINDOWS_CE_GUI] = _T("IMAGE_SUBSYSTEM_WINDOWS_CE_GUI");
	m_mapOptSubsystem[IMAGE_SUBSYSTEM_EFI_APPLICATION] = _T("IMAGE_SUBSYSTEM_EFI_APPLICATION");
	m_mapOptSubsystem[IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER] = _T("IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER");
	m_mapOptSubsystem[IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER] = _T("IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER");
	m_mapOptSubsystem[IMAGE_SUBSYSTEM_EFI_ROM] = _T("IMAGE_SUBSYSTEM_EFI_ROM");
	m_mapOptSubsystem[IMAGE_SUBSYSTEM_XBOX] = _T("IMAGE_SUBSYSTEM_XBOX");
	m_mapOptSubsystem[IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION] = _T("IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION");
}


void PE_OptionHeader::Initialize(LPCVOID pOptHdr)
{
	for (size_t i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)
	{
		m_pDataDirectories[i] = new PE_DataDirectory((IMAGE_DATA_DIRECTORY*)((SIZE_T)pOptHdr + m_nDataDirectoriesOffset + (i*sizeof(IMAGE_DATA_DIRECTORY))));
	}
}

CString PE_OptionHeader::OptionMagicName_Get(DWORD dwMagic)
{
	std::map<DWORD, CString>::iterator it = m_mapOptMagic.find(dwMagic);
	if (m_mapOptMagic.end() == it)
		return CString();

	return it->second;
}

CString PE_OptionHeader::OptionSubsystemName_Get(DWORD dwSubsystem)
{
	std::map<DWORD, CString>::iterator it = m_mapOptSubsystem.find(dwSubsystem);
	if (m_mapOptSubsystem.end() == it)
		return CString();

	return it->second;
}


PE_OptionHeader::~PE_OptionHeader()
{
}

void PE_OptionHeader::Present(HWND hTreeCtrl, HTREEITEM hParentNode, PE_PresentOptions* opt)
{
	HTREEITEM hOptHdrNode = NULL;

	if (m_bIsX64)
		hOptHdrNode = InsertTreeItem(hTreeCtrl, hParentNode, _T("IMAGE_OPTIONAL_HEADER64"));
	else
		hOptHdrNode = InsertTreeItem(hTreeCtrl, hParentNode, _T("IMAGE_OPTIONAL_HEADER32"));

	CString s;

	s.Format(_T("Magic =  {%s:%s}"), HexaString(Magic(),opt), OptionMagicName_Get(Magic()));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("MajorLinkerVersion =  {%s}"), HexaString( MajorLinkerVersion(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("SizeOfCode =  {%s}"), HexaString( SizeOfCode(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("SizeOfInitializedData =  {%s}"), HexaString( SizeOfInitializedData(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("SizeOfUninitializedData =  {%s}"), HexaString( SizeOfUninitializedData(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("AddressOfEntryPoint =  {%s}"), HexaString( AddressOfEntryPoint(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("BaseOfCode =  {%s}"), HexaString( BaseOfCode(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("ImageBase =  {%s}"), HexaString( ImageBase(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("SectionAlignment =  {%s}"), HexaString( SectionAlignment(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("FileAlignment =  {%s}"), HexaString( FileAlignment(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("MajorOperatingSystemVersion =  {%s}"), HexaString( MajorOperatingSystemVersion(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("MinorOperatingSystemVersion =  {%s}"), HexaString( MinorOperatingSystemVersion(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("MajorImageVersion =  {%s}"), HexaString( MajorImageVersion(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("MinorImageVersion =  {%s}"), HexaString( MinorImageVersion(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("MajorSubsystemVersion =  {%s}"), HexaString( MajorSubsystemVersion(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("MinorSubsystemVersion =  {%s}"), HexaString( MinorSubsystemVersion(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("Win32VersionValue =  {%s}"), HexaString( Win32VersionValue(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("SizeOfImage =  {%s}"), HexaString( SizeOfImage(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("SizeOfHeaders =  {%s}"), HexaString( SizeOfHeaders(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("CheckSum =  {%s}"), HexaString( CheckSum(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("Subsystem =  {%s:%s}"),HexaString( Subsystem(), opt), OptionSubsystemName_Get(Subsystem()));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("DllCharacteristics =  {%s}"), HexaString( DllCharacteristics(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("SizeOfStackReserve =  {%s}"), HexaString( SizeOfStackReserve(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("SizeOfStackCommit =  {%s}"), HexaString( SizeOfStackCommit(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("SizeOfHeapReserve =  {%s}"), HexaString( SizeOfHeapReserve(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("SizeOfHeapCommit =  {%s}"), HexaString( SizeOfHeapCommit(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	s.Format(_T("LoaderFlags =  {%s}"), HexaString( LoaderFlags(), opt));
	InsertTreeItem(hTreeCtrl, hOptHdrNode, s);

	for (size_t i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)
	{
		if (nullptr != opt) {
			s.Format(_T("(%ld)"), i);
			opt->setSubfix(s);
		}
		m_pDataDirectories[i]->Present(hTreeCtrl, hOptHdrNode, opt);
	}
}