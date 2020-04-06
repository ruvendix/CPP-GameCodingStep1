// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� ������ ����Դϴ�.
// =====================================================================================

#ifndef WORLD__H__
#define WORLD__H__

#include "GameElement.h"

#pragma pack(push, 1)
struct WorldFileHeader
{
	char ID[4] = { 'W', 'R', 'D', '1' }; // 4����Ʈ
	SizeInfo sizeInfo; // 8����Ʈ
	Int32 staticObjCnt = 0; // 4����Ʈ
};
#pragma pack(pop)

class GameObj;

class World : public GameElem
{
	friend class LevelDesign;

public:
	using VecGameObjLine = std::vector<std::shared_ptr<GameObj>>;

#pragma region ������ �� �Ҹ���
	World(const SizeInfo& sizeInfo);
	virtual ~World() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnSaveFile(FILE* pFileStream) override;
	virtual EErrorType OnLoadFile(FILE* pFileStream) override;
	virtual EErrorType OnFinalize() override;

	void Reset();

	// ���ø� �޼��� ������ �̿��ҰԿ�!
	EErrorType SaveFile(const std::string_view& szFileName);
	EErrorType LoadFile(const std::string_view& szFileName);

	std::shared_ptr<GameObj> FindGameObj(Int32 x, Int32 y) const;

	COORD CalcCenterBySize()
	{
		return COORD{ static_cast<SHORT>(m_size.width / 2), static_cast<SHORT>(m_size.height / 2) };
	}

	const SizeInfo& getSize() const
	{
		return m_size;
	}

	std::shared_ptr<WorldFileHeader> getWorldFileHeader() const
	{
		return m_spWorldFileHeader;
	}

	std::vector<VecGameObjLine>& getVecGameObj()
	{
		return m_vecGameObj;
	}

protected:
	// ���忡 ���� ������Ʈ�� ��ġ�ϴ� �� ��� ����� LevelDesign������ �����ؿ�!
	void SpawnGameObj(std::shared_ptr<GameObj> spGameObj);
	void SpawnGameObj(const COORD& pos, std::shared_ptr<GameObj> spGameObj);
	void SpawnGameObj(Int32 x, Int32 y, std::shared_ptr<GameObj> spGameObj);

private:
	Int32 m_staticObjCnt = 0;
	Int32 m_dynamicObjCnt = 0;
	SizeInfo m_size;
	std::shared_ptr<WorldFileHeader> m_spWorldFileHeader;
	std::vector<VecGameObjLine> m_vecGameObj;
};

#endif