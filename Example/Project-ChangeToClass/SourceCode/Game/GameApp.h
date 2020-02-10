// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#ifndef GAME_APP__H__
#define GAME_APP__H__

#include "GlobalEnum.h"

/*
    인스턴스는 단 하나만 존재해야 해요!
    게임 선택, 관리 등 핵심 기능을 담당합니다.
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