// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �⺻ �޴��Դϴ�.
// �ش� Ŭ������ ��� �޾Ƽ� ���� �޴��� ������ �� �ֽ��ϴ�.
// =====================================================================================

#ifndef MENU_H__
#define MENU_H__

#include "Common\CommonMacro.h"
#include "Handler\ErrorHandler\ErrorType.h"
#include "Element\NameTag.h"

class Menu
{
	DECLARE_ROOT_RTTI(Menu);
	HAS_NAME_TAG();

public:
#pragma region ������ �� �Ҹ���
	Menu() = default;
	virtual ~Menu() = default;

	Menu(const std::string_view& szNameTag);
	Menu(const std::string_view& szNameTag, const COORD& pos);
	Menu(const std::string_view& szNameTag, const COORD& pos, const COORD& offsetCenterPos);
#pragma endregion

	virtual EErrorType OnExcute();
	virtual void OnTrigger_Excute(); // Ʈ���� Ÿ�̸Ӹ� ����� ��!

	void AddPos(const COORD& pos)
	{
		m_pos.X += pos.X;
		m_pos.Y += pos.Y;
	}

	const SizeInfo& getSizeInfo() const
	{
		return m_sizeInfo;
	}

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

private:
	SizeInfo m_sizeInfo; // �޴� ������ ũ��
	COORD m_pos; // �޴��� �׷��� ��ġ (���� �� ����)
	COORD m_offsetCenterPos; // �߾� ������ ���� ������ (��� ���δ� ����)
};

#endif