// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��ġ, ȸ��, ���� ������ �ֽ��ϴ�.
// ������ �����ϰ� ��ġ�� �־����ϴ�.
// =====================================================================================
#pragma once

#include "Base/IComponent.h"

class Transform : public IComponent
{
	GENERATE_HIERARCHY(Transform, IComponent);

public:
	using IComponent::IComponent;
	virtual ~Transform() = default;

	void Print() const
	{
		RX_INFO("x: %f\ty: %f", m_x, m_y);
	}

private:
	float m_x = 0.0f;
	float m_y = 0.0f;
};