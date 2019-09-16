// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdarg>
#include <string>

using int32  = signed __int32; // "typedef signed __int32 int32"�� ���ƿ�.
using real32 = float; // "typedef float real32"�� ���ƿ�.

// constexpr�� ��ȯ�ϸ� ������ Ÿ�ӿ��� ��� �����ؿ�~!
constexpr int32 DoubleSize(int32 srcSize)
{
	return (srcSize * 2);
}

// �����ڰ� �Լ��� �Ű�������� ���������δ� const �����ڿ���.
// �Ϲ� �����ڷ� ����Ϸ��� �������� ���� ǥ���ϴ� �� ��õ�ҰԿ�! (_Out_ ������ ����)
// ������ �Ϲ� �����ڷ� ����ϰ� �Ǹ� ��� ��ٴ�...
void DoubleRefNum(_Out_ int32& targetNum)
{
	targetNum *= 2;
}

// ���ڿ� ���ͷ��� ���ڷ� ������ ���� ���� ���� ������ �־��.
// const std::string&�� �Ű������� ������� ���� �׷��ѵ�...
// C++17���ʹ� const std::string_view�� ���� ���� ������ ������ �� �־��.
// std::string���� �ٸ��� ���ڿ��� �������� �����Ƿ� c_str�� �ƴ϶� data�� �̿��ؾ� �ؿ�!
void ShowStringLineFeed(const std::string_view& srcStr)
{
	printf("%s\n", srcStr.data());
}

// printfó�� ���� ���ڿ��� �����ؼ� std::string���� ���� �� �־��.
std::string MakeFormatStr(const char* szFormat, ...)
{
	// va_list�� �������ڶ�� ǥ�����ִ� ���̰� (char*)
	// va_start�� ���������� ���� �κ��� �˷����.
	va_list va = nullptr;
	va_start(va, szFormat);

	// ���� ���ڿ��� ���̸� ���ؾ� �ؿ�.
	// _vscprintf�� �������� ���ڿ��� ������ִµ�, ���� ���� �� ����ؿ�.
	int32 strLength = _vscprintf(szFormat, va);

	// �������ڷ� ���ڿ��� �����Ϸ��� �޸� ������ �ʿ��ؿ�.
	// std::string�� �޸� ������ �������̶� �̿��� �� ����.
	// �ܼ��ϰ� ����Ʈ ������ �����Ҵ��ؾ� �ϴϱ� std::malloc()�� ����ҰԿ�.
	char* strBuffer = nullptr;
	int32 bufferSize = strLength + 1; // �ι��ڰ� �� ������ �������ּ���!
	strBuffer = (char*)(std::malloc(bufferSize));
	::memset(strBuffer, 0, bufferSize);

	// vsprintf_s�� �������� ���ڿ��� �޸� ������ ������ְ�
	// va_end�� ���������� ������ �κ��� �˷����.
	vsprintf_s(strBuffer, bufferSize, szFormat, va);
	va_end(va);

	std::string strResult = strBuffer; // ���⼭ ���� ���簡 �߻��ؿ�.
	free(strBuffer); // �����Ҵ��� �޸� ������ �ʼ�!
	return strResult;
}

int main()
{
#if 0
	std::string strTable[DoubleSize(4)];
	int32 lastIdx = _countof(strTable) - 1;
	strTable[lastIdx] = "������ ��ġ";
	printf("%s\n", strTable[lastIdx].c_str());
#endif

#if 0
	int32 speed = 10;
	printf("�����ϱ� ���� �ӷ� : %d\n", speed);
	DoubleRefNum(speed);
	printf("������ ���� �ӷ�   : %d\n", speed);
#endif

#if 0
	ShowStringLineFeed("C++17���� ���� ���� ��Ʈ�� �信��~");	
	std::string strGuide = "������ std::string���� �����ص� ���� ���縦 ���� �ʾƿ�.";
	ShowStringLineFeed(strGuide);
#endif

#if 0
	// 1ȸ�����θ� ����� ���� �ӽð�ü�� �̿��غ�����.
	printf("%s\n\n", MakeFormatStr("������ ����غ��Կ�   : %d", 100).c_str());
	printf("%s\n\n", MakeFormatStr("�Ǽ��� ����غ��Կ�   : %f", 54.24f).c_str());
	printf("%s\n\n", MakeFormatStr("���ڸ� ����غ��Կ�   : %c", 'D').c_str());
	printf("%s\n\n", MakeFormatStr("���ڿ��� ����غ��Կ� : %s", "string").c_str());
	printf("%s\n\n", MakeFormatStr("���ÿ� ����غ��Կ�   : %d %f %c %s", 100, 54.24f, 'D', "string").c_str());
#endif

	return EXIT_SUCCESS;
}