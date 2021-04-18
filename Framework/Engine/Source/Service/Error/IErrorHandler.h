// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 에러 핸들러의 인터페이스입니다.
// =====================================================================================
#pragma once

#include "Common/CommonInterface.h"
#include "ErrorEnum.h"

class IErrorHandler : public IDefault
{
public:
	IErrorHandler() = default;
	virtual ~IErrorHandler() = default;

	virtual EReturnType SetUp() { return EReturnType::SUCCESS; }
	virtual EReturnType CleanUp() { return EReturnType::SUCCESS; }

	virtual void FindErrorContent(OUT std::string& strError) = 0;
	virtual void SetLastError(EErrorType error) = 0;
};