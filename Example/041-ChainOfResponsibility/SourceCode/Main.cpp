// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
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
				printf("BaseHandler::handle()로 작업 떠넘김!\n");

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
					printf("ConcreteHandlerA::handle()에서 처리!\n");
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
					printf("ConcreteHandlerB::handle()에서 처리!\n");
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
				printf("BaseHandlerChain::OnHandle()로 작업 떠넘김!\n");

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
					printf("ConcreteHandlerA::OnHandle()에서 처리!\n");
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
					printf("ConcreteHandlerB::OnHandle()에서 처리!\n");
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
					printf("첫 번째 전투 페이즈!\n");
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
					printf("두 번째 전투 페이즈!\n");
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
				printf("세 번째 전투 페이즈!\n");
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
			printf("<기본 Chain Of Responsibility 테스트!>\n\n");

#pragma region A->B 테스트
			printf("A->B 테스트!\n");
			Handler* pHandle1 = new ConcreteHandlerA();
			Handler* pHandle2 = new ConcreteHandlerB();

			pHandle1->setNext(pHandle2);
			pHandle1->handle(0);

			delete pHandle1;
#pragma endregion

			printf("\n");

#pragma region B->A 테스트
			printf("B->A 테스트!\n");

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
			printf("<패턴 변형 테스트!>\n\n");

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
			printf("<패턴 적용 테스트!>\n\n");

			BattlePhaseChain* pBattlePhase = new FirstBattlePhase();

			printf("HP를 90으로 전달!\n");
			pBattlePhase->OnTestHP(90);
			printf("\n");

			printf("HP를 70으로 전달!\n");
			pBattlePhase->OnTestHP(70);
			printf("\n");

			printf("HP를 30으로 전달!\n");
			pBattlePhase->OnTestHP(30);

			delete pBattlePhase;
			printf("\n");
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// 프로그램이 시작되는 곳이에요.
int main()
{
	//unit_test::basic::Test();
	//unit_test::variation::Test();

	//unit_test::use_pattern::Test();
	return 0;
}