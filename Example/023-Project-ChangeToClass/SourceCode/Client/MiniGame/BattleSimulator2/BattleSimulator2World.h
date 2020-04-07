// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ����Ϳ��� ����ϴ� �����Դϴ�.
// ���� �����ʹ� �������� �ʰ� ���� ������ �����͸� �����մϴ�.
// =====================================================================================

#ifndef BATTLE_SIMULATOR_WORLD__H__
#define BATTLE_SIMULATOR_WORLD__H__

#include "Element\World.h"

class BattleSimulator2World : public World
{
public:
#pragma region ������ �� �Ҹ���
	using World::World;
	virtual ~BattleSimulator2World() = default;
#pragma endregion

	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnSaveFile(FILE* pFileStream) override;
	virtual EErrorType OnLoadFile(FILE* pFileStream) override;
};

#endif