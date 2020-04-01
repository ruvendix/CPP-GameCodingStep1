// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 리소스 경로를 관리합니다.
// 실행 파일이 있는 폴더가 기본 경로입니다.
// 기본 경로에 다른 경로를 조합해서 새로운 경로를 만듭니다.
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
