// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 디버그 모드에서만 사용되는 패널입니다.
// 패널 기본형으로서 클라이언트에서는 상속 받아서 ShowContents를 구현해야 합니다.
// =====================================================================================

#ifndef DEBUG_PANEL_CONTROLLER__H__
#define DEBUG_PANEL_CONTROLLER__H__

#include "Common\CommonType.h"
#include "Common\CommonMacro.h"

class DebugPanelController
{
	DECLARE_PHOENIX_SINGLETON(DebugPanelController);

public:
	void Initialize();
	void PollInput();
	void ShowContents(Int32 x, Int32 y);

private:
	bool m_bShow = true;
};

#endif