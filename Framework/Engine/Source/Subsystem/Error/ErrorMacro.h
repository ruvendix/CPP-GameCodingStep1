// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �ڵ鷯�� �ʿ��� ��ũ�� �Լ� �����Դϴ�.
// =====================================================================================
#pragma once

#define CHECK_NULLPTR(ptr)\
	if (ptr == nullptr)\
	{\
		RX_SIMPLE_ERRORTYPE(EErrorType::INDIRECT_NULLPTR);\
	}