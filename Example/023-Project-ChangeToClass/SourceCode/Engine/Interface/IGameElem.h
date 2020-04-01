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

class IGameElem
{
public:
	virtual EErrorType OnInitialize() = 0;
	virtual EErrorType OnPostInitialize() = 0;
	virtual EErrorType OnInput() = 0;
	virtual EErrorType OnUpdate() = 0;
	virtual EErrorType OnRender() = 0;
	virtual EErrorType OnFinalize() = 0;
	virtual EErrorType OnSaveFile(const std::string_view& szFileName) = 0;
	virtual EErrorType OnLoadFile(const std::string_view& szFileName) = 0;
};

#endif