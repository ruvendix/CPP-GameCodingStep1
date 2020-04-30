// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2���� ����ϴ� ���� �������Դϴ�.
// �����ͷ� �������� ����� �����ϰų� �ҷ��� �� �ֽ��ϴ�.
// =====================================================================================

#include "PCH.h"
#include "BattleSimulator2_LevelDesign.h"

#include "Element\World.h"

#include "BattleSimulator2_DataCollector.h"
#include "GameObject\DynamicObject\Viking.h"
#include "GameObject\DynamicObject\MedievalKnight.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BattleSimulator2_LevelDesignHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(BattleSimulator2_LevelDesignHelper);

public:
	static std::shared_ptr<DynamicObj> CreateDynamicObj(EObjID ID);
};

std::shared_ptr<DynamicObj> BattleSimulator2_LevelDesignHelper::CreateDynamicObj(EObjID ID)
{
	switch (ID)
	{
	case EObjID::VIKING:
	{
		BattleSimulator2_DataCollector::I()->ModifyBattleData(EObjID::VIKING,
			EBattleDataType::TOTAL_UNIT_CNT, EDataProgressDir::POSITIVENESS, 1);
		return std::make_shared<Viking>(ID);
	}

	case EObjID::MEDIEVAL_KNIGHT:
	{
		BattleSimulator2_DataCollector::I()->ModifyBattleData(EObjID::MEDIEVAL_KNIGHT,
			EBattleDataType::TOTAL_UNIT_CNT, EDataProgressDir::POSITIVENESS, 1);
		return std::make_shared<MedievalKnight>(ID);
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

EErrorType BattleSimulator2_LevelDesign::OnLoadFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::LOAD_FILE_FAIL);

	// ���� ���� �ҷ�����
	std::shared_ptr<LevelDesignFileHeader> spLevelDesignFileHeader = getFileHeader();
	for (TSize i = 0; i < spLevelDesignFileHeader->levelDesignObjCnt; ++i)
	{
		// ���̵� üũ�ؼ� �����!
		EObjID ID = EObjID::UNKNOWN;
		fread(&ID, sizeof(EObjID), 1, pFileStream);

		std::shared_ptr<DynamicObj> spObj = BattleSimulator2_LevelDesignHelper::CreateDynamicObj(ID);
		if (spObj->OnLoadFile(pFileStream) == EErrorType::LOAD_FILE_FAIL)
		{
			return EErrorType::LOAD_FILE_FAIL;
		}

		//DEBUG_LOG("(%d)��° �б� ����!", i);
		AddObj(spObj);
	}

	return EErrorType::NOTHING;
}
