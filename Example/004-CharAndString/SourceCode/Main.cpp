// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <string> // std::string이 있어요.

using int32  = __int32; // "typedef __int32 int32"와 같아요.
using real32 = float;   // "typedef float real32"와 같아요.

int main()
{
#if 0

	//////////////////////////////////////////////////////////////////////////
	// char에 대해서 짚고 넘어가요~
	//////////////////////////////////////////////////////////////////////////
	
	char value = 'A'; // ASCII값이 저장되요~
	printf("value => %c\n", value);

	value += 1; // ASCII값이 곧 숫자!
	printf("value => %c\n", value);

	value = '\\'; // 파일 경로에서 자주 사용되는 역슬래시에요!
	if (value == '\\')
	{
		printf("value => %c\n", value);
	}

#endif

#if 0

	//////////////////////////////////////////////////////////////////////////
	// std::string을 이용해봐요~
	//////////////////////////////////////////////////////////////////////////

	std::string szWeaponName = "드라이기"; // 이렇게 초기화해서 사용!
	printf("무기 이름 => <%s>\n", szWeaponName.c_str()); // 내부 문자열 가져오기! (const string 약자)
	
	int32 weaponNameLength = szWeaponName.length();
	printf("%s는 문자 %d개로 되어있어요.\n\n", szWeaponName.c_str(), weaponNameLength);

	//////////////////////////////////////////////////////////////////////////

	std::string szWeaponPrefixName = "뜨거운";
	szWeaponName = szWeaponPrefixName + " " + szWeaponName; // 이렇게 더할 수 있어요.
	printf("무기 이름 => <%s>\n", szWeaponName.c_str());

	weaponNameLength = szWeaponName.length();
	printf("%s는 문자 %d개로 되어있어요.\n\n", szWeaponName.c_str(), weaponNameLength);

	//////////////////////////////////////////////////////////////////////////

	int32 foundDelimiterPos = szWeaponName.find(" ");
	if (foundDelimiterPos == std::string::npos)
	{
		printf("<%s>를 찾지 못했어요...\n", " ");
		return EXIT_FAILURE;
	}

	szWeaponName.replace(szWeaponName.begin(), szWeaponName.begin() + foundDelimiterPos, "식어버린");
	printf("무기 이름 => <%s>\n", szWeaponName.c_str());

	weaponNameLength = szWeaponName.length();
	printf("%s는 문자 %d개로 되어있어요.\n\n", szWeaponName.c_str(), weaponNameLength);

	//////////////////////////////////////////////////////////////////////////

	foundDelimiterPos = szWeaponName.find(" ");
	if (foundDelimiterPos == std::string::npos)
	{
		printf("<%s>를 찾지 못했어요...\n", " ");
		return EXIT_FAILURE;
	}

	szWeaponName = szWeaponName.substr(foundDelimiterPos + 1, weaponNameLength);
	printf("무기 이름 => <%s>\n", szWeaponName.c_str());
	
	weaponNameLength = szWeaponName.length();
	printf("%s는 문자 %d개로 되어있어요.\n\n", szWeaponName.c_str(), weaponNameLength);

#endif

#if 0

	//////////////////////////////////////////////////////////////////////////
	// std::to_string을 이용해봐요~
	//////////////////////////////////////////////////////////////////////////

	int32 playerMaxHP = 100;
	int32 playerHP    = playerMaxHP;
	printf("플레이어의 HP (%d / %d)\n", playerHP, playerMaxHP);

	std::string szPlayerMaxHP = std::to_string(playerMaxHP); // 정수를 std::string으로 변환!
	std::string szPlayerHP    = szPlayerMaxHP;
	printf("플레이어의 HP (%s / %s)\n\n", szPlayerHP.c_str(), szPlayerMaxHP.c_str());

	//////////////////////////////////////////////////////////////////////////

	real32 percentOfEvasion = 30.0f;
	printf("공격을 피할 확률 (%.2f%%)\n", percentOfEvasion);

	std::string szPercentOfEvasion = std::to_string(percentOfEvasion);
	printf("공격을 피할 확률 (%.5s%%)\n\n", szPercentOfEvasion.c_str());
	
#endif

	return EXIT_SUCCESS;
}