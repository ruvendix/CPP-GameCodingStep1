// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
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

			// C++에서는 기본형대로 코딩 불가능
			//virtual Iterator getNext() const abstract;

			virtual bool hasMore() const abstract;
		};

		class IterableCollection
		{
		public:
			IterableCollection() = default;
			virtual ~IterableCollection() = default;

			// C++에서는 기본형대로 코딩 불가능
			//virtual Iterator createIterator() abstract;
		};

		// 상호 참조이므로...
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
					printf("더 이상 요소가 없음!\n");
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
			printf("<기본 Iterator 테스트!>\n\n");

			ConcreteCollection collection;
			for (int i = 0; i < ConcreteCollection::MAX_ELEM; ++i)
			{
				collection.Add(i);
			}

			printf("Iterator 생성!\n");
			ConcreteIterator iterator = collection.createIterator();
			printf("iterator가 갖고 있는 값: %d\n", *iterator);
			printf("\n");

			for (int i = 0; i < ConcreteCollection::MAX_ELEM; ++i)
			{
				printf("Iterator 전진!\n");
				iterator.getNext();

				if (iterator.hasMore())
				{
					printf("iterator가 갖고 있는 값: %d\n", *iterator);
				}
				printf("\n");
			}

			printf("한번 더 전진해봄!\n");
			iterator.getNext();
			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<패턴 적용 테스트!>\n\n");

			const int MAX_ELEM = 4;

			std::array<int, MAX_ELEM> arr;
			for (int i = 0; i < MAX_ELEM; ++i)
			{
				arr[i] = i;
			}
			
			printf("앞에서부터 순회!\n");
			std::array<int, MAX_ELEM>::const_iterator forwardIter = arr.cbegin();
			std::array<int, MAX_ELEM>::const_iterator forwardIterEnd = arr.cend();
			for (/*초깃값 없음*/; forwardIter != forwardIterEnd; ++forwardIter)
			{
				printf("iter가 갖고 있는 값: %d\n", *forwardIter);
			}
			printf("\n");

			printf("뒤에서부터 순회!\n");
			std::array<int, MAX_ELEM>::const_reverse_iterator backwardIter = arr.crbegin();
			std::array<int, MAX_ELEM>::const_reverse_iterator backwardIterEnd = arr.crend();
			for (/*초깃값 없음*/; backwardIter != backwardIterEnd; ++backwardIter)
			{
				printf("iter가 갖고 있는 값: %d\n", *backwardIter);
			}
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