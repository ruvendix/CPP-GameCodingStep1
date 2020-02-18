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

// VLD�� ��ü �������� Ȯ�� �ʿ�!
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

// ���� �� �̵��� �����ϴ� ��ũ�ο���. (Copy Semantics, Move Semantics)
#define NON_COPYABLE_CLASS(TClass)\
public:\
	TClass(const TClass&) = delete;\
	TClass(const TClass&&) = delete;\
	TClass& operator=(const TClass&) = delete;\
	TClass&& operator=(const TClass&&) = delete;

// �ܺο����� ���� �� �Ҹ��� ���� ��ũ�ο���. (�⺻ �����ڸ� ����)
// ������ ��� ���迡���� ���� �����ϰ� ����� �ؿ�.
#define NON_EXTERNAL_CLASS(TClass)\
protected:\
	TClass() = default;\
	virtual ~TClass() = default;

// ��� ���迡���� ���� �Ұ����� �����Դϴ�.
#define ONLY_PRIVATE_CLASS(TClass)\
private:\
	TClass() = default;\
	~TClass() = default;

// NON_COPYABLE_CLASS�� ONLY_PRIVATE_CLASS�� ȥ���߾��!
#define NON_COPYABLE_ONLY_PRIVATE_CLASS(TClass) NON_COPYABLE_CLASS(TClass) ONLY_PRIVATE_CLASS(TClass)

// �̱����� NON_COPYABLE_ONLY_PRIVATE_CLASS�Դϴ�!
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

// ���â���� �α׸� Ȯ���� �� �ֽ��ϴ�. (����� ��� ����)
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
		DEBUG_LOG_CATEGORY(Common, "%s�� ��������!", #ptr);\
		__debugbreak();\
	}

// NameTag�� ��� �޴� ���ο� �α� Ŭ������ �����մϴ�.
#define DECLARE_LOG_CATEGORY(Tag)\
	class LogCategory##Tag : public NameTag\
	{\
	public:\
		LogCategory##Tag() : NameTag(TO_STRING(Log##Tag)) { }\
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

#endif