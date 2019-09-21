// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>

using int32  = signed   __int32; // "typedef signed   __int32 int32"와 같아요.
using uint32 = unsigned __int32; // "typedef unsigned __int32 uint32"와 같아요.
using real32 = float;            // "typedef float real32"와 같아요.

int main()
{
	//////////////////////////////////////////////////////////////////////////
	// 프로젝트 - 배틀 시뮬레이터를 만들어봐요~
	//////////////////////////////////////////////////////////////////////////
	
	printf("\n");
	printf("\t   ▲▲▲▲▲▲▲▲▲▲\n");
	printf("\t   <중세기사 VS 바이킹>\n");
	printf("\t   ▼▼▼▼▼▼▼▼▼▼\n\n");

	// 스탯은 HP(Hit Point), 공격력, 공격 성공율만 설정할게요.
	// 좀 더 그럴듯한 게임을 만들려면 스탯을 추가해보세요.

	// 중세기사의 기본 스탯을 정할게요.
	int32  medievalKnightMaxHP = 180;
	int32  medievalKnightHP = medievalKnightMaxHP;
	int32  medievalKnightAttackDamage = 14;
	real32 medievalKnightAttackSuccessRate = 0.78f;
	
	// 바이킹의 기본 스탯을 정할게요.
	int32  vikingMaxHP = 198;
	int32  vikingHP = vikingMaxHP;
	int32  vikingAttackDamage = 18;
	real32 vikingAttackSuccessRate = 0.52f;

	printf("-------------------------------------------\n");
	printf("              중세기사   바이킹\n");
	printf("-------------------------------------------\n");
	printf("HP           : %7d\t%7d\n", medievalKnightMaxHP, vikingMaxHP);
	printf("공격력       : %7d\t%7d\n", medievalKnightAttackDamage, vikingAttackDamage);
	printf("공격 성공율  : %7d%%\t%7d%%\n", (int32)(medievalKnightAttackSuccessRate * 100.0f),
		(int32)(vikingAttackSuccessRate * 100.0f));
	printf("-------------------------------------------\n\n");

	// 의사 난수 발생기의 시드값을 설정할게요.
	std::srand((uint32)std::time(0));

	printf("∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼\n");

	// 중세기사와 바이킹의 수를 입력 받도록 할게요.
	int32 medievalKnightCount = 0;
	printf("중세기사의 수를 입력해주세요 : ");
	scanf_s("%d", &medievalKnightCount);
	printf("입력된 중세기사의 수 : %d\n\n", medievalKnightCount);
	int32 totalMedievalKnightCount = medievalKnightCount;

	int32 vikingCount = 0;
	printf("바이킹의 수를 입력해주세요 : ");
	scanf_s("%d", &vikingCount);
	printf("입력된 바이킹의 수 : %d\n", vikingCount);
	int32 totalVikingCount = vikingCount;

	printf("∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼\n");
	printf("모의 전투를 시작할게요~!\n\n\n\n");

	// 코드를 보면 전투는 1:1로 벌어지지만,
	// 프로그램이 굉장히 빠르게 작업을 처리하므로 마치 대규모 전투처럼 처리돼요!
	while ( (medievalKnightCount > 0) &&
		    (vikingCount > 0) )
	{
		real32 attackSuccessRate = 0.0f;

		// 중세기사 -> 바이킹
		attackSuccessRate = (std::rand() % (100 + 1)) * 0.01f;
		if (attackSuccessRate < medievalKnightAttackSuccessRate)
		{
			vikingHP -= medievalKnightAttackDamage;

			if (vikingHP <= 0)
			{
				vikingHP = vikingMaxHP;
				--vikingCount;
			}
		}

		// 바이킹 -> 중세기사
		attackSuccessRate = (std::rand() % (100 + 1)) * 0.01f;
		if (attackSuccessRate < vikingAttackSuccessRate)
		{
			medievalKnightHP -= vikingAttackDamage;

			if (medievalKnightHP <= 0)
			{
				medievalKnightHP = medievalKnightMaxHP;
				--medievalKnightCount;
			}
		}
	}

	printf("모의 전투가 끝났어요~!\n");
	printf("전투 결과를 알아볼까요?\n");
	printf("∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼\n\n");

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	printf("-------------------------------------------\n");
	printf("              중세기사   바이킹\n");
	printf("-------------------------------------------\n");

	printf("살아남은 수 : %7d\t%7d\n", medievalKnightCount, vikingCount);

	int32 medievalKnightDeadCount = totalMedievalKnightCount - medievalKnightCount;
	int32 vikingDeadCount = totalVikingCount - vikingCount;
	printf("사망한 수   : %7d\t%7d\n", medievalKnightDeadCount, vikingDeadCount);

	// 각 부대가 준 피해량
	int32 totalMedievalKnightAttackDamage = (vikingMaxHP * vikingDeadCount) + (vikingMaxHP -  vikingHP);
	int32 totalVikingAttackDamage = (medievalKnightMaxHP * medievalKnightDeadCount) + (medievalKnightMaxHP - medievalKnightHP);

	printf("준 피해량   : %7d\t%7d\n", totalMedievalKnightAttackDamage, totalVikingAttackDamage);	
	printf("-------------------------------------------\n");

	// 어느 쪽이 이겼는지 점수를 계산해보죠~
	// "준 피해량"은 공정하지 않으므로 점수에서 제외할게요.
	// 아군이 살아남은 수만큼 5점 득점, 적군이 사망된 수만큼 3점 득점!
	int32 medievalKnightTroopScore = (medievalKnightCount * 5) + (vikingDeadCount * 3);
	int32 vikingTroopScore = (vikingCount * 5) + (medievalKnightDeadCount * 3);

	printf("총점        : %7d\t%7d\n", medievalKnightTroopScore, vikingTroopScore);
	printf("-------------------------------------------\n\n");
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	printf("※ 승리한 부대는 ");
	if (medievalKnightTroopScore == vikingTroopScore)
	{
		printf("없네요... 점수가 동일해요.");
	}
	else
	{
		std::string szWinner;
		if (medievalKnightTroopScore > vikingTroopScore)
		{
			szWinner = "중세기사";
		}
		else
		{
			szWinner = "바이킹";
		}

		printf("\"%s\" 부대네요~!", szWinner.c_str());
	}
	printf(" ※\n\n");

	return EXIT_SUCCESS;
}