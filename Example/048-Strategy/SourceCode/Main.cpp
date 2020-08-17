// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
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

			// ���ø����� ����� �� ������ �����ϰ� std::vector��...
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
				printf("���������� �����մϴ�!\n");
			}
		};

		class SelectionSorter : public ISortStrategy
		{
		public:
			SelectionSorter() = default;
			virtual ~SelectionSorter() = default;

			virtual void OnExcute(std::vector<int>& vec) override
			{
				printf("���������� �����մϴ�!\n");
			}
		};

		class InsertionSorter : public ISortStrategy
		{
		public:
			InsertionSorter() = default;
			virtual ~InsertionSorter() = default;

			virtual void OnExcute(std::vector<int>& vec) override
			{
				printf("�������� �����մϴ�!\n");
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
			printf("<�⺻ Strategy �׽�Ʈ!>\n\n");

			Context context;
			printf("ConcreteStrategyA �׽�Ʈ!\n");
			context.setStrategy(new ConcreteStrategyA());
			context.doSomething();
			printf("\n");

			printf("ConcreteStrategyB �׽�Ʈ!\n");
			context.setStrategy(new ConcreteStrategyB());
			context.doSomething();
			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<���� ���� �׽�Ʈ!>\n\n");

			SortTester sortTester;
			std::vector<int> vec{ 1, 5, 3, 8, 2 };
			printf("��ǰ������ �õ��մϴ�!\n");
			sortTester.Sort(vec);
			printf("\n");

			printf("���������� �õ��մϴ�!\n");
			sortTester.setStrategy(new SelectionSorter());
			sortTester.Sort(vec);
			printf("\n");

			printf("���������� �õ��մϴ�!\n");
			sortTester.setStrategy(new InsertionSorter());
			sortTester.Sort(vec);
			printf("\n");
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
int main()
{
	//unit_test::basic::Test();

	unit_test::use_pattern::Test();
	return 0;
}