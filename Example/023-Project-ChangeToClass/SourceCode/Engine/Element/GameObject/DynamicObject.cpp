// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� ���� ������Ʈ�� ����Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "DynamicObject.h"

#include "Controller\FrameController.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DynamicObjHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(DynamicObjHelper);

public:
	static SHORT CalcMoveToTargetAxis(EMoveAxisDir moveAxisDir, Int32 myAxis, Int32 targetAxis,
		Int32 interval, _Out_ Real32& accumulationMove);
};

SHORT DynamicObjHelper::CalcMoveToTargetAxis(EMoveAxisDir moveAxisDir, Int32 myAxis, Int32 targetAxis,
	Int32 interval, _Out_ Real32& accumulationMove)
{
	if (interval == 0)
	{
		return 0;
	}

	Real32 dir = 0.0f;
	if (moveAxisDir == EMoveAxisDir::POSITIVENESS)
	{
		dir = 1.0f;
	}
	else if (moveAxisDir == EMoveAxisDir::NEGATIVENESS)
	{
		dir = -1.0f;
	}

	// �ܼ� ��ǥ�� �����̹Ƿ� �ᱹ�� ������ ��ȯ �ʼ�!
	// ������ �̵����� 1.0f�� ������ ��ǥ�� 1�� ���ϸ� �̰� �� �ӷ�!
	if (accumulationMove >= 1.0f)
	{
		accumulationMove -= 1.0f;
		return static_cast<SHORT>(1.0f * dir);
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

EErrorType DynamicObj::OnSaveFile(FILE* pFileStream)
{
	if (GameObj::OnSaveFile(pFileStream) == EErrorType::SAVE_FILE_FAIL)
	{
		return EErrorType::SAVE_FILE_FAIL;
	}

	fwrite(&m_moveSpeed, sizeof(m_moveSpeed), 1, pFileStream);
	return EErrorType();
}

EErrorType DynamicObj::OnLoadFile(FILE* pFileStream)
{
	if (GameObj::OnLoadFile(pFileStream) == EErrorType::LOAD_FILE_FAIL)
	{
		return EErrorType::LOAD_FILE_FAIL;
	}

	fread(&m_moveSpeed, sizeof(m_moveSpeed), 1, pFileStream);
	return EErrorType();
}

bool DynamicObj::MoveToTarget(DynamicObjPtr spTargetObj)
{
	// ��ǥ ����
	const COORD& pos = getPos();
	const COORD& targetPos = spTargetObj->getPos();
	
	// ���� �̵��� ��ġ�� ��ġ���� üũ!
	// ���� 1������ Ȯ���ϸ� ��
	Uint32 intervalX = std::abs(pos.X - targetPos.X);
	Uint32 intervalY = std::abs(pos.Y - targetPos.Y);

	if (intervalX + intervalY == 1)
	{
		//DEBUG_LOG("���� ���̴� ��ĭ!");
		return false;
	}

	// �̸� ����
	Real32 deltaTime = FrameController::I()->getDeltaTime();
	Real32 timeScale = FrameController::I()->getTimeScale();

	// �̵��� ����
	m_accumulationMove += (m_moveSpeed * deltaTime * timeScale);
	
	COORD movePos{ 0, 0 };
	if (m_preferMoveAxis == EPreferMoveAxis::X)
	{		
		movePos.X = DynamicObjHelper::CalcMoveToTargetAxis(getMoveAxisDir(0), pos.X, targetPos.X, intervalX, m_accumulationMove);
		AddPosX(movePos.X);
		
		movePos.Y = DynamicObjHelper::CalcMoveToTargetAxis(getMoveAxisDir(1), pos.Y, targetPos.Y, intervalY, m_accumulationMove);
		AddPosY(movePos.Y);
	}
	else
	{
		movePos.Y = DynamicObjHelper::CalcMoveToTargetAxis(getMoveAxisDir(1), pos.Y, targetPos.Y, intervalY, m_accumulationMove);
		AddPosY(movePos.Y);

		movePos.X = DynamicObjHelper::CalcMoveToTargetAxis(getMoveAxisDir(0), pos.X, targetPos.X, intervalX, m_accumulationMove);
		AddPosX(movePos.X);
	}

	return true;
}
