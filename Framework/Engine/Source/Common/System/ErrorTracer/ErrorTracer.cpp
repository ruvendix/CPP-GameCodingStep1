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
#include "ErrorTracer.h"

class ErrorTracerInside final
{
public:
	ErrorTracerInside() = default;
	~ErrorTracerInside() = default;

	void SetUp();
	const Char* FindErrorString(EErrorCode errorCode) const;

private:
	std::unordered_map<EErrorCode, std::string> m_mapErrorString;
};

void ErrorTracerInside::SetUp()
{
	m_mapErrorString.emplace(EErrorCode::UNKNOWN, "�� �� ���� ����!");
	m_mapErrorString.emplace(EErrorCode::INDIRECT_NULLPTR, "nullptr�� �������� �� ����!!");
	m_mapErrorString.emplace(EErrorCode::OUT_OF_HEAP_MEMORY, "�� �޸� ����!");

	m_mapErrorString.emplace(EErrorCode::DUPLICATED_SUBSYSTEM, "�ߺ��� ����ý���!");
	m_mapErrorString.emplace(EErrorCode::REGISTER_SUBSYSTEM_FAIL, "����ý��� ��� ����!");
	m_mapErrorString.emplace(EErrorCode::NOT_EXIST_SUBSYSTEM, "�������� �ʴ� ����ý���!");	

	m_mapErrorString.emplace(EErrorCode::CLEAR_SCREEN_FAIL, "ȭ�� ����� ����!");
	m_mapErrorString.emplace(EErrorCode::INVALID_SCREEN_COLOR, "��ȿ���� ���� ȭ�� ����!");

	m_mapErrorString.emplace(EErrorCode::OUT_OF_GAMEOBJECT, "�� �̻� ���� ������Ʈ�� ������ �� ����!");

	m_mapErrorString.emplace(EErrorCode::OPEN_FILE_STREAM_FAIL, "���� ��Ʈ�� ���� ����!");
	m_mapErrorString.emplace(EErrorCode::CLOSE_FILE_STREAM_FAIL, "���� ��Ʈ�� �ݱ� ����!");

	m_mapErrorString.emplace(EErrorCode::DUPLICATED_COMPONENT, "�ߺ��� ������Ʈ: %s!");
	m_mapErrorString.emplace(EErrorCode::ADD_COMPONENT_FAIL, "������Ʈ �߰� ����: %s!");
	m_mapErrorString.emplace(EErrorCode::NOT_EXIST_COMPONENT, "�������� �ʴ� ������Ʈ: %s!");

	m_mapErrorString.emplace(EErrorCode::CASTING_FAIL, "ĳ���� ����!");
}

const Char* ErrorTracerInside::FindErrorString(EErrorCode errorCode) const
{
	const auto& iter = m_mapErrorString.find(errorCode);
	if (iter == m_mapErrorString.cend())
	{
		return "��ϵ��� ���� �����Դϴ�!";
	}

	return iter->second.c_str();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	���� �ڵ鷯�� �ʱ�ȭ�մϴ�.
	���� Ÿ�Կ� �ش�Ǵ� ���� ������ �����ؿ�.
*/
void ErrorTracer::SetUp()
{
	m_pInside = new ErrorTracerInside;
	m_pInside->SetUp();
}

/*
	���� �ڵ鷯�� �����մϴ�.
	������ �߰��� ������ �����.
*/
void ErrorTracer::CleanUp()
{
	SAFE_DELETE(m_pInside);
}

/*
	�������� �߻��� ������ �ش�Ǵ� ������ �����ɴϴ�.
*/
const Char* ErrorTracer::LastErrorString() const
{
	EErrorCode errorCode = GetLastErrorCode();
	return m_pInside->FindErrorString(errorCode);
}