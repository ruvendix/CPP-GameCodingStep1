// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���������� ���Ǵ� ��ũ�ο� ��ũ�� �Լ� �����Դϴ�.
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

#define GENERATE_HIERARCHY_COMMON(CurrentClass)\
public:\
    static CurrentClass* StaticClass()\
    {\
        static CurrentClass staticClass;\
        return &staticClass;\
    }\

#define GENERATE_HIERARCHY(CurrentClass, ParentClass)\
    GENERATE_HIERARCHY_COMMON(CurrentClass);\
    virtual void InitClassMetadata() override\
    {\
		static_assert(std::is_base_of_v<ParentClass, CurrentClass>, "It's not parent!");\
        CurrentClass* pCurrentClass = CurrentClass::StaticClass();\
        ParentClass* pParentClass = ParentClass::StaticClass();\
\
        if (pCurrentClass->GetParentClass() == nullptr)\
		{\
			pCurrentClass->SetParentClass(pParentClass);\
		}\
\
		if (pCurrentClass == this)\
		{\
			return;\
		}\
\
		SetClass(pCurrentClass);\
        SetParentClass(pParentClass);\
    }