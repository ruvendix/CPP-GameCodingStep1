// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 모든 월드의 기반입니다.
// =====================================================================================

#ifndef WORLD__H__
#define WORLD__H__

#include "GameElement.h"

#pragma pack(push, 1)
struct WorldFileHeader
{
	char ID[4] = { 'W', 'R', 'D', '1' }; // 4바이트
	SizeInfo sizeInfo; // 8바이트
	Int32 staticObjCnt = 0; // 4바이트
};
#pragma pack(pop)

class GameObj;

class World : public GameElem
{
public:
	using VecGameObjLine = std::vector<std::shared_ptr<GameObj>>;

#pragma region 생성자 및 소멸자
	World(const SizeInfo& sizeInfo);
	virtual ~World() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnSaveFile(const std::string_view& szFileName) override;
	virtual EErrorType OnLoadFile(const std::string_view& szFileName) override;
	virtual EErrorType OnFinalize() override;

	EErrorType LoadFile(const std::string_view& szFileName); // 템플릿 메서드 패턴
	std::shared_ptr<GameObj> FindGameObj(Int32 x, Int32 y) const;

	const SizeInfo& getSize() const
	{
		return m_sizeInfo;
	}

	std::shared_ptr<WorldFileHeader> getWorldFileHeader() const
	{
		return m_spWorldFileHeader;
	}

protected:
	// 월드에 게임 오브젝트를 배치하는 건 상속 관계와 LevelDesign에서만 가능해요!
	void SpawnGameObj(std::shared_ptr<GameObj> spGameObj);
	void SpawnGameObj(const COORD& pos, std::shared_ptr<GameObj> spGameObj);
	void SpawnGameObj(Int32 x, Int32 y, std::shared_ptr<GameObj> spGameObj);

private:
	Int32 m_staticObjCnt = 0;
	SizeInfo m_sizeInfo;
	std::shared_ptr<WorldFileHeader> m_spWorldFileHeader;
	//WorldFileHeader m_worldFileHeader;
	std::vector<VecGameObjLine> m_vecGameObj;
};

#endif