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

#pragma region �α� ī�װ��� ���� �����Դϴ�.

#ifdef _DEBUG
#define RX_SIMPLE_TRACE(szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Trace(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_SIMPLE_ASSERT(expression)\
    if (!(expression))\
    {\
        ServiceLocator::I().ILoggerInstance()->Assert(nullptr, #expression, __TIME__, __FILE__, __LINE__);\
    }
#else
#define RX_SIMPLE_TRACE(szFormat, ...) __noop
#define RX_SIMPLE_ASSERT(expression) __noop
#endif

#define RX_SIMPLE_INFO(szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Info(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_SIMPLE_WARNING(szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Warning(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_SIMPLE_ERROR(szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Error(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_SIMPLE_ERRORTYPE(error)\
    ServiceLocator::I().IErrorHandlerInstance()->SetLastError(error);\
    RX_SIMPLE_ERROR(nullptr);

#define RX_SIMPLE_FATAL(szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Fatal(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)
#pragma endregion

#pragma region �α� ī�װ��� �ִ� �����Դϴ�.

#ifdef _DEBUG
#define RX_TRACE(logCategory, szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Trace(&g_##logCategory, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_ASSERT(logCategory, expression)\
    if (!(expression))\
    {\
        ServiceLocator::I().ILoggerInstance()->Assert(&g_##logCategory, #expression, __TIME__, __FILE__, __LINE__);\
    }
#else
#define RX_TRACE(logCategory, szFormat, ...) __noop
#define RX_ASSERT(logCategory, expression) __noop
#endif

#define RX_INFO(logCategory, szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Info(&g_##logCategory, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_WARNING(logCategory, szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Warning(&g_##logCategory, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_ERROR(logCategory, szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Error(&g_##logCategory, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_ERRORTYPE(logCategory, error)\
    ServiceLocator::I().IErrorHandlerInstance()->SetLastError(error);\
    RX_ERROR(logCategory, nullptr);

#define RX_FATAL(logCategory, szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Fatal(&g_##logCategory, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)
#pragma endregion