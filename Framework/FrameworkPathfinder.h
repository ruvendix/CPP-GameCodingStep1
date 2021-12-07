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
	void StartUp();

	const std::string& GetAbsolutePath() const { return m_strAbsolutePath; }
	const std::string& GetRelativePath() const { return m_strRelativePath; }

	UINT32 GetRelativePathStartPos() const { return m_strRelativePath.length(); }

private:
	friend class PathManager;

	FrameworkPathfinder() = default;
	~FrameworkPathfinder() = default;

	std::string m_strAbsolutePath;
	std::string m_strRelativePath;
};