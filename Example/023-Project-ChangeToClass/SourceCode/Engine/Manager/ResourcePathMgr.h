// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���ҽ� ��θ� �����մϴ�.
// ���� ������ �ִ� ������ �⺻ ����Դϴ�.
// �⺻ ��ο� �ٸ� ��θ� �����ؼ� ���ο� ��θ� ����ϴ�.
// =====================================================================================

#ifndef RESOURCE_PATH_MGR__H__
#define RESOURCE_PATH_MGR__H__

#include "Common\CommonType.h"
#include "Common\CommonMacro.h"
#include "Common\CommonNecessary.h"
#include "Element\NameTag.h"

enum class EResourcePathTypeIdx : Int32
{
	ROOT = 0,
	WORLD,
	LEVEL_DESIGN,
};

DECLARE_LOG_CATEGORY(ResourcePathMgr);

class ResourcePathMgr final
{
	DECLARE_PHOENIX_SINGLETON(ResourcePathMgr);

public:
	void Initialize();
	void AddPath(const std::string_view& szAdditionPath);
	const std::string& FindPath(EResourcePathTypeIdx resourcePathTypeIdx);

private:
	std::vector<std::string> m_vecResourcePath;
};

#endif