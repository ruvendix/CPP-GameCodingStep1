// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 마지막에 발생된 에러에 해당되는 내용을 알려줍니다.
// 에러가 발생되자마자 에러 핸들러가 작동됩니다.
// =====================================================================================
#pragma once

#include "IErrorHandler.h"

class ErrorHandler : public IErrorHandler
{
public:
	ErrorHandler() = default;
	virtual ~ErrorHandler() = default;

	virtual EReturnType SetUp() override;
	virtual EReturnType CleanUp() override;

	virtual void FindErrorContent(OUT std::string& strError) override;
	virtual void SetLastError(EErrorType error) override;

private:
	EErrorType m_lastError = EErrorType::NONE;
	std::unordered_map<EErrorType, std::string> m_mapError;
};