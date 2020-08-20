// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <cstdlib>

namespace unit_test
{
	namespace basic
	{
		class AbstractClass
		{
		public:
			AbstractClass() = default;
			virtual ~AbstractClass() = default;

			void step1() const
			{
				printf("AbstractClass::step1()\n");
			}

			void step2() const
			{
				printf("AbstractClass::step2()\n");
			}

			virtual void step3() abstract;
			virtual void step4() abstract;

			void templateMethod()
			{
				step1();
				step2();
				step3();
				step4();
			}
		};

		class ConcreteClassA : public AbstractClass
		{
		public:
			ConcreteClassA() = default;
			virtual ~ConcreteClassA() = default;

			virtual void step3() override
			{
				printf("ConcreteClassA::step3()\n");
			}

			virtual void step4() override
			{
				printf("ConcreteClassA::step4()\n");
			}
		};

		class ConcreteClassB : public AbstractClass
		{
		public:
			ConcreteClassB() = default;
			virtual ~ConcreteClassB() = default;

			virtual void step3() override
			{
				printf("ConcreteClassB::step3()\n");
			}

			virtual void step4() override
			{
				printf("ConcreteClassB::step4()\n");
			}
		};
	}

	namespace use_pattern
	{
		class Shop
		{
		public:
			Shop() = default;
			virtual ~Shop() = default;

			virtual void OnGreet() abstract;
			virtual void OnShowGoodsTable() abstract;
			virtual void OnGuide() abstract;

			void Enter()
			{
				OnGreet();
				OnShowGoodsTable();
				OnGuide();
			}
		};

		class Grocery : public Shop
		{
		public:
			Grocery() = default;
			virtual ~Grocery() = default;

			virtual void OnGreet() override
			{
				printf("식료품점에 잘 오셨습니다~!\n");
			}

			virtual void OnShowGoodsTable() override
			{
				printf("(다양한 식료품을 보여줌)\n");
			}

			virtual void OnGuide() override
			{
				printf("필요하신 게 있으시면 알려주세요.\n");
			}
		};

		class WeaponShop : public Shop
		{
		public:
			WeaponShop() = default;
			virtual ~WeaponShop() = default;

			virtual void OnGreet() override
			{
				printf("여어~ 무기점에 잘 왔어~!\n");
			}

			virtual void OnShowGoodsTable() override
			{
				printf("(다양한 장비를 보여줌)\n");
			}

			virtual void OnGuide() override
			{
				printf("필요한 게 있으면 말만하라구!\n");
			}
		};
	}
}

namespace unit_test
{
	namespace basic
	{
		void Test()
		{
			printf("<기본 Template Method 테스트!>\n\n");

			printf("ConcreteClassA 테스트!\n");
			ConcreteClassA classA;
			classA.templateMethod();
			printf("\n");

			printf("ConcreteClassB 테스트!\n");
			ConcreteClassB classB;
			classB.templateMethod();
			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<패턴 적용 테스트!>\n\n");

			printf("식료품점 입장 테스트!\n");
			Grocery grocery;
			grocery.Enter();
			printf("\n");

			printf("무기점 입장 테스트!\n");
			WeaponShop weaponShop;
			weaponShop.Enter();
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