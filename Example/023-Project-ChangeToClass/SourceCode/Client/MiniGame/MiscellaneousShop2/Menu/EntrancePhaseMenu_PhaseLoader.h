// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 입장 페이즈에서 사용되는 메뉴입니다.
// 열거형을 이용해서 전환할 다음 페이즈를 생성합니다.
// =====================================================================================

#ifndef ENTRANCE_PHASE_MENU_PHASE_LOADER_H__
#define ENTRANCE_PHASE_MENU_PHASE_LOADER_H__

#include "Element\Menu\Menu.h"
#include "MiniGame\MiscellaneousShop2\Phase\MiscellaneousShop2PhaseType.h"

class EntrancePhaseMenu_PhaseLoader : public Menu
{
public:
	using Menu::Menu;

#pragma region 생성자 및 소멸자
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