// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 모든 씬의 기반입니다.
// =====================================================================================

#ifndef SCENE__H__
#define SCENE__H__

#include "GameElement.h"

class Scene : public GameElem
{
public:
	using GameElem::GameElem;

#pragma region 생성자 및 소멸자
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