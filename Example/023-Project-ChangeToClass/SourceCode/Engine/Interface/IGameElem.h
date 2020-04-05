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

class IGameElem
{
public:
	virtual EErrorType OnInitialize() = 0;
	virtual EErrorType OnPostInitialize() = 0;
	virtual EErrorType OnInput() = 0;
	virtual EErrorType OnUpdate() = 0;
	virtual EErrorType OnRender() = 0;
	virtual EErrorType OnFinalize() = 0;
	virtual EErrorType OnPreSaveFile(FILE* pFileStream) = 0;
	virtual EErrorType OnSaveFile(FILE* pFileStream) = 0;
	virtual EErrorType OnLoadFile(FILE* pFileStream) = 0;
};

#endif