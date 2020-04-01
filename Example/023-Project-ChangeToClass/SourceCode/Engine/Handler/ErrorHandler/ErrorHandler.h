// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 에러 타입에 따라 처리해주는 핸들러입니다.
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