// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 위치, 회전, 수축 정보가 있습니다.
// 지금은 간단하게 위치만 넣었습니다.
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