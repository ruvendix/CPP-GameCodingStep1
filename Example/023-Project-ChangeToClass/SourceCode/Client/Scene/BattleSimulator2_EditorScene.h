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
#include "MiniGame\BattleSimulator2\GameObject\ObjectID.h"

enum class EBattleSimulator2Mode : Int32
{
	MENU = 0,
	EDIT,
};

class Viking;
class MedievalKnight;
class MenuTable_Row;
class BattleSimulator2World;
class BattleSimulator2_LevelDesign;

using VikingPtr = std::shared_ptr<Viking>;
using MedievalKnightPtr = std::shared_ptr<MedievalKnight>;

DECLARE_LOG_CATEGORY(BattleSimulator2_EditorScene);

class BattleSimulator2_EditorScene final : public Scene
{
	DECLARE_RTTI(BattleSimulator2_EditorScene, Scene);
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
		return m_spLevelDesign;
	}

	EDynamicObjID getCurrentPrototypeUnitID() const
	{
		return m_currentPrototypeUnitID;
	}

	void setMode(EBattleSimulator2Mode mode)
	{
		m_mode = mode;
	}

	void setCurrentPrototypeUnitID(EDynamicObjID unitID)
	{
		m_currentPrototypeUnitID = unitID;
	}

private:
	EBattleSimulator2Mode m_mode = EBattleSimulator2Mode::MENU;
	std::shared_ptr<MenuTable_Row> m_spEditorMenuTable = nullptr;;

	EDynamicObjID m_currentPrototypeUnitID = EDynamicObjID::UNKNOWN;
	std::shared_ptr<BattleSimulator2World> m_spWorld = nullptr;
	std::shared_ptr<BattleSimulator2_LevelDesign> m_spLevelDesign = nullptr;
};

#endif