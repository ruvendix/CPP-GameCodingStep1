// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �⺻ �޴��Դϴ�.
// �ش� Ŭ������ ��� �޾Ƽ� ���� �޴��� ������ �� �ֽ��ϴ�.
// =====================================================================================

#include "PCH.h"
#include "Menu.h"

Menu::Menu(const std::string_view& szNameTag) :
	m_nameTag(szNameTag),
	m_pos{ 0, 0 },
	m_offsetCenterPos{ 0, 0 }
{
	m_sizeInfo.width = szNameTag.size();
	m_sizeInfo.height = 0; // ���̸� ���� �ʴ´ٴ� �ǹ�
}

Menu::Menu(const std::string_view& szNameTag, const COORD& pos) :
	Menu::Menu(szNameTag)	
{
	m_pos = pos;
}

Menu::Menu(const std::string_view& szNameTag, const COORD& pos, const COORD& offsetCenterPos) :
	Menu::Menu(szNameTag, pos)
{
	m_offsetCenterPos = offsetCenterPos;
}

EErrorType Menu::OnExcute()
{
	//DEBUG_LOG("Menu���� �̰� ���̸� OnExcute()�� ���������ּ���!");
	return EErrorType::NONE;
}

void Menu::OnTrigger_ExcuteMenu()
{

}
