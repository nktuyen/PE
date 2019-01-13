#pragma once

#include "PE_Entity.h"

class PE_DosHeader;
class PE_NtHeader;

class PE_File : public PE_Entity
{
private:
	PE_DosHeader*	m_pDosHeader;
	PE_NtHeader*	m_pNtHeader;
public:
	PE_File(LPCVOID lpFileBase);
	~PE_File();
	virtual void Present(HWND hTreeCtrl, HTREEITEM hParentNode, PE_PresentOptions* opt = nullptr);
};

