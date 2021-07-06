// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� �������� �������̽��Դϴ�.
// =====================================================================================
#pragma once

#include "IPathManager.h"

// ���� ����
class FrameworkPathfinder;

class PathManager final : public IPathManager
{
	ONLY_SUBSYSTEM(PathManager);

public:
	virtual void SetUp();
	virtual void CleanUp();

	virtual const std::string& FrameworkAbsolutePath() const override;
	virtual const std::string& FrameworkRelativePath() const override;
	virtual Uint32 FrameworkRelativePathStartPos() const override;

	virtual const std::string& ClientAbsolutePath() const override { return m_strClientAbsolutePath; }
	virtual const std::string& ClientRelativePath() const override { return m_strClientRelativePath; };
	virtual Uint32 ClientRelativePathStartPos() const override { return m_strClientRelativePath.length(); };

	virtual const Char* ExtractExtension(const std::string_view& strFilePath) const override;

private:
	// ���ο����� ����ϴ� �����ʹ� ���� Ŭ������ �̿������� FrameworkPathfinder�� �����Դϴ�.
	// FrameworkPathfinder�� �ܺο��� ���� �� �Ҹ��� �������� friend�� �̿��ϴµ�
	// friend�� �ܺ� Ŭ�������� ����ϴ� �� �������� ���ƿ�.
	// ����� �ܺο��� ���� �� �Ҹ��� ���������� ����Ʈ �����͸� ����ϱⰡ �ſ� ��ٷο����ϴ�.
	// �׷��� ����Ʈ �����͸� �����ϰ� �Ϲ� �����͸� ����ϴ� �� ��õ�ҰԿ�.
	FrameworkPathfinder* m_pFrameworkPathFinder = nullptr;

	// ���ο����� ����ϴ� ���������� ���� ������ �ϰ� ������� �ʴ� �������̹Ƿ� ���� Ŭ������ ���� �����Կ�.
	std::string m_strClientAbsolutePath;
	std::string m_strClientRelativePath;
};