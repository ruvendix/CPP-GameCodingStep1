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

// VLD로 대체 가능한지 확인 필요!
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__ )                                            
#endif

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

// 복사 및 이동을 금지하는 매크로에요. (Copy Semantics, Move Semantics)
#define NON_COPYABLE_CLASS(TClass)\
public:\
	TClass(const TClass&) = delete;\
	TClass(const TClass&&) = delete;\
	TClass& operator=(const TClass&) = delete;\
	TClass&& operator=(const TClass&&) = delete;

// 외부에서만 생성 및 소멸을 막는 매크로에요. (기본 생성자만 막힘)
// 하지만 상속 관계에서는 접근 가능하게 해줘야 해요.
#define NON_EXTERNAL_CLASS(TClass)\
protected:\
	TClass() = default;\
	virtual ~TClass() = default;

// 상속 관계에서도 접근 불가능한 버전입니다.
#define ONLY_PRIVATE_CLASS(TClass)\
private:\
	TClass() = default;\
	~TClass() = default;

// NON_COPYABLE_CLASS와 ONLY_PRIVATE_CLASS를 혼용했어요!
#define NON_COPYABLE_ONLY_PRIVATE_CLASS(TClass) NON_COPYABLE_CLASS(TClass) ONLY_PRIVATE_CLASS(TClass)

// 싱글톤은 NON_COPYABLE_ONLY_PRIVATE_CLASS입니다!
#define DECLARE_SINGLETON(TClass)\
	NON_COPYABLE_ONLY_PRIVATE_CLASS(TClass)\
\
public:\
	static TClass* I();\
	static void Destroy();\
\
private:\
	static TClass* m_pInst;

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
		m_pInst = new TClass;\
\
		return m_pInst;\
	}\
\
	void TClass::Destroy()\
	{\
		SAFE_DELETE(m_pInst);\
	}

#define FRIEND_WITH_HELPER(THelperClass) friend class THelperClass
#define TO_STRING(src) (#src)

// 출력창에서 로그를 확인할 수 있습니다. (디버그 모드 전용)
#if defined(DEBUG) || defined(_DEBUG)
#define DEBUG_LOG(szFormat, ...) CommonFunc::ShowLog("", CommonFunc::MakeFormatString(szFormat, __VA_ARGS__))
#define DEBUG_LOG_CATEGORY(logCategory, szFormat, ...)\
	CommonFunc::ShowLog(g_logCategory##logCategory.getNameTag(), CommonFunc::MakeFormatString(szFormat, __VA_ARGS__))
#else
#define DEBUG_LOG(szFormat, ...) __noop
#define DEBUG_LOG_CATEGORY(logCategory, szFormat, ...) __noop
#endif

#define CHECK_NULLPTR(ptr)\
	if (ptr == nullptr)\
	{\
		DEBUG_LOG_CATEGORY(Common, "%s는 널포인터!", #ptr);\
		__debugbreak();\
	}

// NameTag를 상속 받는 새로운 로그 클래스를 선언합니다.
#define DECLARE_LOG_CATEGORY(Tag)\
	class LogCategory##Tag : public NameTag\
	{\
	public:\
		LogCategory##Tag() : NameTag(TO_STRING(Log##Tag)) { }\
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

#endif