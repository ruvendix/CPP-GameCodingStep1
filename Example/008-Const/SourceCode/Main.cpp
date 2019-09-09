// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <string>

using int32  = signed __int32; // "typedef signed __int32 int32"와 같아요.
using real32 = float;          // "typedef float real32"와 같아요.

int main()
{
#if 0
	//////////////////////////////////////////////////////////////////////////
	// 리터럴 타입을 알아볼게요~
	//////////////////////////////////////////////////////////////////////////
	
	int32 winCount = 100; // 100이란 숫자는 정수 리터럴, 즉 리터럴 타입은 int
	printf("이긴 횟수   : %d\n", winCount);

	real32 criticalChance = 78.32f; // 78.32f란 숫자는 실수 리터럴, 즉 리터럴 타입은 float
	printf("치명타 확률 : %5.2f\n", criticalChance);
#endif

#if 0
	//////////////////////////////////////////////////////////////////////////
	// 리터럴 상수를 알아볼게요~
	//////////////////////////////////////////////////////////////////////////

	// 100이란 숫자는 정수 리터럴이자 리터럴 상수, 즉 리터럴 타입은 int
	// winCount은 const로 설정된 심볼릭 상수
	const int32 winCount = 100;
	printf("이긴 횟수   : %d\n", winCount);

	// 78.32f란 숫자는 실수 리터럴, 즉 리터럴 타입은 float
	// criticalChance은 const로 설정된 심볼릭 상수
	const real32 criticalChance = 78.32f;
	printf("치명타 확률 : %5.2f\n", criticalChance);
#endif

#if 0
	//////////////////////////////////////////////////////////////////////////
	// 리터럴 상수를 배열의 개수로 이용해볼게요~
	//////////////////////////////////////////////////////////////////////////

	const int32 enemyCount = 4;
	std::string szEnmiesName[enemyCount] = { "달팽이", "리본돼지", "주황버섯", "슬라임" };
	
	// C+11부터 가능한 범위 기반 for(Range-for loop)에요.
	// 반복자를 의미하는 Iterator는 약자로, i 또는 iter로 자주 사용되니까 기억해두세요.
	// 참고로 몹(Mob)은 Mobile의 약자로, 게임에서는 움직이는 오브젝트를 표현하는 용어로 사용되요~
	for (std::string iter : szEnmiesName)
	{
		printf("몹 이름 : %s\n", iter.c_str());
	}
	printf("\n");
#endif

	return EXIT_SUCCESS;
}