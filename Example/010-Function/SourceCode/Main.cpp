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

	return EXIT_SUCCESS;
}