// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터 에디터 씬입니다.
// 기본 월드에 다양한 레벨 디자인을 만들 수 있습니다.
// =====================================================================================

#ifndef BATTLE_SIMULATOR2_EDITOR_SCENE_H__
#define BATTLE_SIMULATOR2_EDITOR_SCENE_H__

#include "Element\Scene.h"
#include "Controller\ConsoleControllerEnum.h"
#include "MiniGame\BattleSimulator2\GameObject\DynamicObject\DynamicObjectID.h"

enum class EMode : Int32
{
	MENU = 0,
	EDIT,
};

class MenuTable_Row;
class BattleSimulator2World;
class BattleSimulator2_LevelDesign;
class Unit;

DECLARE_LOG_CATEGORY(BattleSimulator2_EditorScene);

class BattleSimulator2_EditorScene final : public Scene
{
	FRIEND_WITH_HELPER(BattleSimulator2_EditorSceneHelper);
	INPUT_FPS_LIMITED(18);

public:
#pragma region 생성자 및 소멸자
	using Scene::Scene;
	virtual ~BattleSimulator2_EditorScene() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;

	std::shared_ptr<BattleSimulator2World> getWorld()
	{
		return m_spWorld;
	}

	std::shared_ptr<BattleSimulator2_LevelDesign> getLevelDesign()
	{
		return m_spCurrentLevelDesign;
	}

	std::shared_ptr<Unit> getSampleUnit(Int32 idx) const
	{
		CHECK_RANGE(idx, 0, m_vecSampleUnit.size() - 1);
		return m_vecSampleUnit.at(idx);
	}

	std::shared_ptr<Unit> getCurrentSampleUnit() const
	{
		return getSampleUnit(m_currentSampleUnitIdx);
	}

	void setMode(EMode mode)
	{
		m_mode = mode;
	}

private:
	EMode m_mode = EMode::MENU;
	std::vector<std::shared_ptr<Unit>> m_vecSampleUnit;
	std::shared_ptr<MenuTable_Row> m_spEditorMenuTable = nullptr;;
	std::shared_ptr<BattleSimulator2World> m_spWorld = nullptr;;

	Int32 m_currentSampleUnitIdx = 0;
	std::shared_ptr<BattleSimulator2_LevelDesign> m_spCurrentLevelDesign = nullptr;
};

#endif