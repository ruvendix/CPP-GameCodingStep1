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

class ErrorHandlerInside
{
public:
	ErrorHandlerInside() = default;
	~ErrorHandlerInside() = default;

	void SetUp();
	const Char* FindErrorString(EErrorCode errorCode);

private:
	std::unordered_map<EErrorCode, std::string> m_mapErrorString;
};

void ErrorHandlerInside::SetUp()
{
	m_mapErrorString.emplace(EErrorCode::UNKNOWN, "�� �� ���� ����!");
	m_mapErrorString.emplace(EErrorCode::INDIRECT_NULLPTR, "nullptr�� �������� �� ����!!");
	m_mapErrorString.emplace(EErrorCode::FAILED_CLEAR_SCREEN, "ȭ�� ����� ����!");
	m_mapErrorString.emplace(EErrorCode::INVALID_SCREEN_COLOR, "��ȿ���� ���� ȭ�� ����!");
}

const Char* ErrorHandlerInside::FindErrorString(EErrorCode errorCode)
{
	const auto& iter = m_mapErrorString.find(errorCode);
	if (iter == m_mapErrorString.cend())
	{
		return "��ϵ��� ���� �����Դϴ�!";
	}

	return iter->second.c_str();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
ErrorHandler::ErrorHandler()
{
	m_spInside = std::make_unique<ErrorHandlerInside>();
}

/*
	���� �ڵ鷯�� �ʱ�ȭ�մϴ�.
	���� Ÿ�Կ� �ش�Ǵ� ���� ������ �����ؿ�.
*/
void ErrorHandler::SetUp()
{
	m_spInside->SetUp();
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
const Char* ErrorHandler::LastErrorString()
{
	EErrorCode errorCode = IErrorHandler::Data()->GetLastErrorCode();
	return m_spInside->FindErrorString(errorCode);
}