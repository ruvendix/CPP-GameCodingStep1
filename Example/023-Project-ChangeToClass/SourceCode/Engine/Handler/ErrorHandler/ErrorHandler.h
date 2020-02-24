// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� Ÿ�Կ� ���� ó�����ִ� �ڵ鷯�Դϴ�.
// =====================================================================================

#ifndef ERROR_HANDLER__H__
#define ERROR_HANDLER__H__

#include "Common\CommonMacro.h"
#include "ErrorType.h"
#include "Element\NameTag.h"

//#pragma warning(disable: 6011)

DECLARE_LOG_CATEGORY(ErrorHandler);

class ErrorHandler final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(ErrorHandler);

public:
	static void ShowErrorString(EErrorType errorType);
	static void ShowErrorFormatString(const std::string_view& szError);
	static std::string_view GetErrorFormatString(EErrorType errorType);
};

#endif