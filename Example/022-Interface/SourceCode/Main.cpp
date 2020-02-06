// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
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

// ���� ���� �Լ��� ���ִ� Ŭ������ �������̽���� �ؿ�.
// ������ �������̽��� �� �� ���� �ǹ̷� �ܺο� �����Ǵ� Ŭ������ ����Լ��� ���ϱ⵵ ����.
// C++���� �������̽��� �ǹ��ϴ� Ű���尡 ���� ��� �ǹ̰� Ȯ��Ǿ��ٰ� �� �� �־��!
class IAction
{
public:
	virtual void Walk() = 0; // ��� �ް� �Ǹ� �ݵ�� ���� �ʼ�!
};

class Monster : public IAction
{
public:
	virtual void Walk() override
	{
		printf("�̰� ���̸� �ȴ� ������ �������ּ���!\n");
	}
};

class Snail : public Monster
{
public:
	virtual void Walk() override
	{
		printf("�����̰� ���ٴϰ� �־��.\n");
	}
};

class Slime : public Monster
{
public:
	virtual void Walk() override
	{
		printf("�������� �پ�ٴϰ� �־��.\n");
	}
};

class Wraith : public Monster
{
public:
	virtual void Walk() override
	{
		printf("���̽��� ���ƴٴϰ� �־��.\n");
	}
};

//////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
Int32 main()
{
	// �޸� ������ Ȯ���ϴ� ����̿���.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// �����̳ʿ� ����Ʈ �����͸� �ִ� �� ��� C++���� �����ϴ� ���!
	std::vector<std::unique_ptr<Monster>> vecMonster;

	// ����Ʈ �����͸� �̿��ϸ� �޸� ������ �����ο�����!
	vecMonster.emplace_back(std::make_unique<Snail>());
	vecMonster.emplace_back(std::make_unique<Slime>());
	vecMonster.emplace_back(std::make_unique<Wraith>());

	// �����̳ʸ� ��ȸ�ϸ� Walk �������̽��� ȣ���ϸ� RTTI(RunTime Type Information)��
	// ����Ǹ鼭 ���� �ν��Ͻ��� �ش�Ǵ� Walk�� ȣ��ȴٴ� �� �� ���μ���!
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