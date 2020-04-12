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
	TSize worldObjCnt = 0; // 4����Ʈ
};
#pragma pack(pop)

class StaticObj;

class World : public GameElem
{
	DECLARE_RTTI(World, GameElem);
	friend class LevelDesign;

public:
	using VecWorldObj = std::vector<std::shared_ptr<StaticObj>>;

#pragma region ������ �� �Ҹ���
	World() = default;
	virtual ~World() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnSaveFile(FILE* pFileStream) override;
	virtual EErrorType OnLoadFile(FILE* pFileStream) override;
	virtual EErrorType OnFinalize() override;

	void AddObj(std::shared_ptr<StaticObj> spWorldObj);

	// ���ø� �޼��� ������ �̿��ҰԿ�!
	EErrorType SaveFile(const std::string_view& szFileName);
	EErrorType LoadFile(const std::string_view& szFileName);

	COORD CalcCenterBySize()
	{
		return COORD{ static_cast<SHORT>(m_size.width / 2), static_cast<SHORT>(m_size.height / 2) };
	}

	const SizeInfo& getSize() const
	{
		return m_size;
	}

	std::shared_ptr<WorldFileHeader> getFileHeader() const
	{
		return m_spFileHeader;
	}

	VecWorldObj& getVecObj()
	{
		return m_vecObj;
	}

	void setSize(const SizeInfo& worldSize)
	{
		m_size = worldSize;
	}

private:
	SizeInfo m_size;
	std::shared_ptr<WorldFileHeader> m_spFileHeader;
	VecWorldObj m_vecObj;
};

#endif