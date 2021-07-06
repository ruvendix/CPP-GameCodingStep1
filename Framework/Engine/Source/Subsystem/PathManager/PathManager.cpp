// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� �������� �������̽��Դϴ�.
// =====================================================================================
#include "EnginePCH.h"
#include "PathManager.h"

#include "../../FrameworkPathfinder.h"

/*
	�����ӿ�ũ�� Ŭ���̾�Ʈ�� ������ �� ����θ� �����մϴ�.
*/
void PathManager::SetUp()
{
	m_pFrameworkPathFinder = new FrameworkPathfinder;
	m_pFrameworkPathFinder->SetUp();

	Char buffer[MAX_PATH];
	::GetModuleFileName(nullptr, buffer, MAX_PATH);
	m_strClientAbsolutePath.assign(buffer);

	Uint32 clientRelativePathStartPos = m_strClientAbsolutePath.rfind('\\');
	clientRelativePathStartPos += 1; // '\\' ����!

	m_strClientRelativePath = m_strClientAbsolutePath.substr(0, clientRelativePathStartPos);
}

/*
	������ FrameworkPathFinder�� �����մϴ�.
*/
void PathManager::CleanUp()
{
	SAFE_DELETE(m_pFrameworkPathFinder);
}

/*
	�����ӿ�ũ�� �����θ� �����ɴϴ�.
*/
const std::string& PathManager::FrameworkAbsolutePath() const
{
	return m_pFrameworkPathFinder->GetAbsolutePath();
}

/*
	�����ӿ�ũ�� ����θ� �����ɴϴ�.
*/
const std::string& PathManager::FrameworkRelativePath() const
{
	return m_pFrameworkPathFinder->GetRelativePath();
}

/*
	�����ӿ�ũ�� ����� ���� ��ġ�� �����ɴϴ�.
*/
Uint32 PathManager::FrameworkRelativePathStartPos() const
{
	return m_pFrameworkPathFinder->GetRelativePathStartPos();
}

/*
	��ο��� Ȯ���ڸ� �����մϴ�.
*/
const Char* PathManager::ExtractExtension(const std::string_view& strFilePath) const
{
	Uint32 extensionStartPos = strFilePath.rfind('.');
	RX_ASSERT(extensionStartPos != std::string::npos);
	extensionStartPos += 1; // '.' ����!
	return (strFilePath.data() + extensionStartPos);
}