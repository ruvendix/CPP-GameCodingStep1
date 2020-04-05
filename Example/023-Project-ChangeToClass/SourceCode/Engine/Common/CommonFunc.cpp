// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �������� ���Ǵ� �Լ� ���� �����Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "CommonFunc.h"

#include "Context\ConfigContext.h"
#include "Controller\ConsoleController.h"

/*
�α׸� ����մϴ�.
*/
void CommonFunc::ShowLog(const std::string_view& szLogCategory, const std::string_view& szLog)
{
	std::string strLog;

	if (szLogCategory.empty() == false)
	{
		strLog += "[";
		strLog += szLogCategory;
		strLog += "]: ";
	}

	strLog += szLog;
	strLog += "\n"; // �ڵ� ����!

	::OutputDebugString(strLog.c_str());
}

/*
Create�� ���� �����͸� �̿��ؼ� ó������ ���� �� ����ϰ�
Make�� ���޵� �����͵��� �����ؼ� ���� �� ����մϴ�. (��� ���� ���̴� ����...)
printf()ó�� ���� ���ڿ��� ����ϸ� std::string �ڷ������� ���ڿ��� ����ϴ�.
*/
std::string CommonFunc::MakeFormatString(const char* szFormat, ...)
{
	va_list va = nullptr;
	va_start(va, szFormat);

	// ���� ���ڿ��� ���̸� ���մϴ�.
	// �����Ҵ��� ���� ���� ���ڸ� �����ؾ� �մϴ�.
	Int32 length = _vscprintf(szFormat, va) + 1;

	// ���� ���ڷ� ���ڿ��� �����Ϸ��� �޸� ���۰� �ʿ��մϴ�.
	// std::string�� �޸� ���۰� �������̶� ����� �� �����ϴ�.
	// ����� �ܼ��ϰ� ����Ʈ ������ �����Ҵ��� ���� std::malloc()�� ����մϴ�.
	char* pMemoryBuffer = nullptr;
	pMemoryBuffer = reinterpret_cast<char*>(std::malloc(length * sizeof(char)));
	if (pMemoryBuffer == nullptr)
	{
		return std::string();
	}

	::ZeroMemory(pMemoryBuffer, (length * sizeof(char)));

	vsprintf_s(pMemoryBuffer, length, szFormat, va);
	va_end(va);

	std::string strFormat = pMemoryBuffer;
	free(pMemoryBuffer);

	return strFormat;
}

/*
���ڸ� �Է� ������ ���ÿ� �Է� ������ ����� ���� ������ �ڵ� �����մϴ�.
*/
bool CommonFunc::InputNumClamp(_Out_ Int32& num, Int32 minNum, Int32 maxNum)
{
	// �ּڰ��� �ִ񰪺��� ũ�ٸ� ���� �ٲ�� �ؿ�! (swap)
	if (minNum > maxNum)
	{
		std::swap(minNum, maxNum);
	}

	DEBUG_LOG_CATEGORY(Common, "�Է� ������ ����� �ڵ� �����˴ϴ�. (%d ~ %d)\n", minNum, maxNum);
	printf("> ");

	Int32 retInput = scanf_s("%d", &num);
	printf("\n");
	ConsoleController::I()->ClearStdInputBuffer();

	if (retInput == 0)
	{
		printf("������ �Է� �����ؿ�!\n\n");
		return false;
	}

	num = math::Clamp(num, minNum, maxNum);
	return true;
}