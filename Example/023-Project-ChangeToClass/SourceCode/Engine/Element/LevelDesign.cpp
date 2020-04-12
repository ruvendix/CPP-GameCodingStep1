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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace
{
	const std::string_view& s_szLevelDesignExt = ".level";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PredLevelDesignObj
{
public:
	PredLevelDesignObj(std::shared_ptr<DynamicObj> spObj)
		: m_spObj(spObj)
	{ 

	}

	~PredLevelDesignObj() = default;

	bool operator()(std::shared_ptr<DynamicObj> spObj)
	{
		if (spObj == nullptr)
		{
			return false;
		}

		const COORD& srcPos = spObj->getPos();
		const COORD& dsetPos = m_spObj->getPos();

		if ( (srcPos.X == dsetPos.X) &&
			 (srcPos.Y == dsetPos.Y) )
		{
			return true;
		}

		return false;
	}

private:
	std::shared_ptr<DynamicObj> m_spObj = nullptr;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

EErrorType LevelDesign::OnInitialize()
{
	if (m_spFileHeader != nullptr)
	{
		m_vecObj.reserve(m_spFileHeader->levelDesignObjCnt);
	}

	return EErrorType();
}

EErrorType LevelDesign::OnRender()
{
	for (const auto& iter : m_vecObj)
	{
		CHECK_NULLPTR_CONTINUE(iter);

		// 렌더링 최적화를 위해...
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

EErrorType LevelDesign::OnSaveFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::SAVE_FILE_FAIL);

	// 파일 내용 넣기
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

EErrorType LevelDesign::OnLoadFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::LOAD_FILE_FAIL);

	// 파일 내용 불러오기
	for (TSize i = 0; i < m_spFileHeader->levelDesignObjCnt; ++i)
	{
		std::shared_ptr<DynamicObj> spLevelDesignObj = std::make_shared<DynamicObj>();
		if (spLevelDesignObj->OnLoadFile(pFileStream) == EErrorType::LOAD_FILE_FAIL)
		{
			return EErrorType::LOAD_FILE_FAIL;
		}

		AddObj(spLevelDesignObj);
	}

	return EErrorType::NOTHING;
}

EErrorType LevelDesign::OnFinalize()
{
	m_vecObj.clear();
	return EErrorType::NOTHING;
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
	m_spFileHeader = std::make_shared<LevelDesignFileHeader>();
	m_spFileHeader->levelDesignObjCnt = m_vecObj.size();
	fwrite(&*m_spFileHeader, sizeof(LevelDesignFileHeader), 1, pFileStream);
	
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

	if (OnFinalize() == EErrorType::INIT_FAIL)
	{
		return EErrorType::INIT_FAIL;
	}

	// 파일 헤더 불러오기
	m_spFileHeader = std::make_shared<LevelDesignFileHeader>();
	fread(&*m_spFileHeader, sizeof(LevelDesignFileHeader), 1, pFileStream);

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

void LevelDesign::AddObj(std::shared_ptr<DynamicObj> spLevelDesignObj)
{
	// 이전과 위치가 똑같으면? 지운다
	auto iter = std::find_if(m_vecObj.cbegin(), m_vecObj.cend(), PredLevelDesignObj(spLevelDesignObj));
	if (iter != m_vecObj.cend())
	{
		m_vecObj.erase(iter);
	}

	m_vecObj.push_back(spLevelDesignObj);
}

void LevelDesign::Reset()
{
	if (OnFinalize() == EErrorType::FINAL_FAIL)
	{
		return;
	}
}
