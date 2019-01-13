#include "stdafx.h"
#include "PE_File.h"
#include "PE_DosHeader.h"
#include "PE_NtHeader.h"

PE_File::PE_File(LPCVOID lpFileBase)
{
	IMAGE_DOS_HEADER* pDosHdr = (IMAGE_DOS_HEADER*)lpFileBase;
	this->m_pDosHeader = new PE_DosHeader(pDosHdr);
	this->m_pNtHeader = new	 PE_NtHeader((IMAGE_NT_HEADERS32*)((SIZE_T)lpFileBase + (SIZE_T)pDosHdr->e_lfanew));
}


PE_File::~PE_File()
{
	delete this->m_pDosHeader;
	delete this->m_pNtHeader;
}

void PE_File::Present(HWND hTreeCtrl, HTREEITEM hParentNode, PE_PresentOptions* opt)
{
	this->m_pDosHeader->Present(hTreeCtrl, hParentNode, opt);
	this->m_pNtHeader->Present(hTreeCtrl, hParentNode, opt);
}