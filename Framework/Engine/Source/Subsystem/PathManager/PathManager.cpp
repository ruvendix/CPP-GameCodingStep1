// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� �Ŵ����� �������̽��Դϴ�.
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
	clientRelativePathStartPos += 1; // '\\' ����!

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
	extensionPos += 1; // '.' ����!
	return (strFilePath.data() + extensionPos);
}