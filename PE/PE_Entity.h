#pragma once

#include <map>
class PE_PresentOptions
{
	friend class PE_Entity;
private:
	bool		m_bHexa;
	TCHAR		m_szPrefix[256];
	TCHAR		m_szSubfix[256];
public:
	PE_PresentOptions()
	{
		m_bHexa = false;
		ZeroMemory(m_szPrefix, 256*sizeof(TCHAR));
		ZeroMemory(m_szSubfix, 256 * sizeof(TCHAR));
	}
	virtual ~PE_PresentOptions()
	{

	}

	bool Hexa() const { return m_bHexa; }
	void setHexa(bool bHexa) { m_bHexa = bHexa; }
	LPCTSTR Prefix() const { return m_szPrefix; }
	void setPrefix(LPCTSTR lpszPrefix) { _tcscpy_s(m_szPrefix, 255, lpszPrefix); }
	LPCTSTR Subfix() const { return m_szSubfix; }
	void setSubfix(LPCTSTR lpszSubfix) { _tcscpy_s(m_szSubfix, 255, lpszSubfix); }
};

class PE_Entity
{
private:
	BOOL					m_bValid;
	static std::map<DWORD, CString> m_mapFileMagic;
protected:
	HTREEITEM InsertTreeItem(HWND hTreeCtrl, HTREEITEM hParentNode, LPCTSTR lpszText);
protected:
	inline void Validity_Set(BOOL bValid) { m_bValid = bValid; }
	static CString MagicName_Get(DWORD w);
	static CString HexaString(BYTE by, PE_PresentOptions* opt = nullptr);
	static CString HexaString(WORD w, PE_PresentOptions* opt = nullptr);
	static CString HexaString(DWORD dw, PE_PresentOptions* opt = nullptr);
	static CString HexaString(QWORD qw, PE_PresentOptions* opt = nullptr);
	static CString HexaString(LONG lng, PE_PresentOptions* opt = nullptr);
public:
	PE_Entity();
	virtual ~PE_Entity();
	virtual void Validate() { ; }
	virtual void Present(HWND hTreeCtrl, HTREEITEM hParentNode, PE_PresentOptions* = nullptr) { ; }
public:
	inline BOOL Validity_Get() { return m_bValid; }
};

