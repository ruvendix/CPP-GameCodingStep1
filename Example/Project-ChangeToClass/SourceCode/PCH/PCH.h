// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#ifndef PCH__H__
#define PCH__H__

#include <crtdbg.h>

// windows.h에서 최소로 필요한 부분만 포함시켜주는 방법!
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

#include <type_traits>
#include <cstdio>
#include <algorithm>

// 포함 순서 중요해요! (꼬이면 망...)
#include "GlobalType.h"
#include "GlobalMacro.h"
#include "GlobalEnum.h"
#include "GlobalFunc.h"

#endif