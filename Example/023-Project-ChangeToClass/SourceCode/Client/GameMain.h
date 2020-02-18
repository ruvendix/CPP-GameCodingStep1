// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ����, ���� �� �ٽ� ����� ����մϴ�.
// �ν��Ͻ��� �ϳ��� �����ؾ� �ϴ� �̱����Դϴ�.
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