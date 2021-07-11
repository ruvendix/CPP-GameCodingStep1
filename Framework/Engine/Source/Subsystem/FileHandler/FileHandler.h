// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �ڵ鷯�Դϴ�.
// �ܺο��� ���� ������ ���ų� �ݴ� ����� �ֽ��ϴ�.
// =====================================================================================
#pragma once

#include "Base/IFileHandler.h"

class FileHandler : public IFileHandler
{
	ONLY_SUBSYSTEM(FileHandler);

public:
	virtual void SetUp();
	virtual void CleanUp();

	virtual Bool OpenFileStream(const std::string_view& strFilePath,
		EFileMode fileMode, EAccessMode accessMode, OUT FILE** ppFile) const override;

	virtual void CloseFileStream(FILE* pFile) const override;
};