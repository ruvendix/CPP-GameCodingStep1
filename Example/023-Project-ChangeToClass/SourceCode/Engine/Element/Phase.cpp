// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �⺻ �������Դϴ�.
// ����� ��ó�� ���� ��ȯ�ؾ� �մϴ�.
// �Ｎ���� ��ȯ�ϸ� ���� ������� ���װ� �߻��մϴ�.
// =====================================================================================

#include "PCH.h"
#include "Phase.h"

Phase::Phase(const std::string_view& szNameTag, Int32 level) :
	GameElem(szNameTag),
	m_level(level)
{

}
