// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2에서 사용되는 메뉴입니다.
// 레벨 디자인을 에디터합니다.
// =====================================================================================

#include "PCH.h"
#include "Menu_EditLevelDesign.h"

#include "Controller\ConsoleController.h"
#include "Manager\TriggerTimerManager.h"

#include "Scene\BattleSimulator2_EditorScene.h"
#include "..\BattleSimulator2World.h"
#include "..\BattleSimulator2_DataCollector.h"
#include "..\GameObject\DynamicObject\Unit.h"

Menu_EditLevelDesign::Menu_EditLevelDesign(const std::string_view& szNameTag,
	const COORD& pos, BattleSimulator2_EditorScene* pTargetScene) :
	Menu(szNameTag, pos),
	m_pTargetScene(pTargetScene)
{

}

EErrorType Menu_EditLevelDesign::OnExcute()
{
	CHECK_NULLPTR(m_pTargetScene);
	m_pTargetScene->setMode(EBattleSimulator2Mode::EDIT);

	ConsoleController::I()->PushBackupConsoleSelector();

	std::shared_ptr<BattleSimulator2World> spWorld = m_pTargetScene->getWorld();
	COORD centerPos = spWorld->CalcCenterBySize();

	ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	centerPos.X *= consoleSelector.getShapeLength();
	ConsoleController::I()->ModifyCurrentConsoleSelectorPos(centerPos); // 월드 중앙 좌표로!

	consoleSelector.setMinSelectorPos(2, 1);

	SizeInfo worldSize = spWorld->getSize();

	// 끝 인덱스 제외, 벽 제외 => -2
	consoleSelector.setMaxSelectorPos((worldSize.width - 2) * consoleSelector.getShapeLength(), worldSize.height - 2);

	// 리스트에서 첫번째꺼
	Int32 defaultPrototypeUnitID = common_func::ToUnderlyingType(EObjID::START_DYNAMIC_OBJ_ID) + 1;
	m_pTargetScene->setCurrentPrototypeUnitID(static_cast<EObjID>(defaultPrototypeUnitID));
	consoleSelector.setShape(
		BattleSimulator2_DataCollector::I()->FindPrototypeUnit(m_pTargetScene->getCurrentPrototypeUnitID())->getShape());

	RESERVE_RENDERING_STRING(1.0f, std::bind(&Menu_EditLevelDesign::OnTrigger_Excute, this));
	return EErrorType::NOTHING;
}

void Menu_EditLevelDesign::OnTrigger_Excute()
{
	PUT_STRING(82, 28, "에디터 모드로 변경!");
}
