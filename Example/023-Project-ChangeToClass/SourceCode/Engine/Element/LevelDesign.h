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
	TSize levelDesignObjCnt = 0; // 4바이트
};
#pragma pack(pop)

class DynamicObj;

using VecLevelDesigndObj = std::vector<std::shared_ptr<DynamicObj>>;

class LevelDesign : public GameElem
{
	DECLARE_RTTI(LevelDesign, GameElem);

public:
#pragma region 생성자 및 소멸자
	using GameElem::GameElem;

	LevelDesign() = default;
	virtual ~LevelDesign() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnSaveFile(FILE* pFileStream) override;
	virtual EErrorType OnLoadFile(FILE* pFileStream) override;
	virtual EErrorType OnFinalize() override;

	// 템플릿 메서드 패턴을 이용할게요!
	EErrorType SaveFile(const std::string_view& szFileName);
	EErrorType LoadFile(const std::string_view& szFileName);

	void AddObj(std::shared_ptr<DynamicObj> spLevelDesignObj);
	void Reset();

	std::shared_ptr<LevelDesignFileHeader> getFileHeader() const
	{
		return m_spFileHeader;
	}

	VecLevelDesigndObj& getVecObj()
	{
		return m_vecObj;
	}

private:
	std::shared_ptr<LevelDesignFileHeader> m_spFileHeader;
	VecLevelDesigndObj m_vecObj;
};

#endif