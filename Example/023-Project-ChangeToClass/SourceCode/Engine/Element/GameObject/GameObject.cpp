// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� ���� ������Ʈ�� ����Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "GameObject.h"

#include "Controller\ConsoleController.h"

EErrorType GameObj::OnRender()
{
	//PUT_STRING(m_pos.X, m_pos.Y, m_strShape.c_str());
	ConsoleController::I()->PutString(m_pos.X, m_pos.Y, m_strShape.c_str());
	return EErrorType::NONE;
}

EErrorType GameObj::OnSaveFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::SAVE_FILE_FAIL);

	const COORD& pos = getPos();
	fwrite(&pos, sizeof(pos), 1, pFileStream);

	Uint8 shapeSize = static_cast<Uint8>(getShape().size());
	fwrite(&shapeSize, sizeof(shapeSize), 1, pFileStream);

	shapeSize = (sizeof(char) * shapeSize) + 1;
	char* shapeBuffer = reinterpret_cast<char*>(std::malloc(shapeSize)); // �ι��� ����
	StringCchCopy(shapeBuffer, shapeSize, getShape().c_str()); // �ι��ڸ� ��������
	fwrite(shapeBuffer, 1, shapeSize, pFileStream);
	std::free(shapeBuffer);

	return EErrorType::NONE;
}

EErrorType GameObj::OnLoadFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::LOAD_FILE_FAIL);

	COORD pos{ 0, 0 };
	fread(&pos, sizeof(pos), 1, pFileStream);
	setPos(pos);

	Uint8 shapeSize = 0;
	fread(&shapeSize, sizeof(shapeSize), 1, pFileStream);

	shapeSize = (sizeof(char) * shapeSize) + 1;
	char* shapeBuffer = reinterpret_cast<char*>(std::malloc(shapeSize));
	fread(shapeBuffer, 1, shapeSize, pFileStream);
	setShape(shapeBuffer);
	std::free(shapeBuffer);

	return EErrorType::NONE;
}
