// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 모든 게임 오브젝트의 기반입니다.
// =====================================================================================

#ifndef GAME_OBJ__H__
#define GAME_OBJ__H__

#include "GameObjectType.h"
#include "..\GameElement.h"

class GameObj : public GameElem
{
	DECLARE_RTTI(GameObj, GameElem);

public:
#pragma region 생성자 및 소멸자
	using GameElem::GameElem;

	GameObj() = default;
	virtual ~GameObj() = default;

	GameObj(Int32 objID);
#pragma endregion

	virtual EErrorType OnRender() override;
	virtual EErrorType OnPreSaveFile(FILE* pFileStream) override;
	virtual EErrorType OnSaveFile(FILE* pFileStream) override;
	virtual EErrorType OnLoadFile(FILE* pFileStream) override;

	virtual EGameObjType OnGetType() const
	{
		return EGameObjType::UNKNOWN;
	}

	void AddPosX(Int32 x)
	{
		m_pos.X += x;
	}

	void AddPosY(Int32 y)
	{
		m_pos.Y += y;
	}

	Int32 getID() const
	{
		return m_ID;
	}

	Int32 getState() const
	{
		return m_state;
	}

	const COORD& getPos() const
	{
		return m_pos;
	}

	const std::string& getShape() const
	{
		return m_strShape;
	}

	void setID(Int32 ID)
	{
		m_ID = ID;
	}

	void setState(Int32 state)
	{
		m_state = state;
	}

	void setPos(const COORD& pos)
	{
		m_pos = pos;
	}

	void setPos(Int32 x, Int32 y)
	{
		m_pos.X = x;
		m_pos.Y = y;
	}

	void setShape(const std::string_view& szShape)
	{
		m_strShape = szShape;
	}

private:
	// 사용하는 쪽에서는 enum class로 매핑시키는 게 좋아요!
	// 0은 아무 의미가 없음을 의미해요.
	Int32 m_ID = 0;
	Int32 m_state = 0;

	COORD m_pos;
	std::string m_strShape;
};

#endif