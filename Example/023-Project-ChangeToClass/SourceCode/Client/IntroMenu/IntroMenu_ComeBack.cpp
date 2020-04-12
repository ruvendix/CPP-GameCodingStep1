// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 인트로 메뉴 씬으로 돌아오게 해줍니다.
// 여러 게임에서 사용 가능합니다.
// =====================================================================================

#include "PCH.h"
#include "IntroMenu_ComeBack.h"

#include "Manager\SceneManager.h"
#include "Scene\IntroMenuScene.h"

EErrorType IntroMenu_ComeBack::OnExcute()
{
	SceneMgr::I()->CreateScene<IntroMenuScene>(ECreateType::NEXT);
	return EErrorType::NOTHING;
}