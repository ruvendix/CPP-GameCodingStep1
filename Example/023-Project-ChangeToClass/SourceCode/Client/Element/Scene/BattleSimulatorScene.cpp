// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터 씬입니다.
// =====================================================================================

#include "PCH.h"
#include "BattleSimulatorScene.h"

#include "Controller\ConsoleController.h"
#include "Controller\InputController.h"
#include "Manager\SceneManager.h"
#include "IntroMenuScene.h"
#include "Math\Random.h"
#include "MiniGame\BattleSimulator\MedievalKnight.h"
#include "MiniGame\BattleSimulator\Viking.h"

namespace
{
	MedievalKnight s_dummyMedievalKnight;
	Viking s_dummyViking;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BattleSimulatorSceneHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(BattleSimulatorSceneHelper);

public:
	static void DrawTitle();
	static void DrawUnitStat();
	static void DrawBattleReport(const BattleSimulatorScene& helperTarget);

	static MedievalKnight* CloneMedievalKnight();
	static Viking* CloneViking();
};

void BattleSimulatorSceneHelper::DrawTitle()
{
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::LIGHT_AQUA);

	Int32 drawPosY = -1;
	PRINTF(12, ++drawPosY, "▲▲▲▲▲▲▲▲▲▲");
	PRINTF(12, ++drawPosY, "<중세기사 VS 바이킹>");
	PRINTF(12, ++drawPosY, "▼▼▼▼▼▼▼▼▼▼");

	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::WHITE);
}

void BattleSimulatorSceneHelper::DrawUnitStat()
{
	Int32 drawPosY = 3;
	PRINTF(0, ++drawPosY, "-------------------------------------------");
	PRINTF(0, ++drawPosY, "              중세기사    바이킹");
	PRINTF(0, ++drawPosY, "-------------------------------------------");
	PRINTF(0, ++drawPosY, "HP           : %7d   %7d", s_dummyMedievalKnight.getMaxHP(), s_dummyViking.getMaxHP());
	PRINTF(0, ++drawPosY, "공격력       : %7d   %7d", s_dummyMedievalKnight.getAttackDamage(), s_dummyViking.getAttackDamage());
	PRINTF(0, ++drawPosY, "공격 성공율  : %7d%%  %7d%%", static_cast<Int32>(s_dummyMedievalKnight.getAttackSuccessRate() * 100.0f),
		static_cast<Int32>(s_dummyViking.getAttackSuccessRate() * 100.0f));
	PRINTF(0, ++drawPosY, "-------------------------------------------");
}

void BattleSimulatorSceneHelper::DrawBattleReport(const BattleSimulatorScene& helperTarget)
{
	Int32 remainMedievalKnightCnt = static_cast<Int32>(helperTarget.m_vecMedievalKnight.size());
	Int32 remainVikingCnt = static_cast<Int32>(helperTarget.m_vecViking.size());

	Int32 drawPosX = 50;
	Int32 drawPosY = 3;
	PRINTF(drawPosX, ++drawPosY, "-------------------------------------------");
	PRINTF(drawPosX, ++drawPosY, "              중세기사    바이킹");
	PRINTF(drawPosX, ++drawPosY, "-------------------------------------------");
	PRINTF(drawPosX, ++drawPosY, "살아남은 수 : %7d   %7d", remainMedievalKnightCnt, remainVikingCnt);

	Int32 medievalKnightDeadCnt = MedievalKnight::GetTotalCnt() - remainMedievalKnightCnt;
	Int32 vikingDeadCnt = Viking::GetTotalCnt() - remainVikingCnt;
	PRINTF(drawPosX, ++drawPosY, "사망한 수   : %7d   %7d", medievalKnightDeadCnt, vikingDeadCnt);

	// 중세기사 부대가 준 피해량
	Int32 totalMedievalKnightAttackDamage = (s_dummyViking.getMaxHP() * vikingDeadCnt);
	if (helperTarget.m_vecViking.empty() == false)
	{
		Viking* pViking = helperTarget.m_vecViking[0];
		CHECK_NULLPTR_RETURN_VOID(pViking);
		totalMedievalKnightAttackDamage += (s_dummyViking.getMaxHP() - pViking->getHP());
	}

	// 바이킹 부대가 준 피해량
	Int32 totalVikingAttackDamage = (s_dummyMedievalKnight.getMaxHP() * medievalKnightDeadCnt);
	if (helperTarget.m_vecMedievalKnight.empty() == false)
	{
		MedievalKnight* pMedievalKnight = helperTarget.m_vecMedievalKnight[0];
		CHECK_NULLPTR_RETURN_VOID(pMedievalKnight);
		totalVikingAttackDamage += (s_dummyMedievalKnight.getMaxHP() - pMedievalKnight->getHP());
	}

	PRINTF(drawPosX, ++drawPosY, "준 피해량   : %7d   %7d", totalMedievalKnightAttackDamage, totalVikingAttackDamage);
	PRINTF(drawPosX, ++drawPosY, "-------------------------------------------");

	// 어느 쪽이 이겼는지 점수를 계산해보죠~
	// "준 피해량"은 공정하지 않으므로 점수에서 제외할게요.
	// 아군이 살아남은 수만큼 5점 득점, 적군이 사망된 수만큼 3점 득점!
	Int32 totalMedievalKnightScore = (remainMedievalKnightCnt * 5) + (vikingDeadCnt * 3);
	Int32 totalVikingScore = (remainVikingCnt * 5) + (medievalKnightDeadCnt * 3);

	PRINTF(drawPosX, ++drawPosY, "총점        : %7d   %7d", totalMedievalKnightScore, totalVikingScore);
	PRINTF(drawPosX, ++drawPosY, "-------------------------------------------");

	PRINTF(drawPosX, ++drawPosY, "※ 승리한 부대는 ");
	if (totalMedievalKnightScore == totalVikingScore)
	{
		PRINTF(drawPosX, ++drawPosY, "없네요... 점수가 동일해요.");
	}
	else
	{
		std::string strWinner;
		if (totalMedievalKnightScore > totalVikingScore)
		{
			strWinner = "중세기사";
		}
		else
		{
			strWinner = "바이킹";
		}

		PRINTF(drawPosX, ++drawPosY, "\"%s\" 부대네요~!", strWinner.c_str());
	}
}

MedievalKnight* BattleSimulatorSceneHelper::CloneMedievalKnight()
{
	MedievalKnight* pUnit = trace_new MedievalKnight;
	*pUnit = s_dummyMedievalKnight;
	return pUnit;
}

Viking* BattleSimulatorSceneHelper::CloneViking()
{
	Viking* pUnit = trace_new Viking;
	*pUnit = s_dummyViking;
	return pUnit;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_LOG_CATEGORY(BattleSimulatorScene);

EErrorType BattleSimulatorScene::OnInitialize()
{
	DEBUG_LOG("배틀 시뮬레이터 씬!");
	InputController::I()->InsertInputMappingInfo("GotoIntro", VK_ESCAPE);

	// 더미 중세기사의 스탯을 정할게요.
	s_dummyMedievalKnight.setHP(180);
	s_dummyMedievalKnight.setMaxHP(180);
	s_dummyMedievalKnight.setAttackDamage(14);
	s_dummyMedievalKnight.setAttackSuccessRate(0.78f);

	// 더미 바이킹의 스탯을 정할게요.
	s_dummyViking.setHP(198);
	s_dummyViking.setMaxHP(198);
	s_dummyViking.setAttackDamage(18);
	s_dummyViking.setAttackSuccessRate(0.58f);

	// 더블 버퍼링에 콘솔 Win32API를 사용 중이므로 scanf()는 사용할 수 없어요.
	// 따라서 숫자 입력을 받는 기능은 제거할게요.

	// 설정된 중세기사의 수만큼 채워줄게요.
	MedievalKnight::SetTotalCnt(30);
	m_vecMedievalKnight.resize(MedievalKnight::GetTotalCnt());
	std::generate(m_vecMedievalKnight.begin(), m_vecMedievalKnight.end(), &BattleSimulatorSceneHelper::CloneMedievalKnight);

	// 설정된 바이킹의 수만큼 채워줄게요.
	Viking::SetTotalCnt(30);
	m_vecViking.resize(Viking::GetTotalCnt());
	std::generate(m_vecViking.begin(), m_vecViking.end(), &BattleSimulatorSceneHelper::CloneViking);

	return EErrorType::NONE;
}

EErrorType BattleSimulatorScene::OnUpdate()
{
	if (InputController::I()->CheckInputState("GotoIntro", EInputMappingState::DOWN) == true)
	{
		SceneMgr::I()->CreateScene<IntroMenuScene>(ESceneType::NEXT);
	}

	// 중세기사 또는 바이킹이 없으면 아무 처리도 하지 않을게요!
	if ( (m_vecMedievalKnight.empty() == true) ||
		 (m_vecViking.empty() == true) )
	{
		m_bBattleEnd = true;
		return EErrorType::NONE;
	}

	// 턴제로 한번씩 공격
	Unit* pMedievalKnight = m_vecMedievalKnight[0];
	CHECK_NULLPTR_RETURN_ERRORTYPE(pMedievalKnight);

	Unit* pViking = m_vecViking[0];
	CHECK_NULLPTR_RETURN_ERRORTYPE(pViking);

#pragma region 중세기사 -> 바이킹
	pMedievalKnight->Attack(pViking);

	if (pViking->IsDeath())
	{
		SAFE_DELETE(pViking);
		m_vecViking.erase(m_vecViking.begin());
		if (m_vecViking.empty() == true)
		{
			return EErrorType::NONE;
		}

		pViking = m_vecViking[0];
		CHECK_NULLPTR_RETURN_ERRORTYPE(pViking);
	}
#pragma endregion

#pragma region 바이킹 -> 중세기사
	pViking->Attack(pMedievalKnight);

	if (pMedievalKnight->IsDeath())
	{
		SAFE_DELETE(pMedievalKnight);
		m_vecMedievalKnight.erase(m_vecMedievalKnight.begin());
	}
#pragma endregion

	// 원래는 죽은 유닛들의 대한 정보도 저장해야 하지만
	// 배틀 시뮬레이터는 간단한 게임이니까 따로 저장하지는 않을게요.

	return EErrorType::NONE;
}

EErrorType BattleSimulatorScene::OnRender()
{
	BattleSimulatorSceneHelper::DrawTitle();
	BattleSimulatorSceneHelper::DrawUnitStat();

	Int32 drawPosY = 11;
	PRINTF(0, ++drawPosY, "남은 중세기사의 수 : %d / %d", static_cast<Int32>(m_vecMedievalKnight.size()), MedievalKnight::GetTotalCnt());
	PRINTF(0, ++drawPosY, "남은 바이킹의 수   : %d / %d", static_cast<Int32>(m_vecViking.size()), Viking::GetTotalCnt());

	++drawPosY;
	PRINTF(0, ++drawPosY, "∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼");
	PRINTF(0, ++drawPosY, "모의 전투를 시작할게요~!");

	if (m_bBattleEnd == false)
	{
		return EErrorType::NONE;
	}

	PRINTF(0, ++drawPosY, "모의 전투가 끝났어요~!");
	PRINTF(0, ++drawPosY, "전투 결과를 알아볼까요?");
	PRINTF(0, ++drawPosY, "∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼");

	BattleSimulatorSceneHelper::DrawBattleReport(*this);

	return EErrorType::NONE;
}

EErrorType BattleSimulatorScene::OnFinalize()
{
	for (auto& iter : m_vecMedievalKnight)
	{
		SAFE_DELETE(iter);
	}

	for (auto& iter : m_vecViking)
	{
		SAFE_DELETE(iter);
	}

	return EErrorType::NONE;
}
