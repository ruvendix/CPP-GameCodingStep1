// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 입장 페이즈에서 사용되는 메뉴입니다.
// 열거형을 이용해서 전환할 다음 페이즈를 생성합니다.
// =====================================================================================

#include "PCH.h"
#include "EntrancePhaseMenu_PhaseLoader.h"

#include "Manager\PhaseManager.h"

#include "..\Phase\EntrancePhase.h"
#include "..\Phase\BuyPhase.h"
#include "..\Phase\SellPhase.h"
#include "..\Phase\ArrangePhase.h"

EntrancePhaseMenu_PhaseLoader::EntrancePhaseMenu_PhaseLoader(const std::string_view& szNameTag,
	const COORD& pos, EMiscellaneousShop2PhaseType miscellaneousShop2PhaseType) :
	Menu(szNameTag, pos),
	m_selectedPhaseType(miscellaneousShop2PhaseType)
{

}

EErrorType EntrancePhaseMenu_PhaseLoader::OnExcute()
{
	switch (m_selectedPhaseType)
	{
	case EMiscellaneousShop2PhaseType::ENTRANCE:
	{
		PhaseMgr::I()->CreatePhase<EntrancePhase>(ECreateType::NEXT, 0);
		break;
	}

	case EMiscellaneousShop2PhaseType::BUY:
	{
		PhaseMgr::I()->CreatePhase<BuyPhase>(ECreateType::NEXT, 1);
		break;
	}

	case EMiscellaneousShop2PhaseType::SELL:
	{
		PhaseMgr::I()->CreatePhase<SellPhase>(ECreateType::NEXT, 1);
		break;
	}

	case EMiscellaneousShop2PhaseType::ARRANGE:
	{
		PhaseMgr::I()->CreatePhase<ArrangePhase>(ECreateType::NEXT, 1);
		break;
	}

	default:
	{
		DEFAULT_ERROR_HANDLER(EErrorType::UNKNOWN_PHASE_TYPE);
		break;
	}
	}

	return EErrorType();
}
