// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 모든 게임 오브젝트의 기반입니다.
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
	fwrite(&m_ID, sizeof(m_ID), 1, pFileStream);

	return EErrorType::NOTHING;
}

EErrorType GameObj::OnSaveFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::SAVE_FILE_FAIL);

	fwrite(&m_pos, sizeof(m_pos), 1, pFileStream);
	fprintf(pFileStream, "%s\n", getNameTag().c_str());
	fprintf(pFileStream, "%s\n", getShape().c_str());

	//Uint8 shapeSize = static_cast<Uint8>(getShape().size());
	//fwrite(&shapeSize, sizeof(shapeSize), 1, pFileStream);

	//shapeSize = (sizeof(char) * shapeSize) + 1;
	//char* shapeBuffer = reinterpret_cast<char*>(std::malloc(shapeSize)); // 널문자 포함
	//StringCchCopy(shapeBuffer, shapeSize, getShape().c_str()); // 널문자를 대입해줌
	//fwrite(shapeBuffer, 1, shapeSize, pFileStream);
	//std::free(shapeBuffer);

	return EErrorType::NOTHING;
}

EErrorType GameObj::OnLoadFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::LOAD_FILE_FAIL);

	fread(&m_pos, sizeof(m_pos), 1, pFileStream);
	
	char buffer[256];
	::ZeroMemory(buffer, sizeof(buffer));
	fscanf_s(pFileStream, "%s\n", buffer, sizeof(buffer));
	setNameTag(buffer);

	fscanf_s(pFileStream, "%s\n", buffer, sizeof(buffer));
	setShape(buffer);

	//Uint8 shapeSize = 0;
	//fread(&shapeSize, sizeof(shapeSize), 1, pFileStream);

	//shapeSize = (sizeof(char) * shapeSize) + 1;
	//char* shapeBuffer = reinterpret_cast<char*>(std::malloc(shapeSize));
	//fread(shapeBuffer, 1, shapeSize, pFileStream);
	//setShape(shapeBuffer);
	//std::free(shapeBuffer);

	return EErrorType::NOTHING;
}

EErrorType GameObj::Copy(const GameObj& src)
{
	setID(src.getID());
	setNameTag(src.getNameTag());
	setPos(src.getPos());
	setShape(src.getShape());

	return EErrorType::NOTHING;
}
