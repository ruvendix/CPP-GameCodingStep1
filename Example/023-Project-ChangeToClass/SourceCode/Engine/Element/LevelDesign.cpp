// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 모든 레벨 디자인의 기반입니다.
// =====================================================================================

#include "PCH.h"
#include "LevelDesign.h"

#include "Manager\FileStreamManager.h"
#include "Manager\ResourcePathManager.h"
#include "World.h"
#include "GameObject\DynamicObject.h"

namespace
{
	const std::string_view& s_szLevelDesignExt = ".level";
}

LevelDesign::LevelDesign(std::shared_ptr<World> spWorld) :
	m_spWorld(spWorld)
{
	
}

EErrorType LevelDesign::OnSaveFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::SAVE_FILE_FAIL);

	// 파일 내용 넣기
	for (const auto& iter1 : m_spWorld->m_vecGameObj)
	{
		for (const auto& iter2 : iter1)
		{
			CHECK_NULLPTR_CONTINUE(iter2);

			if (iter2->getType() != EGameObjType::DYNAMIC)
			{
				continue;
			}

			if (iter2->OnSaveFile(pFileStream) == EErrorType::SAVE_FILE_FAIL)
			{
				return EErrorType::SAVE_FILE_FAIL;
			}
		}
	}

	return EErrorType::NONE;
}

EErrorType LevelDesign::OnLoadFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::LOAD_FILE_FAIL);

	// 파일 내용 불러오기
	for (Int32 i = 0; i < m_spLevelDesignFileHeader->dynamicObjCnt; ++i)
	{
		std::shared_ptr<DynamicObj> spDynamicObj = std::make_shared<DynamicObj>();
		if (spDynamicObj->OnLoadFile(pFileStream) == EErrorType::LOAD_FILE_FAIL)
		{
			return EErrorType::LOAD_FILE_FAIL;
		}

		SpawnGameObj(spDynamicObj);
	}

	return EErrorType::NONE;
}

EErrorType LevelDesign::SaveFile(const std::string_view& szFileName)
{
	if (FileStreamMgr::I()->CheckSameExt(szFileName, s_szLevelDesignExt) == false)
	{
		return EErrorType::SAVE_FILE_FAIL;
	}

	std::string strFullPath = ResourcePathMgr::I()->FindPath(EResourcePathTypeIdx::LEVEL_DESIGN);
	strFullPath += szFileName;

	FILE* pFileStream = FileStreamMgr::I()->OpenFileStream(szFileName, strFullPath, EFileStreamMode::WRITE_BINARY);
	if (pFileStream == nullptr)
	{
		return EErrorType::SAVE_FILE_FAIL;
	}

	// 파일 헤더에 정보 넣기
	m_spLevelDesignFileHeader = std::make_shared<LevelDesignFileHeader>();
	m_spLevelDesignFileHeader->dynamicObjCnt = m_spWorld->m_dynamicObjCnt;
	fwrite(&*m_spLevelDesignFileHeader, sizeof(LevelDesignFileHeader), 1, pFileStream);

	if (OnSaveFile(pFileStream) == EErrorType::SAVE_FILE_FAIL)
	{
		return EErrorType::SAVE_FILE_FAIL;
	}

	FileStreamMgr::I()->CloseFileStream(szFileName);
	return EErrorType();
}

EErrorType LevelDesign::LoadFile(const std::string_view& szFileName)
{
	if (FileStreamMgr::I()->CheckSameExt(szFileName, s_szLevelDesignExt) == false)
	{
		return EErrorType::LOAD_FILE_FAIL;
	}

	std::string strFullPath = ResourcePathMgr::I()->FindPath(EResourcePathTypeIdx::LEVEL_DESIGN);
	strFullPath += szFileName;

	FILE* pFileStream = FileStreamMgr::I()->OpenFileStream(szFileName, strFullPath, EFileStreamMode::READ_BINARY);
	if (pFileStream == nullptr)
	{
		return EErrorType::LOAD_FILE_FAIL;
	}

	// 파일 헤더 불러오기
	m_spLevelDesignFileHeader = std::make_shared<LevelDesignFileHeader>();
	fread(&*m_spLevelDesignFileHeader, sizeof(LevelDesignFileHeader), 1, pFileStream);

	if (OnLoadFile(pFileStream) == EErrorType::LOAD_FILE_FAIL)
	{
		return EErrorType::LOAD_FILE_FAIL;
	}

	FileStreamMgr::I()->CloseFileStream(szFileName);
	return EErrorType();
}

void LevelDesign::SpawnGameObj(std::shared_ptr<GameObj> spGameObj)
{
	const COORD& pos = spGameObj->getPos();
	SpawnGameObj(pos, spGameObj);
}

void LevelDesign::SpawnGameObj(Int32 x, Int32 y, std::shared_ptr<GameObj> spGameObj)
{
	m_spWorld->SpawnGameObj(x, y, spGameObj);
}

void LevelDesign::SpawnGameObj(const COORD& pos, std::shared_ptr<GameObj> spGameObj)
{
	SpawnGameObj(pos.X, pos.Y, spGameObj);
}
