// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <crtdbg.h>
#include <cstdio>
#include <memory>
#include <vector>

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__ )                                            
#endif

using Int32 = signed __int32;
using Real32 = float;

// 순수 가상 함수만 모여있는 클래스를 인터페이스라고 해요.
// 하지만 인터페이스는 좀 더 넓은 의미로 외부에 공개되는 클래스의 멤버함수를 뜻하기도 하죠.
// C++에는 인터페이스를 의미하는 키워드가 따로 없어서 의미가 확장되었다고 할 수 있어요!
class IAction
{
public:
	virtual void Walk() = 0; // 상속 받게 되면 반드시 정의 필수!
};

class Monster : public IAction
{
public:
	virtual void Walk() override
	{
		printf("이게 보이면 걷는 동작을 정의해주세요!\n");
	}
};

class Snail : public Monster
{
public:
	virtual void Walk() override
	{
		printf("달팽이가 기어다니고 있어요.\n");
	}
};

class Slime : public Monster
{
public:
	virtual void Walk() override
	{
		printf("슬라임이 뛰어다니고 있어요.\n");
	}
};

class Wraith : public Monster
{
public:
	virtual void Walk() override
	{
		printf("레이스가 날아다니고 있어요.\n");
	}
};

//////////////////////////////////////////////////////////////////////////
// 프로그램이 시작되는 곳이에요.
Int32 main()
{
	// 메모리 누수를 확인하는 방법이에요.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 컨테이너에 스마트 포인터를 넣는 건 모던 C++에서 권장하는 방식!
	std::vector<std::unique_ptr<Monster>> vecMonster;

	// 스마트 포인터를 이용하면 메모리 릭에서 자유로워져요!
	vecMonster.emplace_back(std::make_unique<Snail>());
	vecMonster.emplace_back(std::make_unique<Slime>());
	vecMonster.emplace_back(std::make_unique<Wraith>());

	// 컨테이너를 순회하며 Walk 인터페이스를 호출하면 RTTI(RunTime Type Information)가
	// 적용되면서 실제 인스턴스에 해당되는 Walk가 호출된다는 걸 잘 봐두세요!
	for (const auto& iter : vecMonster)
	{
		if (iter == nullptr)
		{
			continue;
		}

		iter->Walk();
	}

	return 0;
}