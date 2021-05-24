// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� ���񽺿� ������ �� ���˴ϴ�.
// ���� �������ʹ� �̱������� �����߽��ϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonMacro.h"
#include "SubsystemEnum.h"

// ���� ����
class ISubsystem;

// ���� �������� ������ Ȱ���߽��ϴ�.
class SubsystemLocator final
{
	GENERATE_LOCAL_SINGLETON(SubsystemLocator);

public:
	// ����ý����� �߰��ϸ� ������ �ʿ䰡 �����ϴ�.
	template <typename TSubsystem>
	void AddSubsystem();

	template <typename TSubsystem>
	TSubsystem* FindSubsystem();

	void SetUp();
	void CleanUp();

private:
	std::unordered_map<ESubsystemType, ISubsystem*> m_mapSubsystem;
};

template<typename TSubsystem>
inline void SubsystemLocator::AddSubsystem()
{
	static_assert(std::is_base_of_v<ISubsystem, TSubsystem>, "It't not subsystem!");

	if (FindSubsystem<TSubsystem>() != nullptr)
	{
		::OutputDebugString("�̹� ���� �迭�� ����ý����� �����մϴ�!\n");
		return;
	}

	ISubsystem* pSubsystem = new TSubsystem;
	if (pSubsystem == nullptr)
	{
		::OutputDebugString("���޸� �������� ����ý����� ������ �� �����ϴ�!\n");
		return;
	}

	const auto& ret = m_mapSubsystem.emplace(TSubsystem::MatchType(), pSubsystem);
	if (ret.second == false) // ���� ������ ���
	{
		::OutputDebugString("����ý����� �߰����� ���߽��ϴ�!\n");
		SAFE_DELETE(pSubsystem);
		return;
	}

	pSubsystem->SetUp();
}

template <typename TSubsystem>
inline TSubsystem* SubsystemLocator::FindSubsystem()
{
	static_assert(std::is_base_of_v<ISubsystem, TSubsystem>, "It't not subsystem!");

	const auto& iter = m_mapSubsystem.find(TSubsystem::MatchType());
	if ((iter == m_mapSubsystem.cend()) ||
		(iter->second == nullptr))
	{
		//::OutputDebugString("����ý����� ã�� �� �����ϴ�!\n"); // �ʿ��� ���� ���
		return nullptr;
	}

	TSubsystem* pSubsystem = dynamic_cast<TSubsystem*>(iter->second);
	if (pSubsystem == nullptr)
	{
		::OutputDebugString("����ý����� ĳ������ �� �����ϴ�!\n");
		return nullptr;
	}

	return pSubsystem;
}