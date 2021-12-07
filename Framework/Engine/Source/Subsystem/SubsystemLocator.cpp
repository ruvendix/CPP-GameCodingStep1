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

#include "SubsystemInclusion.h"

/*
	�⺻ ����ý��۸� ����մϴ�.
	���⿡ ���� ����ý����� Ŭ���̾�Ʈ���� �߰����ּ���!
	��� ����ý����� �����ϰ� ���������� �ʱ�ȭ���� ���� ����ý����̶��
	�μ���ý����� �̿��ϹǷ� ������ �����ϴ�.
*/
void SubsystemLocator::StartUp()
{
	RegisterSubsystem<TimeHandler>();
	Logger::I().SetTimeHandler(FIND_SUBSYSTEM(ITimeHandler));

	RegisterSubsystem<PathManager>();
	Logger::I().SetPathManager(FIND_SUBSYSTEM(IPathManager));

	RegisterSubsystem<ConsoleHandler>();
	//RegisterSubsystem<DoubleBufferingConsoleHandler>();
	Logger::I().SetConsoleHandler(FIND_SUBSYSTEM(IConsoleHandler));

	RegisterSubsystem<FileHandler>();
	Logger::I().SetFileHandler(FIND_SUBSYSTEM(IFileHandler));

	RegisterSubsystem<ConstantFrameManager>();
	RegisterSubsystem<ActorManager>();
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