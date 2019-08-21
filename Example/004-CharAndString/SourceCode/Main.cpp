// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <string> // std::string�� �־��.

using int32  = __int32; // "typedef __int32 int32"�� ���ƿ�.
using real32 = float;   // "typedef float real32"�� ���ƿ�.

int main()
{
#if 0

	//////////////////////////////////////////////////////////////////////////
	// char�� ���ؼ� ¤�� �Ѿ��~
	//////////////////////////////////////////////////////////////////////////
	
	char value = 'A'; // ASCII���� ����ǿ�~
	printf("value => %c\n", value);

	value += 1; // ASCII���� �� ����!
	printf("value => %c\n", value);

	value = '\\'; // ���� ��ο��� ���� ���Ǵ� �������ÿ���!
	if (value == '\\')
	{
		printf("value => %c\n", value);
	}

#endif

#if 0

	//////////////////////////////////////////////////////////////////////////
	// std::string�� �̿��غ���~
	//////////////////////////////////////////////////////////////////////////

	std::string szWeaponName = "����̱�"; // �̷��� �ʱ�ȭ�ؼ� ���!
	printf("���� �̸� => <%s>\n", szWeaponName.c_str()); // ���� ���ڿ� ��������! (const string ����)
	
	int32 weaponNameLength = szWeaponName.length();
	printf("%s�� ���� %d���� �Ǿ��־��.\n\n", szWeaponName.c_str(), weaponNameLength);

	//////////////////////////////////////////////////////////////////////////

	std::string szWeaponPrefixName = "�߰ſ�";
	szWeaponName = szWeaponPrefixName + " " + szWeaponName; // �̷��� ���� �� �־��.
	printf("���� �̸� => <%s>\n", szWeaponName.c_str());

	weaponNameLength = szWeaponName.length();
	printf("%s�� ���� %d���� �Ǿ��־��.\n\n", szWeaponName.c_str(), weaponNameLength);

	//////////////////////////////////////////////////////////////////////////

	int32 foundDelimiterPos = szWeaponName.find(" ");
	if (foundDelimiterPos == std::string::npos)
	{
		printf("<%s>�� ã�� ���߾��...\n", " ");
		return EXIT_FAILURE;
	}

	szWeaponName.replace(szWeaponName.begin(), szWeaponName.begin() + foundDelimiterPos, "�ľ����");
	printf("���� �̸� => <%s>\n", szWeaponName.c_str());

	weaponNameLength = szWeaponName.length();
	printf("%s�� ���� %d���� �Ǿ��־��.\n\n", szWeaponName.c_str(), weaponNameLength);

	//////////////////////////////////////////////////////////////////////////

	foundDelimiterPos = szWeaponName.find(" ");
	if (foundDelimiterPos == std::string::npos)
	{
		printf("<%s>�� ã�� ���߾��...\n", " ");
		return EXIT_FAILURE;
	}

	szWeaponName = szWeaponName.substr(foundDelimiterPos + 1, weaponNameLength);
	printf("���� �̸� => <%s>\n", szWeaponName.c_str());
	
	weaponNameLength = szWeaponName.length();
	printf("%s�� ���� %d���� �Ǿ��־��.\n\n", szWeaponName.c_str(), weaponNameLength);

#endif

#if 0

	//////////////////////////////////////////////////////////////////////////
	// std::to_string�� �̿��غ���~
	//////////////////////////////////////////////////////////////////////////

	int32 playerMaxHP = 100;
	int32 playerHP    = playerMaxHP;
	printf("�÷��̾��� HP (%d / %d)\n", playerHP, playerMaxHP);

	std::string szPlayerMaxHP = std::to_string(playerMaxHP); // ������ std::string���� ��ȯ!
	std::string szPlayerHP    = szPlayerMaxHP;
	printf("�÷��̾��� HP (%s / %s)\n\n", szPlayerHP.c_str(), szPlayerMaxHP.c_str());

	//////////////////////////////////////////////////////////////////////////

	real32 percentOfEvasion = 30.0f;
	printf("������ ���� Ȯ�� (%.2f%%)\n", percentOfEvasion);

	std::string szPercentOfEvasion = std::to_string(percentOfEvasion);
	printf("������ ���� Ȯ�� (%.5s%%)\n\n", szPercentOfEvasion.c_str());
	
#endif

	return EXIT_SUCCESS;
}