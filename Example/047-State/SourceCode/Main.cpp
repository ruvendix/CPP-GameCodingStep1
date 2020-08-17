// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>

namespace unit_test
{
	namespace basic
	{
		class State abstract
		{
		public:
			State() = default;
			virtual ~State() = default;

			virtual void doThis() abstract;
			virtual void doThat() abstract;
		};

		class Context
		{
		public:
			Context(State* initialState) :
				state(initialState)
			{

			}

			~Context()
			{
				ReleaseState();
			}

			void ReleaseState()
			{
				if (state != nullptr)
				{
					delete state;
				}
			}

			void changeState(State* state)
			{
				ReleaseState();
				this->state = state;
			}

			void doThis()
			{
				state->doThis();
			}

			void doThat()
			{
				state->doThat();
			}

		private:
			State* state = nullptr;
		};

		class ConcreteStateA : public State
		{
		public:
			ConcreteStateA() = default;
			virtual ~ConcreteStateA() = default;

			virtual void doThis() override
			{
				printf("ConcreteStateA::doThis()\n");
			}

			virtual void doThat() override
			{
				printf("ConcreteStateA::doThat()\n");
			}
		};

		class ConcreteStateB : public State
		{
		public:
			ConcreteStateB() = default;
			virtual ~ConcreteStateB() = default;

			virtual void doThis() override
			{
				printf("ConcreteStateB::doThis()\n");
			}

			virtual void doThat() override
			{
				printf("ConcreteStateB::doThat()\n");
			}
		};
	}

	namespace use_pattern
	{
		class State abstract
		{
		public:
			State() = default;
			virtual ~State() = default;

			virtual void OnUpdate() abstract;
		};

		class Monster
		{
		public:
			Monster(); // �⺻ ���� �ʿ�!

			~Monster()
			{
				ReleaseState();
			}

			void ReleaseState()
			{
				if (m_pState != nullptr)
				{
					delete m_pState;
				}
			}

			void Update()
			{
				m_pState->OnUpdate();
			}

			void ChangeState(State* pState)
			{
				ReleaseState();
				m_pState = pState;
			}

			int getAttckDamage() const
			{
				return m_attackDamage;
			}

		private:
			int m_attackDamage = 10;

			State* m_pState = nullptr;
		};

		class MonsterState : public State
		{
		public:
			explicit MonsterState(Monster* pMonster) :
				m_pMonster(pMonster)
			{

			}

			virtual ~MonsterState() = default;

			virtual void OnUpdate() override
			{

			}

			Monster* getMonster() const
			{
				return m_pMonster;
			}

		private:
			Monster* m_pMonster = nullptr;
		};

		class MonsterIdleState : public MonsterState
		{
		public:
			using MonsterState::MonsterState;
			virtual ~MonsterIdleState() = default;

			virtual void OnUpdate() override;
		};

		class MonsterChaseState : public MonsterState
		{
		public:
			using MonsterState::MonsterState;
			virtual ~MonsterChaseState() = default;

			virtual void OnUpdate() override;
		};

		class MonsterAttackState : public MonsterState
		{
		public:
			using MonsterState::MonsterState;
			virtual ~MonsterAttackState() = default;

			virtual void OnUpdate() override;
		};

		Monster::Monster()
		{
			m_pState = new MonsterIdleState(this);
		}

		void MonsterIdleState::OnUpdate()
		{
			printf("���Ͱ� ���� �����Դϴ�!\n");

			if (true)
			{
				printf("���Ͱ� ���ѱ� �����մϴ�!\n");
				getMonster()->ChangeState(new MonsterChaseState(getMonster()));
			}
		}

		void MonsterChaseState::OnUpdate()
		{
			printf("���Ͱ� ��븦 ���Ѵ� ���Դϴ�!\n");

			if (true)
			{
				printf("���Ͱ� �����ϱ� �����մϴ�!\n");
				getMonster()->ChangeState(new MonsterAttackState(getMonster()));
			}
		}

		void MonsterAttackState::OnUpdate()
		{
			printf("������ �������� \"%d\"��ŭ�� ���ظ� �Ծ����ϴ�!\n", getMonster()->getAttckDamage());

			if (true)
			{
				printf("���Ͱ� �������κ��� ������ϴ�!\n");
				getMonster()->ChangeState(new MonsterIdleState(getMonster()));
			}
		}
	}
}

namespace unit_test
{
	namespace basic
	{
		void Test()
		{
			printf("<�⺻ State �׽�Ʈ!>\n\n");

			Context context(new ConcreteStateA());
			context.doThis();
			context.doThat();
			printf("\n");

			printf("���¸� �����մϴ�!\n");
			context.changeState(new ConcreteStateB());
			context.doThis();
			context.doThat();
			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<���� ���� �׽�Ʈ!>\n\n");

			printf("������ Idle ���¸� �׽�Ʈ�մϴ�!\n");
			Monster monster;
			monster.Update();
			printf("\n");

			printf("������ Chase ���¸� �׽�Ʈ�մϴ�!\n");
			monster.Update();
			printf("\n");

			printf("������ Attack ���¸� �׽�Ʈ�մϴ�!\n");
			monster.Update();
			printf("\n");

			printf("������ Idle ���¸� �׽�Ʈ�մϴ�!\n");
			monster.Update();
			printf("\n");
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
int main()
{
	//unit_test::basic::Test();

	//unit_test::use_pattern::Test();
	return 0;
}