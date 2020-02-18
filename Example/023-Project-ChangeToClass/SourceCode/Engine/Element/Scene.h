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

class Scene : public GameElement
{
public:
	using GameElement::GameElement;

	Scene() = default;
	virtual ~Scene() = default;

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;
};

#endif