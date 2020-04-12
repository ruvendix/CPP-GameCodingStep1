// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 모든 동적 오브젝트의 기반입니다.
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

#pragma region 생성자 및 소멸자
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