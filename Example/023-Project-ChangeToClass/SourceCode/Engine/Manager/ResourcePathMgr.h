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