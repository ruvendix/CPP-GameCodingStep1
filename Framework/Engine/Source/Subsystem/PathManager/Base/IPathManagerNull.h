// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ����� ���� ��� �������Դϴ�.
// ��� �����ڰ� �ʱ�ȭ���� �ʾ��� �� ���˴ϴ�.
// FIND_SUBSYSTEM() ��ũ�θ� ���ؼ��� ���˴ϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "IPathManager.h"

class IPathManagerNull : public IPathManager
{
public:
	virtual void StartUp() OVERRIDE_EMPTY_FUNC;
	virtual void CleanUp() OVERRIDE_EMPTY_FUNC;

	virtual const std::string& FrameworkAbsolutePath() CONST_OVERRIDE_RETURN_FUNC(m_str);
	virtual const std::string& FrameworkRelativePath() CONST_OVERRIDE_RETURN_FUNC(m_str);
	virtual Uint32 FrameworkRelativePathStartPos() CONST_OVERRIDE_RETURN_FUNC(0);

	virtual const std::string& ClientAbsolutePath() CONST_OVERRIDE_RETURN_FUNC(m_str);
	virtual const std::string& ClientRelativePath() CONST_OVERRIDE_RETURN_FUNC(m_str);
	virtual Uint32 ClientRelativePathStartPos() CONST_OVERRIDE_RETURN_FUNC(0);

	virtual const Char* ExtractExtension(const std::string_view& strFilePath) CONST_OVERRIDE_RETURN_FUNC("");

private:
	std::string m_str;
};