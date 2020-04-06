// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ����Ϳ��� ����ϴ� ���� �������Դϴ�.
// �����ͷ� ������ ����� �����ϰų� �ҷ��� �� �ֽ��ϴ�.
// =====================================================================================

#include "PCH.h"
#include "BattleSimulator2_LevelDesign.h"

#include "Element\World.h"

#include "GameObject\DynamicObject\Viking.h"
#include "GameObject\DynamicObject\MedievalKnight.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BattleSimulator2_LevelDesignHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(BattleSimulator2_LevelDesignHelper);

public:
	static std::shared_ptr<BattleSimulator2_DynamicObj> CreateDynamicObj(EDynamicObjID dynamicObjID);
};

std::shared_ptr<BattleSimulator2_DynamicObj> BattleSimulator2_LevelDesignHelper::CreateDynamicObj(EDynamicObjID dynamicObjID)
{
	switch (dynamicObjID)
	{
	case EDynamicObjID::VIKING:
	{
		return std::make_shared<Viking>(dynamicObjID);
	}

	case EDynamicObjID::MEDIEVALKNIGHT:
	{
		return std::make_shared<MedievalKnight>(dynamicObjID);
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

EErrorType BattleSimulator2_LevelDesign::OnSaveFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::SAVE_FILE_FAIL);

	// ���� ���� �ֱ�
	for (const auto& iter1 : getWorld()->getVecGameObj())
	{
		for (const auto& iter2 : iter1)
		{
			CHECK_NULLPTR_CONTINUE(iter2);

			if (iter2->getType() != EGameObjType::DYNAMIC)
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

EErrorType BattleSimulator2_LevelDesign::OnLoadFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::LOAD_FILE_FAIL);

	// ���� ���� �ҷ�����
	std::shared_ptr<LevelDesignFileHeader> spLevelDesignFileHeader = getLevelDesignFileHeader();
	for (Int32 i = 0; i < spLevelDesignFileHeader->dynamicObjCnt; ++i)
	{
		// ���̵� üũ�ؼ� �����!
		Int32 objID = 0;
		fread(&objID, sizeof(Int32), 1, pFileStream);

		std::shared_ptr<DynamicObj> spDynamicObj =
			BattleSimulator2_LevelDesignHelper::CreateDynamicObj(static_cast<EDynamicObjID>(objID));

		if (spDynamicObj->OnLoadFile(pFileStream) == EErrorType::LOAD_FILE_FAIL)
		{
			return EErrorType::LOAD_FILE_FAIL;
		}

		//DEBUG_LOG("(%d)��° �б� ����!", i);
		SpawnGameObj(spDynamicObj);
	}

	return EErrorType::NONE;
}
