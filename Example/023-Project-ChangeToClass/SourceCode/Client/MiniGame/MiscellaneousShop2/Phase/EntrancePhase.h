// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 입장 페이즈입니다.
// 입장 페이즈에서는 다른 페이즈를 선택할 수 있습니다.
// =====================================================================================

#ifndef ENTRANCE_PHASE_H__
#define ENTRANCE_PHASE_H__

#include "Element\Phase.h"
#include "Element\Menu\MenuTable_Matrix.h"

class EntrancePhase : public Phase
{
	FRIEND_WITH_HELPER(EntrancePhaseHelper);

public:
#pragma region 생성자 및 소멸자
	using Phase::Phase;
	virtual ~EntrancePhase() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnRender() override;

private:
	std::shared_ptr<MenuTable_Mat> m_spMenuTable;
};

#endif