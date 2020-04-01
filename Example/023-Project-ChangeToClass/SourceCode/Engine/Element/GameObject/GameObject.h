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
public:
#pragma region ������ �� �Ҹ���
	using GameElem::GameElem;
	virtual ~GameObj() = default;
#pragma endregion

	virtual EErrorType OnRender() override;
	virtual EErrorType OnSaveFile(const std::string_view& szFileName) override;
	virtual EErrorType OnLoadFile(const std::string_view& szFileName) override;

	virtual EGameObjType getType() const
	{
		return EGameObjType::NONE;
	}

	bool IsOpenFileStream() const
	{
		return (m_pFileStream != nullptr);
	}

	const COORD& getPos() const
	{
		return m_pos;
	}

	const std::string& getShape() const
	{
		return m_strShape;
	}

	FILE* getFileStream() const
	{
		return m_pFileStream;
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

	void setFileStream(FILE* pFileStream)
	{
		m_pFileStream = pFileStream;
	}

private:
	COORD m_pos;
	std::string m_strShape;
	FILE* m_pFileStream = nullptr; // ȣ���ڿ� ���� ó���� ��� ���� ��Ʈ���� �ִ��� �Ǵ�!
};

#endif