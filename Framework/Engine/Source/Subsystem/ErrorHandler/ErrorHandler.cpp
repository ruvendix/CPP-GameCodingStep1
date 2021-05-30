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
	m_mapError.emplace(EErrorCode::UNKNOWN, "�� �� ���� ����!");
	m_mapError.emplace(EErrorCode::INDIRECT_NULLPTR, "nullptr ������!");
	m_mapError.emplace(EErrorCode::FAILED_CLEAR_SCREEN, "ȭ�� ����� ����!");
	m_mapError.emplace(EErrorCode::INVALID_SCREEN_COLOR, "��ȿ���� ���� ȭ�� ����!");
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
const Char* ErrorHandler::FindErrorContent(EErrorCode errorCode) const
{
	const auto& iter = m_mapError.find(m_lastError);
	if (iter == m_mapError.cend())
	{
		return "";
	}

	return iter->second.c_str();
}