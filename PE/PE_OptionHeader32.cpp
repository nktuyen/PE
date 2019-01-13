#include "stdafx.h"
#include "PE_OptionHeader32.h"


PE_OptionHeader32::PE_OptionHeader32(IMAGE_OPTIONAL_HEADER32* pOptHdr)
	:PE_OptionHeader()
{
	ZeroMemory(&m_header, sizeof(IMAGE_OPTIONAL_HEADER32));
	if (nullptr != pOptHdr)
	{
		CopyMemory(&m_header, pOptHdr, sizeof(IMAGE_OPTIONAL_HEADER32));
	}

	__super::Initialize(pOptHdr);
}


PE_OptionHeader32::~PE_OptionHeader32()
{
	__super::Finalize();
}