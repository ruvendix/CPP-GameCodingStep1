// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <string>

using int32 = signed __int32; // "typedef signed __int32 int32"�� ���ƿ�.

int main()
{
#if 0
	//////////////////////////////////////////////////////////////////////////
	// �����ڸ� �˾ƺ��Կ�~
	//////////////////////////////////////////////////////////////////////////
	int32  forceLevel = 4;
	int32& refForceLevel = forceLevel; // �����ڴ� �ʱ�ȭ �ʼ�!

	++refForceLevel;
	printf("���� ���� : %d (����)\n", forceLevel);
	printf("���� ���� : %d (������)\n", refForceLevel);

	const int32& refConstForceLevel = refForceLevel; // �����ڳ����� �Ҵ� ����!
	//++refConstForceLevel; // const�� ���� �����ڴ� ���� �Ұ���!
#endif

#if 0
	//////////////////////////////////////////////////////////////////////////
	// �����ڸ� �ݺ��ڷ� �̿��غ��Կ�~
	//////////////////////////////////////////////////////////////////////////
	std::string szAnimalsName[4] = { "��", "����", "����", "�ڳ���" };

	// ������ iter�� ������ ���簡 �߻����� �ʾƿ�.
	printf("<�����ڸ� ����� �������>\n");
	for (std::string& iter : szAnimalsName)
	{
		iter.insert(0, "������ ");
		printf("���� ��� : %s\n", iter.c_str());

		// �����͸� ������� �����ҰԿ�.
		iter = iter.substr(7, iter.length());
	}
	printf("\n");

	printf("<const �����ڸ� ����� �������>\n");
	for (const std::string& iter : szAnimalsName)
	{
		//iter.insert(0, "������ "); // const �����ڴ� �����͸� ������ �� �����!
		printf("���� ��� : %s\n", iter.c_str());
	}
	printf("\n");
#endif

	return EXIT_SUCCESS;
}