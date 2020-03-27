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
#pragma region ������ �� �Ҹ���
	using Scene::Scene;
	virtual ~BattleSimulatorScene() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;

private:
	std::vector<std::shared_ptr<MedievalKnight>> m_vecMedievalKnight;
	std::vector<std::shared_ptr<Viking>> m_vecViking;

	bool m_bBattleEnd = false;
};

#endif