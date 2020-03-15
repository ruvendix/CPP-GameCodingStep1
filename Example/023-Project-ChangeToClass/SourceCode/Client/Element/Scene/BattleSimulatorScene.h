// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ����� ���Դϴ�.
// =====================================================================================

#ifndef BATTLE_SIMULATOR_SCENE_H__
#define BATTLE_SIMULATOR_SCENE_H__

#include "Element\Scene.h"
#include "Controller\ConsoleControllerEnum.h"

class MedievalKnight;
class Viking;

DECLARE_LOG_CATEGORY(BattleSimulatorScene);

class BattleSimulatorScene final : public Scene
{
	FRIEND_WITH_HELPER(BattleSimulatorSceneHelper);

public:
	using Scene::Scene;

#pragma region ������ �� �Ҹ���
	BattleSimulatorScene() = default;
	virtual ~BattleSimulatorScene() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;

private:
	std::vector<MedievalKnight*> m_vecMedievalKnight;
	std::vector<Viking*> m_vecViking;

	bool m_bBattleEnd = false;
};

#endif