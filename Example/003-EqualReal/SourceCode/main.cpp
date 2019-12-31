// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

using int32  = __int32; // "typedef __int32 int32"�� ���ƿ�.
using real32 = float;   // "typedef float real32"�� ���ƿ�.

int main()
{
#if 0
	//////////////////////////////////////////////////////////////////////////
	// �Ǽ��� ������ �ٸ��� ���� ������ Ȯ���ϴ� �� �������.
	real32 jumpingPower = 0.034f; // float�� ���̻�(���� �ٴ� �ܾ�) f�� �ٿ��� �ؿ�.
	
	printf("<����ϰ� ���غ��Կ�>\n");
	if (jumpingPower + 0.004f == 0.038f)
	{
		printf("(%f + %f)�� %f�� ���ƿ�.\n", jumpingPower, 0.004f, 0.038f);
	}
	else
	{
		printf("(%f + %f)�� %f�� �޶��.\n", jumpingPower, 0.004f, 0.038f);
	}
#endif
	
#if 0
	//////////////////////////////////////////////////////////////////////////
	// �̹����� ���� ����(Absolute range)�� FLT_EPSILON�� �̿��ؼ� ���ҰԿ�.
	real32 jumpingPower    = 0.034f;
	real32 intervalOfValue = (jumpingPower + 0.004f) - 0.038f; // �� ���� ������ Ȯ���ҰԿ�.

	printf("<���� ������ �̿��ؼ� ���ҰԿ�>\n");
	if (std::abs(intervalOfValue) <= FLT_EPSILON)
	{
		printf("(%f + %f)�� %f�� ���ƿ�.\n", jumpingPower, 0.004f, 0.038f);
	}
	else
	{
		printf("(%f + %f)�� %f�� �޶��.\n", jumpingPower, 0.004f, 0.038f);
	}

	//////////////////////////////////////////////////////////////////////////
	// ������ ������ Ŀ���� ����� �ٸ��� ���Ϳ�.
	jumpingPower    = 3.4f;
	intervalOfValue = (jumpingPower + 0.4f) - 3.8f;

	if (std::abs(intervalOfValue) <= FLT_EPSILON)
	{
		printf("(%f + %f)�� %f�� ���ƿ�.\n", jumpingPower, 0.4f, 3.8f);
	}
	else
	{
		printf("(%f + %f)�� %f�� �޶��.\n", jumpingPower, 0.4f, 3.8f);
	}
#endif

#if 0
	//////////////////////////////////////////////////////////////////////////
	// �̹����� ��� ����(Relative range)�� �̿��ؼ� ���ҰԿ�.
	real32 jumpingPower    = 0.034f;
	real32 intervalOfValue = (jumpingPower + 0.004f) - 0.038f;
	real32 largerValue     = std::fmax(jumpingPower + 0.004f, 0.038f); // �� ū ���� ã���Կ�.

	printf("<��� ������ �̿��ؼ� ���ҰԿ�>\n");
	if (std::abs(intervalOfValue) <= FLT_EPSILON * largerValue)
	{
		printf("(%f + %f)�� %f�� ���ƿ�.\n", jumpingPower, 0.004f, 0.038f);
	}
	else
	{
		printf("(%f + %f)�� %f�� �޶��.\n", jumpingPower, 0.004f, 0.038f);
	}

	//////////////////////////////////////////////////////////////////////////
	// �̹����� ������ Ŀ���� ���� �����!
	jumpingPower    = 3.4f;
	intervalOfValue = (jumpingPower + 0.4f) - 3.8f;
	largerValue     = std::fmax(jumpingPower + 0.4f, 3.8f);

	if (std::abs(intervalOfValue) <= FLT_EPSILON * std::abs(largerValue))
	{
		printf("(%f + %f)�� %f�� ���ƿ�.\n", jumpingPower, 0.4f, 3.8f);
	}
	else
	{
		printf("(%f + %f)�� %f�� �޶��.\n", jumpingPower, 0.4f, 3.8f);
	}
#endif

	return 0;
}