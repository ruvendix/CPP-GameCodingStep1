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

#ifndef PHASE_H__
#define PHASE_H__

#include "Element\GameElement.h"

class Phase : public GameElem
{
	DECLARE_RTTI(Phase, GameElem);

public:
#pragma region ������ �� �Ҹ���
	Phase() = default;
	virtual ~Phase() = default;

	Phase(const std::string_view& szNameTag, Int32 level);
#pragma endregion

	Int32 getLevel() const
	{
		return m_level;
	}

private:
	Int32 m_level = 0;
};

#endif