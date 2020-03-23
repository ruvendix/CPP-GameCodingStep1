// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 플레이어의 정보 모음입니다.
// 지금은 인벤토리와 소지금만 있습니다.
// =====================================================================================

#include "PCH.h"
#include "PlayerContext.h"

#include "Inven.h"
#include "Item\ItemDBContext.h"

DEFINE_PHOENIX_SINGLETON(PlayerCtx);

void PlayerCtx::Initialize()
{
	m_pInven = trace_new Inven;

	// 인벤에 아이템 넣고 테스트
	m_pInven->AddInvenItemInfo(ItemDBCtx::I()->QueryItem("만병통치약"));
	m_pInven->AddInvenItemInfo(ItemDBCtx::I()->QueryItem("만병통치약"));
	m_pInven->AddInvenItemInfo(ItemDBCtx::I()->QueryItem("특제 회복약"));
}

void PlayerCtx::Finalize()
{
	SAFE_DELETE(m_pInven);
}