// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 인트로 메뉴 씬에서 사용되는 보조 클래스의 기본형입니다.
// 보조 클래스는 "기본형_보조형" 이런 형식의 이름을 갖습니다.
// =====================================================================================

#ifndef INTRO_MENU_H__
#define INTRO_MENU_H__

#include "Common\CommonMacro.h"
#include "Handler\ErrorHandler\ErrorType.h"
#include "Element\NameTag.h"

// 인트로 메뉴 씬에서 사용되는 보조 클래스에요!
class IntroMenu
{
	HAS_NAME_TAG();

public:
#pragma region 생성자 및 소멸자
	IntroMenu() = default;
	virtual ~IntroMenu() = default;

	IntroMenu(const std::string_view& szNameTag, const COORD& offsetCenterPos);
#pragma endregion

	virtual EErrorType OnExcute();

	// 나중에 좌표 클래스 만들면 그걸로 적용할 예정!
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
	COORD m_pos; // 메뉴가 그려질 위치 (왼쪽 위 기준)
	COORD m_offsetCenterPos; // 중앙 정렬일 때의 오프셋 (사용 여부는 자유)
};

#endif