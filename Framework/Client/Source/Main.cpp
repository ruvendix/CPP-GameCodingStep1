// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 프로그램의 진입점입니다.
// =====================================================================================

#include <EnginePCH.h>

#ifdef _DEBUG
#pragma comment(lib, "Engine_Debug.lib")
#else
#pragma comment(lib, "Engine.lib")
#endif

int main()
{
	PrintF("%s\n\n", "Variadic 템플릿으로 printf()를 호출합니다.");

	Char buffer[DEFAULT_CHAR_BUFFER_SIZE];
	StringPrint(buffer, DEFAULT_CHAR_BUFFER_SIZE, "%s", "std::string에 문자열을 출력합니다.");
	printf("%s\n\n", buffer);

	std::string str("[덧붙일 문자열]");
	std::string strResult = MakeFormatString("%s %s", buffer, str);
	printf("%s\n\n", strResult.c_str());

	return 0;
}