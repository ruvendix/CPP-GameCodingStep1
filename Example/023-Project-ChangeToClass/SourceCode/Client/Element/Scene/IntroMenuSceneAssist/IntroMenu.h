// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʈ�� �޴� ������ ���Ǵ� ���� Ŭ������ �⺻���Դϴ�.
// ���� Ŭ������ "�⺻��_������" �̷� ������ �̸��� �����ϴ�.
// =====================================================================================

#ifndef INTRO_MENU_H__
#define INTRO_MENU_H__

#include "Common\CommonMacro.h"
#include "Handler\ErrorHandler\ErrorType.h"
#include "Element\NameTag.h"

// ��Ʈ�� �޴� ������ ���Ǵ� ���� Ŭ��������!
class IntroMenu
{
	HAS_NAME_TAG();

public:
#pragma region ������ �� �Ҹ���
	IntroMenu() = default;
	virtual ~IntroMenu() = default;

	IntroMenu(const std::string_view& szNameTag, const COORD& offsetCenterPos);
#pragma endregion

	virtual EErrorType OnExcute();

	// ���߿� ��ǥ Ŭ���� ����� �װɷ� ������ ����!
	const COORD& getPos() const
	{
		return m_pos;
	}

	void setPos(const COORD& pos)
	{
		m_pos = pos;
	}

	const COORD& getOffsetCenterPos() const
	{
		return m_offsetCenterPos;
	}

	void setOffsetCenterPos(Int32 x, Int32 y)
	{
		m_offsetCenterPos.X = x;
		m_offsetCenterPos.Y = y;
	}

private:
	COORD m_pos; // �޴��� �׷��� ��ġ (���� �� ����)
	COORD m_offsetCenterPos; // �߾� ������ ���� ������ (��� ���δ� ����)
};

#endif