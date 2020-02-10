// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#ifndef PCH__H__
#define PCH__H__

#include <crtdbg.h>

// windows.h���� �ּҷ� �ʿ��� �κи� ���Խ����ִ� ���!
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

#include <type_traits>
#include <cstdio>
#include <algorithm>

// ���� ���� �߿��ؿ�! (���̸� ��...)
#include "GlobalType.h"
#include "GlobalMacro.h"
#include "GlobalEnum.h"
#include "GlobalFunc.h"

#endif