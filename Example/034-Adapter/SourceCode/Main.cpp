#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>

namespace unit_test
{
	namespace basic
	{
		struct SpecialData
		{
			int value = 0;
		};

		// 수정할 수 없는 외부 코드를 의미합니다. (라이브러리 같은 거)
		class Service final
		{
		public:
			Service() = default;
			~Service() = default;

			void serviceMethod(const SpecialData& specialData)
			{
				printf("전달 받은 value: %d\n", specialData.value);
			}
		};

		struct Data
		{
			int value = 10;
		};

		class ClientInterface abstract
		{
		public:
			ClientInterface() = default;
			virtual ~ClientInterface() = default;

			virtual void method(const Data& data) abstract;
		};

		// 이게 핵심 클래스!
		// 객체 Adapter입니다.
		class Adapter : public ClientInterface
		{
		public:
			Adapter(Service* pService)
			{
				adaptee = pService;
			}

			virtual ~Adapter()
			{
				delete adaptee;
			}

			virtual void method(const Data& data) override
			{
				printf("Data의 value: %d\n", data.value);

				SpecialData specialData;
				specialData.value = data.value; // 서로 다른 데이터를 호환시키는 과정
				printf("Data -> SpecialData로 변환!\n");

				adaptee->serviceMethod(specialData);
			}

		private:
			Service* adaptee = nullptr;
		};
	}

	namespace use_pattern
	{
		class RoundHole final
		{
		public:
			RoundHole(int radius) :
				m_radius(radius)
			{

			}

			~RoundHole() = default;

		private:
			int m_radius = 0;
		};

		class CirclePeg
		{
		public:
			CirclePeg() = default;
			virtual ~CirclePeg() = default;

			CirclePeg(int radius) :
				m_radius(radius)
			{

			}

			virtual int OnToRadius() const
			{
				return m_radius;
			}

		private:
			int m_radius = 0;
		};

		class SquarePeg
		{
		public:
			SquarePeg(int width) :
				m_width(width)
			{
				printf("사각못의 길이: %d\n", m_width);
			}

			virtual ~SquarePeg() = default;

			int getWidth() const
			{
				return m_width;
			}

		private:
			int m_width = 0;
		};

		class SquarePegAdapter : public CirclePeg
		{
		public:
			SquarePegAdapter(SquarePeg* pAdaptee)
			{
				m_pAdaptee = pAdaptee;
			}

			virtual ~SquarePegAdapter()
			{
				delete m_pAdaptee;
			}

			virtual int OnToRadius() const override
			{
				return (m_pAdaptee->getWidth() * static_cast<int>(std::sqrt(2.0f) / 2));
			}

		private:
			SquarePeg* m_pAdaptee = nullptr;
		};
	}
}

namespace unit_test
{
	namespace basic
	{
		void Test()
		{
			printf("<기본 Adapter 테스트!>\n\n");

			Adapter adapter(new Service());
			adapter.method(Data());

			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<패턴 적용 테스트!>\n\n");

			SquarePegAdapter adapter(new SquarePeg(5));
			printf("변환된 반지름 길이: %d\n", adapter.OnToRadius());

			printf("\n");
		}
	}
}

int main()
{
	//unit_test::basic::Test();

	//unit_test::use_pattern::Test();
	return 0;
}