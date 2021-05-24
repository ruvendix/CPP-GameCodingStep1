// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 게임 오브젝트의 기본형입니다.
// 게임 오브젝트는 보이는 것과 보이지 않는 것, 움직이는 것과 움직이지 않는 것들을
// 전부 포함하는 개념이라고 생각하시면 됩니다.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "Common/CommonInterface.h"

class GameObject : public IGameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	virtual void SetUp() override;
	virtual void CleanUp() override;

	virtual void Update() override;
	virtual void Render() override;

private:
	std::string m_strTag;
	std::string m_strShape;

	Int32 m_posX = 0;
	Int32 m_posY = 0;
};