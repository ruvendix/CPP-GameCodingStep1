// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ΰſ��� �ʿ��� ��ũ�� �Լ� �����Դϴ�.
// =====================================================================================
#pragma once

// LogCategoryBase�� ��ӹ޴� ���ο� �α� ī�װ� Ŭ������ �����մϴ�.
#define DECLARE_LOG_CATEGORY(CategoryName)\
	class CategoryName##Type : public LogCategoryBase\
	{\
	public:\
		CategoryName##Type() : LogCategoryBase(#CategoryName) EMPTY_FUNC\
	};\
	\
	extern CategoryName##Type CategoryName

// DECLARE_LOG_CATEGORY()���� ������ Ŭ������ ��ü�� ����ϴ�.
// ������ ��ü�� ���� ���� ��ũ�ο� ������ �̸��� �����ϰ� ����ϴ�.
#define DEFINE_LOG_CATEGORY(CategoryName) CategoryName##Type CategoryName

#pragma region �α� ī�װ��� ���� �����Դϴ�.
#define RX_SIMPLE_TRACE(szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Trace(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_SIMPLE_ASSERT(szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Assert(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_SIMPLE_INFO(szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Info(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_SIMPLE_WARNING(szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Warning(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_SIMPLE_ERROR(szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Error(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_SIMPLE_FATAL(szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Fatal(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)
#pragma endregion

#pragma region �α� ī�װ��� �ִ� �����Դϴ�.
#define RX_TRACE(logCategory, szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Trace(&logCategory, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_ASSERT(logCategory, szFormat, ...)\
	ServiceLocator::I().ILoggerInstance()->Assert(&logCategory, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_INFO(logCategory, szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Info(&logCategory, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_WARNING(logCategory, szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Warning(&logCategory, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_ERROR(logCategory, szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Error(&logCategory, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)

#define RX_FATAL(logCategory, szFormat, ...)\
    ServiceLocator::I().ILoggerInstance()->Fatal(&logCategory, MakeFormatString(szFormat, __VA_ARGS__), __TIME__, __FILE__, __LINE__)
#pragma endregion