// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� ���� ����Դϴ�.
// =====================================================================================

#ifndef SCENE__H__
#define SCENE__H__

#include "GameElement.h"

class Scene : public GameElem
{
public:
	using GameElem::GameElem;

#pragma region ������ �� �Ҹ���
	Scene() = default;
	virtual ~Scene() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;
};

#endif