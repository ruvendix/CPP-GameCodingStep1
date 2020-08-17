// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
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
			Monster(); // 기본 상태 필요!

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
			printf("몬스터가 보통 상태입니다!\n");

			if (true)
			{
				printf("몬스터가 뒤쫓기 시작합니다!\n");
				getMonster()->ChangeState(new MonsterChaseState(getMonster()));
			}
		}

		void MonsterChaseState::OnUpdate()
		{
			printf("몬스터가 상대를 뒤쫓는 중입니다!\n");

			if (true)
			{
				printf("몬스터가 공격하기 시작합니다!\n");
				getMonster()->ChangeState(new MonsterAttackState(getMonster()));
			}
		}

		void MonsterAttackState::OnUpdate()
		{
			printf("몬스터의 공격으로 \"%d\"만큼의 피해를 입었습니다!\n", getMonster()->getAttckDamage());

			if (true)
			{
				printf("몬스터가 공격으로부터 벗어났습니다!\n");
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
			printf("<기본 State 테스트!>\n\n");

			Context context(new ConcreteStateA());
			context.doThis();
			context.doThat();
			printf("\n");

			printf("상태를 변경합니다!\n");
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
			printf("<패턴 적용 테스트!>\n\n");

			printf("몬스터의 Idle 상태를 테스트합니다!\n");
			Monster monster;
			monster.Update();
			printf("\n");

			printf("몬스터의 Chase 상태를 테스트합니다!\n");
			monster.Update();
			printf("\n");

			printf("몬스터의 Attack 상태를 테스트합니다!\n");
			monster.Update();
			printf("\n");

			printf("몬스터의 Idle 상태를 테스트합니다!\n");
			monster.Update();
			printf("\n");
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// 프로그램이 시작되는 곳이에요.
int main()
{
	//unit_test::basic::Test();

	//unit_test::use_pattern::Test();
	return 0;
}