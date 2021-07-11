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

namespace Component
{
	class Transfrom final : public IComponent
	{
		GENERATE_COMPONENT(EComponentType::TRANSFORM, Transform);

	public:
		Transfrom(Actor* pActor);
		virtual ~Transfrom() = default;

		virtual void SetUp() override;
		virtual void Update() override;

		void Print() const
		{
			RX_INFO("x: %f\ty: %f", m_x, m_y);
		}

	private:
		float m_x = 0.0f;
		float m_y = 0.0f;
	};
}