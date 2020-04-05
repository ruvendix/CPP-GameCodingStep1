// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ������� ���Ǵ� �޴��Դϴ�.
// �������� �̿��ؼ� ��ȯ�� ���� ����� �����մϴ�.
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
