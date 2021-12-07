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

Actor::Actor()
{
	m_vecComponent.reserve(DEFAULT_COMPONENT_COUNT);
}

Actor::Actor(const std::string& strName) : Actor()
{
	m_strName = strName;
}

void Actor::Update()
{

}