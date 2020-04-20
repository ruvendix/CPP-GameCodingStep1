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
	TSize levelDesignObjCnt = 0; // 4����Ʈ
};
#pragma pack(pop)

class DynamicObj;

using VecLevelDesigndObj = std::vector<std::shared_ptr<DynamicObj>>;

class LevelDesign : public GameElem
{
	DECLARE_RTTI(LevelDesign, GameElem);

public:
#pragma region ������ �� �Ҹ���
	using GameElem::GameElem;

	LevelDesign() = default;
	virtual ~LevelDesign() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnSaveFile(FILE* pFileStream) override;
	virtual EErrorType OnLoadFile(FILE* pFileStream) override;
	virtual EErrorType OnFinalize() override;

	// ���ø� �޼��� ������ �̿��ҰԿ�!
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