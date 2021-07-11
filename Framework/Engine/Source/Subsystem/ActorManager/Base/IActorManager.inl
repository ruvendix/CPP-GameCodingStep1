// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �������� ���ø� �Լ����� �����Ǿ��ֽ��ϴ�.
// =====================================================================================

#include "Subsystem/Logger/LogMacro.h"
#include "Scene/Actor/Actor.h"

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