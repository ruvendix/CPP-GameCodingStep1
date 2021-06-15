// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� �Ŵ����� �������̽��Դϴ�.
// =====================================================================================
#pragma once

#include "Subsystem/ISubsytem.h"

class IPathManager : public ISubsystem
{
	GENERATE_SUBSYSTEM_TYPE(ESubsystemType::PATH_MANAGER);

public:
	IPathManager() = default;
	virtual ~IPathManager() = default;

	virtual const std::string& FrameworkAbsolutePath() const PURE_FUNC;
	virtual const Uint32 FrameworkRelativePathStartPos() const PURE_FUNC;

	virtual const std::string& ClientAbsolutePath() const PURE_FUNC;

	virtual const Char* ExtractExtension(const std::string_view& strFilePath) const PURE_FUNC;
};