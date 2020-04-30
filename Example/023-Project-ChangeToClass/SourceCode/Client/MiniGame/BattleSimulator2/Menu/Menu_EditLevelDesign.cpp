// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2���� ���Ǵ� �޴��Դϴ�.
// ���� �������� �������մϴ�.
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
	ConsoleController::I()->ModifyCurrentConsoleSelectorPos(centerPos); // ���� �߾� ��ǥ��!

	consoleSelector.setMinSelectorPos(2, 1);

	SizeInfo worldSize = spWorld->getSize();

	// �� �ε��� ����, �� ���� => -2
	consoleSelector.setMaxSelectorPos((worldSize.width - 2) * consoleSelector.getShapeLength(), worldSize.height - 2);

	// ����Ʈ���� ù��°��
	Int32 defaultPrototypeUnitID = common_func::ToUnderlyingType(EObjID::START_DYNAMIC_OBJ_ID) + 1;
	m_pTargetScene->setCurrentPrototypeUnitID(static_cast<EObjID>(defaultPrototypeUnitID));
	consoleSelector.setShape(
		BattleSimulator2_DataCollector::I()->FindPrototypeUnit(m_pTargetScene->getCurrentPrototypeUnitID())->getShape());

	RESERVE_RENDERING_STRING(1.0f, std::bind(&Menu_EditLevelDesign::OnTrigger_Excute, this));
	return EErrorType::NOTHING;
}

void Menu_EditLevelDesign::OnTrigger_Excute()
{
	PUT_STRING(82, 28, "������ ���� ����!");
}
