// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �������Դϴ�.
// ���� ��������� �ٸ� ����� ������ �� �ֽ��ϴ�.
// =====================================================================================

#include "PCH.h"
#include "EntrancePhase.h"

#include "Controller\ConsoleController.h"
#include "Controller\InputController.h"
#include "Manager\SceneManager.h"
#include "Element\ConsoleSelector.h"

#include "Scene\IntroMenuScene.h"
#include "MiscellaneousShop2PhaseType.h"
#include "BuyPhase.h"
#include "SellPhase.h"
#include "ArrangePhase.h"
#include "IntroMenu\IntroMenu_ComeBack.h"
#include "..\Menu\EntrancePhaseMenu_PhaseLoader.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace
{
	std::unique_ptr<UI_PosInfo> s_spUI_posInfo;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EntrancePhaseHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(EntrancePhaseHelper);

public:
	static void DrawMenu(const COORD& pos, std::shared_ptr<MenuTable_Mat> spMenuTable);
};

void EntrancePhaseHelper::DrawMenu(const COORD& pos, std::shared_ptr<MenuTable_Mat> spMenuTable)
{
	Int32 drawPosY = pos.Y;
	PUT_STRING(pos.X,   drawPosY, "����������������������������������������������������������������������");
	PUT_STRING(pos.X, ++drawPosY, "�� ��ȭ ������ ���� �� ȯ���ؿ�~!  ��");
	PUT_STRING(pos.X, ++drawPosY, "�� ���� �Ϸ� ���̳���?             ��");
	PUT_STRING(pos.X, ++drawPosY, "����������������������������������������������������������������������");
	PUT_STRING(pos.X, ++drawPosY, "��                ��                ��");
	PUT_STRING(pos.X, ++drawPosY, "����������������������������������������������������������������������");
	PUT_STRING(pos.X, ++drawPosY, "��                ��                ��");
	PUT_STRING(pos.X, ++drawPosY, "����������������������������������������������������������������������");

	spMenuTable->DrawMenu();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

EErrorType EntrancePhase::OnInitialize()
{	
	InputController::I()->InsertInputMappingInfo("GotoIntro", VK_ESCAPE);

	s_spUI_posInfo = std::make_unique<UI_PosInfo>();
	s_spUI_posInfo->startPos = COORD{ 0, 0 };
	s_spUI_posInfo->menuStartPos = s_spUI_posInfo->startPos;
	s_spUI_posInfo->menuStartPos.X += ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU;
	s_spUI_posInfo->menuStartPos.Y += 4;
	s_spUI_posInfo->diffSize = SizeInfo{ 17, 2 };

	m_spMenuTable = std::make_shared<MenuTable_Mat>(2, 2, false, false);
	m_spMenuTable->AddForMat(std::make_shared<EntrancePhaseMenu_PhaseLoader>("����", s_spUI_posInfo->menuStartPos,
		EMiscellaneousShop2PhaseType::BUY), 0, 0);

	m_spMenuTable->AddForMat(std::make_shared<EntrancePhaseMenu_PhaseLoader>("�Ǹ�",
		COORD{ s_spUI_posInfo->menuStartPos.X + static_cast<SHORT>(s_spUI_posInfo->diffSize.width),
		s_spUI_posInfo->menuStartPos.Y }, EMiscellaneousShop2PhaseType::SELL), 0, 1);

	m_spMenuTable->AddForMat(std::make_shared<EntrancePhaseMenu_PhaseLoader>("����",
		COORD{ s_spUI_posInfo->menuStartPos.X,
		s_spUI_posInfo->menuStartPos.Y + static_cast<SHORT>(s_spUI_posInfo->diffSize.height) },
		EMiscellaneousShop2PhaseType::ARRANGE), 1, 0);

	m_spMenuTable->AddForMat(std::make_shared<IntroMenu_ComeBack>("������",
		COORD{ s_spUI_posInfo->menuStartPos.X + static_cast<SHORT>(s_spUI_posInfo->diffSize.width),
		s_spUI_posInfo->menuStartPos.Y + static_cast<SHORT>(s_spUI_posInfo->diffSize.height) }), 1, 1);

	ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	consoleSelector.setSelectorPos(
		s_spUI_posInfo->startPos.X + ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_BORDER, s_spUI_posInfo->menuStartPos.Y);

	return EErrorType::NOTHING;
}

EErrorType EntrancePhase::OnPostInitialize()
{
	COORD selectorPos = ConsoleController::I()->QueryCurrentConsoleSelectorPos();
	selectorPos.X += (ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU - ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_BORDER);

	Int32 currentMenuIdx = m_spMenuTable->ToMenuIdx(selectorPos);
	m_spMenuTable->setCurrentMenuIdx(currentMenuIdx);

	return EErrorType::NOTHING;
}

EErrorType EntrancePhase::OnInput()
{
	m_spMenuTable->OnInput();

	if (InputController::I()->CheckInputState("GotoIntro", EInputMappingState::DOWN) == true)
	{
		SceneMgr::I()->CreateScene<IntroMenuScene>(ECreateType::NEXT);
	}

	return EErrorType::NOTHING;
}

EErrorType EntrancePhase::OnRender()
{
	EntrancePhaseHelper::DrawMenu(s_spUI_posInfo->startPos, m_spMenuTable);
	ConsoleController::I()->DrawSelector();

	return EErrorType::NOTHING;
}