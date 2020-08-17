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
				printf("ConcreteSubscriberA::update()가 받은 값: %d\n", context);
			}
		};

		class ConcreteSubscriberB : public Subscriber
		{
		public:
			ConcreteSubscriberB() = default;
			virtual ~ConcreteSubscriberB() = default;

			virtual void update(int context) override
			{
				printf("ConcreteSubscriberB::update()가 받은 값: %d\n", context);
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
			printf("MonsterSpawner::OnEvent() => 보스 몬스터를 소환합니다!\n");
		}

		void QuestMgr::OnEvent(const Player& player)
		{
			printf("QuestMgr::OnEvent() => 보스방 진입 퀘스트가 달성되었습니다!\n");
		}

		void AchievementMgr::OnEvent(const Player& player)
		{
			printf("AchievementMgr::OnEvent() => \"심연까지 가본 자\" 업적이 달성되었습니다!\n");
		}
	}
}

namespace unit_test
{
	namespace basic
	{
		void Test()
		{
			printf("<기본 Observer 테스트!>\n\n");

			// 구독자 생성!
			ConcreteSubscriberA subscriberA;
			ConcreteSubscriberB subscriberB;
			
			Publisher publisher;
			publisher.subscribe(&subscriberA);
			printf("subscriberA가 구독자가 되었습니다!\n");
			printf("\n");

			printf("이벤트를 발생시킵니다!\n");
			publisher.mainBusinesslogic(999);
			printf("\n");

			publisher.subscribe(&subscriberB);
			printf("subscriberB가 구독자가 되었습니다!\n");
			printf("\n");

			printf("이벤트를 발생시킵니다!\n");
			publisher.mainBusinesslogic(222);
			printf("\n");

			publisher.unsubscribe(&subscriberA);
			printf("subscriberA가 구독을 취소합니다!\n");
			printf("\n");

			printf("이벤트를 발생시킵니다!\n");
			publisher.mainBusinesslogic(777);
			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<패턴 적용 테스트!>\n\n");

			// 구독자 생성!
			MonsterSpawner monsterSpanwer;
			QuestMgr questMgr;
			AchievementMgr achievementMgr;

			Player player;
			printf("Player를 관심 대상으로 등록합니다!\n");
			player.Subscribe(&monsterSpanwer);
			player.Subscribe(&questMgr);
			player.Subscribe(&achievementMgr);
			printf("\n");

			printf("Player가 보스방에 진입했습니다!\n");
			player.EnterBossRoom();
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