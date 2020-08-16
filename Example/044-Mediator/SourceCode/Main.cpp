// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <vector>
#include <string>
#include <functional>

namespace unit_test
{
	namespace basic
	{
		// 전방 선언 필수!
		class Component;

		class Mediator abstract
		{
		public:
			Mediator() = default;
			virtual ~Mediator() = default;

			virtual void notify(const Component* pSender) abstract;
		};

		class Component
		{
		public:
			Component() = default;
			virtual ~Component() = default;

			Mediator* getMediator() const
			{
				return m;
			}

			void setMediator(Mediator* m)
			{
				this->m = m;
			}

		private:
			Mediator* m = nullptr;
		};

		class ComponentA : public Component
		{
		public:
			using Component::Component;
			virtual ~ComponentA() = default;

			void operationA()
			{
				printf("ComponentA::operationA()\n");
				getMediator()->notify(this);
			}
		};

		class ComponentB : public Component
		{
		public:
			using Component::Component;
			virtual ~ComponentB() = default;

			void operationB()
			{
				printf("ComponentB::operationB()\n");
				getMediator()->notify(this);
			}
		};

		class ConcreteMediator : public Mediator
		{
		public:
			ConcreteMediator(ComponentA* componentA, ComponentB* componentB)
			{
				this->componentA = componentA;
				this->componentA->setMediator(this);

				this->componentB = componentB;
				this->componentB->setMediator(this);
			}

			virtual ~ConcreteMediator() = default;

			virtual void notify(const Component* pSender) override
			{
				if (pSender == componentA)
				{
					reactOnA();
				}
				else if (pSender == componentB)
				{
					reactOnB();
				}
			}

			void reactOnA()
			{
				printf("ConcreteMediator::reactOnA()\n");
			}

			void reactOnB()
			{
				printf("ConcreteMediator::reactOnB()\n");
			}

		private:
			ComponentA* componentA = nullptr;
			ComponentB* componentB = nullptr;
		};
	}

	namespace use_pattern
	{
		enum class EChatRoomActionType : int
		{
			JOIN = 0,
			SEND_MSG,
			OUT,
		};

		class ChatRoomMediator;

		class Player
		{
		public:
			Player(const std::string& strName) :
				m_strName(strName)
			{

			}

			virtual ~Player() = default;

			void JoinChatRoom(ChatRoomMediator* pChatRoomMediator);
			void SendMsg(const std::string& strMsg);
			void OutChatRoom();

			ChatRoomMediator* getChatRoom() const
			{
				return m_pChatRoomMediator;
			}

			void setChatRoom(ChatRoomMediator* pChatRoomMediator)
			{
				m_pChatRoomMediator = pChatRoomMediator;
			}

			const std::string& getName() const
			{
				return m_strName;
			}

			const std::string& getMsg() const
			{
				return m_strMsg;
			}

		private:
			std::string m_strName;
			std::string m_strMsg;

			ChatRoomMediator* m_pChatRoomMediator = nullptr;
		};

		class ChatRoomMediator
		{
		public:
			ChatRoomMediator() = default;
			virtual ~ChatRoomMediator() = default;

			void AddPlayer(Player* pPlayer)
			{
				pPlayer->setChatRoom(this);
				m_vecPlayer.push_back(pPlayer);
			}

			void ErasePlayer(Player* pPlayer)
			{
				pPlayer->setChatRoom(nullptr);
				m_vecPlayer.erase(std::remove(m_vecPlayer.begin(), m_vecPlayer.end(), pPlayer));
			}

			void Notify(const Player* pSender, EChatRoomActionType chatRoomActionType)
			{
				std::function<void(const Player* pSender)> func;

				switch (chatRoomActionType)
				{
				case EChatRoomActionType::JOIN:
				{
					func = std::bind(&ChatRoomMediator::ReceiveEvent_Join, this, pSender);
					break;
				}

				case EChatRoomActionType::SEND_MSG:
				{
					func = std::bind(&ChatRoomMediator::ReceiveEvent_SendMsg, this, pSender);
					break;
				}

				case EChatRoomActionType::OUT:
				{
					func = std::bind(&ChatRoomMediator::ReceiveEvent_Out, this, pSender);
					break;
				}
				}

				for (const auto& iter : m_vecPlayer)
				{
					func(pSender);
					printf(" (로컬 주소: %p)\n", iter);
				}
			}

			void ReceiveEvent_Join(const Player* pSender)
			{
				printf("\"%s\"님이 방에 입장했습니다!", pSender->getName().c_str());
			}

			void ReceiveEvent_SendMsg(const Player* pSender)
			{
				printf("\"%s\": %s", pSender->getName().c_str(), pSender->getMsg().c_str());
			}

			void ReceiveEvent_Out(const Player* pSender)
			{
				printf("\"%s\"님이 방을 나갔습니다!", pSender->getName().c_str());
			}

		private:
			std::vector<Player*> m_vecPlayer;
		};

		void Player::JoinChatRoom(ChatRoomMediator* pChatRoomMediator)
		{
			setChatRoom(pChatRoomMediator);

			getChatRoom()->AddPlayer(this);
			getChatRoom()->Notify(this, EChatRoomActionType::JOIN);
		}

		void Player::SendMsg(const std::string& strMsg)
		{
			m_strMsg = strMsg;
			getChatRoom()->Notify(this, EChatRoomActionType::SEND_MSG);
		}

		void Player::OutChatRoom()
		{
			getChatRoom()->Notify(this, EChatRoomActionType::OUT);
			getChatRoom()->ErasePlayer(this);
		}
}
}

namespace unit_test
{
	namespace basic
	{
		void Test()
		{
			printf("<기본 Mediator 테스트!>\n\n");

			ComponentA componentA;
			ComponentB componentB;

			ConcreteMediator mediator(&componentA, &componentB);

			componentA.operationA();
			printf("\n");

			componentB.operationB();
			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<패턴 적용 테스트!>\n\n");

			Player player1("신규회원");
			Player player2("토끼겅듀");
			Player player3("잘익은김치");
			Player player4("블록덕후");

			printf("채팅방이 생성되었습니다!\n");
			ChatRoomMediator chatRoomMediator;

			player1.JoinChatRoom(&chatRoomMediator);
			player1.SendMsg("아무도 없음?");
			printf("\n");

			player2.JoinChatRoom(&chatRoomMediator);
			player2.SendMsg("안녕하세요~");
			printf("\n");

			player3.JoinChatRoom(&chatRoomMediator);
			printf("\n");

			player4.JoinChatRoom(&chatRoomMediator);
			player4.SendMsg("와 방에 사람 많네!");
			printf("\n");

			player3.OutChatRoom();
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