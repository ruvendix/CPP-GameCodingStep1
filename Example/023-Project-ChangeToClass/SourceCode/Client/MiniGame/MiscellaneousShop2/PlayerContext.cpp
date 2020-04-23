// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �÷��̾��� ���� �����Դϴ�.
// ������ �κ��丮�� �����ݸ� �ֽ��ϴ�.
// =====================================================================================

#include "PCH.h"
#include "PlayerContext.h"

#include "Inven.h"
#include "Item\ItemDBContext.h"

DEFINE_PHOENIX_SINGLETON(PlayerCtx);

void PlayerCtx::Initialize()
{
	m_spInven = std::make_shared<Inven>();

	// �κ��� ������ �ְ� �׽�Ʈ
	m_spInven->AddInvenItemInfo(ItemDBCtx::I()->FindItem("������ġ��"));
	m_spInven->AddInvenItemInfo(ItemDBCtx::I()->FindItem("������ġ��"));
	m_spInven->AddInvenItemInfo(ItemDBCtx::I()->FindItem("Ư�� ȸ����"));
}