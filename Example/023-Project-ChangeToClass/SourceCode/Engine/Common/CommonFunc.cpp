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
void common_func::ShowLog(const std::string_view& szLogCategory, const std::string_view& szLog)
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
Ư�����ڸ� �̿��ؼ� ��輱�� �׸��ϴ�.
*/
void common_func::DrawBorder(const COORD& pos, const SizeInfo& size)
{
	COORD drawPos = pos;

#pragma region ���� ��輱
	PUT_STRING(drawPos.X, drawPos.Y, "��");
	for (TSize i = 0; i < size.width; ++i)
	{
		drawPos.X += 2;
		PUT_STRING(drawPos.X, drawPos.Y, "��");
	}

	drawPos.X += 2;
	PUT_STRING(drawPos.X, drawPos.Y, "��");
#pragma endregion

#pragma region ���� ��輱
	drawPos.X = pos.X;
	for (TSize i = 0; i < size.height; ++i)
	{
		PUT_STRING(drawPos.X, ++drawPos.Y, "��");
		PUT_STRING(drawPos.X + (size.width * 2) + (ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU / 2), drawPos.Y, "��");
	}
#pragma endregion

#pragma region �Ʒ��� ��輱
	drawPos.X = pos.X;
	PUT_STRING(drawPos.X, ++drawPos.Y, "��");

	for (TSize i = 0; i < size.width; ++i)
	{
		drawPos.X += 2;
		PUT_STRING(drawPos.X, drawPos.Y, "��");
	}

	drawPos.X += 2;
	PUT_STRING(drawPos.X, drawPos.Y, "��");
#pragma endregion
}

/*
Create�� ���� �����͸� �̿��ؼ� ó������ ���� �� ����ϰ�
Make�� ���޵� �����͵��� �����ؼ� ���� �� ����մϴ�. (��� ���� ���̴� ����...)
printf()ó�� ���� ���ڿ��� ����ϸ� std::string �ڷ������� ���ڿ��� ����ϴ�.
*/
std::string common_func::MakeFormatString(const char* szFormat, ...)
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
bool common_func::InputNumClamp(_Out_ Int32& num, Int32 minNum, Int32 maxNum)
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

	num = rx_math::Clamp(num, minNum, maxNum);
	return true;
}