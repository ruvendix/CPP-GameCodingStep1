// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include "PCH.h"
#include "GameApp.h"

GameApp* GameApp::m_pInst = nullptr;

GameApp* GameApp::I()
{
	if (m_pInst != nullptr)
	{
		return m_pInst;
	}

	m_pInst = new GameApp;

	return m_pInst;
}

void GameApp::Destroy()
{
	SAFE_DELETE(m_pInst);
}

EGameState GameApp::RunGameLoop()
{
	while (m_currentGameState != EGameState::EXIT)
	{
		DrawMainScene();
	}

	return m_currentGameState;
}

// 이거부터 작업하기!
void GameApp::DrawMainScene()
{
	printf("하하핫!\n");
}
