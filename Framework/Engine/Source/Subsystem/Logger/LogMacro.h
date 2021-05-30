// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ΰŰ� �ʿ��� ��ũ�� �Լ� �����Դϴ�.
// =====================================================================================
#pragma once

// LogCategoryBase�� ��ӹ޴� ���ο� �α� ī�װ� Ŭ������ �����մϴ�.
#define DECLARE_LOG_CATEGORY(CategoryName)\
	class CategoryName##Type : public LogCategoryBase\
	{\
	public:\
		CategoryName##Type() : LogCategoryBase(#CategoryName) { }\
	};\
	\
	extern CategoryName##Type g_##CategoryName

// DECLARE_LOG_CATEGORY()���� ������ Ŭ������ ��ü�� ����ϴ�.
// ������ ��ü�� ���� ���� ��ũ�ο� ������ �̸��� �����ϰ� ����ϴ�.
#define DEFINE_LOG_CATEGORY(CategoryName) CategoryName##Type g_##CategoryName

#define ACTIVATE_LOG_CATEGORY(CategoryName) g_##CategoryName.Activate()
#define DEACTIVATE_LOG_CATEGORY(CategoryName) g_##CategoryName.Deactivate()

#pragma region �α� ī�װ��� ���� �����Դϴ�.
#ifdef _DEBUG
#define RX_SIMPLE_TRACE(szFormat, ...)\
    FIND_SUBSYSTEM(ILogger)->Trace(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_SIMPLE_ASSERT(expression)\
    if (!(expression))\
    {\
        FIND_SUBSYSTEM(ILogger)->Assert(nullptr, #expression, __TIME__, __FILE__, __LINE__);\
    }
#else
#define RX_SIMPLE_TRACE(szFormat, ...) __noop
#define RX_SIMPLE_ASSERT(expression) __noop
#endif

#define RX_SIMPLE_INFO(szFormat, ...)\
    FIND_SUBSYSTEM(ILogger)->Info(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_SIMPLE_WARNING(szFormat, ...)\
    FIND_SUBSYSTEM(ILogger)->Warning(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_SIMPLE_ERROR(errorCode, ...)\
    FIND_SUBSYSTEM(IErrorHandler)->ModifyLastError(errorCode);\
    FIND_SUBSYSTEM(ILogger)->Error(nullptr,\
        MakeFormatString(FIND_SUBSYSTEM(IErrorHandler)->FindErrorContent(errorCode), __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_SIMPLE_FATAL(szFormat, ...)\
    FIND_SUBSYSTEM(ILogger)->Fatal(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)
#pragma endregion

#pragma region �α� ī�װ��� �ִ� �����Դϴ�.
#ifdef _DEBUG
#define RX_TRACE(logCategory, szFormat, ...)\
    FIND_SUBSYSTEM(ILogger)->Trace(&g_##logCategory, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_ASSERT(logCategory, expression)\
    if (!(expression))\
    {\
        FIND_SUBSYSTEM(ILogger)->Assert(&g_##logCategory, #expression, __TIME__, __FILE__, __LINE__);\
    }
#else
#define RX_TRACE(logCategory, szFormat, ...) __noop
#define RX_ASSERT(logCategory, expression) __noop
#endif

#define RX_INFO(logCategory, szFormat, ...)\
    FIND_SUBSYSTEM(ILogger)->Info(&g_##logCategory, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_WARNING(logCategory, szFormat, ...)\
    FIND_SUBSYSTEM(ILogger)->Warning(&g_##logCategory, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_ERROR(logCategory, errorCode, ...)\
    FIND_SUBSYSTEM(IErrorHandler)->ModifyLastError(errorCode);\
    FIND_SUBSYSTEM(ILogger)->Error(&g_##logCategory,\
        MakeFormatString(FIND_SUBSYSTEM(IErrorHandler)->FindErrorContent(errorCode), __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_FATAL(logCategory, szFormat, ...)\
    FIND_SUBSYSTEM(ILogger)->Fatal(&g_##logCategory, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)
#pragma endregion