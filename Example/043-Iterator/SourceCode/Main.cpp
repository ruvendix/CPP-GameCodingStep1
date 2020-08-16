// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <array>

namespace unit_test
{
	namespace basic
	{
		class Iterator abstract
		{
		public:
			Iterator() = default;
			virtual ~Iterator() = default;

			// C++������ �⺻����� �ڵ� �Ұ���
			//virtual Iterator getNext() const abstract;

			virtual bool hasMore() const abstract;
		};

		class IterableCollection
		{
		public:
			IterableCollection() = default;
			virtual ~IterableCollection() = default;

			// C++������ �⺻����� �ڵ� �Ұ���
			//virtual Iterator createIterator() abstract;
		};

		// ��ȣ �����̹Ƿ�...
		class ConcreteIterator;

		class ConcreteCollection : public IterableCollection
		{	
		public:
			static const int MAX_ELEM = 4;

			using IterableCollection::IterableCollection;
			virtual ~ConcreteCollection() = default;

			ConcreteIterator createIterator();

			void Add(int elem)
			{
				m_arrContainer[m_currentIdx] = elem;
				++m_currentIdx;
			}

			int* Begin()
			{
				return (&m_arrContainer[0]);
			}

			int* End()
			{
				return ((&m_arrContainer[0]) + MAX_ELEM);
			}

		private:
			int m_currentIdx = 0;
			std::array<int, MAX_ELEM> m_arrContainer;
		};

		class ConcreteIterator : public Iterator
		{
		public:
			ConcreteIterator(ConcreteCollection* collection)
			{
				this->collection = collection;
				iterationState = collection->Begin();
			}

			virtual ~ConcreteIterator() = default;

			virtual bool hasMore() const override
			{
				if (iterationState == collection->End())
				{
					printf("�� �̻� ��Ұ� ����!\n");
					return false;
				}

				return true;
			}

			void getNext()
			{
				if (hasMore() == false)
				{
					iterationState = collection->End();
					return;
				}

				++iterationState;
			}

			int operator*()
			{
				return *iterationState;
			}

		private:
			int* iterationState = nullptr;
			ConcreteCollection* collection = nullptr;
		};

		ConcreteIterator ConcreteCollection::createIterator()
		{
			return ConcreteIterator(this);
		}
	}
}

namespace unit_test
{
	namespace basic
	{
		void Test()
		{
			printf("<�⺻ Iterator �׽�Ʈ!>\n\n");

			ConcreteCollection collection;
			for (int i = 0; i < ConcreteCollection::MAX_ELEM; ++i)
			{
				collection.Add(i);
			}

			printf("Iterator ����!\n");
			ConcreteIterator iterator = collection.createIterator();
			printf("iterator�� ���� �ִ� ��: %d\n", *iterator);
			printf("\n");

			for (int i = 0; i < ConcreteCollection::MAX_ELEM; ++i)
			{
				printf("Iterator ����!\n");
				iterator.getNext();

				if (iterator.hasMore())
				{
					printf("iterator�� ���� �ִ� ��: %d\n", *iterator);
				}
				printf("\n");
			}

			printf("�ѹ� �� �����غ�!\n");
			iterator.getNext();
			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<���� ���� �׽�Ʈ!>\n\n");

			const int MAX_ELEM = 4;

			std::array<int, MAX_ELEM> arr;
			for (int i = 0; i < MAX_ELEM; ++i)
			{
				arr[i] = i;
			}
			
			printf("�տ������� ��ȸ!\n");
			std::array<int, MAX_ELEM>::const_iterator forwardIter = arr.cbegin();
			std::array<int, MAX_ELEM>::const_iterator forwardIterEnd = arr.cend();
			for (/*�ʱ갪 ����*/; forwardIter != forwardIterEnd; ++forwardIter)
			{
				printf("iter�� ���� �ִ� ��: %d\n", *forwardIter);
			}
			printf("\n");

			printf("�ڿ������� ��ȸ!\n");
			std::array<int, MAX_ELEM>::const_reverse_iterator backwardIter = arr.crbegin();
			std::array<int, MAX_ELEM>::const_reverse_iterator backwardIterEnd = arr.crend();
			for (/*�ʱ갪 ����*/; backwardIter != backwardIterEnd; ++backwardIter)
			{
				printf("iter�� ���� �ִ� ��: %d\n", *backwardIter);
			}
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