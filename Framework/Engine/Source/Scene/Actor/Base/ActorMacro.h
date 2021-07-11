// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ���� ��ũ�� �Լ� �����Դϴ�.
// =====================================================================================
#pragma once

#define ONLY_ACTOR_MANAGER(ActorType)\
private:\
	FRIEND_CLASS(IActorManager);\
	FRIEND_CLASS(ActorManager);\
	ActorType() = default;\
	virtual ~ActorType() = default;

#define ONLY_ACTOR_MANAGER_CTOR(ActorType)\
private:\
	FRIEND_CLASS(IActorManager);\
	FRIEND_CLASS(ActorManager);\
	ActorType();\
	virtual ~ActorType() = default;