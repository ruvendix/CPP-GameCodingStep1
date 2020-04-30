// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2���� ����ϴ� �����Դϴ�.
// ���� �����ʹ� �������� �ʰ� ���� ������ �����͸� �����մϴ�.
// =====================================================================================

#include "PCH.h"
#include "BattleSimulator2World.h"

#include "GameObject\StaticObject\Wall.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace
{
	static Int32 s_wallNum = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BattleSimulator2WorldHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(BattleSimulator2WorldHelper);

public:
	static std::shared_ptr<StaticObj> CreateStaticObj(EObjID ID);
};

std::shared_ptr<StaticObj> BattleSimulator2WorldHelper::CreateStaticObj(EObjID ID)
{
	switch (ID)
	{
	case EObjID::WALL:
	{
		return std::make_shared<Wall>(ID);
	}

	default:
	{
		DEFAULT_ERROR_HANDLER(EErrorType::UNKNOWN_STATIC_OBJ);
		return nullptr;
	}
	}

	return nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

EErrorType BattleSimulator2World::OnPostInitialize()
{
	s_wallNum = 0;

	const SizeInfo& sizeInfo = getSize();
	for (Int32 i = 0; i < static_cast<Int32>(sizeInfo.width); ++i)
	{
		std::shared_ptr<Wall> staticObj = std::make_shared<Wall>(EObjID::WALL);
		staticObj->setPos(i, 0);
		staticObj->setNameTag(common_func::MakeFormatString("Wall_%d", s_wallNum++));
		staticObj->setShape("��");
		AddObj(staticObj);

		staticObj = std::make_shared<Wall>(EObjID::WALL);
		staticObj->setPos(i, sizeInfo.height - 1);
		staticObj->setNameTag(common_func::MakeFormatString("Wall_%d", s_wallNum++));
		staticObj->setShape("��");
		AddObj(staticObj);
	}

	for (Int32 i = 1; i < static_cast<Int32>(sizeInfo.height - 1); ++i)
	{
		std::shared_ptr<Wall> staticObj = std::make_shared<Wall>(EObjID::WALL);
		staticObj->setPos(0, i);
		staticObj->setNameTag(common_func::MakeFormatString("Wall_%d", s_wallNum++));
		staticObj->setShape("��");
		AddObj(staticObj);

		staticObj = std::make_shared<Wall>(EObjID::WALL);
		staticObj->setPos(sizeInfo.width - 1, i);
		staticObj->setNameTag(common_func::MakeFormatString("Wall_%d", s_wallNum++));
		staticObj->setShape("��");
		AddObj(staticObj);
	}

	return EErrorType::NOTHING;
}

EErrorType BattleSimulator2World::OnLoadFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::LOAD_FILE_FAIL);

	std::shared_ptr<WorldFileHeader> spWorldFileHeader = getFileHeader();
	for (TSize i = 0; i < spWorldFileHeader->worldObjCnt; ++i)
	{
		// ���̵� üũ�ؼ� �����!
		EObjID ID = EObjID::UNKNOWN;
		fread(&ID, sizeof(EObjID), 1, pFileStream);

		std::shared_ptr<StaticObj> spObj = BattleSimulator2WorldHelper::CreateStaticObj(ID);
		if (spObj->OnLoadFile(pFileStream) == EErrorType::LOAD_FILE_FAIL)
		{
			return EErrorType::LOAD_FILE_FAIL;
		}

		//DEBUG_LOG("(%d)��° �б� ����!", i);
		AddObj(spObj);
	}

	return EErrorType::NOTHING;
}
