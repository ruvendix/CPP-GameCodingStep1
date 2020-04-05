// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ������� ���Ǵ� �޴��Դϴ�.
// �������� �̿��ؼ� ��ȯ�� ���� ����� �����մϴ�.
// =====================================================================================

#ifndef ENTRANCE_PHASE_MENU_PHASE_LOADER_H__
#define ENTRANCE_PHASE_MENU_PHASE_LOADER_H__

#include "Element\Menu\Menu.h"
#include "MiniGame\MiscellaneousShop2\Phase\MiscellaneousShop2PhaseType.h"

class EntrancePhaseMenu_PhaseLoader : public Menu
{
public:
	using Menu::Menu;

#pragma region ������ �� �Ҹ���
	EntrancePhaseMenu_PhaseLoader() = default;
	virtual ~EntrancePhaseMenu_PhaseLoader() = default;

	EntrancePhaseMenu_PhaseLoader(const std::string_view& szNameTag,
		const COORD& pos, EMiscellaneousShop2PhaseType miscellaneousShop2PhaseType);
#pragma endregion

	virtual EErrorType OnExcute() override;

private:
	EMiscellaneousShop2PhaseType m_selectedPhaseType = EMiscellaneousShop2PhaseType::UNKNOWN;
};

#endif