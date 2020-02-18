// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 게임 선택, 관리 등 핵심 기능을 담당합니다.
// 인스턴스가 하나만 존재해야 하는 싱글톤입니다.
// =====================================================================================

#ifndef GAME_MAIN__H__
#define GAME_MAIN__H__

#include "Common\CommonType.h"

class GameMain final
{
    DECLARE_SINGLETON(GameMain);
    FRIEND_WITH_HELPER(GameMainHelper);

public:
    Int32 Run();
};

#endif