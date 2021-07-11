// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ����� ���� ���� �ڵ鷯�Դϴ�.
// ���� �ڵ鷯�� �ʱ�ȭ���� �ʾ��� �� ���˴ϴ�.
// FIND_SUBSYSTEM() ��ũ�θ� ���ؼ��� ���˴ϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "IFileHandler.h"

class IFileHandlerNull : public IFileHandler
{
public:
	virtual void SetUp() OVERRIDE_EMPTY_FUNC;
	virtual void CleanUp() OVERRIDE_EMPTY_FUNC;

	virtual Bool OpenFileStream(const std::string_view& strFilePath, EFileMode fileMode, EAccessMode accessMode, FILE** ppFile) CONST_RETURN_FUNC(true);
	virtual void CloseFileStream(FILE* pFile) CONST_OVERRIDE_EMPTY_FUNC;
};