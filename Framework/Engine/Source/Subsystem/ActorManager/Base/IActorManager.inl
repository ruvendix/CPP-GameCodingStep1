// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �������� ���ø� �Լ����� �����Ǿ��ֽ��ϴ�.
// =====================================================================================

#include "Common/System/Logger/LogMacro.h"
#include "Scene/Actor/Base/ActorInclusion.h"

/*
	���͸� �����մϴ�.
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