// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���α׷��� �������Դϴ�.
// =====================================================================================

#include <EnginePCH.h>

#ifdef _DEBUG
#pragma comment(lib, "Engine_Debug.lib")
#else
#pragma comment(lib, "Engine.lib")
#endif

int main()
{
	PrintF("%s\n\n", "Variadic ���ø����� printf()�� ȣ���մϴ�.");

	Char buffer[DEFAULT_CHAR_BUFFER_SIZE];
	StringPrint(buffer, DEFAULT_CHAR_BUFFER_SIZE, "%s", "std::string�� ���ڿ��� ����մϴ�.");
	printf("%s\n\n", buffer);

	std::string str("[������ ���ڿ�]");
	std::string strResult = MakeFormatString("%s %s", buffer, str);
	printf("%s\n\n", strResult.c_str());

	return 0;
}