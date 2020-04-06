// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터에서 사용하는 레벨 디자인입니다.
// 에디터로 편집한 결과를 저장하거나 불러올 수 있습니다.
// =====================================================================================

#ifndef BATTLE_SIMULATOR_LEVEL_DESIGN__H__
#define BATTLE_SIMULATOR_LEVEL_DESIGN__H__

#include "Element\LevelDesign.h"

class BattleSimulator2_LevelDesign : public LevelDesign
{
public:
#pragma region 생성자 및 소멸자
	using LevelDesign::LevelDesign;
	virtual ~BattleSimulator2_LevelDesign() = default;
#pragma endregion

	virtual EErrorType OnSaveFile(FILE* pFileStream) override;
	virtual EErrorType OnLoadFile(FILE* pFileStream) override;
};

#endif