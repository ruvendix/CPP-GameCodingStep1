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
	void RegisterSubsystem();

	template <typename TSubsystem>
	TSubsystem* FindSubsystem();

	template <typename TSubsystem>
	void ExchangeSubsystem();

	void SetUp();
	void CleanUp();

private:
	std::unordered_map<ESubsystemType, ISubsystem*> m_mapSubsystem;
};