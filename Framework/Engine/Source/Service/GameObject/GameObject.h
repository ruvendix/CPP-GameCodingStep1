// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ������Ʈ�� �⺻���Դϴ�.
// ���� ������Ʈ�� ���̴� �Ͱ� ������ �ʴ� ��, �����̴� �Ͱ� �������� �ʴ� �͵���
// ���� �����ϴ� �����̶�� �����Ͻø� �˴ϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "Common/CommonInterface.h"

class GameObject : public IGameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	virtual EReturnType SetUp() override;
	virtual EReturnType CleanUp() override;

	virtual EReturnType Update() override;
	virtual EReturnType Render() override;

private:
	std::string m_strTag;
	std::string m_strShape;

	Int32 m_posX = 0;
	Int32 m_posY = 0;
};