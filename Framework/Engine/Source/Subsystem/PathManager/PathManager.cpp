// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 경로 관리자의 인터페이스입니다.
// =====================================================================================
#include "EnginePCH.h"
#include "PathManager.h"

#include "../../FrameworkPathfinder.h"

/*
	프레임워크와 클라이언트의 절대경로 및 상대경로를 설정합니다.
*/
void PathManager::SetUp()
{
	m_pFrameworkPathFinder = new FrameworkPathfinder;
	m_pFrameworkPathFinder->SetUp();

	Char buffer[MAX_PATH];
	::GetModuleFileName(nullptr, buffer, MAX_PATH);
	m_strClientAbsolutePath.assign(buffer);

	Uint32 clientRelativePathStartPos = m_strClientAbsolutePath.rfind('\\');
	clientRelativePathStartPos += 1; // '\\' 포함!

	m_strClientRelativePath = m_strClientAbsolutePath.substr(0, clientRelativePathStartPos);
}

/*
	생성한 FrameworkPathFinder를 해제합니다.
*/
void PathManager::CleanUp()
{
	SAFE_DELETE(m_pFrameworkPathFinder);
}

/*
	프레임워크의 절대경로를 가져옵니다.
*/
const std::string& PathManager::FrameworkAbsolutePath() const
{
	return m_pFrameworkPathFinder->GetAbsolutePath();
}

/*
	프레임워크의 상대경로를 가져옵니다.
*/
const std::string& PathManager::FrameworkRelativePath() const
{
	return m_pFrameworkPathFinder->GetRelativePath();
}

/*
	프레임워크의 상대경로 시작 위치를 가져옵니다.
*/
Uint32 PathManager::FrameworkRelativePathStartPos() const
{
	return m_pFrameworkPathFinder->GetRelativePathStartPos();
}

/*
	경로에서 확장자를 추출합니다.
*/
const Char* PathManager::ExtractExtension(const std::string_view& strFilePath) const
{
	Uint32 extensionStartPos = strFilePath.rfind('.');
	RX_ASSERT(extensionStartPos != std::string::npos);
	extensionStartPos += 1; // '.' 포함!
	return (strFilePath.data() + extensionStartPos);
}