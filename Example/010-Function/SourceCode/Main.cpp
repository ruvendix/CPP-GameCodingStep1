// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdarg>
#include <string>

using int32  = signed __int32; // "typedef signed __int32 int32"와 같아요.
using real32 = float; // "typedef float real32"와 같아요.

// constexpr을 반환하면 컴파일 타임에도 사용 가능해요~!
constexpr int32 DoubleSize(int32 srcSize)
{
	return (srcSize * 2);
}

// 참조자가 함수의 매개변수라면 관습적으로는 const 참조자에요.
// 일반 참조자로 사용하려면 가독성을 위해 표기하는 걸 추천할게요! (_Out_ 정도면 무난)
// 하지만 일반 참조자로 사용하게 되면 경고가 뜬다는...
void DoubleRefNum(_Out_ int32& targetNum)
{
	targetNum *= 2;
}

// 문자열 리터럴을 인자로 전달할 때는 내부 복사 과정이 있어요.
// const std::string&을 매개변수로 만들었을 때가 그러한데...
// C++17부터는 const std::string_view로 내부 복사 과정을 생략할 수 있어요.
// std::string과는 다르게 문자열을 저장하지 않으므로 c_str이 아니라 data를 이용해야 해요!
void ShowStringLineFeed(const std::string_view& srcStr)
{
	printf("%s\n", srcStr.data());
}

// printf처럼 서식 문자열로 전달해서 std::string으로 만들 수 있어요.
std::string MakeFormatStr(const char* szFormat, ...)
{
	// va_list는 가변인자라고 표기해주는 것이고 (char*)
	// va_start는 가변인자의 시작 부분을 알려줘요.
	va_list va = nullptr;
	va_start(va, szFormat);

	// 서식 문자열의 길이를 구해야 해요.
	// _vscprintf는 가변인자 문자열을 출력해주는데, 길이 구할 때 사용해요.
	int32 strLength = _vscprintf(szFormat, va);

	// 가변인자로 문자열을 조합하려면 메모리 공간이 필요해요.
	// std::string은 메모리 공간이 가변적이라 이용할 수 없죠.
	// 단순하게 바이트 단위로 동적할당해야 하니까 std::malloc()을 사용할게요.
	char* strBuffer = nullptr;
	int32 bufferSize = strLength + 1; // 널문자가 들어갈 공간도 포함해주세요!
	strBuffer = (char*)(std::malloc(bufferSize));
	::memset(strBuffer, 0, bufferSize);

	// vsprintf_s는 가변인자 문자열을 메모리 공간에 출력해주고
	// va_end는 가변인자의 마지막 부분을 알려줘요.
	vsprintf_s(strBuffer, bufferSize, szFormat, va);
	va_end(va);

	std::string strResult = strBuffer; // 여기서 내부 복사가 발생해요.
	free(strBuffer); // 동적할당은 메모리 해제가 필수!
	return strResult;
}

int main()
{
#if 0
	std::string strTable[DoubleSize(4)];
	int32 lastIdx = _countof(strTable) - 1;
	strTable[lastIdx] = "마지막 위치";
	printf("%s\n", strTable[lastIdx].c_str());
#endif

#if 0
	int32 speed = 10;
	printf("증가하기 전의 속력 : %d\n", speed);
	DoubleRefNum(speed);
	printf("증가된 후의 속력   : %d\n", speed);
#endif

#if 0
	ShowStringLineFeed("C++17에서 새로 생긴 스트링 뷰에요~");	
	std::string strGuide = "기존의 std::string으로 전달해도 내부 복사를 하지 않아요.";
	ShowStringLineFeed(strGuide);
#endif

#if 0
	// 1회용으로만 사용할 때는 임시객체를 이용해보세요.
	printf("%s\n\n", MakeFormatStr("정수를 출력해볼게요   : %d", 100).c_str());
	printf("%s\n\n", MakeFormatStr("실수를 출력해볼게요   : %f", 54.24f).c_str());
	printf("%s\n\n", MakeFormatStr("문자를 출력해볼게요   : %c", 'D').c_str());
	printf("%s\n\n", MakeFormatStr("문자열을 출력해볼게요 : %s", "string").c_str());
	printf("%s\n\n", MakeFormatStr("동시에 출력해볼게요   : %d %f %c %s", 100, 54.24f, 'D', "string").c_str());
#endif

	return EXIT_SUCCESS;
}