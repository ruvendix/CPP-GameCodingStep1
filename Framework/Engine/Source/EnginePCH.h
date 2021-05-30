// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// PCH는 PreCompiled Header의 약자입니다.
// 자주 사용하지만 거의 변경되지 않는 헤더 파일만 모아서 사용해야 합니다.
// PCH가 자주 변경된다면 빌드할 때마다 거의 처음부터 빌드하는 리빌드 상황이 자주 발생합니다.
// =====================================================================================
#pragma once

#include "../../FrameworkPathfinder.h"

#include "Common/CommonInclusion.h"
#include "Subsystem/SubsystemInclusion.h"
#include "Subsystem/Logger/LogCategory.h"

#pragma comment(lib, "winmm.lib") // ::timeGetTime() 때문...

#pragma warning(disable:6031) // 반환값을 무시했다는 경고(반환값이 항상 필요한 게 아니므로 무시)
#pragma warning(disable:6387) // nullptr이 전달될 수 있다는 경고(_Notnull_을 앞에 붙여주면 되는데 귀찮아서 무시)
#pragma warning(disable:26812) // enum을 정수값으로 사용했다는 경고(enum class는 처리가 귀찮아서 무시)