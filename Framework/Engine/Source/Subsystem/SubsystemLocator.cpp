// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� ���񽺿� ������ �� ���˴ϴ�.
// ���� �������ʹ� �̱������� �����߽��ϴ�.
// =====================================================================================
#include "EnginePCH.h"
#include "SubsystemLocator.h"

#include <Subsystem/Log/Logger.h>
#include <Subsystem/Error/ErrorHandler.h>
#include <Subsystem/GameObject/GameObjectManager.h>
#include <Subsystem/Time/FrameTimeManager.h>
#include <Subsystem/Console/DoubleBufferingConsoleHandler.h>

/*
	�⺻ ����ý��۸� �߰��մϴ�.
	���⿡ ���� ����ý����� Ŭ���̾�Ʈ���� �߰����ּ���!
*/
void SubsystemLocator::SetUp()
{
	AddSubsystem<Logger>();
	AddSubsystem<ErrorHandler>();
	AddSubsystem<GameObjectManager>();
	AddSubsystem<FrameTimeManager>();
	AddSubsystem<DoubleBufferingConsoleHandler>();
}

void SubsystemLocator::CleanUp()
{
	for (auto& iter : m_mapSubsystem)
	{
		if (iter.second == nullptr)
		{
			continue;
		}

		iter.second->CleanUp();
		SAFE_DELETE(iter.second);
	}	
}