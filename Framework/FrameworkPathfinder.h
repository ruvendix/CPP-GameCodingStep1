// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Framework ���� ��θ� �˾Ƴ��� �뵵�Դϴ�.
// __FILE__ ��ũ�ο� �������ֽ��ϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "Common/CommonType.h"

class FrameworkPathfinder final
{
public:
	static void SetUp()
	{
		m_strPath = __FILE__;
		m_folderPathLength = m_strPath.rfind('\\');
		m_folderPathLength += 1; // '\\' ����!
	}

	static const std::string& GetPath()
	{
		return m_strPath;
	}

	static Uint32 GetFolderPathLength()
	{
		return m_folderPathLength;
	}

private:
	FrameworkPathfinder() = default;
	~FrameworkPathfinder() = default;

	static std::string m_strPath;
	static Uint32 m_folderPathLength;
};