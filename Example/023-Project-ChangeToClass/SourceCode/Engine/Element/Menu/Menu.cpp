// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 기본 메뉴입니다.
// 해당 클래스를 상속 받아서 여러 메뉴를 구현할 수 있습니다.
// =====================================================================================

#include "PCH.h"
#include "Menu.h"

Menu::Menu(const std::string_view& szNameTag) :
	m_nameTag(szNameTag),
	m_pos{ 0, 0 },
	m_offsetCenterPos{ 0, 0 }
{
	m_sizeInfo.width = szNameTag.size();
	m_sizeInfo.height = 0; // 높이를 쓰지 않는다는 의미
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
	//DEBUG_LOG("Menu에서 이게 보이면 OnExcute()를 재정의해주세요!");
	return EErrorType::NONE;
}

void Menu::OnTrigger_ExcuteMenu()
{

}
