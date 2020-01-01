// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <type_traits>
#include <array>

using Int32 = signed __int32;
using Real32 = float;

enum class EWeaponType : Int32
{
	NONE = 0,
	SWORD,
	BOW,
	WAND,
};

enum ECharcterInfoIdx
{
	CII_WEAPON_TYPE,
	CII_ATK, // 공격력
	CII_DEF, // 방어력
	CII_END,
};

// C++17 이상에서만 사용 가능
template <typename EType>
constexpr auto ToUnderlyingType(EType val) noexcept
{
	static_assert(std::is_enum_v<EType>, "Only use enum type!");
	return static_cast<std::underlying_type_t<EType>>(val);
}

// C++14 이상에서만 사용 가능
//template <typename EType>
//constexpr auto ToUnderlyingType(EType val) noexcept
//{
//	static_assert(typename std::is_enum<EType>::value, "Only use enum type!");
//	return static_cast<std::underlying_type_t<EType>>(val);
//}

// C++11 이상에서만 사용 가능
//template <typename EType>
//constexpr typename std::underlying_type<EType>::type ToUnderlyingType(EType val) noexcept
//{
//	static_assert(typename std::is_enum<EType>::value, "Only use enum type!");
//	return static_cast<typename std::underlying_type<EType>::type>(val);
//}

void ShowMyWeapon(EWeaponType weaponType)
{
	switch (weaponType)
	{
	case EWeaponType::SWORD:
	{
		printf("검을 사용하고 있어요!\n");
		break;
	}

	case EWeaponType::BOW:
	{
		printf("활을 사용하고 있어요!\n");
		break;
	}

	case EWeaponType::WAND:
	{
		printf("마법봉을 사용하고 있어요!\n");
		break;
	}

	default:
	{
		printf("기본 무기를 사용하고 있어요!\n");
		break;
	}

	}

	printf("\n");
}

//////////////////////////////////////////////////////////////////////////
// 프로그램이 시작되는 곳이에요.
Int32 main()
{
	std::array<Int32, CII_END> characterInfo;

	// 기본 정보를 넣어볼게요.
	characterInfo[CII_ATK] = 100;
	characterInfo[CII_DEF] = 50;

	// enum class의 바탕 형식으로 변환해서 넣어야 해요.
	characterInfo[CII_WEAPON_TYPE] = ToUnderlyingType(EWeaponType::SWORD);

	printf("공격력 : %d\n", characterInfo[CII_ATK]);
	printf("방어력 : %d\n", characterInfo[CII_DEF]);

	ShowMyWeapon(static_cast<EWeaponType>(characterInfo[CII_WEAPON_TYPE]));

	// 무기를 변경해볼게요.
	characterInfo[CII_WEAPON_TYPE] = ToUnderlyingType(EWeaponType::WAND);

	printf("공격력 : %d\n", characterInfo[CII_ATK]);
	printf("방어력 : %d\n", characterInfo[CII_DEF]);
	ShowMyWeapon(static_cast<EWeaponType>(characterInfo[CII_WEAPON_TYPE]));
	
	return 0;
}