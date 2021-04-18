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
#include "EnginePCH.h"
#include "GameObject.h"

#include "Service/ServiceInclusion.h"

/*
	게임 오브젝트를 초기화합니다.
	태그와 모양을 기본사항으로 설정해요.
*/
EReturnType GameObject::SetUp()
{
	m_strTag = "Default";
	m_strShape = "A";

	return EReturnType::SUCCESS;
}

/*
	게임 오브젝트를 정리합니다.
	아직은 추가할 내용이 없어요.
*/
EReturnType GameObject::CleanUp()
{
	return EReturnType::SUCCESS;
}

/*
	게임 오브젝트의 내용을 갱신합니다.
*/
EReturnType GameObject::Update()
{
	return EReturnType::SUCCESS;
}

/*
	게임 오브젝트를 그립니다.
*/
EReturnType GameObject::Render()
{
	ServiceLocator::I().IConsoleHandlerInstance()->RenderString(m_posX, m_posY, m_strShape.c_str());
	return EReturnType::SUCCESS;
}