// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <ctime>
#include <string>

using int32  = signed __int32;
using uint32 = unsigned __int32;
using real32 = float;

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

// 정수를 제한된 범위로만 고정해주는 함수에요.
// 아직 템플릿을 알아보지는 않았으니까 정수만 만들게요.
// int32 정도는 참조자를 사용하지 않고 그냥 반환하는 게 관습이에요~
int32 ClampNum(int32 num, int32 minNum, int32 maxNum)
{
	int32 resultNum = num;

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

// 전에 만들어봤던 배틀 시뮬레이터르 함수로 변경해볼게요~
// 예제답게 최대한 함수를 많이 만들어볼게요~
void ShowIntro();
void ShowUnitStat(int32 medievalKnightMaxHP, int32 medievalKnightAttackDamage, real32 medievalKnightAttackSuccessRate,
	              int32 vikingMaxHP, int32 vikingAttackDamage, real32 vikingKnightAttackSuccessRate);
void InitRandomSeed();
bool InputUnitCount(_Out_ int32& medievalKnightCount, _Out_ int32& totalMedievalKnightCount,
	                _Out_ int32& vikingCount, _Out_ int32& totalVikingCount);
bool AttackUnit(real32 attackSuccessRate, int32 attackdDamage, int32 targetMaxHP,
	            _Out_ int32& targetHP, _Out_ int32& targetCount);
void ShowBattleReport(int32 totalMedievalKnightCount, int32 medievalKnightCount,
	                  int32 medievalKnightMaxHP, int32 medievalKnightHP, int32 medievalKnightDeadCount,
	                  int32 totalVikingCount, int32 vikingCount, int32 vikingMaxHP, int32 vikingHP, int32 vikingDeadCount);
int32 CalcBattleScore(int32 survivedUnitCount, int32 enemyDeadCount);
void ShowBattleWinner(int32 medievalKnightTroopScore, int32 vikingTroopScore);

int main()
{
#if 0
	std::string strTable[DoubleSize(4)];
	int32 lastIdx = _countof(strTable) - 1;
	strTable[lastIdx] = "마지막 위치";
	printf("%s (인덱스값 : %d)\n", strTable[lastIdx].c_str(), lastIdx);
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
	//////////////////////////////////////////////////////////////////////////
	// 프로젝트 - 배틀 시뮬레이터를 만들어봐요~
	//////////////////////////////////////////////////////////////////////////

	// 의사 난수 발생기의 시드값을 설정할게요.
	InitRandomSeed();

	// 게임 인트로를 보여줄게요.
	ShowIntro();

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

	// 설정된 유닛의 스탯을 출력할게요.
	ShowUnitStat(medievalKnightMaxHP, medievalKnightAttackDamage, medievalKnightAttackSuccessRate,
		         vikingMaxHP, vikingAttackDamage, vikingAttackSuccessRate);

	printf("∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼\n");

	// 중세기사와 바이킹의 수를 입력 받을 수 있도록 변수를 만들게요.
	int32 medievalKnightCount = 0;
	int32 totalMedievalKnightCount = 0;
	int32 vikingCount = 0;
	int32 totalVikingCount = 0;

	// 중세기사와 바이킹의 수를 입력 받을게요.
	// 입력에 오류가 발생되면 게임을 종료시켜요~
	if (InputUnitCount(medievalKnightCount, totalMedievalKnightCount, vikingCount, totalVikingCount) == false)
	{
		printf("입력 오류로 인해 게임이 강제 종료되었어요... ㅠ_ㅠ\n\n");
		return EXIT_FAILURE;
	}

	printf("∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼\n\n");
	printf("모의 전투를 시작할게요~!\n.\n.\n.\n");

	// 코드를 보면 전투는 1:1로 벌어지지만,
	// 프로그램이 굉장히 빠르게 작업을 처리하므로 마치 대규모 전투처럼 처리돼요!
	while ( (medievalKnightCount > 0) &&
		    (vikingCount > 0) )
	{
		// 중세기사 -> 바이킹
		AttackUnit(medievalKnightAttackSuccessRate, medievalKnightAttackDamage, vikingMaxHP, vikingHP, vikingCount);

		// 바이킹 -> 중세기사
		AttackUnit(vikingAttackSuccessRate, vikingAttackDamage, medievalKnightMaxHP, medievalKnightHP, medievalKnightCount);
	}

	printf("모의 전투가 끝났어요~!\n");
	printf("전투 결과를 알아볼까요?\n\n");

	// 사망한 유닛의 수를 구해볼게요.
	int32 medievalKnightDeadCount = totalMedievalKnightCount - medievalKnightCount;
	int32 vikingDeadCount = totalVikingCount - vikingCount;

	// 전투 결과를 출력해볼게요.
	ShowBattleReport(totalMedievalKnightCount, medievalKnightCount, medievalKnightMaxHP, medievalKnightHP,
		             medievalKnightDeadCount, totalVikingCount, vikingCount, vikingMaxHP, vikingHP, vikingDeadCount);

	// 전투 총점을 구해볼게요.
	int32 medievalKnightTroopScore = CalcBattleScore(medievalKnightCount, vikingDeadCount);
	int32 vikingTroopScore = CalcBattleScore(vikingCount, medievalKnightDeadCount);

	// 전투 총점을 출력해볼게요.
	printf("총점        : %7d\t%7d\n", medievalKnightTroopScore, vikingTroopScore);
	printf("-------------------------------------------\n\n");

	// 누가 전투에서 이겼는지 알아볼게요.
	ShowBattleWinner(medievalKnightTroopScore, vikingTroopScore);
#endif

	return EXIT_SUCCESS;
}

void ShowIntro()
{
	printf("\n");
	printf("\t   ▲▲▲▲▲▲▲▲▲▲\n");
	printf("\t   <중세기사 VS 바이킹>\n");
	printf("\t   ▼▼▼▼▼▼▼▼▼▼\n\n");
}

void ShowUnitStat(int32 medievalKnightMaxHP, int32 medievalKnightAttackDamage, real32 medievalKnightAttackSuccessRate,
	              int32 vikingMaxHP, int32 vikingAttackDamage, real32 vikingKnightAttackSuccessRate)
{
	printf("-------------------------------------------\n");
	printf("              중세기사   바이킹\n");
	printf("-------------------------------------------\n");
	printf("HP           : %7d\t%7d\n", medievalKnightMaxHP, vikingMaxHP);
	printf("공격력       : %7d\t%7d\n", medievalKnightAttackDamage, vikingAttackDamage);
	printf("공격 성공율  : %7d%%\t%7d%%\n", (int32)(medievalKnightAttackSuccessRate * 100.0f),
		(int32)(vikingKnightAttackSuccessRate * 100.0f));
	printf("-------------------------------------------\n\n");
}

void InitRandomSeed()
{
	std::srand((uint32)std::time(0));
}

bool InputUnitCount(_Out_ int32& medievalKnightCount, _Out_ int32& totalMedievalKnightCount,
	                _Out_ int32& vikingCount, _Out_ int32& totalVikingCount)
{
	printf("중세기사의 수를 입력해주세요 : ");
	int32 inputResult = scanf_s("%d", &medievalKnightCount);
	if (inputResult == 0)
	{
		printf("정수만 입력 가능해요!\n");
		return false;
	}

	medievalKnightCount = ClampNum(medievalKnightCount, 0, INT_MAX);
	printf("입력된 중세기사의 수 : %d\n\n", medievalKnightCount);
	totalMedievalKnightCount = medievalKnightCount;

	printf("바이킹의 수를 입력해주세요 : ");
	inputResult = scanf_s("%d", &vikingCount);
	if (inputResult == 0)
	{
		printf("정수만 입력 가능해요!\n");
		return false;
	}

	vikingCount = ClampNum(vikingCount, 0, INT_MAX);
	printf("입력된 바이킹의 수 : %d\n", vikingCount);
	totalVikingCount = vikingCount;

	return true;
}

bool AttackUnit(real32 attackSuccessRate, int32 attackdDamage, int32 targetMaxHP,
	            _Out_ int32& targetHP, _Out_ int32& targetCount)
{
	real32 randomRate = (std::rand() % (100 + 1)) * 0.01f;
	if (randomRate < attackSuccessRate)
	{
		targetHP -= attackdDamage;

		if (targetHP <= 0)
		{
			targetHP = targetMaxHP;
			--targetCount;
		}

		return true;
	}

	return false;
}

void ShowBattleReport(int32 totalMedievalKnightCount, int32 medievalKnightCount,
	                  int32 medievalKnightMaxHP, int32 medievalKnightHP, int32 medievalKnightDeadCount,
	                  int32 totalVikingCount, int32 vikingCount, int32 vikingMaxHP, int32 vikingHP, int32 vikingDeadCount)
{
	printf("-------------------------------------------\n");
	printf("              중세기사   바이킹\n");
	printf("-------------------------------------------\n");

	printf("살아남은 수 : %7d\t%7d\n", medievalKnightCount, vikingCount);
	printf("사망한 수   : %7d\t%7d\n", medievalKnightDeadCount, vikingDeadCount);

	// 각 부대가 준 피해량
	int32 totalMedievalKnightAttackDamage = (vikingMaxHP * vikingDeadCount) + (vikingMaxHP - vikingHP);
	int32 totalVikingAttackDamage = (medievalKnightMaxHP * medievalKnightDeadCount) + (medievalKnightMaxHP - medievalKnightHP);

	printf("준 피해량   : %7d\t%7d\n", totalMedievalKnightAttackDamage, totalVikingAttackDamage);
	printf("-------------------------------------------\n");
}

int32 CalcBattleScore(int32 survivedUnitCount, int32 enemyDeadCount)
{
	return ((survivedUnitCount * 5) + (enemyDeadCount * 3));
}

void ShowBattleWinner(int32 medievalKnightTroopScore, int32 vikingTroopScore)
{
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
}