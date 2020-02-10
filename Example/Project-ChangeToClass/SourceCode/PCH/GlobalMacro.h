// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#ifndef GLOBAL_MACRO__H__
#define GLOBAL_MACRO__H__

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
	virtual ~TClass() = default;

#endif