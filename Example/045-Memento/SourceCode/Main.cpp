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
		class Originator
		{
		public:
			Originator() = default;
			~Originator() = default;

			class Memento
			{
			private:
				// �ܺο����� ���� ����
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
			printf("��ǥ: (%d, %d)\n", info.x, info.y);
		}

		class Player
		{
		public:
			Player() = default;
			~Player() = default;

			class Memento
			{
			private:
				// �ܺο����� ���� ����
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

			// ��ǥ Ȯ���� ���� �ӽ÷� ���� �Լ�
			void ShowPos() const
			{
				printf("��ǥ: (%d, %d)\n", m_info.x, m_info.y);
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
			printf("<�⺻ Memento �׽�Ʈ!>\n\n");

			printf("Originator�� ���� ����!\n");
			Originator originator;
			originator.setState(2);
			originator.showState();
			printf("\n");

			printf("Caretaker�� ���� ����!\n");
			Caretaker caretaker(&originator);
			caretaker.doSomething();

			printf("Originator ���� ����!\n");
			originator.setState(999);
			originator.showState();
			printf("\n");

			printf("Caretaker�� ���� ����!\n");
			caretaker.undo();
			originator.showState();
			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<���� ���� �׽�Ʈ!>\n\n");

			printf("Player�� �����ϰ� Caretaker�� ����!\n");
			Player player;
			Caretaker caretaker(&player);
			printf("\n");

			// Observer�� �̿��ϸ� ���� ĸó�� �� �־��!
			// ������ ������ Memento�� �˾ƺ��� ���̴ϱ� �׳� ĸó�ҰԿ�.
			std::srand(static_cast<unsigned int>(std::time(nullptr)));

			printf("Player ��ǥ ������ ����!\n");
			for (int i = 0; i < 10; ++i)
			{
				player.setPos(std::rand() % 100, std::rand() % 100);
				player.ShowPos();

				caretaker.CaptureSnapshot();
			}
			printf("\n");

			printf("Player ���÷���!\n");
			caretaker.Replay();
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