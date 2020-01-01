// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
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
	CII_ATK, // ���ݷ�
	CII_DEF, // ����
	CII_END,
};

// C++17 �̻󿡼��� ��� ����
template <typename EType>
constexpr auto ToUnderlyingType(EType val) noexcept
{
	static_assert(std::is_enum_v<EType>, "Only use enum type!");
	return static_cast<std::underlying_type_t<EType>>(val);
}

// C++14 �̻󿡼��� ��� ����
//template <typename EType>
//constexpr auto ToUnderlyingType(EType val) noexcept
//{
//	static_assert(typename std::is_enum<EType>::value, "Only use enum type!");
//	return static_cast<std::underlying_type_t<EType>>(val);
//}

// C++11 �̻󿡼��� ��� ����
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
		printf("���� ����ϰ� �־��!\n");
		break;
	}

	case EWeaponType::BOW:
	{
		printf("Ȱ�� ����ϰ� �־��!\n");
		break;
	}

	case EWeaponType::WAND:
	{
		printf("�������� ����ϰ� �־��!\n");
		break;
	}

	default:
	{
		printf("�⺻ ���⸦ ����ϰ� �־��!\n");
		break;
	}

	}

	printf("\n");
}

//////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
Int32 main()
{
	std::array<Int32, CII_END> characterInfo;

	// �⺻ ������ �־�Կ�.
	characterInfo[CII_ATK] = 100;
	characterInfo[CII_DEF] = 50;

	// enum class�� ���� �������� ��ȯ�ؼ� �־�� �ؿ�.
	characterInfo[CII_WEAPON_TYPE] = ToUnderlyingType(EWeaponType::SWORD);

	printf("���ݷ� : %d\n", characterInfo[CII_ATK]);
	printf("���� : %d\n", characterInfo[CII_DEF]);

	ShowMyWeapon(static_cast<EWeaponType>(characterInfo[CII_WEAPON_TYPE]));

	// ���⸦ �����غ��Կ�.
	characterInfo[CII_WEAPON_TYPE] = ToUnderlyingType(EWeaponType::WAND);

	printf("���ݷ� : %d\n", characterInfo[CII_ATK]);
	printf("���� : %d\n", characterInfo[CII_DEF]);
	ShowMyWeapon(static_cast<EWeaponType>(characterInfo[CII_WEAPON_TYPE]));
	
	return 0;
}