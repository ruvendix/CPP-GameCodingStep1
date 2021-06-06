// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 에러 핸들러에 사용되는 외부 데이터입니다.
// =====================================================================================
#pragma once

#include "Common/CommonType.h"
#include "Subsystem/SubsystemData.h"
#include "ErrorEnum.h"

class ErrorHandlerData final : public SubsystemData
{
public:
	ErrorHandlerData() = default;
	~ErrorHandlerData() = default;

	EErrorCode GetLastErrorCode() const { return m_errorCode; }
	void SetLastErrorCode(EErrorCode errorCode) { m_errorCode = errorCode; }

private:
	EErrorCode m_errorCode = EErrorCode::UNKNOWN;
};