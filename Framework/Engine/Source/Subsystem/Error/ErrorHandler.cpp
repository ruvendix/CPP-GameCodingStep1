// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �������� �߻��� ������ �ش�Ǵ� ������ �˷��ݴϴ�.
// ������ �߻����ڸ��� ���� �ڵ鷯�� �۵��˴ϴ�.
// =====================================================================================
#include "EnginePCH.h"
#include "ErrorHandler.h"

/*
	���� �ڵ鷯�� �ʱ�ȭ�մϴ�.
	���� Ÿ�Կ� �ش�Ǵ� ���� ������ �����ؿ�.
*/
void ErrorHandler::SetUp()
{
	m_mapError.insert(std::make_pair(EErrorType::INDIRECT_NULLPTR, "nullptr ������ ����!"));

	
}

/*
	���� �ڵ鷯�� �����մϴ�.
	������ �߰��� ������ �����.
*/
void ErrorHandler::CleanUp()
{
	
}

/*
	�������� �߻��� ������ �ش�Ǵ� ������ �����ɴϴ�.
*/
void ErrorHandler::FindErrorContent(OUT std::string& strError)
{
	const auto& iter = m_mapError.find(m_lastError);
	if (iter != m_mapError.cend())
	{
		strError = iter->second;
	}
}

/*
	�������� �߻��� ������ ����մϴ�.
*/
void ErrorHandler::SetLastError(EErrorType error)
{
	m_lastError = error;
}