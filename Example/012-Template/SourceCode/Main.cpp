// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
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

// ���ø��� ����� ���ÿ� �����ϴ� �� ���ƿ�! (����� ���ô� �и� ���������� ���Ϸ� �и��� �� ����)
// �׷��� ���ø��� ����ϰ� �Ǹ� �ҽ� �ڵ带 ������ �����ؾ� ����.
// �Լ��� ���, �̷� Ʋ�� "�Լ� ���ø�"�̶�� �ؿ�.
// "�Լ� ���ø�"���� ��������� �Լ��� "���ø� �Լ�"��� ����.
// "���ø� �Լ�"�� ������ Ÿ�ӿ� �������Ƿ�, �ڷ����� ���� ������ ������ ���г���...
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

int32 AddIntNum(int32 LHS, int32 RHS);      // �������� �������.
int32 SubtractIntNum(int32 LHS, int32 RHS); // �������� �����.
int32 MultiplyIntNum(int32 LHS, int32 RHS); // �������� �������.
int32 DivideIntNum(int32 LHS, int32 RHS);   // �������� ������ ���� ���� �˷����.
int32 ModulusIntNum(int32 LHS, int32 RHS);  // �������� ������ ���� �������� �˷����.

// �ڷ��� Ư���� static_assert�� �Բ� ����ϸ� ���ƿ�.
// �� ���� �����Կ�.
template <typename TData>
void CheckType(const TData& data)
{
	static_assert(std::is_integral_v<TData>, "It is not int num!\n");
	static_assert(std::is_floating_point_v<TData>, "It is not real num!\n");
	static_assert(std::is_array_v<TData>, "It is not array!\n"); // �������� ������ �迭�� ����!
}

// std::array�� �����ڷ� �����ϸ� ���ؿ�.
// ������ ������ ��� ������ �������̿���.
// �̷� �� ��Ÿ�� ���ڸ� �̿��ϸ� ��� �迭�� ���� �����ؿ�.
template <typename TData, int32 elemCount>
void ShowArrayElem(const std::array<TData, elemCount>& arr)
{
	for (const TData& iter : arr)
	{
		// printf�� �پ��� �ڷ����� ������ �� ������ ������ std::cout�� ����ؾ� �ؿ�.
		// �츮�� printf�� ����ϰ� �����ϱ�, �ڷ��� Ư���� �̿��ؼ� ó���غ��Կ�.
		// ������ �̷��� ������� �ʴµ� �����ϱ� �����帱�Կ�.
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

// �ǻ� ���� �迭�� ���ڷ� �޾Ƽ� �� �󵵼��� �˷����.
template <typename TData, int32 elemCount, int32 randomRange>
void ShowFrequencyByRandomNumArray(const std::array<TData, elemCount>& arr, std::array<TData, randomRange>& arrResult)
{
	for (const TData& iter : arr)
	{
		arrResult.at(iter)++;
	}

	for (int32 i = 0; i < randomRange; ++i)
	{
		printf("\"%d\"��(��) ���� Ƚ�� : %d\n", i, arrResult.at(i));
	}
	printf("\n");
}

int main()
{
#if 0
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ������ ClampNum�̿���.
	int32 intNum = 999;
	printf("intNum�� �� : %d\n", intNum);
	intNum = ClampNum<int32>(intNum, 0, 100); // ������ �̷��� ��� �ؿ�.
	printf("intNum�� �� : %d\n\n", intNum);
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// �Ǽ��� ClampNum�̿���.
	real32 realNum = 999.99f;
	printf("realNum�� �� : %.2f\n", realNum);
	realNum = ClampNum(realNum, 0.0f, 100.0f); // �Լ��� �̷��� ���� �����ؿ�.
	printf("realNum�� �� : %.2f\n", realNum);
#endif

#if 0
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���ø��� Ȱ��� SafeInt����.
	msl::utilities::SafeInt<int32> safeIntNum = 0; // int32�� ���ø� ���� ���� �ſ���.
	safeIntNum = safeIntNum + 10; // �Ϲ� �����͵� ������ �����ؿ�.
	printf("safeIntNum�� �� : %d\n\n", safeIntNum.Ref()); // �����ʹ� Ref�� �����Ϳ�.

	// ����, ����, ����, ������ �Լ��� �����غ��Կ�.
	// �� �����ڸ��� �����ε��� �ϸ� �� ����������?
	// ����� "SafeInt <-> int32"�� �����ؿ�!
	AddIntNum(safeIntNum, INT_MAX);
	SubtractIntNum(safeIntNum, -INT_MAX);
	MultiplyIntNum(safeIntNum, INT_MAX);
	DivideIntNum(safeIntNum, 0);
	ModulusIntNum(safeIntNum, 0);
#endif

#if 0
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���ø��� Ȱ��� ĳ������ �˾ƺ��Կ�.
	// ������ static_cast�� �˾ƺ� �� �־��.

	// static_cast
	// �Ǽ� ��ǥ�� ���� ��ǥ�� ĳ�����ϴ� �� ���� �ڵ����� ���� �� �� �־��.
	// ������ ��� ĳ������ static_cast�� �̿��ҰԿ�. (C���� ������ ĳ����)
	real32 realPos = 29.26f;
	printf("realPos : %.2f\n", realPos);
	int32  intPos = static_cast<int32>(realPos);
	printf("intPos  : %d\n", intPos);	
#endif

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���ø� Ư��ȭ�� �̿��� �ڷ��� Ư��(Ÿ�� Ʈ����, Type trait)�̿���.
	// ���������δ� ���ø� Ư��ȭ�� �� Ȱ��� ����̶�� �����ؿ�.
	// ���� �����Ϸ��� ����ü�� �˾ƾ� �ϹǷ�, �̹����� ��븸 �غ��Կ�.
	// ���ÿ� Ȯ���ϸ� ���Ⱑ �����ϱ� �ѹ��� �ϳ��� Ȯ���غ��Կ�.
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
	// �������� �迭�� std::array�� ����ҰԿ�.
	// �ڷ��� Ư�� ����� ����Ϸ��� ���ø� Ư��ȭ�� �ʿ��ؿ�.
	std::array<int32, 4> arrTest = { 10, 20, 30, 40 }; // �迭ó�� �ʱ�ȭ ����!

	// �Ϲ� �迭ó�� for ��� ����!
	printf("std::array�� �Ϲݹ迭ó�� ����غ��Կ�!\n");
	int32 elemCount = arrTest.size();
	for (int32 i = 0; i < elemCount; ++i)
	{
		printf("%d ", arrTest[i]);
	}
	printf("\n\n");

	// �ε��� �˻� ����!
	//arrTest.at(4);

	// �� ���� ����!
	arrTest.fill(50);

	// ���� ��� for ��� ����!
	printf("std::array�� ���� ��� for�� ����غ��Կ�!\n");
	for (int32 iter : arrTest)
	{
		printf("%d ", iter);
	}
	printf("\n\n");

	// �������� �ʱ�ȭ ����!
	arrTest = { 25, 25, 25 };
	printf("std::array�� ���� ��� for�� ����غ��Կ�!\n");
	for (int32 iter : arrTest)
	{
		printf("%d ", iter);
	}
	printf("\n\n");

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ����, �Ǽ�, ���ڿ� �迭�� �����Կ�.
	std::array<int32, 4> arrIntNumTable = { 100, 200, 300, 400 };
	printf("���� �迭�� ����غ��Կ�.\n");
	ShowArrayElem(arrIntNumTable);

	std::array<real32, 2> arrRealNumTable = { 11.11f, 22.22f };
	printf("�Ǽ� �迭�� ����غ��Կ�.\n");
	ShowArrayElem(arrRealNumTable);

	std::array<std::string, 5> arrSoldierClasses = { "���ݺ�", "ôź��", "Ư����", "���ݺ�", "���̿��Ͻ�Ʈ" };
	printf("���ڿ� �迭�� ����غ��Կ�.\n");
	ShowArrayElem(arrSoldierClasses);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

#if 0
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���������� ����� ������
	const int32 MAX_TRIAL_COUNT = 2000;
	std::array<int32, 10> arrResult = { 0 };
	std::array<int32, MAX_TRIAL_COUNT> arrRandomNum = { 0 };
	printf("Ȯ���� �׽�Ʈ�غ��Կ�. (���� Ƚ��(%d) ����(%d ~ %d))\n\n", MAX_TRIAL_COUNT, 0, 10);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 1. ���� �߻����� ���� ����
	std::random_device randomDevice; // ���� �߻��⸸ ����ص� �ǻ� ���� �߻�!
	std::uniform_int_distribution<int32> UD_num(0, 9); // �ǻ� ������ ������ (0 ~ 9, 10��)
	for (int32 i = 0; i < MAX_TRIAL_COUNT; ++i)
	{
		arrRandomNum[i] = UD_num(randomDevice);
	}
	
	printf("<���� �߻����� ���� ���� ���>\n");
	ShowFrequencyByRandomNumArray(arrRandomNum, arrResult);

	arrRandomNum = { 0 };
	arrResult = { 0 };

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 2. �޸��� Ʈ�������� ���� ����
	std::mt19937 mersenneTwister(randomDevice()); // std::default_random_engine �̰Ͱ� ����!
	for (int32 i = 0; i < MAX_TRIAL_COUNT; ++i)
	{
		arrRandomNum[i] = UD_num(mersenneTwister);
	}

	printf("<�޸��� Ʈ�������� ���� ���� ���>\n");
	ShowFrequencyByRandomNumArray(arrRandomNum, arrResult);
	
	arrRandomNum = { 0 };
	arrResult = { 0 };

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 3. ���� �߻����� ���� ����
	printf("���� ������ (���� Ƚ��, ���� Ȯ��)�� �ʿ��ؿ�\n");
	std::binomial_distribution<int32> BD_num(9); // ���� Ƚ��, ���� Ȯ�� ����(����Ʈ 0.5)
	for (int32 i = 0; i < MAX_TRIAL_COUNT; ++i)
	{
		arrRandomNum[i] = BD_num(randomDevice);
	}

	printf("<���� �߻����� ���� ���� ���>\n");
	ShowFrequencyByRandomNumArray(arrRandomNum, arrResult);

	arrRandomNum = { 0 };
	arrResult = { 0 };
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 4. �޸��� Ʈ�������� ���� ����
	printf("���� ������ (���� Ƚ��, ���� Ȯ��)�� �ʿ��ؿ�\n");
	for (int32 i = 0; i < MAX_TRIAL_COUNT; ++i)
	{
		arrRandomNum[i] = BD_num(mersenneTwister);
	}

	printf("<�޸��� Ʈ�������� ���� ���� ���>\n");
	ShowFrequencyByRandomNumArray(arrRandomNum, arrResult);

	arrRandomNum = { 0 };
	arrResult = { 0 };

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 5. �õ尪 ������ �޸��� Ʈ�������� ���� ����
	std::array<int32, std::mt19937::state_size> arrSeed; // �õ尪�� 624��
	std::generate_n(arrSeed.begin(), arrSeed.size(), std::ref(randomDevice)); // 624���� ���� �õ尪 ����
	std::seed_seq seedSeq(std::begin(arrSeed), std::end(arrSeed)); // ������ 624���� ���� �õ尪�� ���� ��ü�� ����
	std::mt19937 mersenneTwisterOnSeed(seedSeq); // �޸��� Ʈ�����Ϳ� �õ尪 ����

	for (int32 i = 0; i < MAX_TRIAL_COUNT; ++i)
	{
		arrRandomNum[i] = UD_num(mersenneTwisterOnSeed);
	}

	printf("<�õ尪 ������ �޸��� Ʈ�������� ���� ���� ���>\n");
	ShowFrequencyByRandomNumArray(arrRandomNum, arrResult);

	arrRandomNum = { 0 };
	arrResult = { 0 };

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 6. �õ尪 ������ �޸��� Ʈ�������� ���� ����
	for (int32 i = 0; i < MAX_TRIAL_COUNT; ++i)
	{
		arrRandomNum[i] = BD_num(mersenneTwisterOnSeed);
	}

	printf("<�õ尪 ������ �޸��� Ʈ�������� ���� ���� ���>\n");
	ShowFrequencyByRandomNumArray(arrRandomNum, arrResult);
#endif

	return EXIT_SUCCESS;
}

int32 AddIntNum(int32 LHS, int32 RHS)
{
	int32 result = 0;
	if (msl::utilities::SafeAdd(LHS, RHS, result) == false)
	{
		printf("�����÷ο찡 �߻��߾��!\n");
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
		printf("�����÷ο찡 �߻��߾��!\n");
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
		printf("�����÷ο찡 �߻��߾��!\n");
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
		printf("0���δ� ���� �� �����!\n");
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
		printf("0���δ� ���� �� �����!\n");
	}

#if _DEBUG
	printf("<%d %% %d> = %d\n\n", LHS, RHS, result);
#endif

	return result;
}