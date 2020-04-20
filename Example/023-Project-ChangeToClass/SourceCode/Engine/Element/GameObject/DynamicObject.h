// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� ���� ������Ʈ�� ����Դϴ�.
// =====================================================================================

#ifndef DYNAMIC_OBJ__H__
#define DYNAMIC_OBJ__H__

#include "GameObject.h"
#include "Common\CommonEnum.h"

enum class EPreferMoveAxis : Int32
{
	UNKNOWN,
	X,
	Y,
};

class DynamicObj;
using DynamicObjPtr = std::shared_ptr<DynamicObj>;

class DynamicObj : public GameObj
{
	DECLARE_RTTI(DynamicObj, GameObj);

public:
#pragma region ������ �� �Ҹ���
	using GameObj::GameObj;
	virtual ~DynamicObj() = default;
#pragma endregion

	virtual EErrorType OnSaveFile(FILE* pFileStream) override;
	virtual EErrorType OnLoadFile(FILE* pFileStream) override;

	void MoveToTarget(const SizeInfo& distance, DynamicObjPtr spTargetObj);
	void MoveToTarget(DynamicObjPtr spTargetObj);

	EErrorType Copy(const DynamicObj& src);

	virtual EGameObjType OnGetType() const override
	{
		return EGameObjType::DYNAMIC;
	}

	EDataProgressDir getMoveAxisDir(Int32 idx) const
	{
		CHECK_RANGE(idx, 0, m_arrMoveAxisDir.size());
		return m_arrMoveAxisDir[idx];
	}

	void setMoveSpeed(Real32 moveSpeed)
	{
		m_moveSpeed = moveSpeed;
	}

	void setPreferMoveAxis(EPreferMoveAxis axis)
	{
		m_preferMoveAxis = axis;
	}

	void setMoveAxisDir(Int32 idx, EDataProgressDir moveAxisDir)
	{
		CHECK_RANGE(idx, 0, m_arrMoveAxisDir.size());
		m_arrMoveAxisDir[idx] = moveAxisDir;
	}

	Real32 getMoveSpeed() const
	{
		return m_moveSpeed;
	}

private:
	Real32 m_moveSpeed = 0.0f;
	Real32 m_accumulationMove = 0.0f;

	EPreferMoveAxis m_preferMoveAxis = EPreferMoveAxis::UNKNOWN;
	std::array<EDataProgressDir, 2> m_arrMoveAxisDir;
};

#endif