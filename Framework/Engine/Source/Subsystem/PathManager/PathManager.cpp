// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 경로 매니저의 인터페이스입니다.
// =====================================================================================
#include "EnginePCH.h"
#include "PathManager.h"

#include "../../FrameworkPathfinder.h"

void PathManager::SetUp()
{
	m_pFrameworkPathFinder = new FrameworkPathfinder;
	m_pFrameworkPathFinder->SetUp();

	Char buffer[MAX_PATH];
	::GetModuleFileName(nullptr, buffer, MAX_PATH);
	m_strClientAbsolutePath.assign(buffer);

	Uint32 clientRelativePathStartPos = m_strClientAbsolutePath.rfind('\\');
	clientRelativePathStartPos += 1; // '\\' 포함!

	m_strClientAbsolutePath = m_strClientAbsolutePath.substr(0, clientRelativePathStartPos);
}

void PathManager::CleanUp()
{
	SAFE_DELETE(m_pFrameworkPathFinder);
}

const std::string& PathManager::FrameworkAbsolutePath() const
{
	return m_pFrameworkPathFinder->GetAbsolutePath();
}

const Uint32 PathManager::FrameworkRelativePathStartPos() const
{
	return m_pFrameworkPathFinder->GetRelativePathStartPos();
}

const std::string& PathManager::ClientAbsolutePath() const
{
	return m_strClientAbsolutePath;
}

const Char* PathManager::ExtractExtension(const std::string_view& strFilePath) const
{
	Uint32 extensionPos = strFilePath.rfind('.');
	extensionPos += 1; // '.' 포함!
	return (strFilePath.data() + extensionPos);
}