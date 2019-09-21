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

	return EXIT_SUCCESS;
}