// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ð� ���� �Լ� �����Դϴ�.
// =====================================================================================

#ifndef TIME_UTIL__H__
#define TIME_UTIL__H__

#include "Common\CommonType.h"
#include "Common\CommonMacro.h"
#include "Common\CommonNecessary.h"

namespace rx_time
{

	std::string MakeTimeString_HHMMSS(const TimePoint& timePoint);
	void ToHHMMSS(Real32 elaspedTime, _Out_ Int32* pHour, _Out_ Int32* pMinute, _Out_ Int32* pSecond);

} // namespace rx_time end

#endif