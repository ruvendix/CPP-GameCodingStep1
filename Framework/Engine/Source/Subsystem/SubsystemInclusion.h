// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 서비스 관련 헤더 파일 모음입니다.
// =====================================================================================
#pragma once

#include "ConsoleHandler/Base/IConsoleHandlerNull.h"
#include "ConsoleHandler/ConsoleHandler.h"
#include "ConsoleHandler/DoubleBufferingConsoleHandler.h"

#include "TimeHandler/Base/ITimeHandlerNull.h"
#include "TimeHandler/TimeHandler.h"

#include "FileHandler/Base/IFileHandlerNull.h"
#include "FileHandler/FileHandler.h"

#include "GameObjectManager/Base/IGameObjectManagerNull.h"
#include "GameObjectManager/GameObjectManager.h"

#include "FrameManager/Base/FrameMacro.h"
#include "FrameManager/Base/IFrameManagerNull.h"
#include "FrameManager/ConstantFrameManager.h"

#include "PathManager/Base/IPathManagerNull.h"
#include "PathManager/PathManager.h"

#include "ActorManager/Base/IActorManagerNull.h"
#include "ActorManager/ActorManager.h"

#include "SubsystemMacro.h"
#include "SubsystemLocator.h"
#include "SubsystemLocator.inl"