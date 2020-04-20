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
	static SHORT CalcMoveToTargetAxis(EDataProgressDir moveAxisDir, Int32 myAxis, Int32 targetAxis,
		Int32 interval, _Out_ Real32& accumulationMove);
};

SHORT DynamicObjHelper::CalcMoveToTargetAxis(EDataProgressDir moveAxisDir, Int32 myAxis, Int32 targetAxis,
	Int32 distance, _Out_ Real32& accumulationMove)
{
	if (distance == 0)
	{
		return 0;
	}

	Real32 dir = 0.0f;
	if (moveAxisDir == EDataProgressDir::POSITIVENESS)
	{
		dir = 1.0f;
	}
	else if (moveAxisDir == EDataProgressDir::NEGATIVENESS)
	{
		dir = -1.0f;
	}

	// 콘솔 좌표는 정수이므로 결국은 정수로 변환 필수!
	// 누적된 이동량이 1.0f일 때마다 좌표를 1씩 더하면 이게 곧 속력!
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

void DynamicObj::MoveToTarget(const SizeInfo& distance, DynamicObjPtr spTargetObj)
{
	// 미리 복사
	Real32 deltaTime = FrameController::I()->getDeltaTime();
	Real32 timeScale = FrameController::I()->getTimeScale();

	// 이동량 누적
	m_accumulationMove += (m_moveSpeed * deltaTime * timeScale);

	// 좌표 복사
	const COORD& pos = getPos();
	const COORD& targetPos = spTargetObj->getPos();

	COORD movePos{ 0, 0 };

	if (m_preferMoveAxis == EPreferMoveAxis::X)
	{
		movePos.X = DynamicObjHelper::CalcMoveToTargetAxis(getMoveAxisDir(0),
			pos.X, targetPos.X, distance.width, m_accumulationMove);
		AddPosX(movePos.X);

		movePos.Y = DynamicObjHelper::CalcMoveToTargetAxis(getMoveAxisDir(1),
			pos.Y, targetPos.Y, distance.height, m_accumulationMove);
		AddPosY(movePos.Y);
	}
	else
	{
		movePos.Y = DynamicObjHelper::CalcMoveToTargetAxis(getMoveAxisDir(1),
			pos.Y, targetPos.Y, distance.height, m_accumulationMove);
		AddPosY(movePos.Y);

		movePos.X = DynamicObjHelper::CalcMoveToTargetAxis(getMoveAxisDir(0),
			pos.X, targetPos.X, distance.width, m_accumulationMove);
		AddPosX(movePos.X);
	}

	return;
}

void DynamicObj::MoveToTarget(DynamicObjPtr spTargetObj)
{
	// 좌표 복사
	const COORD& pos = getPos();
	const COORD& targetPos = spTargetObj->getPos();

	// 나와 절댓값 차의 합이 가장 작은 게 최단거리
	SizeInfo distance{ 0, 0 };
	distance.width = std::abs(pos.X - targetPos.X);
	distance.height = std::abs(pos.Y - targetPos.Y);

	if (distance.width + distance.height == 1)
	{
		//DEBUG_LOG("둘의 차이는 한칸!");
		return;
	}

	MoveToTarget(distance, spTargetObj);
}

EErrorType DynamicObj::Copy(const DynamicObj& src)
{
	if (GameObj::Copy(src) == EErrorType::COPY_FAIL)
	{
		return EErrorType::COPY_FAIL;
	}

	setMoveSpeed(src.getMoveSpeed());
	return EErrorType::NOTHING;
}
