// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>

namespace unit_test
{
	namespace basic
	{
		class Handler abstract
		{
		public:
			Handler() = default;
			virtual ~Handler() = default;

			virtual void setNext(Handler* h) abstract;
			virtual void handle(int request) abstract;
		};

		class BaseHandler : public Handler
		{
		public:
			using Handler::Handler;

			virtual ~BaseHandler()
			{
				if (next != nullptr)
				{
					delete next;
				}
			}

			virtual bool canHandle(int request) abstract;

			virtual void setNext(Handler* h) override
			{
				if (next != nullptr)
				{
					delete next;
				}

				next = h;
			}

			virtual void handle(int request) override
			{
				printf("BaseHandler::handle()�� �۾� ���ѱ�!\n");

				if (next != nullptr)
				{
					next->handle(request);
				}
			}

		private:
			Handler* next = nullptr;
		};

		class ConcreteHandlerA : public BaseHandler
		{
		public:
			using BaseHandler::BaseHandler;
			virtual ~ConcreteHandlerA() = default;

			virtual bool canHandle(int request) override
			{
				return true;
			}

			virtual void handle(int request) override
			{
				if (canHandle(request) == true)
				{
					printf("ConcreteHandlerA::handle()���� ó��!\n");
				}
				else
				{
					BaseHandler::handle(request);
				}
			}
		};

		class ConcreteHandlerB : public BaseHandler
		{
		public:
			using BaseHandler::BaseHandler;
			virtual ~ConcreteHandlerB() = default;

			virtual bool canHandle(int request) override
			{
				return false;
			}

			virtual void handle(int request) override
			{
				if (canHandle(request) == true)
				{
					printf("ConcreteHandlerB::handle()���� ó��!\n");
				}
				else
				{
					BaseHandler::handle(request);
				}
			}
		};
	}

	namespace variation
	{
		class IHandlerChain abstract
		{
		public:
			IHandlerChain() = default;
			virtual ~IHandlerChain() = default;

			virtual void OnHandle(int request) abstract;
		};

		class BaseHandlerChain : public IHandlerChain
		{
		public:
			BaseHandlerChain() = default;

			virtual ~BaseHandlerChain()
			{
				ReleaseHandler();
			}

			virtual bool OnCanHandle(int request) abstract;

			void ReleaseHandler()
			{
				if (m_pNextHandler != nullptr)
				{
					delete m_pNextHandler;
				}
			}

			virtual void OnHandle(int request) override
			{
				printf("BaseHandlerChain::OnHandle()�� �۾� ���ѱ�!\n");

				if (m_pNextHandler != nullptr)
				{
					m_pNextHandler->OnHandle(request);
				}
			}

			void setNextHandler(BaseHandlerChain* pHandler)
			{
				ReleaseHandler();
				m_pNextHandler = pHandler;
			}

		private:
			BaseHandlerChain* m_pNextHandler = nullptr;
		};

		class ConcreteHandlerA : public BaseHandlerChain
		{
		public:
			using BaseHandlerChain::BaseHandlerChain;
			virtual ~ConcreteHandlerA() = default;

			virtual bool OnCanHandle(int request) override
			{
				return true;
			}

			virtual void OnHandle(int request) override
			{
				if (OnCanHandle(request) == true)
				{
					printf("ConcreteHandlerA::OnHandle()���� ó��!\n");
				}
				else
				{
					BaseHandlerChain::OnHandle(request);
				}
			}
		};

		class ConcreteHandlerB : public BaseHandlerChain
		{
		public:
			ConcreteHandlerB()
			{
				setNextHandler(new ConcreteHandlerA());
			}

			virtual ~ConcreteHandlerB() = default;

			virtual bool OnCanHandle(int request) override
			{
				return false;
			}

			virtual void OnHandle(int request) override
			{
				if (OnCanHandle(request) == true)
				{
					printf("ConcreteHandlerB::OnHandle()���� ó��!\n");
				}
				else
				{
					BaseHandlerChain::OnHandle(request);
				}
			}
		};
	}

	namespace use_pattern
	{
		class BaseHandlerChain
		{
		public:
			BaseHandlerChain() = default;

			virtual ~BaseHandlerChain()
			{
				ReleaseHandler();
			}

			void ReleaseHandler()
			{
				if (m_pNextHandler != nullptr)
				{
					delete m_pNextHandler;
				}
			}

			BaseHandlerChain* getNextHandler() const
			{
				return m_pNextHandler;
			}

			void setNextHandler(BaseHandlerChain* pHandler)
			{
				ReleaseHandler();
				m_pNextHandler = pHandler;
			}

		private:
			BaseHandlerChain* m_pNextHandler = nullptr;
		};

		class BattlePhaseChain : public BaseHandlerChain
		{
		public:
			BattlePhaseChain() = default;
			virtual ~BattlePhaseChain() = default;

			virtual void OnTestHP(int HP) abstract;

			BattlePhaseChain* getNextHandler() const
			{
				return dynamic_cast<BattlePhaseChain*>(BaseHandlerChain::getNextHandler());
			}
		};

		class FirstBattlePhase : public BattlePhaseChain
		{
		public:
			FirstBattlePhase();
			virtual ~FirstBattlePhase() = default;

			virtual void OnTestHP(int HP) override
			{
				if (HP > 75)
				{
					printf("ù ��° ���� ������!\n");
				}
				else
				{
					BattlePhaseChain::getNextHandler()->OnTestHP(HP);
				}
			}
		};

		class SecondBattlePhase : public BattlePhaseChain
		{
		public:
			SecondBattlePhase();
			virtual ~SecondBattlePhase() = default;

			virtual void OnTestHP(int HP) override
			{
				if (HP > 50)
				{
					printf("�� ��° ���� ������!\n");
				}
				else
				{
					BattlePhaseChain::getNextHandler()->OnTestHP(HP);
				}
			}
		};

		class ThirdBattlePhase : public BattlePhaseChain
		{
		public:
			using BattlePhaseChain::BattlePhaseChain;
			virtual ~ThirdBattlePhase() = default;

			virtual void OnTestHP(int HP) override
			{
				printf("�� ��° ���� ������!\n");
			}
		};

		FirstBattlePhase::FirstBattlePhase()
		{
			setNextHandler(new SecondBattlePhase());
		}

		SecondBattlePhase::SecondBattlePhase()
		{
			setNextHandler(new ThirdBattlePhase());
		}
	}
}

namespace unit_test
{
	namespace basic
	{
		void Test()
		{
			printf("<�⺻ Chain Of Responsibility �׽�Ʈ!>\n\n");

#pragma region A->B �׽�Ʈ
			printf("A->B �׽�Ʈ!\n");
			Handler* pHandle1 = new ConcreteHandlerA();
			Handler* pHandle2 = new ConcreteHandlerB();

			pHandle1->setNext(pHandle2);
			pHandle1->handle(0);

			delete pHandle1;
#pragma endregion

			printf("\n");

#pragma region B->A �׽�Ʈ
			printf("B->A �׽�Ʈ!\n");

			Handler* pHandle3 = new ConcreteHandlerA();
			Handler* pHandle4 = new ConcreteHandlerB();

			pHandle4->setNext(pHandle3);
			pHandle4->handle(0);

			delete pHandle4;
#pragma endregion

			printf("\n");
		}
	}

	namespace variation
	{
		void Test()
		{
			printf("<���� ���� �׽�Ʈ!>\n\n");

			BaseHandlerChain* pHandler = new ConcreteHandlerB();
			pHandler->OnHandle(0);
			delete pHandler;

			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<���� ���� �׽�Ʈ!>\n\n");

			BattlePhaseChain* pBattlePhase = new FirstBattlePhase();

			printf("HP�� 90���� ����!\n");
			pBattlePhase->OnTestHP(90);
			printf("\n");

			printf("HP�� 70���� ����!\n");
			pBattlePhase->OnTestHP(70);
			printf("\n");

			printf("HP�� 30���� ����!\n");
			pBattlePhase->OnTestHP(30);

			delete pBattlePhase;
			printf("\n");
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
int main()
{
	//unit_test::basic::Test();
	//unit_test::variation::Test();

	//unit_test::use_pattern::Test();
	return 0;
}