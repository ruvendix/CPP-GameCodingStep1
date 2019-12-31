// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

using int32  = __int32; // "typedef __int32 int32"와 같아요.
using real32 = float;   // "typedef float real32"와 같아요.

int main()
{
#if 0
	//////////////////////////////////////////////////////////////////////////
	// 실수는 정수랑 다르게 같은 값인지 확인하는 게 어려워요.
	real32 jumpingPower = 0.034f; // float은 접미사(끝에 붙는 단어) f를 붙여야 해요.
	
	printf("<평범하게 비교해볼게요>\n");
	if (jumpingPower + 0.004f == 0.038f)
	{
		printf("(%f + %f)와 %f는 같아요.\n", jumpingPower, 0.004f, 0.038f);
	}
	else
	{
		printf("(%f + %f)와 %f는 달라요.\n", jumpingPower, 0.004f, 0.038f);
	}
#endif
	
#if 0
	//////////////////////////////////////////////////////////////////////////
	// 이번에는 절대 범위(Absolute range)인 FLT_EPSILON을 이용해서 비교할게요.
	real32 jumpingPower    = 0.034f;
	real32 intervalOfValue = (jumpingPower + 0.004f) - 0.038f; // 두 값의 간격을 확인할게요.

	printf("<절대 범위를 이용해서 비교할게요>\n");
	if (std::abs(intervalOfValue) <= FLT_EPSILON)
	{
		printf("(%f + %f)와 %f는 같아요.\n", jumpingPower, 0.004f, 0.038f);
	}
	else
	{
		printf("(%f + %f)와 %f는 달라요.\n", jumpingPower, 0.004f, 0.038f);
	}

	//////////////////////////////////////////////////////////////////////////
	// 하지만 간격이 커지면 결과가 다르게 나와요.
	jumpingPower    = 3.4f;
	intervalOfValue = (jumpingPower + 0.4f) - 3.8f;

	if (std::abs(intervalOfValue) <= FLT_EPSILON)
	{
		printf("(%f + %f)와 %f는 같아요.\n", jumpingPower, 0.4f, 3.8f);
	}
	else
	{
		printf("(%f + %f)와 %f는 달라요.\n", jumpingPower, 0.4f, 3.8f);
	}
#endif

#if 0
	//////////////////////////////////////////////////////////////////////////
	// 이번에는 상대 범위(Relative range)를 이용해서 비교할게요.
	real32 jumpingPower    = 0.034f;
	real32 intervalOfValue = (jumpingPower + 0.004f) - 0.038f;
	real32 largerValue     = std::fmax(jumpingPower + 0.004f, 0.038f); // 더 큰 값을 찾을게요.

	printf("<상대 범위를 이용해서 비교할게요>\n");
	if (std::abs(intervalOfValue) <= FLT_EPSILON * largerValue)
	{
		printf("(%f + %f)와 %f는 같아요.\n", jumpingPower, 0.004f, 0.038f);
	}
	else
	{
		printf("(%f + %f)와 %f는 달라요.\n", jumpingPower, 0.004f, 0.038f);
	}

	//////////////////////////////////////////////////////////////////////////
	// 이번에는 간격이 커져도 문제 없어요!
	jumpingPower    = 3.4f;
	intervalOfValue = (jumpingPower + 0.4f) - 3.8f;
	largerValue     = std::fmax(jumpingPower + 0.4f, 3.8f);

	if (std::abs(intervalOfValue) <= FLT_EPSILON * std::abs(largerValue))
	{
		printf("(%f + %f)와 %f는 같아요.\n", jumpingPower, 0.4f, 3.8f);
	}
	else
	{
		printf("(%f + %f)와 %f는 달라요.\n", jumpingPower, 0.4f, 3.8f);
	}
#endif

	return 0;
}