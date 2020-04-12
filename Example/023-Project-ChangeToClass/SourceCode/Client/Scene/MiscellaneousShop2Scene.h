// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��ȭ ����2 ���Դϴ�.
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
#pragma region ������ �� �Ҹ���
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