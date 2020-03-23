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
	m_pInven = trace_new Inven;

	// �κ��� ������ �ְ� �׽�Ʈ
	m_pInven->AddInvenItemInfo(ItemDBCtx::I()->QueryItem("������ġ��"));
	m_pInven->AddInvenItemInfo(ItemDBCtx::I()->QueryItem("������ġ��"));
	m_pInven->AddInvenItemInfo(ItemDBCtx::I()->QueryItem("Ư�� ȸ����"));
}

void PlayerCtx::Finalize()
{
	SAFE_DELETE(m_pInven);
}