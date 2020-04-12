// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 모든 게임 요소의 기반입니다.
// =====================================================================================

#ifndef GAME_ELEM__H__
#define GAME_ELEM__H__

#include "Interface\IGameElem.h"
#include "NameTag.h"

class GameElem : public IGameElem
{
	DECLARE_ROOT_RTTI(GameElem);
	HAS_NAME_TAG();

public:
#pragma region 생성자 및 소멸자
	GameElem() = default;
	virtual ~GameElem() = default;

	GameElem(const std::string_view& szNameTag) :
		m_nameTag(szNameTag)
	{

	}
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;
	virtual EErrorType OnPreSaveFile(FILE* pFileStream) override;
	virtual EErrorType OnSaveFile(FILE* pFileStream) override;
	virtual EErrorType OnPreLoadFile(FILE* pFileStream) override;
	virtual EErrorType OnLoadFile(FILE* pFileStream) override;

	void ResetError()
	{
		m_errorType = EErrorType::NOTHING;
	}

	void setLastError(EErrorType errorType)
	{
		m_errorType = errorType;
	}

	EErrorType getLastError() const
	{
		return m_errorType;
	}

private:
	EErrorType m_errorType = EErrorType::NOTHING;
	bool m_bFirstInput = true; // 첫 입력 처리는 무시 (우연히 입력 조합이 겹칠 경우 중복 처리가 될 수 있음)
};

#endif