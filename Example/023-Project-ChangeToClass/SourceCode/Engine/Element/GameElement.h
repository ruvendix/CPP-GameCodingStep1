// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� ���� ����� ����Դϴ�.
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
#pragma region ������ �� �Ҹ���
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
	bool m_bFirstInput = true; // ù �Է� ó���� ���� (�쿬�� �Է� ������ ��ĥ ��� �ߺ� ó���� �� �� ����)
};

#endif