// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ΰŰ� �ʿ��� ��ũ�� �Լ� �����Դϴ�.
// =====================================================================================
#pragma once

// BaseLogCategory�� ��ӹ޴� ���ο� �α� ī�װ� Ŭ������ �����մϴ�.
#define DECLARE_LOG_CATEGORY(CategoryName)\
	class CategoryName##Type : public BaseLogCategory\
	{\
	public:\
		CategoryName##Type() : BaseLogCategory(#CategoryName) { }\
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
#define RX_TRACE(szFormat, ...)\
    Logger::I().Trace(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __FILE__, __LINE__)

#define RX_ASSERT(expression)\
    if (!(expression))\
    {\
        Logger::I().Assert(nullptr, #expression, __FILE__, __LINE__);\
    }
#else
#define RX_TRACE(szFormat, ...) __noop
#define RX_ASSERT(expression) __noop
#endif

#define RX_INFO(szFormat, ...)\
    Logger::I().Info(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __FILE__, __LINE__)

#define RX_WARNING(szFormat, ...)\
    Logger::I().Warning(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __FILE__, __LINE__)

#define RX_ERROR(errorCode, ...)\
    ErrorTracer::I().SetLastErrorCode(errorCode);\
    Logger::I().Error(nullptr,\
        MakeFormatString(ErrorTracer::I().LastErrorString(), __VA_ARGS__), __FILE__, __LINE__)

#define RX_FATAL(szFormat, ...)\
    Logger::I().Fatal(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __FILE__, __LINE__)
#pragma endregion

#pragma region �α� ī�װ��� �ִ� �����Դϴ�.
#ifdef _DEBUG
#define RX_TRACE2(logCategory, szFormat, ...)\
    Logger::I().Trace(&g_##logCategory, MakeFormatString(szFormat, __VA_ARGS__), __FILE__, __LINE__)

#define RX_ASSERT2(logCategory, expression)\
    if (!(expression))\
    {\
        Logger::I().Assert(&g_##logCategory, #expression, __FILE__, __LINE__);\
    }
#else
#define RX_TRACE2(logCategory, szFormat, ...) __noop
#define RX_ASSERT2(logCategory, expression) __noop
#endif

#define RX_INFO2(logCategory, szFormat, ...)\
    Logger::I().Info(&g_##logCategory, MakeFormatString(szFormat, __VA_ARGS__), __FILE__, __LINE__)

#define RX_WARNING2(logCategory, szFormat, ...)\
    Logger::I().Warning(&g_##logCategory, MakeFormatString(szFormat, __VA_ARGS__), __FILE__, __LINE__)

#define RX_ERROR2(logCategory, errorCode, ...)\
    ErrorTracer::I().SetLastErrorCode(errorCode);\
    Logger::I().Error(&g_##logCategory,\
        MakeFormatString(ErrorTracer::I().LastErrorString(), __VA_ARGS__), __FILE__, __LINE__)

#define RX_FATAL2(logCategory, szFormat, ...)\
    Logger::I().Fatal(&g_##logCategory, MakeFormatString(szFormat, __VA_ARGS__), __FILE__, __LINE__)
#pragma endregion