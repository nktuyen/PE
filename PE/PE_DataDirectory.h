#pragma once
#include "PE_Entity.h"
class PE_DataDirectory : public PE_Entity
{
private:
	IMAGE_DATA_DIRECTORY	m_DataDirectory;
public:
	PE_DataDirectory(IMAGE_DATA_DIRECTORY* pDataDir = nullptr);
	virtual ~PE_DataDirectory();
	virtual void Present(HWND hTreeCtrl, HTREEITEM hParentNode, PE_PresentOptions* opt = nullptr);

	inline DWORD VirtualAddress() { return m_DataDirectory.VirtualAddress; }
	inline DWORD Size() { return m_DataDirectory.Size; }
};

