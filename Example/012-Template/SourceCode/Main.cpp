// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <safeint.h>
#include <string>
#include <type_traits>
#include <array>
#include <random>

using int32  = signed __int32;
using uint32 = unsigned __int32;
using real32 = float;

// 템플릿은 선언과 동시에 정의하는 게 좋아요! (선언과 동시는 분리 가능하지만 파일로 분리할 수 없음)
// 그래서 템플릿을 사용하게 되면 소스 코드를 무조건 공개해야 하죠.
// 함수인 경우, 이런 틀을 "함수 템플릿"이라고 해요.
// "함수 템플릿"으로 만들어지는 함수를 "템플릿 함수"라고 하죠.
// "템플릿 함수"는 컴파일 타임에 정해지므로, 자료형이 맞지 않으면 컴파일 실패나요...
template <typename TNum>
TNum ClampNum(TNum num, TNum minNum, TNum maxNum)
{
	TNum resultNum = num;

	if (num < minNum)
	{
		resultNum = minNum;
	}
	else if (num > maxNum)
	{
		resultNum = maxNum;
	}

	return resultNum;
}

int32 AddIntNum(int32 LHS, int32 RHS);      // 정수끼리 더해줘요.
int32 SubtractIntNum(int32 LHS, int32 RHS); // 정수끼리 빼줘요.
int32 MultiplyIntNum(int32 LHS, int32 RHS); // 정수끼리 곱해줘요.
int32 DivideIntNum(int32 LHS, int32 RHS);   // 정수끼리 나눴을 때의 몫을 알려줘요.
int32 ModulusIntNum(int32 LHS, int32 RHS);  // 정수끼리 나눴을 때의 나머지를 알려줘요.

// 자료형 특질은 static_assert와 함께 사용하면 좋아요.
// 몇 개만 만들어볼게요.
template <typename TData>
void CheckType(const TData& data)
{
	static_assert(std::is_integral_v<TData>, "It is not int num!\n");
	static_assert(std::is_floating_point_v<TData>, "It is not real num!\n");
	static_assert(std::is_array_v<TData>, "It is not array!\n"); // 문법에서 인정한 배열만 가능!
}

// std::array는 참조자로 전달하면 편해요.
// 하지만 여전히 요소 개수는 제한적이에요.
// 이럴 때 비타입 인자를 이용하면 모든 배열에 적용 가능해요.
template <typename TData, int32 elemCount>
void ShowArrayElem(const std::array<TData, elemCount>& arr)
{
	for (const TData& iter : arr)
	{
		// printf는 다양한 자료형에 대응할 수 없으니 원래는 std::cout을 사용해야 해요.
		// 우리는 printf만 사용하고 있으니까, 자료형 특질을 이용해서 처리해볼게요.
		// 원래는 이렇게 사용하지 않는데 예제니까 보여드릴게요.
		if constexpr (std::is_integral_v<TData>)
		{
			printf("%d ", iter);
		}
		else if constexpr (std::is_floating_point_v<TData>)
		{
			printf("%f ", iter);
		}
		else
		{
			printf("%s ", iter.c_str());
		}
	}
	printf("\n\n");
}

// 의사 난수 배열을 인자로 받아서 각 빈도수를 알려줘요.
template <typename TData, int32 elemCount, int32 randomRange>
void ShowFrequencyByRandomNumArray(const std::array<TData, elemCount>& arr, std::array<TData, randomRange>& arrResult)
{
	for (const TData& iter : arr)
	{
		arrResult.at(iter)++;
	}

	for (int32 i = 0; i < randomRange; ++i)
	{
		printf("\"%d\"이(가) 뽑힌 횟수 : %d\n", i, arrResult.at(i));
	}
	printf("\n");
}

int main()
{
#if 0
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 정수의 ClampNum이에요.
	int32 intNum = 999;
	printf("intNum의 값 : %d\n", intNum);
	intNum = ClampNum<int32>(intNum, 0, 100); // 원래는 이렇게 써야 해요.
	printf("intNum의 값 : %d\n\n", intNum);
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 실수의 ClampNum이에요.
	real32 realNum = 999.99f;
	printf("realNum의 값 : %.2f\n", realNum);
	realNum = ClampNum(realNum, 0.0f, 100.0f); // 함수는 이렇게 생략 가능해요.
	printf("realNum의 값 : %.2f\n", realNum);
#endif

#if 0
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 템플릿이 활용된 SafeInt에요.
	msl::utilities::SafeInt<int32> safeIntNum = 0; // int32의 템플릿 버전 같은 거예요.
	safeIntNum = safeIntNum + 10; // 일반 정수와도 연산이 가능해요.
	printf("safeIntNum의 값 : %d\n\n", safeIntNum.Ref()); // 데이터는 Ref로 가져와요.

	// 덧셈, 뺄셈, 곱셈, 나눗셈 함수를 래핑해볼게요.
	// 각 연산자마다 오버로딩을 하면 더 편해지겠죠?
	// 참고로 "SafeInt <-> int32"는 가능해요!
	AddIntNum(safeIntNum, INT_MAX);
	SubtractIntNum(safeIntNum, -INT_MAX);
	MultiplyIntNum(safeIntNum, INT_MAX);
	DivideIntNum(safeIntNum, 0);
	ModulusIntNum(safeIntNum, 0);
#endif

#if 0
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 템플릿이 활용된 캐스팅을 알아볼게요.
	// 지금은 static_cast만 알아볼 수 있어요.

	// static_cast
	// 실수 좌표를 정수 좌표로 캐스팅하는 건 게임 코딩에서 쉽게 볼 수 있어요.
	// 앞으로 모든 캐스팅은 static_cast를 이용할게요. (C보다 안전한 캐스팅)
	real32 realPos = 29.26f;
	printf("realPos : %.2f\n", realPos);
	int32  intPos = static_cast<int32>(realPos);
	printf("intPos  : %d\n", intPos);	
#endif

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 템플릿 특수화를 이용한 자료형 특질(타입 트레잇, Type trait)이에요.
	// 개인적으로는 템플릿 특수화가 잘 활용된 기능이라고 생각해요.
	// 직접 구현하려면 구조체를 알아야 하므로, 이번에는 사용만 해볼게요.
	// 동시에 확인하면 보기가 어려우니까 한번에 하나씩 확인해볼게요.
#if 0
	int32 intNum = 10;
	CheckType(intNum);
#endif

#if 0
	real32 realNum = 10.99f;
	CheckType(realNum);
#endif

#if 0
	int32 arrayNum[4];
	CheckType(arrayNum);
#endif

#if 0
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 이제부터 배열은 std::array만 사용할게요.
	// 자료형 특질 기능을 사용하려면 템플릿 특수화가 필요해요.
	std::array<int32, 4> arrTest = { 10, 20, 30, 40 }; // 배열처럼 초기화 가능!

	// 일반 배열처럼 for 사용 가능!
	printf("std::array를 일반배열처럼 출력해볼게요!\n");
	int32 elemCount = arrTest.size();
	for (int32 i = 0; i < elemCount; ++i)
	{
		printf("%d ", arrTest[i]);
	}
	printf("\n\n");

	// 인덱스 검사 가능!
	//arrTest.at(4);

	// 값 통일 가능!
	arrTest.fill(50);

	// 범위 기반 for 사용 가능!
	printf("std::array를 범위 기반 for로 출력해볼게요!\n");
	for (int32 iter : arrTest)
	{
		printf("%d ", iter);
	}
	printf("\n\n");

	// 언제든지 초기화 가능!
	arrTest = { 25, 25, 25 };
	printf("std::array를 범위 기반 for로 출력해볼게요!\n");
	for (int32 iter : arrTest)
	{
		printf("%d ", iter);
	}
	printf("\n\n");

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 정수, 실수, 문자열 배열을 만들어볼게요.
	std::array<int32, 4> arrIntNumTable = { 100, 200, 300, 400 };
	printf("정수 배열을 출력해볼게요.\n");
	ShowArrayElem(arrIntNumTable);

	std::array<real32, 2> arrRealNumTable = { 11.11f, 22.22f };
	printf("실수 배열을 출력해볼게요.\n");
	ShowArrayElem(arrRealNumTable);

	std::array<std::string, 5> arrSoldierClasses = { "돌격병", "척탄병", "특수병", "저격병", "사이오니스트" };
	printf("문자열 배열을 출력해볼게요.\n");
	ShowArrayElem(arrSoldierClasses);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

#if 0
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 공통적으로 사용할 데이터
	const int32 MAX_TRIAL_COUNT = 2000;
	std::array<int32, 10> arrResult = { 0 };
	std::array<int32, MAX_TRIAL_COUNT> arrRandomNum = { 0 };
	printf("확률을 테스트해볼게요. (시행 횟수(%d) 범위(%d ~ %d))\n\n", MAX_TRIAL_COUNT, 0, 10);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 1. 난수 발생기의 균일 분포
	std::random_device randomDevice; // 난수 발생기만 사용해도 의사 난수 발생!
	std::uniform_int_distribution<int32> UD_num(0, 9); // 의사 난수의 범위는 (0 ~ 9, 10개)
	for (int32 i = 0; i < MAX_TRIAL_COUNT; ++i)
	{
		arrRandomNum[i] = UD_num(randomDevice);
	}
	
	printf("<난수 발생기의 균일 분포 결과>\n");
	ShowFrequencyByRandomNumArray(arrRandomNum, arrResult);

	arrRandomNum = { 0 };
	arrResult = { 0 };

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 2. 메르센 트위스터의 균일 분포
	std::mt19937 mersenneTwister(randomDevice()); // std::default_random_engine 이것과 같음!
	for (int32 i = 0; i < MAX_TRIAL_COUNT; ++i)
	{
		arrRandomNum[i] = UD_num(mersenneTwister);
	}

	printf("<메르센 트위스터의 균일 분포 결과>\n");
	ShowFrequencyByRandomNumArray(arrRandomNum, arrResult);
	
	arrRandomNum = { 0 };
	arrResult = { 0 };

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 3. 난수 발생기의 이항 분포
	printf("이항 분포는 (시행 횟수, 성공 확률)이 필요해요\n");
	std::binomial_distribution<int32> BD_num(9); // 시행 횟수, 성공 확률 순서(디폴트 0.5)
	for (int32 i = 0; i < MAX_TRIAL_COUNT; ++i)
	{
		arrRandomNum[i] = BD_num(randomDevice);
	}

	printf("<난수 발생기의 이항 분포 결과>\n");
	ShowFrequencyByRandomNumArray(arrRandomNum, arrResult);

	arrRandomNum = { 0 };
	arrResult = { 0 };
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 4. 메르센 트위스터의 이항 분포
	printf("이항 분포는 (시행 횟수, 성공 확률)이 필요해요\n");
	for (int32 i = 0; i < MAX_TRIAL_COUNT; ++i)
	{
		arrRandomNum[i] = BD_num(mersenneTwister);
	}

	printf("<메르센 트위스터의 이항 분포 결과>\n");
	ShowFrequencyByRandomNumArray(arrRandomNum, arrResult);

	arrRandomNum = { 0 };
	arrResult = { 0 };

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 5. 시드값 적용한 메르센 트위스터의 균일 분포
	std::array<int32, std::mt19937::state_size> arrSeed; // 시드값은 624개
	std::generate_n(arrSeed.begin(), arrSeed.size(), std::ref(randomDevice)); // 624개의 랜덤 시드값 생성
	std::seed_seq seedSeq(std::begin(arrSeed), std::end(arrSeed)); // 생성된 624개의 랜덤 시드값을 전용 객체로 복사
	std::mt19937 mersenneTwisterOnSeed(seedSeq); // 메르센 트위스터에 시드값 적용

	for (int32 i = 0; i < MAX_TRIAL_COUNT; ++i)
	{
		arrRandomNum[i] = UD_num(mersenneTwisterOnSeed);
	}

	printf("<시드값 적용한 메르센 트위스터의 균일 분포 결과>\n");
	ShowFrequencyByRandomNumArray(arrRandomNum, arrResult);

	arrRandomNum = { 0 };
	arrResult = { 0 };

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 6. 시드값 적용한 메르센 트위스터의 이항 분포
	for (int32 i = 0; i < MAX_TRIAL_COUNT; ++i)
	{
		arrRandomNum[i] = BD_num(mersenneTwisterOnSeed);
	}

	printf("<시드값 적용한 메르센 트위스터의 이항 분포 결과>\n");
	ShowFrequencyByRandomNumArray(arrRandomNum, arrResult);
#endif

	return EXIT_SUCCESS;
}

int32 AddIntNum(int32 LHS, int32 RHS)
{
	int32 result = 0;
	if (msl::utilities::SafeAdd(LHS, RHS, result) == false)
	{
		printf("오버플로우가 발생했어요!\n");
	}

#if _DEBUG
	printf("<%d + %d> = %d\n\n", LHS, RHS, result);
#endif

	return result;
}

int32 SubtractIntNum(int32 LHS, int32 RHS)
{
	int32 result = 0;
	if (msl::utilities::SafeSubtract(LHS, RHS, result) == false)
	{
		printf("오버플로우가 발생했어요!\n");
	}

#if _DEBUG
	printf("<%d - %d> = %d\n\n", LHS, RHS, result);
#endif

	return result;
}

int32 MultiplyIntNum(int32 LHS, int32 RHS)
{
	int32 result = 0;
	if (msl::utilities::SafeMultiply(LHS, RHS, result) == false)
	{
		printf("오버플로우가 발생했어요!\n");
	}

#if _DEBUG
	printf("<%d * %d> = %d\n\n", LHS, RHS, result);
#endif

	return result;
}

int32 DivideIntNum(int32 LHS, int32 RHS)
{
	int32 result = 0;
	if (msl::utilities::SafeDivide(LHS, RHS, result) == false)
	{
		printf("0으로는 나눌 수 없어요!\n");
	}

#if _DEBUG
	printf("<%d / %d> = %d\n\n", LHS, RHS, result);
#endif

	return result;
}

int32 ModulusIntNum(int32 LHS, int32 RHS)
{
	int32 result = 0;
	if (msl::utilities::SafeModulus(LHS, RHS, result) == false)
	{
		printf("0으로는 나눌 수 없어요!\n");
	}

#if _DEBUG
	printf("<%d %% %d> = %d\n\n", LHS, RHS, result);
#endif

	return result;
}