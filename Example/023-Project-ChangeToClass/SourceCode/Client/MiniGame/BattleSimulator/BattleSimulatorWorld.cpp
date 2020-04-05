// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터에서 사용하는 월드입니다.
// 월드 에디터는 지원하지 않고 레벨 디자인 에디터만 지원합니다.
// =====================================================================================

#include "PCH.h"
#include "BattleSimulatorWorld.h"

#include "Manager\FileStreamManager.h"
#include "GameObject\StaticObject\Wall.h"

EErrorType BattleSimulatorWorld::OnPostInitialize()
{
	const SizeInfo& sizeInfo = getSize();

	for (TSize i = 0; i < sizeInfo.width; ++i)
	{
		std::shared_ptr<Wall> staticObj = std::make_shared<Wall>();
		staticObj->setPos(i, 0);
		staticObj->setShape("■");
		SpawnGameObj(staticObj);

		staticObj = std::make_shared<Wall>();
		staticObj->setPos(i, sizeInfo.height - 1);
		staticObj->setShape("■");
		SpawnGameObj(staticObj);
	}

	for (TSize i = 1; i < (sizeInfo.height - 1); ++i)
	{
		std::shared_ptr<Wall> staticObj = std::make_shared<Wall>();
		staticObj->setPos(0, i);
		staticObj->setShape("■");
		SpawnGameObj(staticObj);

		staticObj = std::make_shared<Wall>();
		staticObj->setPos(sizeInfo.width - 1, i);
		staticObj->setShape("■");
		SpawnGameObj(staticObj);
	}

	return EErrorType::NONE;
}

EErrorType BattleSimulatorWorld::OnLoadFile(const std::string_view& szFileName)
{
	FILE* pFileStream = FileStreamMgr::I()->FindFileStream(szFileName);
	if (pFileStream == nullptr)
	{
		return EErrorType::LOAD_FILE_FAIL;
	}

	std::shared_ptr<WorldFileHeader> spWorldFileHeader = getWorldFileHeader();
	for (Int32 i = 0; i < spWorldFileHeader->staticObjCnt; ++i)
	{
		std::shared_ptr<Wall> spStaticObj = std::make_shared<Wall>();
		spStaticObj->setFileStream(pFileStream);

		if (spStaticObj->OnLoadFile(szFileName) == EErrorType::LOAD_FILE_FAIL)
		{
			return EErrorType::LOAD_FILE_FAIL;
		}

		SpawnGameObj(spStaticObj);
	}

	return EErrorType::NONE;
}
