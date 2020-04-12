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
	TSize worldObjCnt = 0; // 4바이트
};
#pragma pack(pop)

class StaticObj;

class World : public GameElem
{
	DECLARE_RTTI(World, GameElem);
	friend class LevelDesign;

public:
	using VecWorldObj = std::vector<std::shared_ptr<StaticObj>>;

#pragma region 생성자 및 소멸자
	World() = default;
	virtual ~World() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnSaveFile(FILE* pFileStream) override;
	virtual EErrorType OnLoadFile(FILE* pFileStream) override;
	virtual EErrorType OnFinalize() override;

	void AddObj(std::shared_ptr<StaticObj> spWorldObj);

	// 템플릿 메서드 패턴을 이용할게요!
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