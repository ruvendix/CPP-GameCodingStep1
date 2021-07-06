// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���α׷��� �������Դϴ�.
// =====================================================================================

#ifdef _DEBUG
#pragma comment(lib, "Engine_Debug.lib")
#else
#pragma comment(lib, "Engine.lib")
#endif

#include <EnginePCH.h>
#include <Scene/GameObject/GameObject.h>

Int32 main()
{
	SubsystemLocator::I().SetUp();

	FIND_SUBSYSTEM(IConsoleHandler)->AdjustSize(120, 20);
	FIND_SUBSYSTEM(ILogger)->Data()->DeactivateOption(EnumIdx::LogOption::TIME);
	FIND_SUBSYSTEM(ILogger)->Data()->DeactivateOption(EnumIdx::LogOption::LINE);
	FIND_SUBSYSTEM(ILogger)->Data()->DeactivateOption(EnumIdx::LogOption::ABSOLUTE_FILEPATH);
	FIND_SUBSYSTEM(ILogger)->Data()->DeactivateOption(EnumIdx::LogOption::RELATIVE_FILEPATH);

	std::string frameworkAbsolutePath = FIND_SUBSYSTEM(IPathManager)->FrameworkAbsolutePath();
	std::string frameworkRelativePath = FIND_SUBSYSTEM(IPathManager)->FrameworkRelativePath();
	std::string clientAbsolutePath = FIND_SUBSYSTEM(IPathManager)->ClientAbsolutePath();
	std::string clientRelativePath = FIND_SUBSYSTEM(IPathManager)->ClientRelativePath();

	RX_INFO("�����ӿ�ũ ������: %s", frameworkAbsolutePath.c_str());
	RX_INFO("�����ӿ�ũ �����: %s", frameworkRelativePath.c_str());
	RX_INFO("Ŭ���̾�Ʈ ������: %s", clientAbsolutePath.c_str());
	RX_INFO("Ŭ���̾�Ʈ �����: %s", clientRelativePath.c_str());

	SubsystemLocator::I().CleanUp();
	return 0;
}