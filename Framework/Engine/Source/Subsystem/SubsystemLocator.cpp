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

#include "Logger/Logger.h"
#include "ErrorHandler/ErrorHandler.h"
#include "GameObjectManager/GameObjectManager.h"
#include "FrameManager/ConstantFrameManager.h"
#include "ConsoleHandler/ConsoleHandler.h"
#include "ConsoleHandler/DoubleBufferingConsoleHandler.h"
#include "TimeHandler/TimeHandler.h"

/*
	�⺻ ����ý��۸� ����մϴ�.
	���⿡ ���� ����ý����� Ŭ���̾�Ʈ���� �߰����ּ���!
*/
void SubsystemLocator::SetUp()
{
	RegisterSubsystem<Logger>();
	RegisterSubsystem<ErrorHandler>();
	RegisterSubsystem<GameObjectManager>();
	RegisterSubsystem<ConstantFrameManager>();
	RegisterSubsystem<TimeHandler>();
	//RegisterSubsystem<ConsoleHandler>();
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