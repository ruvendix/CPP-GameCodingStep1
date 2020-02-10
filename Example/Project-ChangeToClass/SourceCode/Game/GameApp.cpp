// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
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

// �̰ź��� �۾��ϱ�!
void GameApp::DrawMainScene()
{
	printf("������!\n");
}
