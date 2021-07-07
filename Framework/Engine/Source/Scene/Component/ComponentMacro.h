// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������Ʈ ���� ��ũ�� �Լ� �����Դϴ�.
// =====================================================================================
#pragma once

#define GENERATE_COMPONENT(value, tag)\
public:\
	static constexpr EComponentType Type()\
	{\
		return value;\
	}\
\
	static const char* Tag()\
	{\
		return #tag;\
	}