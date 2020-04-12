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

enum class EPreferMoveAxis : Int32
{
	UNKNOWN,
	X,
	Y,
};

enum class EMoveAxisDir : Int32
{
	NEGATIVENESS = 0,
	POSITIVENESS,
};

class DynamicObj : public GameObj
{
	DECLARE_RTTI(DynamicObj, GameObj);

public:
	using DynamicObjPtr = std::shared_ptr<DynamicObj>;

#pragma region ������ �� �Ҹ���
	using GameObj::GameObj;
	virtual ~DynamicObj() = default;
#pragma endregion

	virtual EErrorType OnSaveFile(FILE* pFileStream) override;
	virtual EErrorType OnLoadFile(FILE* pFileStream) override;

	bool MoveToTarget(DynamicObjPtr spTargetObj);

	virtual EGameObjType OnGetType() const override
	{
		return EGameObjType::DYNAMIC;
	}

	EMoveAxisDir getMoveAxisDir(Int32 idx) const
	{
		CHECK_RANGE(idx, 0, m_moveAxisDirs.size());
		return m_moveAxisDirs[idx];
	}

	void setMoveSpeed(Real32 moveSpeed)
	{
		m_moveSpeed = moveSpeed;
	}

	void setPreferMoveAxis(EPreferMoveAxis axis)
	{
		m_preferMoveAxis = axis;
	}

	void setMoveAxisDir(Int32 idx, EMoveAxisDir moveAxisDir)
	{
		CHECK_RANGE(idx, 0, m_moveAxisDirs.size());
		m_moveAxisDirs[idx] = moveAxisDir;
	}

private:
	Real32 m_moveSpeed = 0.0f;
	Real32 m_accumulationMove = 0.0f;

	EPreferMoveAxis m_preferMoveAxis = EPreferMoveAxis::UNKNOWN;
	std::array<EMoveAxisDir, 2> m_moveAxisDirs;
};

#endif