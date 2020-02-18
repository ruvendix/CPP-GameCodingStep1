// =====================================================================================
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
#include "Controller\InputController.h"
#include "Element\Scene\GameIntroMenu.h"

class GameMainHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(GameMainHelper);

public:
#pragma region 게임의 핵심 흐름이에요!
	static void Initialize();
	static void GameLoop();
	static void Finalize();
#pragma endregion

	static void Update();
	static void Render();
};

void GameMainHelper::Initialize()
{
	CommonFunc::ChangeTitle("Change To Class");

	ConfigCtx::I()->setResoultion(SizeInfo{ 125, 30 });
	GameCtx::I()->setCurrentGameState(EGameState::INIT);

	CommonFunc::AdjustConsoleArea(ConfigCtx::I()->getResoultion());
	CommonFunc::GameConsoleStyle();

	SceneMgr::I()->CreateScene<GameIntroMenuScene>(ESceneType::CURRENT);

	printf("게임 초기화 처리 완료!\n");
}

void GameMainHelper::GameLoop()
{
	// 정상 또는 비정상 종료일 때만 게임루프를 탈출!
	while ( (GameCtx::I()->getCurrentGameState() != EGameState::TERMINATION_ABNORMALITY) &&
		    (GameCtx::I()->getCurrentGameState() != EGameState::TERMINATION_SUCCESS) )
	{
		// 씬이 변경되는지 확인해야 해요!
		// 전환될 씬은 초기화가 완료된 상태이므로 현재 씬과 바꿔주기만 하면 돼죠!
		if (SceneMgr::I()->IsGotoNextScene())
		{
			SceneMgr::I()->FlipCurrentScene();
		}

		Update();
		Render();
	}
}

void GameMainHelper::Finalize()
{
	GameCtx::I()->setCurrentGameState(EGameState::FINAL);

	if (SceneMgr::I()->getCurrentScene()->OnFinalize() == EErrorType::FINAL_FAILED)
	{
		ErrorHandler::ShowError(EErrorType::FINAL_FAILED);
	}

	// 씬 관련 마무리
	SceneMgr::I()->DeleteScene();

	// 입력 관련 마무리
	InputController::I()->DeleteAllInputMappingInfo();

	// 싱글톤 처리
	GameCtx::Destroy();
	SceneMgr::Destroy();
	InputController::Destroy();
	ConfigCtx::Destroy();

	printf("게임 마무리 처리 완료!\n");
}

void GameMainHelper::Update()
{
	GameCtx::I()->setCurrentGameState(EGameState::UPDATE);

	// 입력 처리가 최우선!
	InputController::I()->PollInput();

	// 활성화되었을 때만 입력 체크!
	if (::GetConsoleWindow() == ::GetForegroundWindow())
	{
		//DEBUG_LOG_CATEGORY(Common, "활성화되었다!");
	}
	else
	{
		//DEBUG_LOG_CATEGORY(Common, "활성화에서 망했다!");
	}

	if (SceneMgr::I()->getCurrentScene()->OnUpdate() == EErrorType::UPDATE_FAILED)
	{
		ErrorHandler::ShowError(EErrorType::UPDATE_FAILED);
	}
}

void GameMainHelper::Render()
{
	GameCtx::I()->setCurrentGameState(EGameState::RENDER);

	// 콘솔 스크린 버퍼를 깨끗하게 지울게요! (Clear)
	CommonFunc::ClearConsoleScreen();

	// 렌더링이 끝난 후에 콘솔 좌표를 처음으로 복구해야 해요! (Flip)
	COORD backupPos = CommonFunc::GetCurrentConsolePos();

	if (SceneMgr::I()->getCurrentScene()->OnRender() == EErrorType::RENDER_FAILED)
	{
		ErrorHandler::ShowError(EErrorType::RENDER_FAILED);
	}

	// 처음 콘솔 좌표로 이동시킬게요!
	CommonFunc::MoveConsolePos(backupPos);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_SINGLETON(GameMain);

Int32 GameMain::Run()
{
	// 메모리 누수를 확인하는 방법이에요.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GameMainHelper::Initialize();
	GameMainHelper::GameLoop();
	GameMainHelper::Finalize();

	Int32 ret = EXIT_SUCCESS;
	if (GameCtx::I()->getCurrentGameState() == EGameState::TERMINATION_ABNORMALITY)
	{
		ret = EXIT_FAILURE;
	}

	return ret;
}