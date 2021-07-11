// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 액터 관리자의 템플릿 함수들이 구현되어있습니다.
// =====================================================================================

#include "Subsystem/Logger/LogMacro.h"
#include "Scene/Actor/Actor.h"

/*
	액터를 생성합니다.
*/
template<typename TActor>
inline TActor* IActorManager::CreateActor()
{
	static_assert(std::is_base_of_v<Actor, TActor>, "It't not actor!");

	TActor* pActor = new TActor;
	if (pActor == nullptr)
	{
		RX_ERROR(EErrorCode::OUT_OF_HEAP_MEMORY);
		return nullptr;
	}

	return pActor;
}