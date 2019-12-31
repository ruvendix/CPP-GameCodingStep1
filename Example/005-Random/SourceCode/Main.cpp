// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>  // printf가 포함되어있어요.
#include <cstdlib> // rand가 포함되어있어요.

using int32  = signed   __int32; // "typedef signed   __int32 int32"와 같아요.
using uint32 = unsigned __int32; // "typedef unsigned __int32 uint32"와 같아요.
using real32 = float;            // "typedef float real32"와 같아요.

int main()
{
#if 0

	//////////////////////////////////////////////////////////////////////////
	// 의사 난수 발생기를 이용해봐요~
	//////////////////////////////////////////////////////////////////////////

	printf("<의사 난수 발생기 이용 결과~>\n");
	for (int32 i = 0; i < 10; ++i)
	{
		int32 randomNum = std::rand(); // 의사 난수를 만들어줘요. (0 ~ RAND_MAX)
		printf("%d ", randomNum);
	}
	printf("\n\n");

#endif

#if 0

	//////////////////////////////////////////////////////////////////////////
	// 의사 난수 발생기에 시드를 넣어봐요~
	//////////////////////////////////////////////////////////////////////////

	printf("<의사 난수 발생기에 시드를 넣은 결과~>\n");
	
	// 시드값은 항상 변하는 값 => 주로 시간을 넣어요.
	// 필요에 따라 호출 횟수는 달라지지만, 한번이면 충분해요.
	//
	// std::time의 반환 형식은 time_t인데, 이건 정수 자료형이에요.
	// time_t는 재정의된 자료형이므로 std::srand()의 인자 형식과 맞춰줘야 해요.
	std::srand((uint32)std::time(0)); // 시간은 증가되는 값!

	for (int32 i = 0; i < 10; ++i)
	{
		int32 randomNum = std::rand();
		printf("%d ", randomNum);
	}
	printf("\n\n");

#endif

#if 0

	//////////////////////////////////////////////////////////////////////////
	// 의사 난수 발생기의 범위를 조절해봐요~
	//////////////////////////////////////////////////////////////////////////

	printf("<의사 난수 발생기의 범위를 조절한 결과~>\n\n");
	std::srand((uint32)std::time(0));

	printf("난수의 범위를 0 ~ 9로 제한할게요.\n");
	for (int32 i = 0; i < 10; ++i)
	{
		int32 randomNum = std::rand() % 10;
		printf("%d ", randomNum);
	}
	printf("\n\n");

	printf("난수의 범위를 5 ~ 14로 제한할게요.\n");
	for (int32 i = 0; i < 10; ++i)
	{
		int32 randomNum = (std::rand() % 10) + 5;
		printf("%d ", randomNum);
	}
	printf("\n\n");

	printf("난수의 범위를 -20 ~ -11로 제한할게요.\n");
	for (int32 i = 0; i < 10; ++i)
	{
		int32 randomNum = (std::rand() % 10) - 20;
		printf("%d ", randomNum);
	}
	printf("\n\n");

#endif

#if 0

	//////////////////////////////////////////////////////////////////////////
	// 의사 난수 발생기의 범위로 실수 백분율을 만들어봐요~
	//////////////////////////////////////////////////////////////////////////

	printf("<의사 난수 발생기의 범위로 실수 백분율을 만든 결과~>\n");
	std::srand((uint32)std::time(0));

	for (int32 i = 0; i < 10; ++i)
	{
		real32 percent = (std::rand() % (100 + 1)) * 0.01f;
		printf("%.2f ", percent);
	}
	printf("\n\n");

#endif

	return EXIT_SUCCESS;
}