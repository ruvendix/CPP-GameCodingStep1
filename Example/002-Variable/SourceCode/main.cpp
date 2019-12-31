// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// __int32의 별칭 선언 방법이에요.
using int32  = __int32;          // "typedef __int32 int32"와 같아요.
using uint32 = unsigned __int32; // "typedef unsigned __int32 uint32"와 같아요.

// float의 별칭 선언 방법이에요.
using real32 = float;  // "typedef float real32"와 같아요.
using real64 = double; // "typedef double real64"와 같아요.

int main()
{
	// #if 0 ~는 설정한 영역을 컴파일하지 않아요.
	// #if 1 ~은 설정한 영역을 컴파일해요.

#if 0
	//////////////////////////////////////////////////////////////////////////
	int32 numOfPlants   = 8; // 모든 식물들의 수
	int32 damageOfPlant = 4; // 식물 하나의 피해량

	// 모든 식물의 피해량
	int32 totalDamageOfPlant = numOfPlants * damageOfPlant;
	printf("모든 식물들의 수   : %d\n", numOfPlants);
	printf("식물 하나의 피해량 : %d\n", damageOfPlant);
	printf("모든 식물의 피해량 : %d\n", totalDamageOfPlant);
	printf("============================================\n");
	//////////////////////////////////////////////////////////////////////////
	int32 numOfZombies = 3; // 모든 좀비들의 수

	// 좀비들의 수만큼 식물들이 공격받으면, 그만큼 식물들의 수가 줄어들어요...
	numOfPlants = numOfPlants - numOfZombies;
	printf("<식물 %d개가 좀비들에게 먹혔어요... ㅠㅠ>\n", numOfZombies);
	totalDamageOfPlant = numOfPlants * damageOfPlant; // 모든 피해량을 다시 연산해야 해요.

	printf("모든 식물들의 수   : %d\n", numOfPlants);
	printf("식물 하나의 피해량 : %d\n", damageOfPlant);
	printf("모든 식물의 피해량 : %d\n", totalDamageOfPlant);
	printf("============================================\n");
	//////////////////////////////////////////////////////////////////////////
	numOfPlants = numOfPlants + 5; // 식물들을 더 심었어요!
	printf("<식물 %d개를 더 심었어요! ^^>\n", 5);
	totalDamageOfPlant = numOfPlants * damageOfPlant; // 모든 피해량을 다시 연산해야 해요.
	damageOfPlant = totalDamageOfPlant / numOfPlants; // 이번에는 나눗셈으로 연산해볼게요.

	printf("모든 식물들의 수   : %d\n", numOfPlants);
	printf("식물 하나의 피해량 : %d\n", damageOfPlant);
	printf("모든 식물의 피해량 : %d\n", totalDamageOfPlant);
	//////////////////////////////////////////////////////////////////////////
#endif

#if 0
	//////////////////////////////////////////////////////////////////////////
	// 정수형 변수에 최댓값을 넣고, 오버플로우 발생시키기
	int32 num = INT_MAX;
	printf("num = %d\n\n", num);

	num = num + 1;
	printf("num에 1을 더하면?\n");
	printf("num = %d (오버플로우 발생!)\n" , num);
	//////////////////////////////////////////////////////////////////////////
#endif

#if 0
	//////////////////////////////////////////////////////////////////////////
	// 정수형의 연산 결과가 실수일 때, 실수로 캐스팅하기
	int32 num = 10;
	printf("%d / 3 = %d (정수 연산)\n", num, num / 3);

	real32 result = ((float)(num)) / 3;
	printf("%d / 3 = %.2f (실수 연산)\n", num, result);
	//////////////////////////////////////////////////////////////////////////
#endif

	return 0;
}