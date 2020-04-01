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

DECLARE_LOG_CATEGORY(ErrorHandler);

class ErrorHandler final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(ErrorHandler);

public:
	static void RenderString();
	static void OuputDebugString(bool bOutput);
	static void DebugBreak(bool bDebugBreak);

	static std::string_view ToString(EErrorType errorType);
	static std::string_view ToFormatString(EErrorType errorType);

	static COORD m_renderPos;
	static std::string m_strError;
};

#endif