// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� ���� ����� ����Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "GameElement.h"

EErrorType GameElem::OnInitialize()
{
	//DEBUG_LOG("GameElem���� �̰� ���̸� OnInitialize()�� ���������ּ���!");
	return EErrorType::NONE;
}

EErrorType GameElem::OnPostInitialize()
{
	//DEBUG_LOG("GameElem���� �̰� ���̸� OnPostInitialize()�� ���������ּ���!");
	return EErrorType::NONE;
}

EErrorType GameElem::OnInput()
{
	if (m_bFirstInput == true)
	{
		m_bFirstInput = false;
		return EErrorType::FIRST_INPUT; // ������ �ƴ����� ��ȯ�� ����
	}

	//DEBUG_LOG("GameElem���� �̰� ���̸� OnInput()�� ���������ּ���!");
	return EErrorType::NONE;
}

EErrorType GameElem::OnUpdate()
{
	//DEBUG_LOG("GameElem���� �̰� ���̸� OnUpdate()�� ���������ּ���!");
	return EErrorType::NONE;
}

EErrorType GameElem::OnRender()
{
	//DEBUG_LOG("GameElem���� �̰� ���̸� OnRender()�� ���������ּ���!");
	return EErrorType::NONE;
}

EErrorType GameElem::OnFinalize()
{
	//DEBUG_LOG("GameElem���� �̰� ���̸� OnFinalize()�� ���������ּ���!");
	return EErrorType::NONE;
}

EErrorType GameElem::OnSaveFile(const std::string_view& szFileName)
{
	//DEBUG_LOG("GameElem���� �̰� ���̸� OnSaveFile()�� ���������ּ���!");
	return EErrorType::NONE;
}

EErrorType GameElem::OnLoadFile(const std::string_view& szFileName)
{
	//DEBUG_LOG("GameElem���� �̰� ���̸� OnLoadFile()�� ���������ּ���!");
	return EErrorType::NONE;
}
