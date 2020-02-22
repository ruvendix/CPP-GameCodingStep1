// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 이름 설정 또는 반환합니다.
// =====================================================================================

#ifndef NAME_TAG__H__
#define NAME_TAG__H__

#include "Common\CommonNecessary.h"

class NameTag
{
public:
#pragma region 생성자 및 소멸자
	NameTag() = default;
	virtual ~NameTag() = default;

	NameTag(const std::string_view& szNameTag) :
		m_strNameTag(szNameTag)
	{

	}
#pragma endregion

	const std::string& getNameTag() const
	{
		return m_strNameTag;
	}

	void setNameTag(const std::string_view& szName)
	{
		m_strNameTag = szName;
	}

private:
	std::string m_strNameTag;
};

#endif