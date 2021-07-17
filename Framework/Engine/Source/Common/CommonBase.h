// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 공통적으로 사용되는 헤더 파일 모음입니다.
// =====================================================================================
#pragma once

#pragma region 표준
#include <crtdbg.h>
#include <direct.h>

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>

#include <array>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <bitset>
#include <type_traits>
#include <chrono>
#pragma endregion

#pragma region Win32API
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <timeapi.h>
#pragma endregion