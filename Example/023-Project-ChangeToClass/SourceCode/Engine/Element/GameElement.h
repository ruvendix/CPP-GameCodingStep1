// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� ���� ����� ����Դϴ�.
// =====================================================================================

#ifndef GAME_ELEMENT__H__
#define GAME_ELEMENT__H__

#include "Interface\IGameMechanism.h"
#include "NameTag.h"

class GameElement : public IGameMechanism
{
public:
#pragma region ������ �� �Ҹ���
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

#pragma region ������
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