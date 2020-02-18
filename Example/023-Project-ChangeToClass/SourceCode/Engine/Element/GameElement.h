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
	HAS_NAME_TAG();

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
};

#endif