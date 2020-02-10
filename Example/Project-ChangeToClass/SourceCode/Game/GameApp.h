// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#ifndef GAME_APP__H__
#define GAME_APP__H__

#include "GlobalEnum.h"

/*
    �ν��Ͻ��� �� �ϳ��� �����ؾ� �ؿ�!
    ���� ����, ���� �� �ٽ� ����� ����մϴ�.
*/
class GameApp
{
    NON_COPYABLE_CLASS(GameApp);
    ONLY_PRIVATE_CLASS(GameApp);

public:
    static GameApp* I();
    static void Destroy();

    EGameState RunGameLoop();
    void DrawMainScene();
    
private:
    static GameApp* m_pInst;
    EGameState m_currentGameState = EGameState::NONE;
};

#endif