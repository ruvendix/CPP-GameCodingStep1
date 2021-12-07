// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 계층 관계 클래스를 나타내는 용도입니다.
// =====================================================================================
#include "EnginePCH.h"
#include "RClass.h"

void RClass::StartUp()
{
	InitClassMetadata();
}

bool RClass::IsUpperClass(RClass* pUpper) // 자신 기준으로 위
{
	bool bRet = false;
	for (RClass* p = this; p != nullptr; p = p->GetParentClass())
	{
		if (p == pUpper)
		{
			bRet = true;
			break;
		}
	}

	return bRet;
}