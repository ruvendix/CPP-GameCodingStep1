// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �������� ���Ǵ� �Լ� ���� �����Դϴ�.
// ��� �Լ��� static���� ���� �� �����ؾ� �մϴ�.
// =====================================================================================

#ifndef COMMON_FUNC__H__
#define COMMON_FUNC__H__

#include "CommonNecessary.h"
#include "CommonStruct.h"
#include "CommonMacro.h"
#include "Handler\ErrorHandler\ErrorHandler.h"

using TimePoint = std::chrono::system_clock::time_point;

namespace common_func
{

#pragma region �Ϲ� �Լ�
    void DrawBorder(const COORD& pos, const SizeInfo& size);
    std::string MakeFormatString(const char* szFormat, ...);
    bool InputNumClamp(_Out_ Int32& num, Int32 minNum, Int32 maxNum); // �������̵��� _Out_�� �� ������!
#pragma endregion

#pragma region ��ũ�ο����� ���Ǵ� �Լ�
    void ShowLog(const std::string_view& szLogCategory, const std::string_view& szLog);
#pragma endregion

} // namespace common_func end

#endif