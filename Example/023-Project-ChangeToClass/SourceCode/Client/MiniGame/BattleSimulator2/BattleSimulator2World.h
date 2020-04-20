// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2에서 사용하는 월드입니다.
// 월드 에디터는 지원하지 않고 레벨 디자인 에디터만 지원합니다.
// =====================================================================================

#ifndef BATTLE_SIMULATOR2_WORLD__H__
#define BATTLE_SIMULATOR2_WORLD__H__

#include "Element\World.h"

class BattleSimulator2World final : public World
{
	DECLARE_RTTI(BattleSimulator2World, World);

public:
#pragma region 생성자 및 소멸자
	using World::World;
	virtual ~BattleSimulator2World() = default;
#pragma endregion

	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnLoadFile(FILE* pFileStream) override;
};

#endif