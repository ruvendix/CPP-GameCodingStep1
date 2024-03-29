﻿// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 게임 선택, 관리 등 핵심 기능을 담당합니다.
// 인스턴스가 하나만 존재해야 하는 싱글톤입니다.
// =====================================================================================

#include "PCH.h"
#include "GameMain.h"

#include "Context\ConfigContext.h"
#include "Context\GameContext.h"
#include "Manager\SceneManager.h"
#include "Manager\TriggerTimerManager.h"
#include "Manager\PerformanceProfileManager.h"
#include "Manager\ResourcePathManager.h"
#include "Controller\InputController.h"
#include "Controller\FrameController.h"
#include "Controller\ConsoleController.h"
#include "Controller\DebugPanelController.h"
#include "Scene\IntroMenuScene.h"
#include "Math\Random.h"
#include "Element\Menu\MenuTable.h"

#include "Element\World.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameMainHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(GameMainHelper);

public:
#pragma region 게임의 핵심 흐름이에요!
	static void Initialize(_Out_ GameMain& targetHelper);
	static void GameLoop(_Out_ GameMain& targetHelper);
	static void Finalize();
#pragma endregion

	static void Input();
	static void Update();
	static void Render();
};

/*
콘솔창 스타일, 해상도, 게임 상태 등을 초기화합니다.
*/
void GameMainHelper::Initialize(_Out_ GameMain& targetHelper)
{
	DebugPanelController::I()->Initialize();
	ConsoleController::I()->Initialize("Change To Class", SizeInfo{ 125, 30 });
	//ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::BACKGROUND, EConsoleOutputColorType::GREEN);

	GameCtx::I()->setCurrentGameState(EGameState::INIT);
	
	SceneMgr::I()->CreateScene<IntroMenuScene>(ECreateType::CURRENT);
	if (SceneMgr::I()->getCurrentScene()->OnPostInitialize() == EErrorType::INIT_FAIL)
	{
		DEFAULT_ERROR_HANDLER(EErrorType::INIT_FAIL);
	}
	
	FrameController::I()->Initialize();
	FrameController::I()->ChangeFrameRateType(EFrameRateType::CONSTANT);
	//FrameController::I()->ModifyLimitedFrame(60);

	ResourcePathMgr::I()->Initialize();

	rx_math::Random::Initialize();

	MenuTable::Initialize();

	DEBUG_LOG("게임 초기화 처리 완료!");
}

/*
갱신과 렌더링을 반복합니다.
이런 반복 구조를 게임 루프라고 해요.
고정 프레임과 가변 프레임 둘 다 지원하고 상황에 맞게 델타타임이 갱신됩니다.

<고정 프레임 레이트>
사양이 낮은 컴퓨터에서는 프레임을 건너뛰므로 멀티플레이서 싱크 문제가 발생할 수 있습니다.
사양이 높은 컴퓨터에서는 프레임 갱신 속도가 빨라도 제한된 프레임 갱신 속도보다 빠를 수 없습니다.
즉, 안정된 프레임으로 게임을 하고 싶다면 고사양이 유리합니다.

<가변 프레임 레이트>
사양이 낮은 컴퓨터에서는 늦춰진 델타타임만큼 갱신하므로 프레임이 튈 수 있습니다.
사양이 높은 컴퓨터에서는 델타타임이 빨라도 무조건 갱신하므로 프레임이 왔다 갔다 할 수 있습니다.
즉, 저사양과 고사양 둘 다 게임 상태는 비슷하지만 웬만한 고사양이 아니라면 저사양이 유리합니다.
*/
void GameMainHelper::GameLoop(_Out_ GameMain& targetHelper)
{
	// 정상 또는 비정상 종료일 때만 게임루프를 탈출!
	while (GameCtx::I()->IsTerminateGame() == false)
	{
		BEGIN_INPUT_FPS_LIMITED_HELPER(targetHelper);
		if (InputController::I()->IsEnableInput())
		{
			Input();
		}
		END_INPUT_FPS_LIMITED();

		Update();
		Render();
	}
}

void GameMainHelper::Finalize()
{
	if (GameCtx::I()->getCurrentGameState() != EGameState::TERMINATION_ABNORMALITY)
	{
		GameCtx::I()->setCurrentGameState(EGameState::FINAL);
	}

	if (SceneMgr::I()->getCurrentScene()->OnFinalize() == EErrorType::FINAL_FAIL)
	{
		DEFAULT_ERROR_HANDLER(EErrorType::FINAL_FAIL);
	}

	TriggerTimerMgr::I()->Finalize();
	InputController::I()->Finalize();
	ConsoleController::I()->Finalize();

	PerformanceProfileMgr::I()->Report();

	DEBUG_LOG("게임 마무리 처리 완료!");
}

void GameMainHelper::Input()
{
	// 입력 갱신은 콘솔창이 활성화되었을 때만! (포커스를 받고 있다는 의미)
	if (::GetConsoleWindow() != ::GetForegroundWindow())
	{
		//DEFAULT_ERROR_HANDLER(EErrorType::NO_INPUT_FOCUS);
		return;
	}

	InputController::I()->PollInput();

	if (SceneMgr::I()->getCurrentScene()->OnInput() == EErrorType::INPUT_FAIL)
	{
		DEFAULT_ERROR_HANDLER(EErrorType::INPUT_FAIL);
	}

	DebugPanelController::I()->PollInput();

	//DEBUG_LOG_CATEGORY(Common, "콘솔창이 활성화된 상태!");
}

void GameMainHelper::Update()
{
	PERFORMANCE_PROFILE_START(0);

	if (GameCtx::I()->IsTerminateGame() == false)
	{
		GameCtx::I()->setCurrentGameState(EGameState::UPDATE);
	}

	// FPS와 델타타임부터 갱신해야 해요!
	FrameController::I()->UpdateFrame();

	// 씬이 변경되는지 확인해야 해요!
	// 전환될 씬은 초기화가 완료된 상태이므로 현재 씬과 바꿔주기만 하면 돼죠!
	if (SceneMgr::I()->IsGotoNextScene())
	{
		SceneMgr::I()->Flip();
	}

	// 트리거 타이머를 업데이트해야 해요!
	TriggerTimerMgr::I()->UpdateTriggerTimer();

	if (SceneMgr::I()->getCurrentScene()->OnUpdate() == EErrorType::UPDATE_FAIL)
	{
		DEFAULT_ERROR_HANDLER(EErrorType::UPDATE_FAIL);
	}

	PERFORMANCE_PROFILE_END();
}

void GameMainHelper::Render()
{
	if (GameCtx::I()->IsTerminateGame() == false)
	{
		GameCtx::I()->setCurrentGameState(EGameState::RENDER);
	}

	ConsoleController::I()->ClearConsoleScreen(); // 콘솔 스크린 버퍼를 깨끗하게 지울게요! (Clear)

#ifndef ACTIVATION_CONSOLE_DBL_BUFFERING
	// 렌더링이 끝난 후에 콘솔 좌표를 처음으로 복구해야 해요! (Flip)
	COORD backupPos = ConsoleController::I()->GetCurrentConsolePos();
#endif

	if (SceneMgr::I()->getCurrentScene()->OnRender() == EErrorType::RENDER_FAIL)
	{
		DEFAULT_ERROR_HANDLER(EErrorType::RENDER_FAIL);
	}
	
	TriggerTimerMgr::I()->CallTriggerTimerFuncForRender();

	DebugPanelController::I()->ShowContents(0, 0);

#ifdef ACTIVATION_CONSOLE_DBL_BUFFERING	
	ConsoleController::I()->Flipping(); // 활성화시킬 버퍼를 변경할게요!
#else
	ConsoleController::I()->MoveConsolePos(backupPos); // 처음 콘솔 좌표로 이동시킬게요!
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_PHOENIX_SINGLETON(GameMain);

/*
게임의 핵심 흐름입니다.
초기화 ~ 게임 루프 ~ 마무리 순으로 진행됩니다.
*/
Int32 GameMain::Run()
{
	// 메모리 누수를 확인하는 방법이에요.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	GameMainHelper::Initialize(*this);
	GameMainHelper::GameLoop(*this);
	GameMainHelper::Finalize();

	Int32 ret = EXIT_SUCCESS;
	if (GameCtx::I()->getCurrentGameState() == EGameState::TERMINATION_ABNORMALITY)
	{
		ret = EXIT_FAILURE;
	}

	return ret;
}