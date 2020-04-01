// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���̺귯���� �����Ǵ� ��� ���� �����Դϴ�.
// ǥ�� ��� ���� �� ������ ��� ���ϸ� �ش�˴ϴ�.
// FMOD ���� ��� ������ 3rd Party�� �з��˴ϴ�.
// =====================================================================================

#ifndef NECESSARY__H__
#define NECESSARY__H__

#include <crtdbg.h>
#include <strsafe.h>

// windows.h���� �ּҷ� �ʿ��� �κи� ���Խ����ִ� ���!
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

#pragma comment(lib, "winmm.lib") // ������ ��Ƽ�̵�� ��ũ

#endif