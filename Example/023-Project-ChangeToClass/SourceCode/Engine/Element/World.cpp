// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� ������ ����Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "World.h"

#include "GameObject\StaticObject.h"
#include "Manager\ResourcePathManager.h"
#include "Manager\FileStreamManager.h"

namespace
{
	const std::string_view& s_szWorldExt = ".world";
}

EErrorType World::OnInitialize()
{
	if (m_spFileHeader != nullptr)
	{
		m_vecObj.reserve(m_spFileHeader->worldObjCnt);
	}

	return EErrorType::NOTHING;
}

EErrorType World::OnRender()
{
	for (const auto& iter : m_vecObj)
	{
		CHECK_NULLPTR_CONTINUE(iter);

		// ������ ����ȭ�� ����...
		if (iter->getShape().empty())
		{
			continue;
		}

		if (iter->OnRender() == EErrorType::RENDER_FAIL)
		{
			return EErrorType::RENDER_FAIL;
		}
	}

	return EErrorType::NOTHING;
}

EErrorType World::OnSaveFile(FILE* pFileStream)
{	
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::SAVE_FILE_FAIL);

	// ���� ���� �ֱ�
	for (const auto& iter : m_vecObj)
	{
		CHECK_NULLPTR_CONTINUE(iter);

		if (iter->OnPreSaveFile(pFileStream) == EErrorType::SAVE_FILE_FAIL)
		{
			return EErrorType::SAVE_FILE_FAIL;
		}

		if (iter->OnSaveFile(pFileStream) == EErrorType::SAVE_FILE_FAIL)
		{
			return EErrorType::SAVE_FILE_FAIL;
		}
	}

	return EErrorType::NOTHING;
}

EErrorType World::OnLoadFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::LOAD_FILE_FAIL);

	// ���� ���� �ҷ�����
	for (TSize i = 0; i < m_spFileHeader->worldObjCnt; ++i)
	{
		std::shared_ptr<StaticObj> spWorldObj = std::make_shared<StaticObj>();
		if (spWorldObj->OnPreLoadFile(pFileStream) == EErrorType::LOAD_FILE_FAIL)
		{
			return EErrorType::LOAD_FILE_FAIL;
		}

		if (spWorldObj->OnLoadFile(pFileStream) == EErrorType::LOAD_FILE_FAIL)
		{
			return EErrorType::LOAD_FILE_FAIL;
		}

		AddObj(spWorldObj);
	}

	return EErrorType::NOTHING;
}

EErrorType World::OnFinalize()
{
	m_vecObj.clear();
	return EErrorType::NOTHING;
}

EErrorType World::SaveFile(const std::string_view& szFileName)
{
	if (FileStreamMgr::I()->CheckSameExt(szFileName, s_szWorldExt) == false)
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

	// ���� ����� ���� �ֱ�
	m_spFileHeader = std::make_shared<WorldFileHeader>();
	m_spFileHeader->sizeInfo = m_size;
	m_spFileHeader->worldObjCnt = m_vecObj.size();
	fwrite(&*m_spFileHeader, sizeof(WorldFileHeader), 1, pFileStream);

	if (OnSaveFile(pFileStream) == EErrorType::SAVE_FILE_FAIL)
	{
		return EErrorType::SAVE_FILE_FAIL;
	}

	FileStreamMgr::I()->CloseFileStream(szFileName);
	return EErrorType();
}

EErrorType World::LoadFile(const std::string_view& szFileName)
{
	if (FileStreamMgr::I()->CheckSameExt(szFileName, s_szWorldExt) == false)
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

	if (OnFinalize() == EErrorType::FINAL_FAIL)
	{
		return EErrorType::FINAL_FAIL;
	}

	// ���� ��� �ҷ�����
	m_spFileHeader = std::make_shared<WorldFileHeader>();
	fread(&*m_spFileHeader, sizeof(WorldFileHeader), 1, pFileStream);
	m_size = m_spFileHeader->sizeInfo;

	if (OnInitialize() == EErrorType::INIT_FAIL)
	{
		return EErrorType::INIT_FAIL;
	}

	if (OnLoadFile(pFileStream) == EErrorType::LOAD_FILE_FAIL)
	{
		return EErrorType::LOAD_FILE_FAIL;
	}

	FileStreamMgr::I()->CloseFileStream(szFileName);
	return EErrorType();
}

void World::AddObj(std::shared_ptr<StaticObj> spWorldObj)
{
	m_vecObj.push_back(spWorldObj);
}