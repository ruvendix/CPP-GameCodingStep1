// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 기본 메뉴입니다.
// 해당 클래스를 상속 받아서 여러 메뉴를 구현할 수 있습니다.
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
#pragma region 생성자 및 소멸자
	Menu() = default;
	virtual ~Menu() = default;

	Menu(const std::string_view& szNameTag);
	Menu(const std::string_view& szNameTag, const COORD& pos);
	Menu(const std::string_view& szNameTag, const COORD& pos, const COORD& offsetCenterPos);
#pragma endregion

	virtual EErrorType OnExcute();
	virtual void OnTrigger_Excute(); // 트리거 타이머를 사용할 때!

	void AddPos(const COORD& pos)
	{
		m_pos.X += pos.X;
		m_pos.Y += pos.Y;
	}

	const SizeInfo& getSizeInfo() const
	{
		return m_sizeInfo;
	}

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

private:
	SizeInfo m_sizeInfo; // 메뉴 영역의 크기
	COORD m_pos; // 메뉴가 그려질 위치 (왼쪽 위 기준)
	COORD m_offsetCenterPos; // 중앙 정렬일 때의 오프셋 (사용 여부는 자유)
};

#endif