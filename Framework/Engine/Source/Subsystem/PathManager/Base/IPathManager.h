// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� �������� �������̽��Դϴ�.
// =====================================================================================
#pragma once

#include "Subsystem/ISubsytem.h"

class IPathManager : public ISubsystem
{
	GENERATE_SUBSYSTEM(ESubsystemType::PATH_MANAGER);

public:
	IPathManager() = default;
	virtual ~IPathManager() = default;

	virtual const std::string& FrameworkAbsolutePath() CONST_PURE_FUNC;
	virtual const std::string& FrameworkRelativePath() CONST_PURE_FUNC;
	virtual Uint32 FrameworkRelativePathStartPos() CONST_PURE_FUNC;

	virtual const std::string& ClientAbsolutePath() CONST_PURE_FUNC;
	virtual const std::string& ClientRelativePath() CONST_PURE_FUNC;
	virtual Uint32 ClientRelativePathStartPos() CONST_PURE_FUNC;

	virtual const Char* ExtractExtension(const std::string_view& strFilePath) CONST_PURE_FUNC;
};