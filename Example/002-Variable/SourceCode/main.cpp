// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// __int32�� ��Ī ���� ����̿���.
using int32  = __int32;          // "typedef __int32 int32"�� ���ƿ�.
using uint32 = unsigned __int32; // "typedef unsigned __int32 uint32"�� ���ƿ�.

// float�� ��Ī ���� ����̿���.
using real32 = float;  // "typedef float real32"�� ���ƿ�.
using real64 = double; // "typedef double real64"�� ���ƿ�.

int main()
{
	// #if 0 ~�� ������ ������ ���������� �ʾƿ�.
	// #if 1 ~�� ������ ������ �������ؿ�.

#if 0
	//////////////////////////////////////////////////////////////////////////
	int32 numOfPlants   = 8; // ��� �Ĺ����� ��
	int32 damageOfPlant = 4; // �Ĺ� �ϳ��� ���ط�

	// ��� �Ĺ��� ���ط�
	int32 totalDamageOfPlant = numOfPlants * damageOfPlant;
	printf("��� �Ĺ����� ��   : %d\n", numOfPlants);
	printf("�Ĺ� �ϳ��� ���ط� : %d\n", damageOfPlant);
	printf("��� �Ĺ��� ���ط� : %d\n", totalDamageOfPlant);
	printf("============================================\n");
	//////////////////////////////////////////////////////////////////////////
	int32 numOfZombies = 3; // ��� ������� ��

	// ������� ����ŭ �Ĺ����� ���ݹ�����, �׸�ŭ �Ĺ����� ���� �پ����...
	numOfPlants = numOfPlants - numOfZombies;
	printf("<�Ĺ� %d���� ����鿡�� �������... �Ф�>\n", numOfZombies);
	totalDamageOfPlant = numOfPlants * damageOfPlant; // ��� ���ط��� �ٽ� �����ؾ� �ؿ�.

	printf("��� �Ĺ����� ��   : %d\n", numOfPlants);
	printf("�Ĺ� �ϳ��� ���ط� : %d\n", damageOfPlant);
	printf("��� �Ĺ��� ���ط� : %d\n", totalDamageOfPlant);
	printf("============================================\n");
	//////////////////////////////////////////////////////////////////////////
	numOfPlants = numOfPlants + 5; // �Ĺ����� �� �ɾ����!
	printf("<�Ĺ� %d���� �� �ɾ����! ^^>\n", 5);
	totalDamageOfPlant = numOfPlants * damageOfPlant; // ��� ���ط��� �ٽ� �����ؾ� �ؿ�.
	damageOfPlant = totalDamageOfPlant / numOfPlants; // �̹����� ���������� �����غ��Կ�.

	printf("��� �Ĺ����� ��   : %d\n", numOfPlants);
	printf("�Ĺ� �ϳ��� ���ط� : %d\n", damageOfPlant);
	printf("��� �Ĺ��� ���ط� : %d\n", totalDamageOfPlant);
	//////////////////////////////////////////////////////////////////////////
#endif

#if 0
	//////////////////////////////////////////////////////////////////////////
	// ������ ������ �ִ��� �ְ�, �����÷ο� �߻���Ű��
	int32 num = INT_MAX;
	printf("num = %d\n\n", num);

	num = num + 1;
	printf("num�� 1�� ���ϸ�?\n");
	printf("num = %d (�����÷ο� �߻�!)\n" , num);
	//////////////////////////////////////////////////////////////////////////
#endif

#if 0
	//////////////////////////////////////////////////////////////////////////
	// �������� ���� ����� �Ǽ��� ��, �Ǽ��� ĳ�����ϱ�
	int32 num = 10;
	printf("%d / 3 = %d (���� ����)\n", num, num / 3);

	real32 result = ((float)(num)) / 3;
	printf("%d / 3 = %.2f (�Ǽ� ����)\n", num, result);
	//////////////////////////////////////////////////////////////////////////
#endif

	return 0;
}