#include "stdafx.h"
#include "PE_DataDirectory.h"


PE_DataDirectory::PE_DataDirectory(IMAGE_DATA_DIRECTORY* pDataDir)
	:PE_Entity()
{
	ZeroMemory(&m_DataDirectory, sizeof(IMAGE_DATA_DIRECTORY));
	if (nullptr != pDataDir)
	{
		CopyMemory(&m_DataDirectory, pDataDir, sizeof(IMAGE_DATA_DIRECTORY));
	}
}


PE_DataDirectory::~PE_DataDirectory()
{
}



void PE_DataDirectory::Present(HWND hTreeCtrl, HTREEITEM hParentNode, PE_PresentOptions* opt)
{
	CString s;
	s.Format(_T("IMAGE_DATA_DIRECTORY%s"), (nullptr != opt) ? opt->Subfix() : _T(""));
	HTREEITEM hImgDataNode = InsertTreeItem(hTreeCtrl, hParentNode, s);

	s.Format(_T("Virtual Address = {%s}"), HexaString(m_DataDirectory.VirtualAddress, opt));
	InsertTreeItem(hTreeCtrl, hImgDataNode, s);

	s.Format(_T("Size = {%s}"), HexaString(m_DataDirectory.Size, opt));
	InsertTreeItem(hTreeCtrl, hImgDataNode, s);
}