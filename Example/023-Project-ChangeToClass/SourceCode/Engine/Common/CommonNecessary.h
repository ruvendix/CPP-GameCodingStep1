// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 라이브러리로 제공되는 헤더 파일 모음입니다.
// 표준 헤더 파일 및 윈도우 헤더 파일만 해당됩니다.
// FMOD 같은 헤더 파일은 3rd Party로 분류됩니다.
// =====================================================================================

#ifndef NECESSARY__H__
#define NECESSARY__H__

#include <crtdbg.h>
#include <strsafe.h>

// windows.h에서 최소로 필요한 부분만 포함시켜주는 방법!
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <timeapi.h>

#include <type_traits>
#include <cstdio>
#include <algorithm>
#include <string>
#include <memory>
#include <tuple>
#include <functional>
#include <vector>
#include <bitset>
#include <forward_list>
#include <array>
#include <new>
#include <random>
#include <chrono>
#include <stack>

#pragma comment(lib, "winmm.lib") // 윈도우 멀티미디어 링크

#endif