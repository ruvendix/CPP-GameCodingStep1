// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>

using int32  = signed   __int32; // "typedef signed   __int32 int32"�� ���ƿ�.
using uint32 = unsigned __int32; // "typedef unsigned __int32 uint32"�� ���ƿ�.
using real32 = float;            // "typedef float real32"�� ���ƿ�.

int main()
{
	//////////////////////////////////////////////////////////////////////////
	// ������Ʈ - ��Ʋ �ùķ����͸� ��������~
	//////////////////////////////////////////////////////////////////////////
	
	printf("\n");
	printf("\t   �����������\n");
	printf("\t   <�߼���� VS ����ŷ>\n");
	printf("\t   �����������\n\n");

	// ������ HP(Hit Point), ���ݷ�, ���� �������� �����ҰԿ�.
	// �� �� �׷����� ������ ������� ������ �߰��غ�����.

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

	printf("-------------------------------------------\n");
	printf("              �߼����   ����ŷ\n");
	printf("-------------------------------------------\n");
	printf("HP           : %7d\t%7d\n", medievalKnightMaxHP, vikingMaxHP);
	printf("���ݷ�       : %7d\t%7d\n", medievalKnightAttackDamage, vikingAttackDamage);
	printf("���� ������  : %7d%%\t%7d%%\n", (int32)(medievalKnightAttackSuccessRate * 100.0f),
		(int32)(vikingAttackSuccessRate * 100.0f));
	printf("-------------------------------------------\n\n");

	// �ǻ� ���� �߻����� �õ尪�� �����ҰԿ�.
	std::srand((uint32)std::time(0));

	printf("��������������������������������������������\n");

	// �߼����� ����ŷ�� ���� �Է� �޵��� �ҰԿ�.
	int32 medievalKnightCount = 0;
	printf("�߼������ ���� �Է����ּ��� : ");
	scanf_s("%d", &medievalKnightCount);
	printf("�Էµ� �߼������ �� : %d\n\n", medievalKnightCount);
	int32 totalMedievalKnightCount = medievalKnightCount;

	int32 vikingCount = 0;
	printf("����ŷ�� ���� �Է����ּ��� : ");
	scanf_s("%d", &vikingCount);
	printf("�Էµ� ����ŷ�� �� : %d\n", vikingCount);
	int32 totalVikingCount = vikingCount;

	printf("��������������������������������������������\n");
	printf("���� ������ �����ҰԿ�~!\n\n\n\n");

	// �ڵ带 ���� ������ 1:1�� ����������,
	// ���α׷��� ������ ������ �۾��� ó���ϹǷ� ��ġ ��Ը� ����ó�� ó���ſ�!
	while ( (medievalKnightCount > 0) &&
		    (vikingCount > 0) )
	{
		real32 attackSuccessRate = 0.0f;

		// �߼���� -> ����ŷ
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

		// ����ŷ -> �߼����
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

	printf("���� ������ �������~!\n");
	printf("���� ����� �˾ƺ����?\n");
	printf("��������������������������������������������\n\n");

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	printf("-------------------------------------------\n");
	printf("              �߼����   ����ŷ\n");
	printf("-------------------------------------------\n");

	printf("��Ƴ��� �� : %7d\t%7d\n", medievalKnightCount, vikingCount);

	int32 medievalKnightDeadCount = totalMedievalKnightCount - medievalKnightCount;
	int32 vikingDeadCount = totalVikingCount - vikingCount;
	printf("����� ��   : %7d\t%7d\n", medievalKnightDeadCount, vikingDeadCount);

	// �� �δ밡 �� ���ط�
	int32 totalMedievalKnightAttackDamage = (vikingMaxHP * vikingDeadCount) + (vikingMaxHP -  vikingHP);
	int32 totalVikingAttackDamage = (medievalKnightMaxHP * medievalKnightDeadCount) + (medievalKnightMaxHP - medievalKnightHP);

	printf("�� ���ط�   : %7d\t%7d\n", totalMedievalKnightAttackDamage, totalVikingAttackDamage);	
	printf("-------------------------------------------\n");

	// ��� ���� �̰���� ������ ����غ���~
	// "�� ���ط�"�� �������� �����Ƿ� �������� �����ҰԿ�.
	// �Ʊ��� ��Ƴ��� ����ŭ 5�� ����, ������ ����� ����ŭ 3�� ����!
	int32 medievalKnightTroopScore = (medievalKnightCount * 5) + (vikingDeadCount * 3);
	int32 vikingTroopScore = (vikingCount * 5) + (medievalKnightDeadCount * 3);

	printf("����        : %7d\t%7d\n", medievalKnightTroopScore, vikingTroopScore);
	printf("-------------------------------------------\n\n");
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

	return EXIT_SUCCESS;
}