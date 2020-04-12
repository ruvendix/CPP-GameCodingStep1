// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� ���� ������Ʈ�� ����Դϴ�.
// =====================================================================================

#ifndef GAME_OBJ__H__
#define GAME_OBJ__H__

#include "GameObjectType.h"
#include "..\GameElement.h"

class GameObj : public GameElem
{
	DECLARE_RTTI(GameObj, GameElem);

public:
#pragma region ������ �� �Ҹ���
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
	// ����ϴ� �ʿ����� enum class�� ���ν�Ű�� �� ���ƿ�!
	// 0�� �ƹ� �ǹ̰� ������ �ǹ��ؿ�.
	Int32 m_ID = 0;
	Int32 m_state = 0;

	COORD m_pos;
	std::string m_strShape;
};

#endif