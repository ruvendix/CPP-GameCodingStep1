// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �ڵ鷯�� �������̽��Դϴ�.
// =====================================================================================
#pragma once

#include "Subsystem/ISubsytem.h"
#include "FileEnum.h"

class IFileHandler : public ISubsystem
{
	GENERATE_SUBSYSTEM(ESubsystemType::FILE_HANDLER);

public:
	IFileHandler() = default;
	virtual ~IFileHandler() = default;

	virtual Bool OpenFileStream(const std::string_view& strFilePath,
		EFileMode fileMode, EAccessMode accessMode, OUT FILE** ppFile) CONST_PURE_FUNC;

	virtual void CloseFileStream(FILE* pFile) CONST_PURE_FUNC;
};