// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2���� ����ϴ� �����Դϴ�.
// ���� �����ʹ� �������� �ʰ� ���� ������ �����͸� �����մϴ�.
// =====================================================================================

#ifndef BATTLE_SIMULATOR2_WORLD__H__
#define BATTLE_SIMULATOR2_WORLD__H__

#include "Element\World.h"

class BattleSimulator2World final : public World
{
	DECLARE_RTTI(BattleSimulator2World, World);

public:
#pragma region ������ �� �Ҹ���
	using World::World;
	virtual ~BattleSimulator2World() = default;
#pragma endregion

	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnLoadFile(FILE* pFileStream) override;
};

#endif