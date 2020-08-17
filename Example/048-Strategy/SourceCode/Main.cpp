// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <cstdlib>
#include <vector>

namespace unit_test
{
	namespace basic
	{
		class Strategy abstract
		{
		public:
			Strategy() = default;
			virtual ~Strategy() = default;

			virtual void execute(int data) abstract;
		};

		class Context
		{
		public:
			Context() = default;
			
			~Context()
			{
				ReleaseStrategy();
			}

			void ReleaseStrategy()
			{
				if (strategy != nullptr)
				{
					delete strategy;
				}
			}

			void doSomething();

			void setStrategy(Strategy* strategy)
			{
				ReleaseStrategy();
				this->strategy = strategy;
			}

		private:
			Strategy* strategy = nullptr;
		};

		class ConcreteStrategyA : public Strategy
		{
		public:
			ConcreteStrategyA() = default;
			virtual ~ConcreteStrategyA() = default;

			virtual void execute(int data) override
			{
				printf("ConcreteStrategyA::execute() => data: %d\n", data);
			}
		};

		class ConcreteStrategyB : public Strategy
		{
		public:
			ConcreteStrategyB() = default;
			virtual ~ConcreteStrategyB() = default;

			virtual void execute(int data) override
			{
				printf("ConcreteStrategyB::execute() => data: %d\n", data);
			}
		};

		void Context::doSomething()
		{
			strategy->execute(0);
		}
	}

	namespace use_pattern
	{
		class ISortStrategy abstract
		{
		public:
			ISortStrategy() = default;
			virtual ~ISortStrategy() = default;

			// 템플릿으로 만드는 게 좋지만 간단하게 std::vector로...
			virtual void OnExcute(std::vector<int>& vec) abstract;
		};

		class SortTester
		{
		public:
			SortTester();

			~SortTester()
			{
				ReleaseStrategy();
			}

			void ReleaseStrategy()
			{
				if (m_pStrategy != nullptr)
				{
					delete m_pStrategy;
				}
			}

			void Sort(std::vector<int>& vec);

			void setStrategy(ISortStrategy* pStrategy)
			{
				ReleaseStrategy();
				m_pStrategy = pStrategy;
			}

		private:
			ISortStrategy* m_pStrategy = nullptr;
		};

		class BubbleSorter : public ISortStrategy
		{
		public:
			BubbleSorter() = default;
			virtual ~BubbleSorter() = default;

			virtual void OnExcute(std::vector<int>& vec) override
			{
				printf("버블정렬을 실행합니다!\n");
			}
		};

		class SelectionSorter : public ISortStrategy
		{
		public:
			SelectionSorter() = default;
			virtual ~SelectionSorter() = default;

			virtual void OnExcute(std::vector<int>& vec) override
			{
				printf("선택정렬을 실행합니다!\n");
			}
		};

		class InsertionSorter : public ISortStrategy
		{
		public:
			InsertionSorter() = default;
			virtual ~InsertionSorter() = default;

			virtual void OnExcute(std::vector<int>& vec) override
			{
				printf("삽입정렬 실행합니다!\n");
			}
		};

		SortTester::SortTester()
		{
			setStrategy(new BubbleSorter());
		}

		void SortTester::Sort(std::vector<int>& vec)
		{
			m_pStrategy->OnExcute(vec);
		}
	}
}

namespace unit_test
{
	namespace basic
	{
		void Test()
		{
			printf("<기본 Strategy 테스트!>\n\n");

			Context context;
			printf("ConcreteStrategyA 테스트!\n");
			context.setStrategy(new ConcreteStrategyA());
			context.doSomething();
			printf("\n");

			printf("ConcreteStrategyB 테스트!\n");
			context.setStrategy(new ConcreteStrategyB());
			context.doSomething();
			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<패턴 적용 테스트!>\n\n");

			SortTester sortTester;
			std::vector<int> vec{ 1, 5, 3, 8, 2 };
			printf("거품정렬을 시도합니다!\n");
			sortTester.Sort(vec);
			printf("\n");

			printf("선택정렬을 시도합니다!\n");
			sortTester.setStrategy(new SelectionSorter());
			sortTester.Sort(vec);
			printf("\n");

			printf("삽입정렬을 시도합니다!\n");
			sortTester.setStrategy(new InsertionSorter());
			sortTester.Sort(vec);
			printf("\n");
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// 프로그램이 시작되는 곳이에요.
int main()
{
	//unit_test::basic::Test();

	unit_test::use_pattern::Test();
	return 0;
}