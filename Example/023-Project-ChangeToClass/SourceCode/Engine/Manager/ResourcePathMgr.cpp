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

#include "PCH.h"
#include "ResourcePathMgr.h"

DEFINE_LOG_CATEGORY(ResourcePathMgr);
DEFINE_PHOENIX_SINGLETON(ResourcePathMgr)

void ResourcePathMgr::Initialize()
{
	char rootPath[MAX_PATH];
	::GetModuleFileName(nullptr, rootPath, _countof(rootPath));

	std::string strRootPath = rootPath;
	strRootPath = strRootPath.substr(0, strRootPath.rfind("\\") + 1);
	m_vecResourcePath.push_back(strRootPath);

	AddPath("World\\");
	AddPath("LevelDesign\\");
}

void ResourcePathMgr::AddPath(const std::string_view& szAdditionPath)
{
	std::string strFullPath = FindPath(EResourcePathTypeIdx::ROOT);
	if (strFullPath.empty() == true)
	{
		DEFAULT_ERROR_HANDLER(EErrorType::NO_ROOT_PATH);
		return;
	}

	strFullPath += szAdditionPath;
	m_vecResourcePath.push_back(strFullPath);
	
	return;
}

const std::string& ResourcePathMgr::FindPath(EResourcePathTypeIdx resourcePathTypeIdx)
{
	Int32 resourcePathIdx = CommonFunc::ToUnderlyingType(resourcePathTypeIdx);
	CHECK_RANGE(resourcePathIdx, 0, static_cast<Int32>(m_vecResourcePath.size()));

	const std::string& strResourcePath = m_vecResourcePath.at(resourcePathIdx);
	if (strResourcePath.empty() == true)
	{
		DEFAULT_ERROR_HANDLER(EErrorType::NO_RESOURCE_PATH, strResourcePath.c_str());
	}

	return strResourcePath;
}
