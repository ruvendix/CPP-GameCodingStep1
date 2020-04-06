// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� ���� �������� ����Դϴ�.
// =====================================================================================

#ifndef LEVEL_DESIGN__H__
#define LEVEL_DESIGN__H__

#include "GameElement.h"

#pragma pack(push, 1)
struct LevelDesignFileHeader
{
	char ID[4] = { 'L', 'V', 'D', '1' }; // 4����Ʈ
	Int32 dynamicObjCnt = 0; // 4����Ʈ
};
#pragma pack(pop)

class World;
class GameObj;

class LevelDesign : public GameElem
{
public:
#pragma region ������ �� �Ҹ���
	using GameElem::GameElem;

	LevelDesign() = default;
	virtual ~LevelDesign() = default;

	LevelDesign(std::shared_ptr<World> spWorld);
#pragma endregion

	virtual EErrorType OnSaveFile(FILE* pFileStream) override;
	virtual EErrorType OnLoadFile(FILE* pFileStream) override;

	// ���ø� �޼��� ������ �̿��ҰԿ�!
	EErrorType SaveFile(const std::string_view& szFileName);
	EErrorType LoadFile(const std::string_view& szFileName);

	// ���忡 ���� ������Ʈ�� ��ġ�ϴ� �� ��� ����� LevelDesign������ �����ؿ�!
	void SpawnGameObj(std::shared_ptr<GameObj> spGameObj);
	void SpawnGameObj(Int32 x, Int32 y, std::shared_ptr<GameObj> spGameObj);
	void SpawnGameObj(const COORD& pos, std::shared_ptr<GameObj> spGameObj);

	std::shared_ptr<World> getWorld()
	{
		return m_spWorld;
	}

	std::shared_ptr<LevelDesignFileHeader> getLevelDesignFileHeader() const
	{
		return m_spLevelDesignFileHeader;
	}

private:
	std::shared_ptr<LevelDesignFileHeader> m_spLevelDesignFileHeader;
	std::shared_ptr<World> m_spWorld = nullptr;
};

#endif