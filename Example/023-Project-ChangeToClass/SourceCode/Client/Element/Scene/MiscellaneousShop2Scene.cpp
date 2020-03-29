// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��ȭ ����2 ���Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "MiscellaneousShop2Scene.h"

#include "Manager\SceneManager.h"
#include "Controller\InputController.h"
#include "IntroMenuScene.h"

#include "MiniGame\MiscellaneousShop2\Item\ItemDBContext.h"
#include "MiniGame\MiscellaneousShop2\PlayerContext.h"

DEFINE_LOG_CATEGORY(MiscellaneousShop2Scene);

EErrorType MiscellaneousShop2Scene::OnInitialize()
{
	ItemDBCtx::I()->Initialize();
	PlayerCtx::I()->Initialize();

	PlayerCtx::I()->setGameMoney(2000);

	m_spMiscellaneousShop2 = std::make_unique<MiscellaneousShop2>();
	if (m_spMiscellaneousShop2->OnInitialize() == EErrorType::INIT_FAILED)
	{
		return EErrorType::INIT_FAILED;
	}

	return EErrorType::NONE;
}

EErrorType MiscellaneousShop2Scene::OnInput()
{
	if (m_spMiscellaneousShop2->OnInput() == EErrorType::INPUT_FAILED)
	{
		return EErrorType::INPUT_FAILED;
	}

	return EErrorType::NONE;
}

EErrorType MiscellaneousShop2Scene::OnUpdate()
{
	if (m_spMiscellaneousShop2->OnUpdate() == EErrorType::UPDATE_FAILED)
	{
		return EErrorType::UPDATE_FAILED;
	}

	return EErrorType::NONE;
}

EErrorType MiscellaneousShop2Scene::OnRender()
{
	if (m_spMiscellaneousShop2->OnRender() == EErrorType::RENDER_FAILED)
	{
		return EErrorType::RENDER_FAILED;
	}

	return EErrorType::NONE;
}

EErrorType MiscellaneousShop2Scene::OnFinalize()
{
	if (m_spMiscellaneousShop2->OnFinalize() == EErrorType::FINAL_FAILED)
	{
		return EErrorType::FINAL_FAILED;
	}

	PlayerCtx::I()->Finalize();
	ItemDBCtx::I()->Finalize();

	return EErrorType::NONE;
}