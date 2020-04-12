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
	return EErrorType::NOTHING;
}

EErrorType GameElem::OnPostInitialize()
{
	//DEBUG_LOG("GameElem���� �̰� ���̸� OnPostInitialize()�� ���������ּ���!");
	return EErrorType::NOTHING;
}

EErrorType GameElem::OnInput()
{
	if (m_bFirstInput == true)
	{
		m_bFirstInput = false;
		return EErrorType::FIRST_INPUT; // ������ �ƴ����� ��ȯ�� ����
	}

	//DEBUG_LOG("GameElem���� �̰� ���̸� OnInput()�� ���������ּ���!");
	return EErrorType::NOTHING;
}

EErrorType GameElem::OnUpdate()
{
	//DEBUG_LOG("GameElem���� �̰� ���̸� OnUpdate()�� ���������ּ���!");
	return EErrorType::NOTHING;
}

EErrorType GameElem::OnRender()
{
	//DEBUG_LOG("GameElem���� �̰� ���̸� OnRender()�� ���������ּ���!");
	return EErrorType::NOTHING;
}

EErrorType GameElem::OnFinalize()
{
	//DEBUG_LOG("GameElem���� �̰� ���̸� OnFinalize()�� ���������ּ���!");
	return EErrorType::NOTHING;
}

EErrorType GameElem::OnPreSaveFile(FILE* pFileStream)
{
	//DEBUG_LOG("GameElem���� �̰� ���̸� OnPreSaveFile()�� ���������ּ���!");
	return EErrorType::NOTHING;
}

EErrorType GameElem::OnSaveFile(FILE* pFileStream)
{
	//DEBUG_LOG("GameElem���� �̰� ���̸� OnSaveFile()�� ���������ּ���!");
	return EErrorType::NOTHING;
}

EErrorType GameElem::OnPreLoadFile(FILE* pFileStream)
{
	//DEBUG_LOG("GameElem���� �̰� ���̸� OnPreLoadFile()�� ���������ּ���!");
	return EErrorType::NOTHING;
}

EErrorType GameElem::OnLoadFile(FILE* pFileStream)
{
	//DEBUG_LOG("GameElem���� �̰� ���̸� OnLoadFile()�� ���������ּ���!");
	return EErrorType::NOTHING;
}
