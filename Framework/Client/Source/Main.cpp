// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 프로그램의 진입점입니다.
// =====================================================================================

#ifdef _DEBUG
#pragma comment(lib, "Engine_Debug.lib")
#else
#pragma comment(lib, "Engine.lib")
#endif

#include <EnginePCH.h>

//#include <Scene/GameObject/GameObject.h>
#include <Scene/Actor/Base/ActorInclusion.h>
#include <Scene/Component/Transform.h>

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	virtual void Action() = 0;
};

class GroundMonster : public GameObject
{
public:
	using GameObject::GameObject;
	virtual ~GroundMonster() = default;

	virtual void Action() override
	{
		printf("지상 이동중!\n");
	}
};

class FlyMonster : public GameObject
{
public:
	using GameObject::GameObject;
	virtual ~FlyMonster() = default;

	virtual void Action() override
	{
		printf("공중 이동중!\n");
	}
};

// 망한 거임
class GroundAndFlyMonster : public GroundMonster, public FlyMonster
{
public:
	using GroundMonster::GroundMonster;
	using FlyMonster::FlyMonster;
	virtual ~GroundAndFlyMonster() = default;

	virtual void Action() override
	{
		GroundMonster::Action();
		FlyMonster::Action();
	}
};

////////////////////////////////////////////////////
class IMonster
{
public:
	IMonster() = default;
	virtual ~IMonster() = default;

	virtual void Action() = 0;
};

class Monster : public IMonster
{
public:
	using IMonster::IMonster;
	virtual ~Monster() = default;

	virtual void Action() override
	{
		printf("몬스터의 행동!\n");
	}
};

class MonsterDecorator : public IMonster
{
public:
	MonsterDecorator(IMonster* pBase) { m_pBase = pBase; }
	virtual ~MonsterDecorator() { SAFE_DELETE(m_pBase); }

	virtual void Action() override
	{
		m_pBase->Action();
	}

private:
	IMonster* m_pBase = nullptr;
};

class GroundAbility : public MonsterDecorator
{
public:
	using MonsterDecorator::MonsterDecorator;
	virtual ~GroundAbility() = default;

	virtual void Action() override
	{
		MonsterDecorator::Action();
		printf("지상 이동중!\n");
	}
};

class FlyAbility : public MonsterDecorator
{
public:
	using MonsterDecorator::MonsterDecorator;
	virtual ~FlyAbility() = default;

	virtual void Action() override
	{
		MonsterDecorator::Action();
		printf("공중 이동중!\n");
	}
};

Int32 main()
{
	GroundMonster groundMonster;
	groundMonster.Action();
	printf("\n");

	FlyMonster flyMonster;
	flyMonster.Action();
	printf("\n");

	GroundAndFlyMonster groundAndFlyMonster;
	groundAndFlyMonster.Action();
	printf("\n");

	////////////////////////////////////////////////////
	printf("\n");
	printf("\n");
	printf("<데코레이터 패턴 적용>\n");

	IMonster* pGroundMonster = new GroundAbility(new Monster);
	pGroundMonster->Action();
	SAFE_DELETE(pGroundMonster);

	printf("\n");
	IMonster* pFlyMonster = new FlyAbility(new Monster);
	pFlyMonster->Action();
	SAFE_DELETE(pFlyMonster);

	printf("\n");
	IMonster* pGroundAndFlyMonster = new GroundAbility(new FlyAbility(new Monster));
	pGroundAndFlyMonster->Action();
	SAFE_DELETE(pGroundAndFlyMonster);
	printf("\n");

	return 0;
}