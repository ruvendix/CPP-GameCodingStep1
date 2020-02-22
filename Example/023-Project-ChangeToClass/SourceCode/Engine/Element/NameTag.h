// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �̸� ���� �Ǵ� ��ȯ�մϴ�.
// =====================================================================================

#ifndef NAME_TAG__H__
#define NAME_TAG__H__

#include "Common\CommonNecessary.h"

class NameTag
{
public:
#pragma region ������ �� �Ҹ���
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