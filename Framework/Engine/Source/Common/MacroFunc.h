// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��ũ�� �Լ� �����Դϴ�.
// =====================================================================================
#pragma once

#define DECLARE_LOCAL_SINGLETON(Type)\
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