// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ����Ϳ��� ����ϴ� �����Դϴ�.
// ���� �����ʹ� �������� �ʰ� ���� ������ �����͸� �����մϴ�.
// =====================================================================================

#include "PCH.h"
#include "BattleSimulator2World.h"

#include "Manager\FileStreamManager.h"
#include "GameObject\StaticObject\Wall.h"

EErrorType BattleSimulatorWorld::OnPostInitialize()
{
	const SizeInfo& sizeInfo = getSize();
	for (TSize i = 0; i < sizeInfo.width; ++i)
	{
		std::shared_ptr<Wall> staticObj = std::make_shared<Wall>(EStaticObjID::WALL);
		staticObj->setPos(i, 0);
		staticObj->setShape("��");
		SpawnGameObj(staticObj);

		staticObj = std::make_shared<Wall>(EStaticObjID::WALL);
		staticObj->setPos(i, sizeInfo.height - 1);
		staticObj->setShape("��");
		SpawnGameObj(staticObj);
	}

	for (TSize i = 1; i < (sizeInfo.height - 1); ++i)
	{
		std::shared_ptr<Wall> staticObj = std::make_shared<Wall>(EStaticObjID::WALL);
		staticObj->setPos(0, i);
		staticObj->setShape("��");
		SpawnGameObj(staticObj);

		staticObj = std::make_shared<Wall>(EStaticObjID::WALL);
		staticObj->setPos(sizeInfo.width - 1, i);
		staticObj->setShape("��");
		SpawnGameObj(staticObj);
	}

	return EErrorType::NONE;
}

EErrorType BattleSimulatorWorld::OnSaveFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::SAVE_FILE_FAIL);

	// ���� ���� �ֱ�
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

EErrorType BattleSimulatorWorld::OnLoadFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::LOAD_FILE_FAIL);

	std::shared_ptr<WorldFileHeader> spWorldFileHeader = getWorldFileHeader();
	for (Int32 i = 0; i < spWorldFileHeader->staticObjCnt; ++i)
	{
		// ���̵� üũ�ؼ� �����!
		Int32 objID = 0;
		fread(&objID, sizeof(Int32), 1, pFileStream);

		std::shared_ptr<Wall> spStaticObj = nullptr;
		if (objID == CommonFunc::ToUnderlyingType(EStaticObjID::WALL))
		{
			spStaticObj = std::make_shared<Wall>(EStaticObjID::WALL);
		}

		if (spStaticObj->OnLoadFile(pFileStream) == EErrorType::LOAD_FILE_FAIL)
		{
			return EErrorType::LOAD_FILE_FAIL;
		}

		//DEBUG_LOG("(%d)��° �б� ����!", i);
		SpawnGameObj(spStaticObj);
	}

	return EErrorType::NONE;
}
