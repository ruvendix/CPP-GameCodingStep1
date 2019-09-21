// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <ctime>
#include <string>

using int32  = signed __int32;
using uint32 = unsigned __int32;
using real32 = float;

// constexpr�� ��ȯ�ϸ� ������ Ÿ�ӿ��� ��� �����ؿ�~!
constexpr int32 DoubleSize(int32 srcSize)
{
	return (srcSize * 2);
}

// �����ڰ� �Լ��� �Ű�������� ���������δ� const �����ڿ���.
// �Ϲ� �����ڷ� ����Ϸ��� �������� ���� ǥ���ϴ� �� ��õ�ҰԿ�! (_Out_ ������ ����)
// ������ �Ϲ� �����ڷ� ����ϰ� �Ǹ� ��� ��ٴ�...
void DoubleRefNum(_Out_ int32& targetNum)
{
	targetNum *= 2;
}

// ���ڿ� ���ͷ��� ���ڷ� ������ ���� ���� ���� ������ �־��.
// const std::string&�� �Ű������� ������� ���� �׷��ѵ�...
// C++17���ʹ� const std::string_view�� ���� ���� ������ ������ �� �־��.
// std::string���� �ٸ��� ���ڿ��� �������� �����Ƿ� c_str�� �ƴ϶� data�� �̿��ؾ� �ؿ�!
void ShowStringLineFeed(const std::string_view& srcStr)
{
	printf("%s\n", srcStr.data());
}

// ������ ���ѵ� �����θ� �������ִ� �Լ�����.
// ���� ���ø��� �˾ƺ����� �ʾ����ϱ� ������ ����Կ�.
// int32 ������ �����ڸ� ������� �ʰ� �׳� ��ȯ�ϴ� �� �����̿���~
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

// ���� �����ô� ��Ʋ �ùķ����͸� �Լ��� �����غ��Կ�~
// ������� �ִ��� �Լ��� ���� �����Կ�~
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
	strTable[lastIdx] = "������ ��ġ";
	printf("%s (�ε����� : %d)\n", strTable[lastIdx].c_str(), lastIdx);
#endif

#if 0
	int32 speed = 10;
	printf("�����ϱ� ���� �ӷ� : %d\n", speed);
	DoubleRefNum(speed);
	printf("������ ���� �ӷ�   : %d\n", speed);
#endif

#if 0
	ShowStringLineFeed("C++17���� ���� ���� ��Ʈ�� �信��~");	
	std::string strGuide = "������ std::string���� �����ص� ���� ���縦 ���� �ʾƿ�.";
	ShowStringLineFeed(strGuide);
#endif

#if 0
	//////////////////////////////////////////////////////////////////////////
	// ������Ʈ - ��Ʋ �ùķ����͸� ��������~
	//////////////////////////////////////////////////////////////////////////

	// �ǻ� ���� �߻����� �õ尪�� �����ҰԿ�.
	InitRandomSeed();

	// ���� ��Ʈ�θ� �����ٰԿ�.
	ShowIntro();

	// �߼������ �⺻ ������ ���ҰԿ�.
	int32  medievalKnightMaxHP = 180;
	int32  medievalKnightHP = medievalKnightMaxHP;
	int32  medievalKnightAttackDamage = 14;
	real32 medievalKnightAttackSuccessRate = 0.78f;

	// ����ŷ�� �⺻ ������ ���ҰԿ�.
	int32  vikingMaxHP = 198;
	int32  vikingHP = vikingMaxHP;
	int32  vikingAttackDamage = 18;
	real32 vikingAttackSuccessRate = 0.52f;

	// ������ ������ ������ ����ҰԿ�.
	ShowUnitStat(medievalKnightMaxHP, medievalKnightAttackDamage, medievalKnightAttackSuccessRate,
		         vikingMaxHP, vikingAttackDamage, vikingAttackSuccessRate);

	printf("��������������������������������������������\n");

	// �߼����� ����ŷ�� ���� �Է� ���� �� �ֵ��� ������ ����Կ�.
	int32 medievalKnightCount = 0;
	int32 totalMedievalKnightCount = 0;
	int32 vikingCount = 0;
	int32 totalVikingCount = 0;

	// �߼����� ����ŷ�� ���� �Է� �����Կ�.
	// �Է¿� ������ �߻��Ǹ� ������ ������ѿ�~
	if (InputUnitCount(medievalKnightCount, totalMedievalKnightCount, vikingCount, totalVikingCount) == false)
	{
		printf("�Է� ������ ���� ������ ���� ����Ǿ����... ��_��\n\n");
		return EXIT_FAILURE;
	}

	printf("��������������������������������������������\n\n");
	printf("���� ������ �����ҰԿ�~!\n.\n.\n.\n");

	// �ڵ带 ���� ������ 1:1�� ����������,
	// ���α׷��� ������ ������ �۾��� ó���ϹǷ� ��ġ ��Ը� ����ó�� ó���ſ�!
	while ( (medievalKnightCount > 0) &&
		    (vikingCount > 0) )
	{
		// �߼���� -> ����ŷ
		AttackUnit(medievalKnightAttackSuccessRate, medievalKnightAttackDamage, vikingMaxHP, vikingHP, vikingCount);

		// ����ŷ -> �߼����
		AttackUnit(vikingAttackSuccessRate, vikingAttackDamage, medievalKnightMaxHP, medievalKnightHP, medievalKnightCount);
	}

	printf("���� ������ �������~!\n");
	printf("���� ����� �˾ƺ����?\n\n");

	// ����� ������ ���� ���غ��Կ�.
	int32 medievalKnightDeadCount = totalMedievalKnightCount - medievalKnightCount;
	int32 vikingDeadCount = totalVikingCount - vikingCount;

	// ���� ����� ����غ��Կ�.
	ShowBattleReport(totalMedievalKnightCount, medievalKnightCount, medievalKnightMaxHP, medievalKnightHP,
		             medievalKnightDeadCount, totalVikingCount, vikingCount, vikingMaxHP, vikingHP, vikingDeadCount);

	// ���� ������ ���غ��Կ�.
	int32 medievalKnightTroopScore = CalcBattleScore(medievalKnightCount, vikingDeadCount);
	int32 vikingTroopScore = CalcBattleScore(vikingCount, medievalKnightDeadCount);

	// ���� ������ ����غ��Կ�.
	printf("����        : %7d\t%7d\n", medievalKnightTroopScore, vikingTroopScore);
	printf("-------------------------------------------\n\n");

	// ���� �������� �̰���� �˾ƺ��Կ�.
	ShowBattleWinner(medievalKnightTroopScore, vikingTroopScore);
#endif

	return EXIT_SUCCESS;
}

void ShowIntro()
{
	printf("\n");
	printf("\t   �����������\n");
	printf("\t   <�߼���� VS ����ŷ>\n");
	printf("\t   �����������\n\n");
}

void ShowUnitStat(int32 medievalKnightMaxHP, int32 medievalKnightAttackDamage, real32 medievalKnightAttackSuccessRate,
	              int32 vikingMaxHP, int32 vikingAttackDamage, real32 vikingKnightAttackSuccessRate)
{
	printf("-------------------------------------------\n");
	printf("              �߼����   ����ŷ\n");
	printf("-------------------------------------------\n");
	printf("HP           : %7d\t%7d\n", medievalKnightMaxHP, vikingMaxHP);
	printf("���ݷ�       : %7d\t%7d\n", medievalKnightAttackDamage, vikingAttackDamage);
	printf("���� ������  : %7d%%\t%7d%%\n", (int32)(medievalKnightAttackSuccessRate * 100.0f),
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
	printf("�߼������ ���� �Է����ּ��� : ");
	int32 inputResult = scanf_s("%d", &medievalKnightCount);
	if (inputResult == 0)
	{
		printf("������ �Է� �����ؿ�!\n");
		return false;
	}

	medievalKnightCount = ClampNum(medievalKnightCount, 0, INT_MAX);
	printf("�Էµ� �߼������ �� : %d\n\n", medievalKnightCount);
	totalMedievalKnightCount = medievalKnightCount;

	printf("����ŷ�� ���� �Է����ּ��� : ");
	inputResult = scanf_s("%d", &vikingCount);
	if (inputResult == 0)
	{
		printf("������ �Է� �����ؿ�!\n");
		return false;
	}

	vikingCount = ClampNum(vikingCount, 0, INT_MAX);
	printf("�Էµ� ����ŷ�� �� : %d\n", vikingCount);
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
	printf("              �߼����   ����ŷ\n");
	printf("-------------------------------------------\n");

	printf("��Ƴ��� �� : %7d\t%7d\n", medievalKnightCount, vikingCount);
	printf("����� ��   : %7d\t%7d\n", medievalKnightDeadCount, vikingDeadCount);

	// �� �δ밡 �� ���ط�
	int32 totalMedievalKnightAttackDamage = (vikingMaxHP * vikingDeadCount) + (vikingMaxHP - vikingHP);
	int32 totalVikingAttackDamage = (medievalKnightMaxHP * medievalKnightDeadCount) + (medievalKnightMaxHP - medievalKnightHP);

	printf("�� ���ط�   : %7d\t%7d\n", totalMedievalKnightAttackDamage, totalVikingAttackDamage);
	printf("-------------------------------------------\n");
}

int32 CalcBattleScore(int32 survivedUnitCount, int32 enemyDeadCount)
{
	return ((survivedUnitCount * 5) + (enemyDeadCount * 3));
}

void ShowBattleWinner(int32 medievalKnightTroopScore, int32 vikingTroopScore)
{
	printf("�� �¸��� �δ�� ");
	if (medievalKnightTroopScore == vikingTroopScore)
	{
		printf("���׿�... ������ �����ؿ�.");
	}
	else
	{
		std::string szWinner;
		if (medievalKnightTroopScore > vikingTroopScore)
		{
			szWinner = "�߼����";
		}
		else
		{
			szWinner = "����ŷ";
		}

		printf("\"%s\" �δ�׿�~!", szWinner.c_str());
	}
	printf(" ��\n\n");
}