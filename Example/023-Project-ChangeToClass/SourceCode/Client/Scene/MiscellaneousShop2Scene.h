// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 잡화 상점2 씬입니다.
// =====================================================================================

#ifndef MISCELLANEOUS_SHOP2_SCENE_H__
#define MISCELLANEOUS_SHOP2_SCENE_H__

#include "Element\Scene.h"
#include "Controller\ConsoleControllerEnum.h"
#include "MiniGame\MiscellaneousShop2\MiscellaneousShop2.h"

DECLARE_LOG_CATEGORY(MiscellaneousShop2Scene);

class MiscellaneousShop2Scene final : public Scene
{
	DECLARE_RTTI(MiscellaneousShop2Scene, Scene);

public:
#pragma region 생성자 및 소멸자
	using Scene::Scene;
	virtual ~MiscellaneousShop2Scene() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;

private:
	std::unique_ptr<MiscellaneousShop2> m_spMiscellaneousShop2;
};

#endif