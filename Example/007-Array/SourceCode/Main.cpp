// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <string>

using int32 = signed   __int32; // "typedef signed   __int32 int32"�� ���ƿ�.

int main()
{
#if 0

	//////////////////////////////////////////////////////////////////////////
	// 1���� �迭�� �̿��غ���~
	//////////////////////////////////////////////////////////////////////////

	// std::string��ŭ�� ������ 4�� ���� �迭�̿���.
	std::string techTreeTable[4];

	// �迭�� �ε����� 0���� �����ؿ�!
	techTreeTable[0] = "����ü";
	techTreeTable[1] = "����";
	techTreeTable[2] = "���ְ���";
	techTreeTable[3] = "�κ����нü�";

	printf("<1���� �迭�� ���ڿ� ����ϱ�~>\n\n");
	for (int32 i = 0; i < 4; ++i)
	{
		printf("\"%s\"\n", techTreeTable[i].c_str());
	}
	printf("\n");

#endif

#if 0

	//////////////////////////////////////////////////////////////////////////
	// 2���� �迭�� �̿��غ���~
	//////////////////////////////////////////////////////////////////////////

	// std::string��ŭ�� ������ 7���� ���� �ִ� �迭 4������.
	// ��, "4 * 7 = 28"���� ������ ���� ����~
	std::string techTreeTable[4][7];

	// ����ü�� �����ҰԿ�.
	techTreeTable[0][0] = "����ü";
	techTreeTable[0][1] = "Ž����";
	techTreeTable[0][2] = "��";

	// ������ �����ҰԿ�.
	techTreeTable[1][0] = "����";
	techTreeTable[1][1] = "������";
	techTreeTable[1][2] = "�ļ���";
	techTreeTable[1][3] = "������";
	techTreeTable[1][4] = "�絵";
	techTreeTable[1][5] = "���� ���";
	techTreeTable[1][6] = "���� ���";

	// ���ְ����� �����ҰԿ�.
	techTreeTable[2][0] = "���ְ���";
	techTreeTable[2][1] = "�һ���";
	techTreeTable[2][2] = "������";
	techTreeTable[2][3] = "���� ���ݱ�";
	techTreeTable[2][4] = "��ǳ��";
	techTreeTable[2][5] = "���ָ���";

	// �κ����� �ü��� �����ҰԿ�.
	techTreeTable[3][0] = "�κ����� �ü�";
	techTreeTable[3][1] = "������";
	techTreeTable[3][2] = "���� �б���";
	techTreeTable[3][3] = "�Ҹ���";
	techTreeTable[3][4] = "�Ž�";
	techTreeTable[3][5] = "�п���";

	printf("<2���� �迭�� ���ڿ� ����ϱ�~>\n\n");
	for (int32 i = 0; i < 4; ++i)
	{
		printf("\"%s\" ��ũ Ʈ��\n", techTreeTable[i][0].c_str());

		for (int32 j = 1; j < 7; ++j)
		{
			std::string szTechTreeUnitName = techTreeTable[i][j];
			if (szTechTreeUnitName.empty() == true)
			{
				break;
			}

			printf("   \"%s\"\n", techTreeTable[i][j].c_str());
		}

		printf("\n");
	}

#endif

	return EXIT_SUCCESS;
}