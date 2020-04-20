// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 초기화, 갱신, 출력, 마무리로 이루어진 게임 메커니즘입니다.
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
	virtual EErrorType OnPreSaveFile(FILE* pFileStream) abstract; // 파일을 불러올 때 객체 생성 이전에 필요한 값을 저장할 때 사용!
	virtual EErrorType OnSaveFile(FILE* pFileStream) abstract;
	virtual EErrorType OnLoadFile(FILE* pFileStream) abstract;
};

#endif