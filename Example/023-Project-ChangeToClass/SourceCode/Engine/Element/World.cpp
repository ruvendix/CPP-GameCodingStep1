// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 모든 월드의 기반입니다.
// =====================================================================================

#include "PCH.h"
#include "World.h"

#include "GameObject\StaticObject.h"
#include "Manager\ResourcePathMgr.h"
#include "Manager\FileStreamMgr.h"

namespace
{
	const std::string_view& szExt = ".world";
}

World::World(const SizeInfo& sizeInfo)
{
	m_sizeInfo = sizeInfo;
}

EErrorType World::OnInitialize()
{
	m_vecGameObj.resize(m_sizeInfo.height);

	for (auto& iter1 : m_vecGameObj)
	{
		iter1.resize(m_sizeInfo.width);

		for (auto& iter2 : iter1)
		{
			iter2 = std::make_shared<GameObj>();
		}
	}

	m_staticObjCnt = 0;

	return EErrorType();
}

EErrorType World::OnRender()
{
	for (const auto& iter1 : m_vecGameObj)
	{
		for (const auto& iter2 : iter1)
		{
			CHECK_NULLPTR_CONTINUE(iter2);

			// 렌더링 최적화를 위해...
			if (iter2->getShape().empty())
			{
				continue;
			}

			if (iter2->OnRender() == EErrorType::RENDER_FAIL)
			{
				return EErrorType::RENDER_FAIL;
			}
		}
	}

	return EErrorType::NONE;
}

EErrorType World::OnSaveFile(const std::string_view& szFileName)
{
	if (FileStreamMgr::I()->CheckSameExt(szFileName, szExt) == false)
	{
		return EErrorType::SAVE_FILE_FAIL;
	}

	std::string strFullPath = ResourcePathMgr::I()->FindPath(EResourcePathTypeIdx::WORLD);
	strFullPath += szFileName;

	FILE* pFileStream = FileStreamMgr::I()->OpenFileStream(szFileName, strFullPath, EFileStreamMode::WRITE_BINARY);
	if (pFileStream == nullptr)
	{
		return EErrorType::SAVE_FILE_FAIL;
	}

	// 파일 헤더에 정보 넣기
	m_spWorldFileHeader = std::make_shared<WorldFileHeader>();
	m_spWorldFileHeader->sizeInfo = m_sizeInfo;
	m_spWorldFileHeader->staticObjCnt = m_staticObjCnt;
	fwrite(&*m_spWorldFileHeader, sizeof(WorldFileHeader), 1, pFileStream);

	for (const auto& iter1 : m_vecGameObj)
	{
		for (const auto& iter2 : iter1)
		{
			CHECK_NULLPTR_CONTINUE(iter2);

			if (iter2->getType() != EGameObjType::STATIC)
			{
				continue;
			}

			iter2->setFileStream(pFileStream);
			if (iter2->OnSaveFile(szFileName) == EErrorType::SAVE_FILE_FAIL)
			{
				return EErrorType::SAVE_FILE_FAIL;
			}
		}
	}

	FileStreamMgr::I()->CloseFileStream(szFileName);
	return EErrorType::NONE;
}

EErrorType World::OnLoadFile(const std::string_view& szFileName)
{
	FILE* pFileStream = FileStreamMgr::I()->FindFileStream(szFileName);
	if (pFileStream == nullptr)
	{
		return EErrorType::LOAD_FILE_FAIL;
	}

	for (Int32 i = 0; i < m_spWorldFileHeader->staticObjCnt; ++i)
	{
		std::shared_ptr<StaticObj> spStaticObj = std::make_shared<StaticObj>();
		spStaticObj->setFileStream(pFileStream);

		if (spStaticObj->OnLoadFile(szFileName) == EErrorType::LOAD_FILE_FAIL)
		{
			return EErrorType::LOAD_FILE_FAIL;
		}

		SpawnGameObj(spStaticObj);
	}

	return EErrorType::NONE;
}

EErrorType World::OnFinalize()
{
	m_vecGameObj.clear();
	return EErrorType::NONE;
}

EErrorType World::LoadFile(const std::string_view& szFileName)
{
	if (FileStreamMgr::I()->CheckSameExt(szFileName, szExt) == false)
	{
		return EErrorType::LOAD_FILE_FAIL;
	}

	std::string strFullPath = ResourcePathMgr::I()->FindPath(EResourcePathTypeIdx::WORLD);
	strFullPath += szFileName;

	FILE* pFileStream = FileStreamMgr::I()->OpenFileStream(szFileName, strFullPath, EFileStreamMode::READ_BINARY);
	if (pFileStream == nullptr)
	{
		return EErrorType::LOAD_FILE_FAIL;
	}

	// 파일 헤더 불러오기
	m_spWorldFileHeader = std::make_shared<WorldFileHeader>();
	fread(&*m_spWorldFileHeader, sizeof(WorldFileHeader), 1, pFileStream);

	if (OnFinalize() == EErrorType::FINAL_FAIL)
	{
		return EErrorType::FINAL_FAIL;
	}

	if (OnInitialize() == EErrorType::INIT_FAIL)
	{
		return EErrorType::INIT_FAIL;
	}

	if (OnLoadFile(szFileName) == EErrorType::LOAD_FILE_FAIL)
	{
		return EErrorType::LOAD_FILE_FAIL;
	}

	FileStreamMgr::I()->CloseFileStream(szFileName);
	return EErrorType::NONE;
}

std::shared_ptr<GameObj> World::FindGameObj(Int32 x, Int32 y) const
{
	CHECK_RANGE(x, 0, m_sizeInfo.width - 1);
	CHECK_RANGE(y, 0, m_sizeInfo.height - 1);

	return m_vecGameObj.at(y).at(x);
}

void World::SpawnGameObj(std::shared_ptr<GameObj> spGameObj)
{
	SpawnGameObj(spGameObj->getPos(), spGameObj);
}

void World::SpawnGameObj(const COORD& pos, std::shared_ptr<GameObj> spGameObj)
{
	SpawnGameObj(pos.X, pos.Y, spGameObj);
}

void World::SpawnGameObj(Int32 x, Int32 y, std::shared_ptr<GameObj> spGameObj)
{
	CHECK_RANGE(x, 0, m_sizeInfo.width - 1);
	CHECK_RANGE(y, 0, m_sizeInfo.height - 1);

	if (spGameObj->getType() == EGameObjType::STATIC)
	{
		++m_staticObjCnt;
	}

	m_vecGameObj.at(y).at(x) = spGameObj;
}
