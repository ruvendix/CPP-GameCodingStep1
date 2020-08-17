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
#include <typeinfo>

namespace unit_test
{
	namespace basic
	{
		class Subscriber abstract
		{
		public:
			Subscriber() = default;
			virtual ~Subscriber() = default;

			virtual void update(int context) abstract;
		};

		class ConcreteSubscriberA : public Subscriber
		{
		public:
			ConcreteSubscriberA() = default;
			virtual ~ConcreteSubscriberA() = default;

			virtual void update(int context) override
			{
				printf("ConcreteSubscriberA::update()�� ���� ��: %d\n", context);
			}
		};

		class ConcreteSubscriberB : public Subscriber
		{
		public:
			ConcreteSubscriberB() = default;
			virtual ~ConcreteSubscriberB() = default;

			virtual void update(int context) override
			{
				printf("ConcreteSubscriberB::update()�� ���� ��: %d\n", context);
			}
		};
		
		class Publisher
		{
		public:
			Publisher() = default;
			virtual ~Publisher() = default;

			void subscribe(Subscriber* s)
			{
				subscribers.push_back(s);
			}

			void unsubscribe(Subscriber* s)
			{
				subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), s));
			}

			void notifySubscribers()
			{
				for (auto& iter : subscribers)
				{
					if (iter == nullptr)
					{
						continue;
					}

					iter->update(mainState);
				}
			}

			void mainBusinesslogic(int mainState)
			{
				this->mainState = mainState;
				notifySubscribers();
			}

		private:
			int mainState = 0;
			std::vector<Subscriber*> subscribers;
		};
	}

	namespace use_pattern
	{
		class Player;

		class IPlayerObserver abstract
		{
		public:
			IPlayerObserver() = default;
			virtual ~IPlayerObserver() = default;

			virtual void OnEvent(const Player& player) abstract;
		};

		class MonsterSpawner : public IPlayerObserver
		{
		public:
			MonsterSpawner() = default;
			virtual ~MonsterSpawner() = default;

			virtual void OnEvent(const Player& player) override;
		};

		class QuestMgr : public IPlayerObserver
		{
		public:
			QuestMgr() = default;
			virtual ~QuestMgr() = default;

			virtual void OnEvent(const Player& player) override;
		};

		class AchievementMgr : public IPlayerObserver
		{
		public:
			AchievementMgr() = default;
			virtual ~AchievementMgr() = default;

			virtual void OnEvent(const Player& player) override;
		};

		class Player
		{
		public:
			Player() = default;
			virtual ~Player() = default;

			void Subscribe(IPlayerObserver* pObserver)
			{
				m_vecObserver.push_back(pObserver);
			}

			void Unsubscribe(IPlayerObserver* pObserver)
			{
				m_vecObserver.erase(std::remove(m_vecObserver.begin(), m_vecObserver.end(), pObserver));
			}

			void Notify()
			{
				for (auto& iter : m_vecObserver)
				{
					if (iter == nullptr)
					{
						continue;
					}

					iter->OnEvent(*this);
				}
			}

			void EnterBossRoom()
			{
				Notify();
			}

		private:
			std::vector<IPlayerObserver*> m_vecObserver;
		};

		void MonsterSpawner::OnEvent(const Player& player)
		{
			printf("MonsterSpawner::OnEvent() => ���� ���͸� ��ȯ�մϴ�!\n");
		}

		void QuestMgr::OnEvent(const Player& player)
		{
			printf("QuestMgr::OnEvent() => ������ ���� ����Ʈ�� �޼��Ǿ����ϴ�!\n");
		}

		void AchievementMgr::OnEvent(const Player& player)
		{
			printf("AchievementMgr::OnEvent() => \"�ɿ����� ���� ��\" ������ �޼��Ǿ����ϴ�!\n");
		}
	}
}

namespace unit_test
{
	namespace basic
	{
		void Test()
		{
			printf("<�⺻ Observer �׽�Ʈ!>\n\n");

			// ������ ����!
			ConcreteSubscriberA subscriberA;
			ConcreteSubscriberB subscriberB;
			
			Publisher publisher;
			publisher.subscribe(&subscriberA);
			printf("subscriberA�� �����ڰ� �Ǿ����ϴ�!\n");
			printf("\n");

			printf("�̺�Ʈ�� �߻���ŵ�ϴ�!\n");
			publisher.mainBusinesslogic(999);
			printf("\n");

			publisher.subscribe(&subscriberB);
			printf("subscriberB�� �����ڰ� �Ǿ����ϴ�!\n");
			printf("\n");

			printf("�̺�Ʈ�� �߻���ŵ�ϴ�!\n");
			publisher.mainBusinesslogic(222);
			printf("\n");

			publisher.unsubscribe(&subscriberA);
			printf("subscriberA�� ������ ����մϴ�!\n");
			printf("\n");

			printf("�̺�Ʈ�� �߻���ŵ�ϴ�!\n");
			publisher.mainBusinesslogic(777);
			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<���� ���� �׽�Ʈ!>\n\n");

			// ������ ����!
			MonsterSpawner monsterSpanwer;
			QuestMgr questMgr;
			AchievementMgr achievementMgr;

			Player player;
			printf("Player�� ���� ������� ����մϴ�!\n");
			player.Subscribe(&monsterSpanwer);
			player.Subscribe(&questMgr);
			player.Subscribe(&achievementMgr);
			printf("\n");

			printf("Player�� �����濡 �����߽��ϴ�!\n");
			player.EnterBossRoom();
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