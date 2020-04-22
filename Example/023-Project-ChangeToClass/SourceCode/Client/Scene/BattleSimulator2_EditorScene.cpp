// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터 에디터 씬입니다.
// 기본 월드에 다양한 레벨 디자인을 만들 수 있습니다.
// =====================================================================================

#include "PCH.h"
#include "BattleSimulator2_EditorScene.h"

#include "Controller\FrameController.h"
#include "Controller\ConsoleController.h"
#include "Controller\InputController.h"
#include "Manager\SceneManager.h"
#include "Element\Menu\Menu.h"
#include "Element\Menu\MenuTable_Row.h"

#include "Scene\IntroMenuScene.h"
#include "IntroMenu\IntroMenu_ComeBack.h"
#include "MiniGame\BattleSimulator2\BattleSimulator2_BattleReporter.h"
#include "MiniGame\BattleSimulator2\BattleSimulator2World.h"
#include "MiniGame\BattleSimulator2\BattleSimulator2_LevelDesign.h"
#include "MiniGame\BattleSimulator2\Menu\Menu_ResetLevelDesign.h"
#include "MiniGame\BattleSimulator2\Menu\Menu_EditLevelDesign.h"
#include "MiniGame\BattleSimulator2\Menu\Menu_SaveLevelDesign.h"
#include "MiniGame\BattleSimulator2\Menu\Menu_LoadLevelDesign.h"
#include "MiniGame\BattleSimulator2\Menu\Menu_StartGame.h"
#include "MiniGame\BattleSimulator2\BattleSimulator2_DataCollector.h"
#include "MiniGame\BattleSimulator2\GameObject\DynamicObject\MedievalKnight.h"
#include "MiniGame\BattleSimulator2\GameObject\DynamicObject\Viking.h"

namespace
{
	std::unique_ptr<UI_PosInfo> s_spUI_posInfo;
}

class BattleSimulator2_EditorSceneHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(BattleSimulator2_EditorSceneHelper);

public:
	static void DrawMenu(const COORD& pos, std::shared_ptr<MenuTable_Row> spMenuTable);

	static void OnInput_MenuMode(_Inout_ BattleSimulator2_EditorScene& targetHelper);
	static void OnInput_EditorMode(_Inout_ BattleSimulator2_EditorScene& targetHelper);
};

void BattleSimulator2_EditorSceneHelper::DrawMenu(const COORD& pos, std::shared_ptr<MenuTable_Row> spMenuTable)
{
	common_func::DrawBorder(COORD{ pos.X, spMenuTable->getFirstMenu()->getPos().Y - 1 },
		SizeInfo{ (spMenuTable->getLongestMenu()->getNameTag().size() / 2) + 1, spMenuTable->getMenuCnt() });
	spMenuTable->DrawMenu();
}

void BattleSimulator2_EditorSceneHelper::OnInput_MenuMode(_Inout_ BattleSimulator2_EditorScene& targetHelper)
{
	targetHelper.m_spEditorMenuTable->OnInput();

	if (InputController::I()->CheckInputState("GotoIntro", EInputMappingState::DOWN) == true)
	{
		targetHelper.m_spEditorMenuTable->getLastMenu()->OnExcute();
	}
}

void BattleSimulator2_EditorSceneHelper::OnInput_EditorMode(_Inout_ BattleSimulator2_EditorScene& targetHelper)
{
	if (InputController::I()->CheckInputState("MenuMode", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->RestoreConsoleSelector();

		COORD selectorPos = ConsoleController::I()->QueryCurrentConsoleSelectorPos();
		selectorPos.X += (ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU - ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_BORDER);

		Int32 currentMenuIdx = targetHelper.m_spEditorMenuTable->ToMenuIdx(selectorPos);
		targetHelper.m_spEditorMenuTable->setCurrentMenuIdx(currentMenuIdx);

		Int32 currentPrototypeUnitID = common_func::ToUnderlyingType(targetHelper.m_currentPrototypeUnitID);
		currentPrototypeUnitID = common_func::ToUnderlyingType(EDynamicObjID::UNKNOWN) + 1;
		targetHelper.m_currentPrototypeUnitID = static_cast<EDynamicObjID>(currentPrototypeUnitID);
		targetHelper.m_mode = EBattleSimulator2Mode::MENU;
	}

	if (InputController::I()->CheckInputState("Left", EInputMappingState::DOWN) == true)
	{
		const ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
		Int32 movePosX = static_cast<Int32>(consoleSelector.getShapeLength()) * -1;
		ConsoleController::I()->AddSelectorPosX(movePosX);

		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("MenuLeft 눌렀다!");
	}

	if (InputController::I()->CheckInputState("Right", EInputMappingState::DOWN) == true)
	{
		const ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
		ConsoleController::I()->AddSelectorPosX(+consoleSelector.getShapeLength());

		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("MenuRight 눌렀다!");
	}

	if (InputController::I()->CheckInputState("Up", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(-1);

		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("MenuUp 눌렀다!");
	}

	if (InputController::I()->CheckInputState("Down", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+1);

		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("MenuDown 눌렀다!");
	}

	if (InputController::I()->CheckInputState("SpawnObj", EInputMappingState::DOWN) == true)
	{
		// 레벨을 통해서 월드에 스폰!
		const ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
		COORD mappingPos = consoleSelector.getSelectorPos();
		mappingPos.X = mappingPos.X / consoleSelector.getShapeLength();

		// 현재 선택된 ID에 따라 스폰!
		switch (targetHelper.m_currentPrototypeUnitID)
		{
		case EDynamicObjID::VIKING:
		{
			UnitPtr spPrototypeViking = BattleSimulator2_DataCollector::I()->FindPrototypeUnit(EDynamicObjID::VIKING);
			VikingPtr spViking = common_func::KindCastSP<Viking>(spPrototypeViking)->Clone();
			spViking->setPos(mappingPos);

			Int32 vikingCnt = BattleSimulator2_DataCollector::I()->FindBattleData(EDynamicObjID::VIKING, EBattleDataType::TOTAL_UNIT_CNT);
			spViking->setNameTag(common_func::MakeFormatString("%s_%d", spViking->getNameTag().c_str(), vikingCnt));
			BattleSimulator2_DataCollector::I()->ModifyBattleData(EDynamicObjID::VIKING,
				EBattleDataType::TOTAL_UNIT_CNT, EDataProgressDir::POSITIVENESS, 1);

			targetHelper.m_spLevelDesign->AddObj(spViking);
			break;
		}

		case EDynamicObjID::MEDIEVAL_KNIGHT:
		{
			UnitPtr spPrototypeMedievalKnight = BattleSimulator2_DataCollector::I()->FindPrototypeUnit(EDynamicObjID::MEDIEVAL_KNIGHT);
			MedievalKnightPtr spMedievalKnight = common_func::KindCastSP<MedievalKnight>(spPrototypeMedievalKnight)->Clone();
			spMedievalKnight->setPos(mappingPos);

			Int32 medievalKnightCnt =
				BattleSimulator2_DataCollector::I()->FindBattleData(EDynamicObjID::MEDIEVAL_KNIGHT, EBattleDataType::TOTAL_UNIT_CNT);
			spMedievalKnight->setNameTag(common_func::MakeFormatString("%s_%d", spMedievalKnight->getNameTag().c_str(), medievalKnightCnt));
			BattleSimulator2_DataCollector::I()->ModifyBattleData(EDynamicObjID::MEDIEVAL_KNIGHT,
				EBattleDataType::TOTAL_UNIT_CNT, EDataProgressDir::POSITIVENESS, 1);

			targetHelper.m_spLevelDesign->AddObj(spMedievalKnight);
			break;
		}

		default:
		{
			ERROR_HANDLER(false, EErrorType::UNKNOWN_DYNAMIC_OBJ);
			break;
		}
		}

		DEBUG_LOG("SpawnObj 눌렀다!");
	}

	if (InputController::I()->CheckInputState("ChangeObj", EInputMappingState::DOWN) == true)
	{
		Int32 currentPrototypeUnitID = common_func::ToUnderlyingType(targetHelper.m_currentPrototypeUnitID);
		++currentPrototypeUnitID;

		currentPrototypeUnitID = rx_math::ClampCycle(currentPrototypeUnitID,
			common_func::ToUnderlyingType(EDynamicObjID::UNKNOWN) + 1, common_func::ToUnderlyingType(EDynamicObjID::END) - 1);
		targetHelper.m_currentPrototypeUnitID = static_cast<EDynamicObjID>(currentPrototypeUnitID);

		ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
		consoleSelector.setShape(
			BattleSimulator2_DataCollector::I()->FindPrototypeUnit(targetHelper.m_currentPrototypeUnitID)->getShape());

		DEBUG_LOG("SpawnObj 눌렀다!");
	}

	BEGIN_INPUT_FPS_LIMITED_HELPER(targetHelper);
	if (InputController::I()->CheckInputState("Left", EInputMappingState::PRESSING) == true)
	{
		const ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
		Int32 movePosX = static_cast<Int32>(consoleSelector.getShapeLength()) * -1;
		ConsoleController::I()->AddSelectorPosX(movePosX);

		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("MenuLeft 눌렀다!");
	}

	if (InputController::I()->CheckInputState("Right", EInputMappingState::PRESSING) == true)
	{
		const ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
		ConsoleController::I()->AddSelectorPosX(+consoleSelector.getShapeLength());

		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("MenuRight 눌렀다!");
	}

	if (InputController::I()->CheckInputState("Up", EInputMappingState::PRESSING) == true)
	{
		ConsoleController::I()->AddSelectorPosY(-1);

		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("MenuUp 눌렀다!");
	}

	if (InputController::I()->CheckInputState("Down", EInputMappingState::PRESSING) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+1);

		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("MenuDown 눌렀다!");
	}
	END_INPUT_FPS_LIMITED();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_LOG_CATEGORY(BattleSimulator2_EditorScene);

EErrorType BattleSimulator2_EditorScene::OnInitialize()
{
	DEBUG_LOG_CATEGORY(BattleSimulator2_EditorScene, "배틀 시뮬레이터 에디터 씬!");
	InputController::I()->InsertInputMappingInfo("GotoIntro", VK_ESCAPE);
	InputController::I()->InsertInputMappingInfo("MenuMode", VK_ESCAPE);
	InputController::I()->InsertInputMappingInfo("Up", VK_UP);
	InputController::I()->InsertInputMappingInfo("Down", VK_DOWN);
	InputController::I()->InsertInputMappingInfo("Left", VK_LEFT);
	InputController::I()->InsertInputMappingInfo("Right", VK_RIGHT);
	InputController::I()->InsertInputMappingInfo("ChangeObj", 'A');
	InputController::I()->InsertInputMappingInfo("SpawnObj", VK_RETURN);

	m_spWorld = std::make_shared<BattleSimulator2World>();

	// 월드 파일이 있는지?
	// 있다면 파일을 읽고, 아니면 새로 초기화해야 해요!
	EErrorType errorType = m_spWorld->LoadFile("BattleSimulator2.world");
	if (errorType == EErrorType::LOAD_FILE_FAIL)
	{
		m_spWorld->setSize(SizeInfo{ 40, 30 });
		m_spWorld->setLastError(EErrorType::LOAD_FILE_FAIL);

		if (m_spWorld->OnInitialize() == EErrorType::INIT_FAIL)
		{
			return EErrorType::INIT_FAIL;
		}
	}

	// 월드를 불러왔으면 데이터 콜렉터를 초기화해야 해요.
	BattleSimulator2_DataCollector::I()->Initialize();

	// 레벨 디자인 파일은 있을 때만 적용할게요.
	m_spLevelDesign = std::make_shared<BattleSimulator2_LevelDesign>();
	m_spLevelDesign->LoadFile("BattleSimulator2.level");

	// 레벨 디자인을 불러왔으면 데이터 콜렉터의 생존 유닛수를 갱신해줘야 해요.
	Int32 startID = common_func::ToUnderlyingType(EDynamicObjID::UNKNOWN) + 1;
	Int32 endID = common_func::ToUnderlyingType(EDynamicObjID::END);
	for (Int32 i = startID; i < endID; ++i)
	{
		Int32 totalUnitCnt = BattleSimulator2_DataCollector::I()->FindBattleData(
			static_cast<EDynamicObjID>(i), EBattleDataType::TOTAL_UNIT_CNT);

		BattleSimulator2_DataCollector::I()->ModifyBattleData(static_cast<EDynamicObjID>(i),
			EBattleDataType::REMAIN_UNIT_CNT, totalUnitCnt);
	}

	s_spUI_posInfo = std::make_unique<UI_PosInfo>();
	s_spUI_posInfo->startPos = COORD{ 85, 10 };
	s_spUI_posInfo->menuStartPos = s_spUI_posInfo->startPos;
	s_spUI_posInfo->menuStartPos.X += ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU;
	s_spUI_posInfo->menuStartPos.Y += 1;
	s_spUI_posInfo->diffSize.height = 1;

	m_spEditorMenuTable = std::make_shared<MenuTable_Row>();
	m_spEditorMenuTable->AddMenu(std::make_shared<Menu_ResetLevelDesign>("레벨 디자인 초기화",
		COORD{ s_spUI_posInfo->menuStartPos.X, s_spUI_posInfo->menuStartPos.Y }, this));

	Int32 diffMultipleFactor = 0;
	m_spEditorMenuTable->AddMenu(std::make_shared<Menu_EditLevelDesign>("레벨 디자인 편집",
		COORD{ s_spUI_posInfo->menuStartPos.X,
			   s_spUI_posInfo->menuStartPos.Y +
			   static_cast<SHORT>(s_spUI_posInfo->diffSize.height * (++diffMultipleFactor)) }, this));

	m_spEditorMenuTable->AddMenu(std::make_shared<Menu_SaveLevelDesign>("레벨 디자인 저장",
		COORD{ s_spUI_posInfo->menuStartPos.X,
		       s_spUI_posInfo->menuStartPos.Y +
		       static_cast<SHORT>(s_spUI_posInfo->diffSize.height * (++diffMultipleFactor)) }, this));

	m_spEditorMenuTable->AddMenu(std::make_shared<Menu_LoadLevelDesign>("레벨 디자인 열기",
		COORD{ s_spUI_posInfo->menuStartPos.X,
		       s_spUI_posInfo->menuStartPos.Y +
		       static_cast<SHORT>(s_spUI_posInfo->diffSize.height * (++diffMultipleFactor)) }, this));

	m_spEditorMenuTable->AddMenu(std::make_shared<Menu_StartGame>("게임 시작",
		COORD{ s_spUI_posInfo->menuStartPos.X,
		       s_spUI_posInfo->menuStartPos.Y +
		       static_cast<SHORT>(s_spUI_posInfo->diffSize.height * (++diffMultipleFactor)) }));

	m_spEditorMenuTable->AddMenu(std::make_shared<IntroMenu_ComeBack>("나가기",
		COORD{ s_spUI_posInfo->menuStartPos.X,
		       s_spUI_posInfo->menuStartPos.Y +
		       static_cast<SHORT>(s_spUI_posInfo->diffSize.height * (++diffMultipleFactor)) }));

	return EErrorType::NOTHING;
}

EErrorType BattleSimulator2_EditorScene::OnPostInitialize()
{
	if (m_spWorld->getLastError() == EErrorType::LOAD_FILE_FAIL)
	{
		if (m_spWorld->OnPostInitialize() == EErrorType::INIT_FAIL)
		{
			return EErrorType::INIT_FAIL;
		}

		m_spWorld->ResetError();
	}

	ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	consoleSelector.setSelectorPos(
		s_spUI_posInfo->startPos.X + ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_BORDER, s_spUI_posInfo->menuStartPos.Y);
	consoleSelector.setMinSelectorPosY(s_spUI_posInfo->startPos.Y);
	consoleSelector.setMaxSelectorPosY(s_spUI_posInfo->startPos.Y + m_spEditorMenuTable->getLastIdx());

	return EErrorType::NOTHING;
}

EErrorType BattleSimulator2_EditorScene::OnInput()
{
	if (m_mode == EBattleSimulator2Mode::MENU)
	{
		BattleSimulator2_EditorSceneHelper::OnInput_MenuMode(*this);
	}
	else
	{
		BattleSimulator2_EditorSceneHelper::OnInput_EditorMode(*this);
	}

	return EErrorType::NOTHING;
}

EErrorType BattleSimulator2_EditorScene::OnUpdate()
{
	return EErrorType::NOTHING;
}

EErrorType BattleSimulator2_EditorScene::OnRender()
{
	if (m_spWorld->OnRender() == EErrorType::RENDER_FAIL)
	{
		return EErrorType::RENDER_FAIL;
	}

	if (m_spLevelDesign->OnRender() == EErrorType::RENDER_FAIL)
	{
		return EErrorType::RENDER_FAIL;
	}

	BattleSimulator2_BattleReporter::I()->DrawUnitStat();
	BattleSimulator2_EditorSceneHelper::DrawMenu(s_spUI_posInfo->startPos, m_spEditorMenuTable);
	ConsoleController::I()->DrawSelector();

	return EErrorType::NOTHING;
}

EErrorType BattleSimulator2_EditorScene::OnFinalize()
{
	m_spWorld->SaveFile("BattleSimulator2.world"); // 월드는 오토 세이브!
	return EErrorType::NOTHING;
}
