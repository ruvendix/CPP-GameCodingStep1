// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 공통적으로 사용되는 매크로와 매크로 함수 모음입니다.
// =====================================================================================
#pragma once

#define OUT
#define INOUT

#define GENERATE_LOCAL_SINGLETON(Type)\
public:\
	static Type& I()\
	{\
		static Type instance;\
		return instance;\
	}\
\
private:\
	Type() = default;\
	~Type() = default;

#define SAFE_DELETE(ptr)\
	if (ptr != nullptr)\
	{\
		delete ptr;\
		ptr = nullptr;\
	}

#define FRIEND_CLASS(Type) friend class Type
#define PURE_FUNC = 0
#define CONST_PURE_FUNC const PURE_FUNC

#define EMPTY_FUNC { }
#define CONST_EMPTY_FUNC const { }
#define OVERRIDE_EMPTY_FUNC override EMPTY_FUNC
#define CONST_OVERRIDE_EMPTY_FUNC const OVERRIDE_EMPTY_FUNC

#define RETURN_FUNC(value) { return value; }
#define CONST_RETURN_FUNC(value) const RETURN_FUNC(value)
#define OVERRIDE_RETURN_FUNC(value) override RETURN_FUNC(value)
#define CONST_OVERRIDE_RETURN_FUNC(value) const OVERRIDE_RETURN_FUNC(value)

#ifdef _DEBUG
	#undef new
	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif