// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 모든 동적 오브젝트의 기반입니다.
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

	// 콘솔 좌표는 정수이므로 결국은 정수로 변환 필수!
	// 누적된 이동량이 1.0f일 때마다 좌표를 1씩 더하면 이게 곧 속력!
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
	// 좌표 복사
	const COORD& pos = getPos();
	const COORD& targetPos = spTargetObj->getPos();
	
	// 다음 이동할 위치와 겹치는지 체크!
	// 절댓값 1인지만 확인하면 됨
	Uint32 intervalX = std::abs(pos.X - targetPos.X);
	Uint32 intervalY = std::abs(pos.Y - targetPos.Y);

	if (intervalX + intervalY == 1)
	{
		DEBUG_LOG("둘의 차이는 한칸!");
		return false;
	}

	// 미리 복사
	Real32 deltaTime = FrameController::I()->getDeltaTime();
	Real32 timeScale = FrameController::I()->getTimeScale();

	// 이동량 누적
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
		DEBUG_LOG("최초로 만남!");
	}

	return true;
}
