// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 로그 카테고리의 기반입니다.
// =====================================================================================
#include "EnginePCH.h"
#include "BaseLogCategory.h"

Bool BaseLogCategory::CheckActivate() const
{
    if (m_bActivation == true)
    {
        return true;
    }

    return false;
}
