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

GameObj::GameObj(Int32 objID) :
	m_ID(objID)
{

}

EErrorType GameObj::OnRender()
{
	const COORD& pos = getPos();
	PUT_STRING(pos.X * getShape().size(), pos.Y, getShape().c_str());

	return EErrorType::NOTHING;
}

EErrorType GameObj::OnPreSaveFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::SAVE_FILE_FAIL);
	
	Int32 ID = getID();
	fwrite(&ID, sizeof(ID), 1, pFileStream);

	return EErrorType::NOTHING;
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

	return EErrorType::NOTHING;
}

EErrorType GameObj::OnPreLoadFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::LOAD_FILE_FAIL);

	Int32 ID = 0;
	fread(&ID, sizeof(ID), 1, pFileStream);
	setID(ID);

	return EErrorType::NOTHING;
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

	return EErrorType::NOTHING;
}
