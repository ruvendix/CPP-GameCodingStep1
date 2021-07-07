// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������Ʈ�� ���� �� �ִ� �⺻ �����Դϴ�.
// �⺻ ���͸� ��ӹ޾Ƽ� Update()�� ������ �� �ֽ��ϴ�.
// =====================================================================================
#include "EnginePCH.h"
#include "Actor.h"

void Actor::Update()
{
	UpdateComponent();
	UpdateActor();
}

void Actor::UpdateComponent()
{
	RX_INFO("UpdateComponent!");
}

void Actor::UpdateActor()
{
	RX_INFO("UpdateActor!");
}