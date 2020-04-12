// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 공용으로 사용되는 매크로 모음입니다.
// =====================================================================================

#ifndef COMMON_MACRO__H__
#define COMMON_MACRO__H__

/*
VLD로 대체 가능한지 확인 필요!
*/
#define trace_new new(_NORMAL_BLOCK, __FILE__, __LINE__ )                                            

#define SAFE_DELETE(ptr)\
	if (ptr != nullptr)\
	{\
		delete ptr;\
		ptr = nullptr;\
	}

#define SAFE_SWAP_DELETE(srcPtr, destPtr)\
	SAFE_DELETE(srcPtr)\
	srcPtr = destPtr;\
	destPtr = nullptr

/*
복사 및 이동을 금지하는 매크로에요. (Copy Semantics, Move Semantics)
*/
#define NON_COPYABLE_CLASS(TClass)\
public:\
	TClass(const TClass&) = delete;\
	TClass(const TClass&&) = delete;\
	TClass& operator=(const TClass&) = delete;\
	TClass&& operator=(const TClass&&) = delete;

/*
외부에서만 생성 및 소멸을 막는 매크로에요. (기본 생성자만 막힘)
하지만 상속 관계에서는 접근 가능하게 해줘야 해요.
*/
#define NON_EXTERNAL_CLASS(TClass)\
protected:\
	TClass() = default;\
	virtual ~TClass() = default;

// 상속 관계에서도 접근 불가능한 버전입니다.
#define ONLY_PRIVATE_CLASS(TClass)\
private:\
	TClass() = default;\
	~TClass() = default;

/*
NON_COPYABLE_CLASS와 ONLY_PRIVATE_CLASS를 혼용했어요!
*/
#define NON_COPYABLE_ONLY_PRIVATE_CLASS(TClass) NON_COPYABLE_CLASS(TClass) ONLY_PRIVATE_CLASS(TClass)

/*
싱글톤은 NON_COPYABLE_ONLY_PRIVATE_CLASS입니다!
*/
#define DECLARE_SINGLETON(TClass)\
	NON_COPYABLE_ONLY_PRIVATE_CLASS(TClass)\
\
public:\
	static TClass* I();\
	static void Destroy();\
\
private:\
	static TClass* m_pInst

#define DEFINE_SINGLETON(TClass)\
	TClass* TClass::m_pInst = nullptr;\
\
	TClass* TClass::I()\
	{\
		if (m_pInst != nullptr)\
		{\
			return m_pInst;\
		}\
\
		m_pInst = trace_new TClass;\
\
		return m_pInst;\
	}\
\
	void TClass::Destroy()\
	{\
		SAFE_DELETE(m_pInst);\
		DEBUG_LOG("싱글톤 삭제! (%s)", TO_STRING(TClass));\
	}

/*
싱글톤 중에는 피닉스 싱글톤이라는 게 있어요.
죽었다가 다시 부활한다는 의미를 이용하기 위해 피닉스가 되었다네요...

static은 생성과 소멸 순서를 보장할 수 없어요.
이미 소멸된 피닉스 싱글톤을 다른 곳에서 호출하게 되면 다시 부활시킵니다.
다시 소멸시켜야 할 때는 프로그램이 종료되면 자동으로 소멸되도록 std::atexit()을 이용해요!

중간에 new(m_pInst) placement New라고 하는데,
메모리를 새로 할당하는 게 아니라!
이미 할당된 메모리 공간을 이용하므로 생성자만 호출해요.
따라서 피닉스 싱글톤에서는 동적할당을 이용하지 않습니다.
*/
#define DECLARE_PHOENIX_SINGLETON(TClass)\
	NON_COPYABLE_CLASS(TClass)\
\
public:\
	static TClass* I();\
\
private:\
	TClass()\
	{\
		DEBUG_LOG("싱글톤 생성! (%s)", TO_STRING(TClass));\
	}\
\
	~TClass()\
	{\
		m_pInst = nullptr;\
		m_bDead = true;\
		DEBUG_LOG("싱글톤 소멸! (%s)", TO_STRING(TClass));\
	}\
\
	static void Create()\
	{\
		static TClass inst;\
		m_pInst = &inst;\
	}\
\
	static void Destroy()\
	{\
		m_pInst->~TClass();\
	}\
\
	static bool m_bDead;\
	static TClass* m_pInst

#define DEFINE_PHOENIX_SINGLETON(TClass)\
	TClass* TClass::m_pInst = nullptr;\
	bool TClass::m_bDead = false;\
\
	TClass* TClass::I()\
	{\
		if (m_bDead == true)\
		{\
			Create();\
			new(m_pInst) TClass;\
			std::atexit(Destroy);\
			m_bDead = true;\
		}\
\
		if (m_pInst == nullptr)\
		{\
			Create();\
		}\
\
		return m_pInst;\
	}

#define FRIEND_WITH_HELPER(THelperClass) friend class THelperClass
#define TO_STRING(src) (#src)

// 출력창에서 로그를 확인할 수 있습니다. (디버그 모드 전용)
#if defined(DEBUG) || defined(_DEBUG)
#define DEBUG_LOG(szFormat, ...) CommonFunc::ShowLog("", CommonFunc::MakeFormatString(szFormat, __VA_ARGS__))
#define DEBUG_LOG_CATEGORY(logCategory, szFormat, ...)\
	CommonFunc::ShowLog(g_logCategory##logCategory.getNameTag(), CommonFunc::MakeFormatString(szFormat, __VA_ARGS__))
#else
#define DEBUG_LOG(szFormat, ...) CommonFunc::ShowLog("", CommonFunc::MakeFormatString(szFormat, __VA_ARGS__))
#define DEBUG_LOG_CATEGORY(logCategory, szFormat, ...)\
	CommonFunc::ShowLog(g_logCategory##logCategory.getNameTag(), CommonFunc::MakeFormatString(szFormat, __VA_ARGS__))
#endif

#define RESERVE_RENDERING_STRING(keepTime, func) TriggerTimerMgr::I()->AddTriggerTimer("RenderString", 0.0f, keepTime, func, true, false)

// 에러 핸들러에도 서식 문자열을 지원합니다.
#define DEFAULT_ERROR_HANDLER(errorType, ...)\
	ErrorHandler::m_strError = CommonFunc::MakeFormatString(ErrorHandler::ToString(errorType).data(), __VA_ARGS__);\
	ErrorHandler::OuputDebugString(true);\
	ErrorHandler::DebugBreak(true)

#define ERROR_HANDLER(bDebugBreak, errorType, ...)\
	ErrorHandler::m_strError = CommonFunc::MakeFormatString(ErrorHandler::ToString(errorType).data(), __VA_ARGS__);\
	ErrorHandler::OuputDebugString(true);\
	ErrorHandler::DebugBreak(bDebugBreak)

#define ERROR_HANDLER_RENDERING(x, y, keepTime, bOutputDebug, bDebugBreak, errorType, ...)\
	RESERVE_RENDERING_STRING(keepTime, &ErrorHandler::RenderString);\
	ErrorHandler::m_renderPos = COORD{ x, y };\
	ErrorHandler::m_strError = CommonFunc::MakeFormatString(ErrorHandler::ToString(errorType).data(), __VA_ARGS__);\
	ErrorHandler::OuputDebugString(bOutputDebug);\
	ErrorHandler::DebugBreak(bDebugBreak)

#define DEFAULT_ERROR_HANDLER_RENDERING(x, y, keepTime, errorType, ...) ERROR_HANDLER_RENDERING(x, y, keepTime, true, false, errorType, __VA_ARGS__)


// NameTag를 상속 받는 새로운 로그 클래스를 선언합니다.
#define DECLARE_LOG_CATEGORY(Tag)\
class LogCategory##Tag\
{\
	HAS_NAME_TAG()\
\
public:\
	LogCategory##Tag()\
	{\
		setNameTag(TO_STRING(Log##Tag));\
	}\
	virtual ~LogCategory##Tag() = default;\
};\
\
extern LogCategory##Tag g_logCategory##Tag;

// DECLARE_LOG_CATEGORY()에서 선언한 클래스를 객체로 만듭니다.
#define DEFINE_LOG_CATEGORY(Tag) LogCategory##Tag g_logCategory##Tag

// GetAsyncKeyState()에서 사용되는 매크로입니다.
#define IS_INPUT_DOWN(VKCode) ((::GetAsyncKeyState(VKCode) & 0x8000) ? true : false)
#define IS_INPUT_UP(VKCode)   ((::GetAsyncKeyState(VKCode) & 0x8000) ? false : true)

// bitset을 좀 더 편하게 사용하기 위한 매크로입니다.
#define ON_BITSET(bitset, bitIdx)   bitset.set(bitIdx, true)
#define OFF_BITSET(bitset, bitIdx)  bitset.set(bitIdx, false)
#define IS_BITSET(bitset, bitIdx)   bitset.test(bitIdx)
#define FLIP_BITSET(bitset, bitIdx) bitset.flip(bitIdx)
#define ALL_BITSET(bitest)          bitset.all()

// 열거형 클래스도 지원되는 매크로입니다.
#define ON_BITSET_ENUM(bitset, bitIdx)   bitset.set(CommonFunc::ToUnderlyingType(bitIdx), true)
#define OFF_BITSET_ENUM(bitset, bitIdx)  bitset.set(CommonFunc::ToUnderlyingType(bitIdx), false)
#define IS_BITSET_ENUM(bitset, bitIdx)   bitset.test(CommonFunc::ToUnderlyingType(bitIdx))
#define FLIP_BITSET_ENUM(bitset, bitIdx) bitset.flip(CommonFunc::ToUnderlyingType(bitIdx))
#define ALL_BITSET_ENUM(bitest)          bitset.all()

// NameTag는 자주 사용되어서... 매크로로 분리합니다.
#define HAS_NAME_TAG()\
public:\
	const std::string& getNameTag() const\
	{\
		return m_nameTag.getNameTag();\
	}\
\
	void setNameTag(const std::string_view & szName)\
	{\
		m_nameTag.setNameTag(szName);\
	}\
\
private:\
	NameTag m_nameTag;

// ACTIVATION_CONSOLE_DBL_BUFFERING 활성화 여부에 따라 출력 함수가 변경됩니다.
#ifdef ACTIVATION_CONSOLE_DBL_BUFFERING
#define PUT_STRING(x, y, szFormat, ...)\
	ConsoleController::I()->PutString(x, y, CommonFunc::MakeFormatString(szFormat, __VA_ARGS__));
#else
#define PUT_STRING(x, y, szFormat, ...)\
	ConsoleController::I()->MoveConsolePos(x, y);\
	printf(szFormat, __VA_ARGS__)
#endif

#define INPUT_FPS_LIMITED(FPS)\
private:\
	Real32 m_localTime = 0.0f;\
	Real32 m_inputTime = (1.0f / FPS)

#define BEGIN_INPUT_FPS_LIMITED()\
	m_localTime += FrameController::I()->getDeltaTime();\
	if (m_inputTime < m_localTime)\
	{\
		m_localTime -= m_inputTime

#define BEGIN_INPUT_FPS_LIMITED_HELPER(targetHelper)\
	targetHelper.m_localTime += FrameController::I()->getDeltaTime();\
	if (targetHelper.m_inputTime < targetHelper.m_localTime)\
	{\
		targetHelper.m_localTime -= targetHelper.m_inputTime

#define END_INPUT_FPS_LIMITED()\
	}

#define PERFORMANCE_PROFILE_START(inputDataCnt)\
	Int32 ID = __COUNTER__;\
	PerformanceProfileMgr::I()->Start(__FUNCSIG__, ID, inputDataCnt)

#define PERFORMANCE_PROFILE_END() PerformanceProfileMgr::I()->End(ID)

#define CASE_RETURN_STRING(enumValue, sz)\
	case enumValue:\
	{\
		return sz;\
	}

#define CHECK_NULLPTR(ptr)\
	if (ptr == nullptr)\
	{\
		ERROR_HANDLER(false, EErrorType::NULLPTR, #ptr);\
	}

#define CHECK_NULLPTR_CONTINUE(ptr)\
	if (ptr == nullptr)\
	{\
		continue;\
	}

#define CHECK_NULLPTR_RETURN(ptr, value)\
	if (ptr == nullptr)\
	{\
		ERROR_HANDLER(false, EErrorType::NULLPTR, #ptr);\
		return value;\
	}

#define CHECK_NULLPTR_RETURN_VOID(ptr)\
	if (ptr == nullptr)\
	{\
		ERROR_HANDLER(false, EErrorType::NULLPTR, #ptr);\
		return;\
	}

//#define CHECK_NULLPTR_RETURN(ptr, TNegativeness)\
//	if (ptr == nullptr)\
//	{\
//		DEFAULT_ERROR_HANDLER(EErrorType::NULLPTR, #ptr);\
//\
//		if constexpr (std::is_same_v<bool, TNegativeness>)\
//		{\
//			return false;\
//		}\
//		else if constexpr (std::is_void_v<TNegativeness>)\
//		{\
//			return;\
//		}\
//		else\
//		{\
//			return nullptr;\
//		}\
//	}

#define CHECK_RANGE(value, min, max)\
		if (math::IsValidRange(value, min, max) == false)\
		{\
			DEFAULT_ERROR_HANDLER(EErrorType::INVALID_RANGE, value, min, max);\
		}

#define DECLARE_ROOT_RTTI(TClass)\
public:\
	static const FastRTTI* GetRTTI()\
	{\
		static const FastRTTI s_RTTI = FastRTTI(#TClass, nullptr);\
		return &s_RTTI;\
	}\
\
	virtual const FastRTTI* OnGetRTTI() const\
	{\
		return GetRTTI();\
	}

#define DECLARE_RTTI(TChild, TParent)\
public:\
	static const FastRTTI* GetRTTI()\
	{\
		static const FastRTTI s_RTTI = FastRTTI(#TChild, TParent::GetRTTI());\
		return &s_RTTI;\
	}\
\
	virtual const FastRTTI* OnGetRTTI() const override\
	{\
		return GetRTTI();\
	}

#endif