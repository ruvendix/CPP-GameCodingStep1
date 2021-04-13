// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 로거에게 필요한 매크로 함수 모음입니다.
// =====================================================================================
#pragma once

// LogCategoryBase를 상속받는 새로운 로그 카테고리 클래스를 선언합니다.
#define DECLARE_LOG_CATEGORY(CategoryName)\
	class CategoryName##Type : public LogCategoryBase\
	{\
	public:\
		CategoryName##Type() : LogCategoryBase(#CategoryName) EMPTY_FUNC\
	};\
	\
	extern CategoryName##Type CategoryName

// DECLARE_LOG_CATEGORY()에서 선언한 클래스를 객체로 만듭니다.
// 실제로 객체를 만들 때는 매크로에 전달한 이름과 동일하게 만듭니다.
#define DEFINE_LOG_CATEGORY(CategoryName) CategoryName##Type CategoryName

#pragma region 로그 카테고리가 없는 버전입니다.
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

#pragma region 로그 카테고리가 있는 버전입니다.
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