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
		class Originator
		{
		public:
			Originator() = default;
			~Originator() = default;

			class Memento
			{
			private:
				// 외부에서의 접근 막기
				friend class Originator;
				friend class Caretaker;

				Memento(int state) :
					state(state)
				{

				}

				int getState() const
				{
					return state;
				}

			private:
				int state = 0;
			};

			Memento save() const
			{
				return Memento(state);
			}

			void restore(const Memento& m)
			{
				state = m.getState();
			}

			void showState() const
			{
				printf("state: %d\n", state);
			}

			void setState(int state)
			{
				this->state = state;
			}

		private:
			int state = 0;
		};

		class Caretaker
		{
		public:
			Caretaker(Originator* originator) :
				originator(originator)
			{

			}

			~Caretaker() = default;

			void doSomething()
			{
				history.push_back(originator->save());
			}

			void undo()
			{
				const Originator::Memento& m = history.back();
				originator->restore(m);
			}

		private:
			Originator* originator = nullptr;
			std::vector<Originator::Memento> history;
		};
	}

	namespace use_pattern
	{
		struct PlayerInfo
		{
			int x = 0;
			int y = 0;
		};

		void ShowPos(const PlayerInfo& info)
		{
			printf("좌표: (%d, %d)\n", info.x, info.y);
		}

		class Player
		{
		public:
			Player() = default;
			~Player() = default;

			class Memento
			{
			private:
				// 외부에서의 접근 막기
				friend class Player;
				friend class Caretaker;

				Memento(const PlayerInfo& info) :
					m_info(info)
				{

				}

				const PlayerInfo& getPlayerInfo() const
				{
					return m_info;
				}

			private:
				PlayerInfo m_info;
			};

			Memento Save() const
			{
				return Memento(m_info);
			}

			void Restore(const Memento& memento)
			{
				m_info = memento.getPlayerInfo();
			}

			// 좌표 확인을 위해 임시로 만든 함수
			void ShowPos() const
			{
				printf("좌표: (%d, %d)\n", m_info.x, m_info.y);
			}

			void setPos(int x, int y)
			{
				m_info.x = x;
				m_info.y = y;
			}

		private:
			PlayerInfo m_info;
		};

		class Caretaker
		{
		public:
			Caretaker(Player* pTarget) :
				m_pTarget(pTarget)
			{

			}

			~Caretaker() = default;

			void CaptureSnapshot()
			{
				m_vecMemento.push_back(m_pTarget->Save());
			}

			void Replay() const
			{
				for (auto& iter : m_vecMemento)
				{
					ShowPos(iter.getPlayerInfo());
				}
			}

		private:
			Player* m_pTarget = nullptr;
			std::vector<Player::Memento> m_vecMemento;
		};
	}
}

namespace unit_test
{
	namespace basic
	{
		void Test()
		{
			printf("<기본 Memento 테스트!>\n\n");

			printf("Originator에 상태 저장!\n");
			Originator originator;
			originator.setState(2);
			originator.showState();
			printf("\n");

			printf("Caretaker에 상태 저장!\n");
			Caretaker caretaker(&originator);
			caretaker.doSomething();

			printf("Originator 상태 변경!\n");
			originator.setState(999);
			originator.showState();
			printf("\n");

			printf("Caretaker로 상태 복구!\n");
			caretaker.undo();
			originator.showState();
			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<패턴 적용 테스트!>\n\n");

			printf("Player를 생성하고 Caretaker에 설정!\n");
			Player player;
			Caretaker caretaker(&player);
			printf("\n");

			// Observer를 이용하면 쉽게 캡처할 수 있어요!
			// 하지만 지금은 Memento를 알아보는 중이니까 그냥 캡처할게요.
			std::srand(static_cast<unsigned int>(std::time(nullptr)));

			printf("Player 좌표 무작위 설정!\n");
			for (int i = 0; i < 10; ++i)
			{
				player.setPos(std::rand() % 100, std::rand() % 100);
				player.ShowPos();

				caretaker.CaptureSnapshot();
			}
			printf("\n");

			printf("Player 리플레이!\n");
			caretaker.Replay();
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