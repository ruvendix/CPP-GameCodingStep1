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

class GameElem : public IGameMechanism
{
	HAS_NAME_TAG();

public:
#pragma region ������ �� �Ҹ���
	GameElem() = default;
	virtual ~GameElem() = default;

	GameElem(const std::string_view& szNameTag) :
		m_nameTag(szNameTag)
	{

	}
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;
};

#endif