// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ������Ʈ�� �⺻���Դϴ�.
// ���� ������Ʈ�� ���̴� �Ͱ� ������ �ʴ� ��, �����̴� �Ͱ� �������� �ʴ� �͵���
// ���� �����ϴ� �����̶�� �����Ͻø� �˴ϴ�.
// =====================================================================================
#include "EnginePCH.h"
#include "GameObject.h"

#include "Service/ServiceInclusion.h"

/*
	���� ������Ʈ�� �ʱ�ȭ�մϴ�.
	�±׿� ����� �⺻�������� �����ؿ�.
*/
EReturnType GameObject::SetUp()
{
	m_strTag = "Default";
	m_strShape = "A";

	return EReturnType::SUCCESS;
}

/*
	���� ������Ʈ�� �����մϴ�.
	������ �߰��� ������ �����.
*/
EReturnType GameObject::CleanUp()
{
	return EReturnType::SUCCESS;
}

/*
	���� ������Ʈ�� ������ �����մϴ�.
*/
EReturnType GameObject::Update()
{
	return EReturnType::SUCCESS;
}

/*
	���� ������Ʈ�� �׸��ϴ�.
*/
EReturnType GameObject::Render()
{
	ServiceLocator::I().IConsoleHandlerInstance()->RenderString(m_posX, m_posY, m_strShape.c_str());
	return EReturnType::SUCCESS;
}