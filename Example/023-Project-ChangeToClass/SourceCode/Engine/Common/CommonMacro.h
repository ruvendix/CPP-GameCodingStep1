// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �������� ���Ǵ� ��ũ�� �����Դϴ�.
// =====================================================================================

#ifndef COMMON_MACRO__H__
#define COMMON_MACRO__H__

/*
VLD�� ��ü �������� Ȯ�� �ʿ�!
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
���� �� �̵��� �����ϴ� ��ũ�ο���. (Copy Semantics, Move Semantics)
*/
#define NON_COPYABLE_CLASS(TClass)\
public:\
	TClass(const TClass&) = delete;\
	TClass(const TClass&&) = delete;\
	TClass& operator=(const TClass&) = delete;\
	TClass&& operator=(const TClass&&) = delete;

/*
�ܺο����� ���� �� �Ҹ��� ���� ��ũ�ο���. (�⺻ �����ڸ� ����)
������ ��� ���迡���� ���� �����ϰ� ����� �ؿ�.
*/
#define NON_EXTERNAL_CLASS(TClass)\
protected:\
	TClass() = default;\
	virtual ~TClass() = default;

// ��� ���迡���� ���� �Ұ����� �����Դϴ�.
#define ONLY_PRIVATE_CLASS(TClass)\
private:\
	TClass() = default;\
	~TClass() = default;

/*
NON_COPYABLE_CLASS�� ONLY_PRIVATE_CLASS�� ȥ���߾��!
*/
#define NON_COPYABLE_ONLY_PRIVATE_CLASS(TClass) NON_COPYABLE_CLASS(TClass) ONLY_PRIVATE_CLASS(TClass)

/*
�̱����� NON_COPYABLE_ONLY_PRIVATE_CLASS�Դϴ�!
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
		DEBUG_LOG("�̱��� ����! (%s)", TO_STRING(TClass));\
	}

/*
�̱��� �߿��� �Ǵн� �̱����̶�� �� �־��.
�׾��ٰ� �ٽ� ��Ȱ�Ѵٴ� �ǹ̸� �̿��ϱ� ���� �Ǵн��� �Ǿ��ٳ׿�...

static�� ������ �Ҹ� ������ ������ �� �����.
�̹� �Ҹ�� �Ǵн� �̱����� �ٸ� ������ ȣ���ϰ� �Ǹ� �ٽ� ��Ȱ��ŵ�ϴ�.
�ٽ� �Ҹ���Ѿ� �� ���� ���α׷��� ����Ǹ� �ڵ����� �Ҹ�ǵ��� std::atexit()�� �̿��ؿ�!

�߰��� new(m_pInst) placement New��� �ϴµ�,
�޸𸮸� ���� �Ҵ��ϴ� �� �ƴ϶�!
�̹� �Ҵ�� �޸� ������ �̿��ϹǷ� �����ڸ� ȣ���ؿ�.
���� �Ǵн� �̱��濡���� �����Ҵ��� �̿����� �ʽ��ϴ�.
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
		DEBUG_LOG("�̱��� ����! (%s)", TO_STRING(TClass));\
	}\
\
	~TClass()\
	{\
		m_pInst = nullptr;\
		m_bDead = true;\
		DEBUG_LOG("�̱��� �Ҹ�! (%s)", TO_STRING(TClass));\
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

// ���â���� �α׸� Ȯ���� �� �ֽ��ϴ�. (����� ��� ����)
#if defined(DEBUG) || defined(_DEBUG)
#define DEBUG_LOG(szFormat, ...) CommonFunc::ShowLog("", CommonFunc::MakeFormatString(szFormat, __VA_ARGS__))
#define DEBUG_LOG_CATEGORY(logCategory, szFormat, ...)\
	CommonFunc::ShowLog(g_logCategory##logCategory.getNameTag(), CommonFunc::MakeFormatString(szFormat, __VA_ARGS__))
#else
#define DEBUG_LOG(szFormat, ...) __noop
#define DEBUG_LOG_CATEGORY(logCategory, szFormat, ...) __noop
#endif

// ���� �ڵ鷯���� ���� ���ڿ��� �����մϴ�.
#define ERROR_HANDLER(errorType) ErrorHandler::ShowString(errorType)
#define ERROR_HANDLER_DETAIL(errorType, ...)\
	ErrorHandler::ShowFormatString(CommonFunc::MakeFormatString(ErrorHandler::ToFormatString(errorType).data(), __VA_ARGS__))

// NameTag�� ��� �޴� ���ο� �α� Ŭ������ �����մϴ�.
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

// DECLARE_LOG_CATEGORY()���� ������ Ŭ������ ��ü�� ����ϴ�.
#define DEFINE_LOG_CATEGORY(Tag) LogCategory##Tag g_logCategory##Tag

// GetAsyncKeyState()���� ���Ǵ� ��ũ���Դϴ�.
#define IS_INPUT_DOWN(VKCode) ((::GetAsyncKeyState(VKCode) & 0x8000) ? true : false)
#define IS_INPUT_UP(VKCode)   ((::GetAsyncKeyState(VKCode) & 0x8000) ? false : true)

// bitset�� �� �� ���ϰ� ����ϱ� ���� ��ũ���Դϴ�.
#define ON_BITSET(bitset, bitIdx)   bitset.set(bitIdx, true)
#define OFF_BITSET(bitset, bitIdx)  bitset.set(bitIdx, false)
#define IS_BITSET(bitset, bitIdx)   bitset.test(bitIdx)
#define FLIP_BITSET(bitset, bitIdx) bitset.flip(bitIdx)
#define ALL_BITSET(bitest)          bitset.all()

// ������ Ŭ������ �����Ǵ� ��ũ���Դϴ�.
#define ON_BITSET_ENUM(bitset, bitIdx)   bitset.set(CommonFunc::ToUnderlyingType(bitIdx), true)
#define OFF_BITSET_ENUM(bitset, bitIdx)  bitset.set(CommonFunc::ToUnderlyingType(bitIdx), false)
#define IS_BITSET_ENUM(bitset, bitIdx)   bitset.test(CommonFunc::ToUnderlyingType(bitIdx))
#define FLIP_BITSET_ENUM(bitset, bitIdx) bitset.flip(CommonFunc::ToUnderlyingType(bitIdx))
#define ALL_BITSET_ENUM(bitest)          bitset.all()

// NameTag�� ���� ���Ǿ... ��ũ�η� �и��մϴ�.
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

// ACTIVATION_CONSOLE_DBL_BUFFERING Ȱ��ȭ ���ο� ���� ��� �Լ��� ����˴ϴ�.
#ifdef ACTIVATION_CONSOLE_DBL_BUFFERING
#define PRINTF(posX, posY, szFormat, ...)\
	ConsoleController::I()->PrintString(posX, posY, CommonFunc::MakeFormatString(szFormat, __VA_ARGS__));
#else
#define PRINTF(posX, posY, szFormat, ...)\
	ConsoleController::I()->MoveConsolePos(posX, posY);\
	printf(szFormat, __VA_ARGS__)
#endif

#define FRAME_UPDATE_LIMITED(FPS)\
private:\
	Real32 m_localTime = 0.0f;\
	Real32 m_updateTime = (1.0f / FPS)

#define BEGIN_FRAME_UPDDATE_LIMITED()\
	m_localTime += FrameController::I()->getDeltaTime();\
	if (m_updateTime < m_localTime)\
	{\
		m_localTime -= m_updateTime

#define END_FRAME_UPDATE_LIMITED()\
	}

#define PERFORMANCE_PROFILE_START(inputDataCnt)\
	Int32 ID = __COUNTER__;\
	PerformanceProfileMgr::I()->Start(__FUNCSIG__, ID, inputDataCnt)

#define PERFORMANCE_PROFILE_END() PerformanceProfileMgr::I()->End(ID)

#define CASE_LOG_BREAK(enumVal, szLog)\
	case enumVal:\
	{\
		DEBUG_LOG_CATEGORY(ErrorHandler, szLog);\
		break;\
	}

#define CASE_RETURN_STRING(enumVal, sz)\
	case enumVal:\
	{\
		return sz;\
	}

#define CHECK_NULLPTR(ptr)\
	if (ptr == nullptr)\
	{\
		ERROR_HANDLER_DETAIL(EErrorType::NULLPTR, #ptr);\
	}

#define CHECK_NULLPTR_CONTINUE(ptr)\
	if (ptr == nullptr)\
	{\
		ERROR_HANDLER_DETAIL(EErrorType::NULLPTR, #ptr);\
		continue;\
	}

#define CHECK_NULLPTR_RETURN(ptr, TNegativeness)\
	if (ptr == nullptr)\
	{\
		ERROR_HANDLER_DETAIL(EErrorType::NULLPTR, #ptr);\
\
		if constexpr (std::is_same_v<bool, TNegativeness>)\
		{\
			return false;\
		}\
		else if constexpr (std::is_void_v<TNegativeness>)\
		{\
			return;\
		}\
		else\
		{\
			return nullptr;\
		}\
	}

#endif