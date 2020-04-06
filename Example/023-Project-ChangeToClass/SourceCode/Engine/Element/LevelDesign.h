// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 모든 레벨 디자인의 기반입니다.
// =====================================================================================

#ifndef LEVEL_DESIGN__H__
#define LEVEL_DESIGN__H__

#include "GameElement.h"

#pragma pack(push, 1)
struct LevelDesignFileHeader
{
	char ID[4] = { 'L', 'V', 'D', '1' }; // 4바이트
	Int32 dynamicObjCnt = 0; // 4바이트
};
#pragma pack(pop)

class World;
class GameObj;

class LevelDesign : public GameElem
{
public:
#pragma region 생성자 및 소멸자
	using GameElem::GameElem;

	LevelDesign() = default;
	virtual ~LevelDesign() = default;

	LevelDesign(std::shared_ptr<World> spWorld);
#pragma endregion

	virtual EErrorType OnSaveFile(FILE* pFileStream) override;
	virtual EErrorType OnLoadFile(FILE* pFileStream) override;

	// 템플릿 메서드 패턴을 이용할게요!
	EErrorType SaveFile(const std::string_view& szFileName);
	EErrorType LoadFile(const std::string_view& szFileName);

	// 월드에 게임 오브젝트를 배치하는 건 상속 관계와 LevelDesign에서만 가능해요!
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