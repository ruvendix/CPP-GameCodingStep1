// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 모든 게임 요소의 기반입니다.
// =====================================================================================

#ifndef GAME_ELEMENT__H__
#define GAME_ELEMENT__H__

#include "Interface\IGameMechanism.h"
#include "NameTag.h"

class GameElement : public IGameMechanism
{
public:
#pragma region 생성자 및 소멸자
	GameElement() = default;
	virtual ~GameElement() = default;

	GameElement(const std::string_view& szNameTag) :
		m_nameTag(szNameTag)
	{

	}
#pragma endregion

	virtual EErrorType OnInitialize();
	virtual EErrorType OnUpdate();
	virtual EErrorType OnRender();
	virtual EErrorType OnFinalize();

#pragma region 접근자
	const std::string& getNameTag() const
	{
		return m_nameTag.getNameTag();
	}

	void setNameTag(const std::string_view& szName)
	{
		m_nameTag.setNameTag(szName);
	}
#pragma endregion

private:
	NameTag m_nameTag;
};

#endif