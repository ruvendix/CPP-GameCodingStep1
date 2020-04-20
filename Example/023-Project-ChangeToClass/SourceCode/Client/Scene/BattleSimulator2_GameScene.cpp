// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2 ���Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "BattleSimulator2_GameScene.h"

#include "Controller\ConsoleController.h"
#include "Controller\InputController.h"
#include "Controller\FrameController.h"
#include "Manager\SceneManager.h"
#include "Manager\TriggerTimerManager.h"
#include "Math\Random.h"

#include "BattleSimulator2_EditorScene.h"
#include "MiniGame\BattleSimulator2\BattleSimulator2_DataCollector.h"
#include "MiniGame\BattleSimulator2\BattleSimulator2World.h"
#include "MiniGame\BattleSimulator2\BattleSimulator2_LevelDesign.h"
#include "MiniGame\BattleSimulator2\GameObject\DynamicObject\MedievalKnight.h"
#include "MiniGame\BattleSimulator2\GameObject\DynamicObject\Viking.h"

namespace
{
	Uint32 s_triggerTimerID_deathUnit = 0;
}

class PredUnit
{
public:
	PredUnit(UnitPtr spUnit)
		: m_spUnit(spUnit)
	{

	}

	~PredUnit() = default;

	bool operator()(UnitPtr spUnit)
	{
		if (spUnit == nullptr)
		{
			return false;
		}

		CHECK_NULLPTR(spUnit);
		return (m_spUnit == spUnit);
	}

private:
	UnitPtr m_spUnit = nullptr;
};

//
//void BattleSimulator2_GameSceneHelper::DrawTitle()
//{
//	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::LIGHT_AQUA);
//
//	Int32 drawPosY = -1;
//	PUT_STRING(12, ++drawPosY, "�����������");
//	PUT_STRING(12, ++drawPosY, "<�߼���� VS ����ŷ>");
//	PUT_STRING(12, ++drawPosY, "�����������");
//
//	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::WHITE);
//}
//
//void BattleSimulator2_GameSceneHelper::DrawUnitStat()
//{
//	Int32 drawPosY = 3;
//	PUT_STRING(0, ++drawPosY, "-------------------------------------------");
//	PUT_STRING(0, ++drawPosY, "              �߼����    ����ŷ");
//	PUT_STRING(0, ++drawPosY, "-------------------------------------------");
//	PUT_STRING(0, ++drawPosY, "HP           : %7d   %7d", s_dummyMedievalKnight.getMaxHP(), s_dummyViking.getMaxHP());
//	PUT_STRING(0, ++drawPosY, "���ݷ�       : %7d   %7d", s_dummyMedievalKnight.getAttackDamage(), s_dummyViking.getAttackDamage());
//	PUT_STRING(0, ++drawPosY, "���� ������  : %7d%%  %7d%%", static_cast<Int32>(s_dummyMedievalKnight.getAttackSuccessRate() * 100.0f),
//		static_cast<Int32>(s_dummyViking.getAttackSuccessRate() * 100.0f));
//	PUT_STRING(0, ++drawPosY, "-------------------------------------------");
//}
//
//void BattleSimulator2_GameSceneHelper::DrawBattleReport(const BattleSimulator2_GameScene& helperTarget)
//{
//	Int32 remainMedievalKnightCnt = static_cast<Int32>(helperTarget.m_vecMedievalKnight.size());
//	Int32 remainVikingCnt = static_cast<Int32>(helperTarget.m_vecViking.size());
//
//	Int32 drawPosX = 50;
//	Int32 drawPosY = 3;
//	PUT_STRING(drawPosX, ++drawPosY, "-------------------------------------------");
//	PUT_STRING(drawPosX, ++drawPosY, "              �߼����    ����ŷ");
//	PUT_STRING(drawPosX, ++drawPosY, "-------------------------------------------");
//	PUT_STRING(drawPosX, ++drawPosY, "��Ƴ��� �� : %7d   %7d", remainMedievalKnightCnt, remainVikingCnt);
//
//	Int32 medievalKnightDeadCnt = MedievalKnight::GetTotalCnt() - remainMedievalKnightCnt;
//	Int32 vikingDeadCnt = Viking::GetTotalCnt() - remainVikingCnt;
//	PUT_STRING(drawPosX, ++drawPosY, "����� ��   : %7d   %7d", medievalKnightDeadCnt, vikingDeadCnt);
//
//	// �߼���� �δ밡 �� ���ط�
//	Int32 totalMedievalKnightAttackDamage = (s_dummyViking.getMaxHP() * vikingDeadCnt);
//	if (helperTarget.m_vecViking.empty() == false)
//	{
//		std::shared_ptr<Viking> spViking = helperTarget.m_vecViking[0];
//		totalMedievalKnightAttackDamage += (s_dummyViking.getMaxHP() - spViking->getHP());
//	}
//
//	// ����ŷ �δ밡 �� ���ط�
//	Int32 totalVikingAttackDamage = (s_dummyMedievalKnight.getMaxHP() * medievalKnightDeadCnt);
//	if (helperTarget.m_vecMedievalKnight.empty() == false)
//	{
//		std::shared_ptr<MedievalKnight> spMedievalKnight = helperTarget.m_vecMedievalKnight[0];
//		totalVikingAttackDamage += (s_dummyMedievalKnight.getMaxHP() - spMedievalKnight->getHP());
//	}
//
//	PUT_STRING(drawPosX, ++drawPosY, "�� ���ط�   : %7d   %7d", totalMedievalKnightAttackDamage, totalVikingAttackDamage);
//	PUT_STRING(drawPosX, ++drawPosY, "-------------------------------------------");
//
//	// ��� ���� �̰���� ������ ����غ���~
//	// "�� ���ط�"�� �������� �����Ƿ� �������� �����ҰԿ�.
//	// �Ʊ��� ��Ƴ��� ����ŭ 5�� ����, ������ ����� ����ŭ 3�� ����!
//	Int32 totalMedievalKnightScore = (remainMedievalKnightCnt * 5) + (vikingDeadCnt * 3);
//	Int32 totalVikingScore = (remainVikingCnt * 5) + (medievalKnightDeadCnt * 3);
//
//	PUT_STRING(drawPosX, ++drawPosY, "����        : %7d   %7d", totalMedievalKnightScore, totalVikingScore);
//	PUT_STRING(drawPosX, ++drawPosY, "-------------------------------------------");
//
//	PUT_STRING(drawPosX, ++drawPosY, "�� �¸��� �δ�� ");
//	if (totalMedievalKnightScore == totalVikingScore)
//	{
//		PUT_STRING(drawPosX, ++drawPosY, "���׿�... ������ �����ؿ�.");
//	}
//	else
//	{
//		std::string strWinner;
//		if (totalMedievalKnightScore > totalVikingScore)
//		{
//			strWinner = "�߼����";
//		}
//		else
//		{
//			strWinner = "����ŷ";
//		}
//
//		PUT_STRING(drawPosX, ++drawPosY, "\"%s\" �δ�׿�~!", strWinner.c_str());
//	}
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_LOG_CATEGORY(BattleSimulator2_GameScene);

EErrorType BattleSimulator2_GameScene::OnInitialize()
{
	DEBUG_LOG_CATEGORY(BattleSimulator2_GameScene, "��Ʋ �ùķ����� ��!");
	InputController::I()->InsertInputMappingInfo("GotoIntro", VK_ESCAPE);

	// ����� ���� �������� �ҷ��ɴϴ�.
	// �̹� ������ ������ �ҷ��� �������� �Ϲ����� ��Ȳ�� ���߱� ���� �ٽ� �ҷ��ɴϴ�.
	m_spWorld = std::make_shared<BattleSimulator2World>();
	if (m_spWorld->LoadFile("BattleSimulator2.world") == EErrorType::LOAD_FILE_FAIL)
	{
		return EErrorType::LOAD_FILE_FAIL;
	}

	// ���带 �ҷ������� ������ �ݷ��͸� �ʱ�ȭ�ؾ� �ؿ�.
	BattleSimulator2_DataCollector::I()->Initialize();

	m_spLevelDesign = std::make_shared<BattleSimulator2_LevelDesign>();
	if (m_spLevelDesign->LoadFile("BattleSimulator2.level") == EErrorType::LOAD_FILE_FAIL)
	{
		return EErrorType::LOAD_FILE_FAIL;
	}

	// ���� �������� ���� ���ּ��� �ʱ�ȭ�ؾ� �ؿ�!
	Int32 vikingCnt = BattleSimulator2_DataCollector::I()->FindBattleData(EDynamicObjID::VIKING, EBattleDataType::TOTAL_UNIT_CNT);
	BattleSimulator2_DataCollector::I()->ModifyBattleData(EDynamicObjID::VIKING, EBattleDataType::REMAIN_UNIT_CNT, vikingCnt);

	Int32 medievalKnightCnt = BattleSimulator2_DataCollector::I()->FindBattleData(EDynamicObjID::MEDIEVAL_KNIGHT, EBattleDataType::TOTAL_UNIT_CNT);
	BattleSimulator2_DataCollector::I()->ModifyBattleData(EDynamicObjID::MEDIEVAL_KNIGHT, EBattleDataType::REMAIN_UNIT_CNT, medievalKnightCnt);

	const VecLevelDesigndObj& vecObj = m_spLevelDesign->getVecObj();
	m_vecUnit.reserve(vecObj.size());
	common_func::CopySharedPtrContainer(vecObj, m_vecUnit);

	m_mapUnitStateCallback.Subscribe(EUnitState::IDLE,
		std::bind(&BattleSimulator2_GameScene::OnCallback_UpdateIdleState, this, std::placeholders::_1));
	m_mapUnitStateCallback.Subscribe(EUnitState::MOVE,
		std::bind(&BattleSimulator2_GameScene::OnCallback_UpdateMoveState, this, std::placeholders::_1));
	m_mapUnitStateCallback.Subscribe(EUnitState::ATTACK,
		std::bind(&BattleSimulator2_GameScene::OnCallback_UpdateAttackState, this, std::placeholders::_1));
	m_mapUnitStateCallback.Subscribe(EUnitState::DEATH,
		std::bind(&BattleSimulator2_GameScene::OnCallback_UpdateDeathState, this, std::placeholders::_1));

	return EErrorType::NOTHING;
}

EErrorType BattleSimulator2_GameScene::OnInput()
{
	if (InputController::I()->CheckInputState("GotoIntro", EInputMappingState::DOWN) == true)
	{
		BattleSimulator2_DataCollector::I()->Finalize();
		SceneMgr::I()->CreateScene<BattleSimulator2_EditorScene>(ECreateType::NEXT);
	}

	return EErrorType::NOTHING;
}

EErrorType BattleSimulator2_GameScene::OnUpdate()
{
	if (m_bBattleEnd == true)
	{
		return EErrorType::NOTHING;
	}

	// ������ ���� ���ֵ��� ���� ������ �����ؾ� ������
	// ��Ʋ �ùķ����ʹ� ������ �����̴ϱ� ���� ���������� �����Կ�.
	for (auto& iter : m_vecUnit)
	{
		UnitPtr spUnit = common_func::KindCastSP<Unit>(iter);
		CHECK_NULLPTR_CONTINUE(spUnit);

		MapUnitStateCallback::ElemType pCallback = m_mapUnitStateCallback.Find(spUnit->getState());
		if (pCallback != nullptr)
		{
			pCallback(spUnit);
		}
	}

	return EErrorType::NOTHING;
}

EErrorType BattleSimulator2_GameScene::OnRender()
{
	if (m_spWorld->OnRender() == EErrorType::RENDER_FAIL)
	{
		return EErrorType::RENDER_FAIL;
	}

	for (const auto& iter : m_vecUnit)
	{
		CHECK_NULLPTR_CONTINUE(iter);

		if (iter->OnRender() == EErrorType::RENDER_FAIL)
		{
			return EErrorType::RENDER_FAIL;
		}
	}

	//BattleSimulator2_GameSceneHelper::DrawTitle();
	//BattleSimulator2_GameSceneHelper::DrawUnitStat();

	//Int32 drawPosY = 11;
	//PUT_STRING(0, ++drawPosY, "���� �߼������ �� : %d / %d", static_cast<Int32>(m_vecMedievalKnight.size()), MedievalKnight::GetTotalCnt());
	//PUT_STRING(0, ++drawPosY, "���� ����ŷ�� ��   : %d / %d", static_cast<Int32>(m_vecViking.size()), Viking::GetTotalCnt());

	//++drawPosY;
	//PUT_STRING(0, ++drawPosY, "��������������������������������������������");
	//PUT_STRING(0, ++drawPosY, "���� ������ �����ҰԿ�~!");

	//if (m_bBattleEnd == false)
	//{
	//	return EErrorType::NOTHING;
	//}

	//PUT_STRING(0, ++drawPosY, "���� ������ �������~!");
	//PUT_STRING(0, ++drawPosY, "���� ����� �˾ƺ����?");
	//PUT_STRING(0, ++drawPosY, "��������������������������������������������");

	//BattleSimulator2_GameSceneHelper::DrawBattleReport(*this);
	return EErrorType::NOTHING;
}

EErrorType BattleSimulator2_GameScene::OnFinalize()
{
	for (auto& iter : m_vecUnit)
	{
		CHECK_NULLPTR_CONTINUE(iter);

		if (iter->OnFinalize() == EErrorType::FINAL_FAIL)
		{
			return EErrorType::FINAL_FAIL;
		}
	}

	s_triggerTimerID_deathUnit = 0;
	return EErrorType::NOTHING;
}

void BattleSimulator2_GameScene::OnCallback_UpdateIdleState(UnitPtr spUnit)
{
	// �þ� ������ŭ ���� ������ ����Ʈ�� �߰�!
	spUnit->ClearUnitInRange();
	spUnit->FilterUnitInRange(m_vecUnit, m_spWorld->getSize());

	// �߰��� ����Ʈ���� ���� �ִ� �Ÿ���?
	SizeInfo distance{ 0, 0 };
	UnitPtr spTargetUnit = spUnit->SearchShortestPathEnemyInRange(distance);
	if (spTargetUnit == nullptr)
	{
		return; // �þ� �ȿ� �̵��� Ÿ���� ����
	}

	// �� ������ 1ĭ ���� �����¿쿡 �ִ� ���
	if (distance.width + distance.height == 1)
	{
		spUnit->ChangeLockOnTargetUnit(spTargetUnit);
		spUnit->setState(EUnitState::ATTACK);
		//DEBUG_LOG("���� ���̴� ��ĭ!");
	}
	else
	{
		spUnit->setState(EUnitState::MOVE);
	}
}

void BattleSimulator2_GameScene::OnCallback_UpdateMoveState(UnitPtr spUnit)
{
	// �þ� ������ŭ ���� ������ ����Ʈ�� �߰�!
	spUnit->ClearUnitInRange();
	spUnit->FilterUnitInRange(m_vecUnit, m_spWorld->getSize());

	// �߰��� ����Ʈ���� ���� �ִ� �Ÿ���?
	SizeInfo distance{ 0, 0 };
	UnitPtr spTargetUnit = spUnit->SearchShortestPathEnemyInRange(distance);
	if (spTargetUnit == nullptr)
	{
		spUnit->setState(EUnitState::IDLE);
		return; // �þ� �ȿ� �̵��� Ÿ���� ����
	}

	// �� ������ 1ĭ ���� �����¿쿡 �ִ� ���
	if (distance.width + distance.height == 1)
	{
		spUnit->ChangeLockOnTargetUnit(spTargetUnit);
		spUnit->setState(EUnitState::ATTACK);
		//DEBUG_LOG("���� ���̴� ��ĭ!");
	}

	// X�� Y���� ��� �������� �̵��ؾ� ��?
	spUnit->AdjustMoveAxisDir(spTargetUnit);

	EPreferMoveAxis preferMoveAxis = static_cast<EPreferMoveAxis>(math::RandomUtil::GenerateRandom(0, 1));
	spUnit->setPreferMoveAxis(preferMoveAxis);

	const COORD prevPos = spUnit->getPos();
	spUnit->MoveToTarget(spTargetUnit);

	// ������ ��ġ�� ��ġ���� Ȯ��!
	for (const auto& iter : spUnit->getListUnitInRange())
	{
		CHECK_NULLPTR_CONTINUE(iter);

		// ��ġ�� ��ġ�� ���� ���� �����ؾ� �ϴµ� ��ã�� �˰����� �ʿ��ϹǷ� ����...
		if (math::IsSamePos(spUnit->getPos(), iter->getPos()))
		{
			spUnit->setPos(prevPos);
			break;
		}
	}
}

void BattleSimulator2_GameScene::OnCallback_UpdateAttackState(UnitPtr spUnit)
{
	UnitPtr spLockOnTargetUnit = spUnit->getLockOnTargetUnit();
	if (spLockOnTargetUnit == nullptr)
	{
		spUnit->setState(EUnitState::IDLE);
		return;
	}

	// ���� ����!
	spUnit->Attack(spLockOnTargetUnit);

	if ( (spLockOnTargetUnit->getHP() < 0) &&
		 (spLockOnTargetUnit->IsSameState(EUnitState::ERASE) == false) ) // ���� ������ ���� ����!
	{
		spUnit->setState(EUnitState::IDLE);
		spUnit->ChangeLockOnTargetUnit(nullptr); // �������� nullptr ����� ����

		spLockOnTargetUnit->setState(EUnitState::DEATH);
	}
}

void BattleSimulator2_GameScene::OnCallback_UpdateDeathState(UnitPtr spUnit)
{
	// ������ ����Ʈ �����
	spUnit->setShape("��"); // ��ü �渷?

	std::string strTrigger = common_func::MakeFormatString("%s_%d", "Trigger_DeathUnit", s_triggerTimerID_deathUnit++);
	TriggerTimerMgr::I()->AddTriggerTimer(strTrigger, 1.2f, 0.0f,
		this, &BattleSimulator2_GameScene::OnTrigger_DeathUnit, false, false);

	spUnit->setState(EUnitState::ERASE);

	// ���� ������ ť�� �ְ� Ʈ���� Ÿ�̸Ӱ� �ߵ��� �� front�� �����ͼ� �����ҰԿ�!
	m_queueDeathUnit.push(spUnit);
	//DEBUG_LOG("(%s) ���� �־���!", spUnit->getNameTag().c_str());
}

void BattleSimulator2_GameScene::OnTrigger_DeathUnit()
{
	if (m_vecUnit.empty() == true)
	{
		return;
	}

	// Ʈ���ſ� ��ϵ� ������� ������ ��!
	// �̰� �߱��������� ������...
	const auto& iter = std::find_if(m_vecUnit.cbegin(), m_vecUnit.cend(), PredUnit(m_queueDeathUnit.front()));
	if (iter == m_vecUnit.cend())
	{
		return;
	}

	UnitPtr spUnit = *iter;
	CHECK_NULLPTR(spUnit);

	spUnit->ChangeLockOnTargetUnit(nullptr);
	spUnit->ClearUnitInRange();

	BattleSimulator2_DataCollector::I()->ModifyBattleData(static_cast<EDynamicObjID>(spUnit->getID()),
		EBattleDataType::REMAIN_UNIT_CNT, EDataProgressDir::NEGATIVENESS, 1);

	BattleSimulator2_DataCollector::I()->ModifyBattleData(static_cast<EDynamicObjID>(spUnit->getID()),
		EBattleDataType::DEATH_UNIT_CNT, EDataProgressDir::POSITIVENESS, 1);

	//DEBUG_LOG("(%s) ���� ����!", spUnit->getNameTag().c_str());
	m_vecUnit.erase(iter);
	m_queueDeathUnit.pop();

	// ��Ʋ�� �������� ���⼭ Ȯ��!
	if (BattleSimulator2_DataCollector::I()->IsBattleEnd())
	{
		m_bBattleEnd = true;
		RESERVE_RENDERING_STRING(3.0f, std::bind(&BattleSimulator2_GameScene::OnTrigger_BattleEnd, this));
	}
}

void BattleSimulator2_GameScene::OnTrigger_BattleEnd() const
{
	PUT_STRING(82, 28, "��Ʋ ��!");
}