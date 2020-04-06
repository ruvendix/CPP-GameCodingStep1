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
#include "BattleSimulator2World.h"

#include "GameObject\StaticObject\Wall.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BattleSimulator2WorldHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(BattleSimulator2WorldHelper);

public:
	static std::shared_ptr<BattleSimulator2_StaticObj> CreateStaticObj(EStaticObjID staticObjID);
};

std::shared_ptr<BattleSimulator2_StaticObj> BattleSimulator2WorldHelper::CreateStaticObj(EStaticObjID staticObjID)
{
	switch (staticObjID)
	{
	case EStaticObjID::WALL:
	{
		return std::make_shared<Wall>(staticObjID);
	}

	default:
	{
		DEFAULT_ERROR_HANDLER(EErrorType::UNKNOWN_DYNAMIC_OBJ);
		return nullptr;
	}
	}

	return nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

EErrorType BattleSimulator2World::OnPostInitialize()
{
	const SizeInfo& sizeInfo = getSize();
	for (TSize i = 0; i < sizeInfo.width; ++i)
	{
		std::shared_ptr<Wall> staticObj = std::make_shared<Wall>(EStaticObjID::WALL);
		staticObj->setPos(i, 0);
		staticObj->setShape("■");
		SpawnGameObj(staticObj);

		staticObj = std::make_shared<Wall>(EStaticObjID::WALL);
		staticObj->setPos(i, sizeInfo.height - 1);
		staticObj->setShape("■");
		SpawnGameObj(staticObj);
	}

	for (TSize i = 1; i < (sizeInfo.height - 1); ++i)
	{
		std::shared_ptr<Wall> staticObj = std::make_shared<Wall>(EStaticObjID::WALL);
		staticObj->setPos(0, i);
		staticObj->setShape("■");
		SpawnGameObj(staticObj);

		staticObj = std::make_shared<Wall>(EStaticObjID::WALL);
		staticObj->setPos(sizeInfo.width - 1, i);
		staticObj->setShape("■");
		SpawnGameObj(staticObj);
	}

	return EErrorType::NONE;
}

EErrorType BattleSimulator2World::OnSaveFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::SAVE_FILE_FAIL);

	// 파일 내용 넣기
	std::vector<VecGameObjLine> vecGameObj = getVecGameObj();
	for (const auto& iter1 : vecGameObj)
	{
		for (const auto& iter2 : iter1)
		{
			CHECK_NULLPTR_CONTINUE(iter2);

			if (iter2->getType() != EGameObjType::STATIC)
			{
				continue;
			}

			if (iter2->OnPreSaveFile(pFileStream) == EErrorType::SAVE_FILE_FAIL)
			{
				return EErrorType::SAVE_FILE_FAIL;
			}

			if (iter2->OnSaveFile(pFileStream) == EErrorType::SAVE_FILE_FAIL)
			{
				return EErrorType::SAVE_FILE_FAIL;
			}
		}
	}

	return EErrorType::NONE;
}

EErrorType BattleSimulator2World::OnLoadFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::LOAD_FILE_FAIL);

	std::shared_ptr<WorldFileHeader> spWorldFileHeader = getWorldFileHeader();
	for (Int32 i = 0; i < spWorldFileHeader->staticObjCnt; ++i)
	{
		// 아이디를 체크해서 만든다!
		Int32 objID = 0;
		fread(&objID, sizeof(Int32), 1, pFileStream);

		std::shared_ptr<BattleSimulator2_StaticObj> spStaticObj =
			BattleSimulator2WorldHelper::CreateStaticObj(static_cast<EStaticObjID>(objID));

		if (objID == CommonFunc::ToUnderlyingType(EStaticObjID::WALL))
		{
			spStaticObj = std::make_shared<Wall>(EStaticObjID::WALL);
		}

		if (spStaticObj->OnLoadFile(pFileStream) == EErrorType::LOAD_FILE_FAIL)
		{
			return EErrorType::LOAD_FILE_FAIL;
		}

		//DEBUG_LOG("(%d)번째 읽기 성공!", i);
		SpawnGameObj(spStaticObj);
	}

	return EErrorType::NONE;
}
