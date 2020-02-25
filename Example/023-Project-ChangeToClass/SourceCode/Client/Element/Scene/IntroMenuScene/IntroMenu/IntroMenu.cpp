// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʈ�� �޴� ������ ���Ǵ� ���� Ŭ������ �⺻���Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "IntroMenu.h"

IntroMenu::IntroMenu(const std::string_view& szNameTag, const COORD& offsetCenterPos) :
	m_nameTag(szNameTag),
	m_pos{ 0, 0 },
	m_offsetCenterPos(offsetCenterPos)
{

}

EErrorType IntroMenu::OnExcute()
{
	DEBUG_LOG("IntroMenu���� �̰� ���̸� OnExcute()�� ���������ּ���!");
	return EErrorType::NONE;
}
