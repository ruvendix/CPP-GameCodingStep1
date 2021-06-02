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

#include "Subsystem/Logger/Logger.h"
#include "Subsystem/ErrorHandler/ErrorHandler.h"
#include "Subsystem/GameObjectManager/GameObjectManager.h"
#include "Subsystem/FrameTimeManager/FrameTimeManager.h"
#include "Subsystem/ConsoleHandler/ConsoleHandler.h"
#include "Subsystem/ConsoleHandler/DoubleBufferingConsoleHandler.h"

/*
	�⺻ ����ý��۸� ����մϴ�.
	���⿡ ���� ����ý����� Ŭ���̾�Ʈ���� �߰����ּ���!
*/
void SubsystemLocator::SetUp()
{
	RegisterSubsystem<Logger>();
	RegisterSubsystem<ErrorHandler>();
	RegisterSubsystem<GameObjectManager>();
	RegisterSubsystem<FrameTimeManager>();
	RegisterSubsystem<DoubleBufferingConsoleHandler>();
}

/*
	��ϵ� ��� ����ý����� CleanUp()�� ȣ���մϴ�.
*/
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