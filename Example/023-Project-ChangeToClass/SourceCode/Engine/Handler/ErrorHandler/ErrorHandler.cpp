// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� Ÿ�Կ� ���� ó�����ִ� �ڵ鷯�Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "ErrorHandler.h"

#define CASE_ERROR_STRING(errorType, szError)\
	case errorType:\
	{\
		DEBUG_LOG(szError);\
		break;\
	}

/*
���� Ÿ�Կ� ���� ���� ������ �����ݴϴ�.
*/
void ErrorHandler::ShowError(EErrorType errorType)
{
	switch (errorType)
	{
	CASE_ERROR_STRING(EErrorType::INIT_FAILED, "�ʱ�ȭ ����!");
	CASE_ERROR_STRING(EErrorType::UPDATE_FAILED, "���� ����!");
	CASE_ERROR_STRING(EErrorType::RENDER_FAILED, "������ ����!");
	CASE_ERROR_STRING(EErrorType::FINAL_FAILED, "������ ����!");
	}
}
