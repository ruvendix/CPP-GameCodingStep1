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
	static Int32 CalcMoveToTargetAxis(Int32 myAxis, Int32 targetAxis, Int32 interval, _Out_ Real32& accumulationMove);
};

Int32 DynamicObjHelper::CalcMoveToTargetAxis(Int32 myAxis, Int32 targetAxis, Int32 interval, _Out_ Real32& accumulationMove)
{
	if (interval == 0)
	{
		return 0;
	}

	Real32 dir = 0.0f;
	if (myAxis < targetAxis)
	{
		dir = 1.0f;
	}
	else if (myAxis > targetAxis)
	{
		dir = -1.0f;
	}

	// �ܼ� ��ǥ�� �����̹Ƿ� �ᱹ�� ������ ��ȯ �ʼ�!
	// ������ �̵����� 1.0f�� ������ ��ǥ�� 1�� ���ϸ� �̰� �� �ӷ�!
	if (accumulationMove >= 1.0f)
	{
		accumulationMove -= 1.0f;
		return static_cast<Int32>(1.0f * dir);
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool DynamicObj::MoveToTarget(std::shared_ptr<DynamicObj> spTargetObj)
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
		DEBUG_LOG("���� ���̴� ��ĭ!");
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
		movePos.X = static_cast<SHORT>(DynamicObjHelper::CalcMoveToTargetAxis(pos.X, targetPos.X, intervalX, m_accumulationMove));
		AddPosX(movePos.X);
		
		movePos.Y = static_cast<SHORT>(DynamicObjHelper::CalcMoveToTargetAxis(pos.Y, targetPos.Y, intervalY, m_accumulationMove));
		AddPosY(movePos.Y);
	}
	else
	{
		movePos.Y = static_cast<SHORT>(DynamicObjHelper::CalcMoveToTargetAxis(pos.Y, targetPos.Y, intervalY, m_accumulationMove));
		AddPosY(movePos.Y);

		movePos.X = static_cast<SHORT>(DynamicObjHelper::CalcMoveToTargetAxis(pos.X, targetPos.X, intervalX, m_accumulationMove));
		AddPosX(movePos.X);
	}

	if (intervalX + intervalY == 1)
	{
		DEBUG_LOG("���ʷ� ����!");
	}

	return true;
}
