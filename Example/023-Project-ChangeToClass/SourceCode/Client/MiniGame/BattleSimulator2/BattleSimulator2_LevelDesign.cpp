// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2에서 사용하는 레벨 디자인입니다.
// 에디터로 에디터한 결과를 저장하거나 불러올 수 있습니다.
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

	// 파일 내용 불러오기
	std::shared_ptr<LevelDesignFileHeader> spLevelDesignFileHeader = getFileHeader();
	for (TSize i = 0; i < spLevelDesignFileHeader->levelDesignObjCnt; ++i)
	{
		// 아이디를 체크해서 만든다!
		EObjID ID = EObjID::UNKNOWN;
		fread(&ID, sizeof(EObjID), 1, pFileStream);

		std::shared_ptr<DynamicObj> spObj = BattleSimulator2_LevelDesignHelper::CreateDynamicObj(ID);
		if (spObj->OnLoadFile(pFileStream) == EErrorType::LOAD_FILE_FAIL)
		{
			return EErrorType::LOAD_FILE_FAIL;
		}

		//DEBUG_LOG("(%d)번째 읽기 성공!", i);
		AddObj(spObj);
	}

	return EErrorType::NOTHING;
}
