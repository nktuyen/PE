#include "stdafx.h"
#include "PE_OptionHeader64.h"


PE_OptionHeader64::PE_OptionHeader64(IMAGE_OPTIONAL_HEADER64* pOptHdr)
	:PE_OptionHeader()
{
	ZeroMemory(&m_header, sizeof(IMAGE_OPTIONAL_HEADER64));
	if (nullptr != pOptHdr)
	{
		CopyMemory(&m_header, pOptHdr, sizeof(IMAGE_OPTIONAL_HEADER64));
	}

	__super::Initialize(pOptHdr);
}


PE_OptionHeader64::~PE_OptionHeader64()
{
}