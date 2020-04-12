// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 미리 컴파일된 헤더입니다.
// 자주 변경되지 않을 헤더 파일만 포함해야 합니다.
// =====================================================================================

#ifndef PCH__H__
#define PCH__H__

// 자주 출력되는 경고는 무효시킵니다.
#pragma warning(disable : 6011) // 널포인터 역참조
#pragma warning(disable : 26495) // 멤버변수 초기화 필수

// Common 헤더 파일은 0순위!
#include "Common\CommonNecessary.h"
#include "Common\CommonType.h"
#include "Common\CommonStruct.h"
#include "Common\CommonMacro.h"
#include "Common\CommonFunc.h"
#include "Common\CommonLog.h"
#include "Common\CommonTemplate.h"

// 그 다음 중요도가 높은 헤더 파일을 포함!
#include "Math\Math.h"

#endif