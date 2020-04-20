// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ʱ�ȭ, ����, ���, �������� �̷���� ���� ��Ŀ�����Դϴ�.
// =====================================================================================

#ifndef I_GAME_ELEM_H__
#define I_GAME_ELEM_H__

#include "Handler\ErrorHandler\ErrorHandler.h"

class GameElem;

class IGameElem abstract
{
public:
	virtual EErrorType OnInitialize() abstract;
	virtual EErrorType OnPostInitialize() abstract;
	virtual EErrorType OnInput() abstract;
	virtual EErrorType OnUpdate() abstract;
	virtual EErrorType OnRender() abstract;
	virtual EErrorType OnFinalize() abstract;
	virtual EErrorType OnPreSaveFile(FILE* pFileStream) abstract; // ������ �ҷ��� �� ��ü ���� ������ �ʿ��� ���� ������ �� ���!
	virtual EErrorType OnSaveFile(FILE* pFileStream) abstract;
	virtual EErrorType OnLoadFile(FILE* pFileStream) abstract;
};

#endif