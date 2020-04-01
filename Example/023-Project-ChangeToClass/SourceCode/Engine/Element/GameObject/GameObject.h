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
public:
#pragma region 생성자 및 소멸자
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
	FILE* m_pFileStream = nullptr; // 호출자에 의해 처리될 경우 파일 스트림이 있는지 판단!
};

#endif