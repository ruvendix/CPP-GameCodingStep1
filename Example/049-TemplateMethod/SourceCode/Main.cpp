// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
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
				printf("�ķ�ǰ���� �� ���̽��ϴ�~!\n");
			}

			virtual void OnShowGoodsTable() override
			{
				printf("(�پ��� �ķ�ǰ�� ������)\n");
			}

			virtual void OnGuide() override
			{
				printf("�ʿ��Ͻ� �� �����ø� �˷��ּ���.\n");
			}
		};

		class WeaponShop : public Shop
		{
		public:
			WeaponShop() = default;
			virtual ~WeaponShop() = default;

			virtual void OnGreet() override
			{
				printf("����~ �������� �� �Ծ�~!\n");
			}

			virtual void OnShowGoodsTable() override
			{
				printf("(�پ��� ��� ������)\n");
			}

			virtual void OnGuide() override
			{
				printf("�ʿ��� �� ������ �����϶�!\n");
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
			printf("<�⺻ Template Method �׽�Ʈ!>\n\n");

			printf("ConcreteClassA �׽�Ʈ!\n");
			ConcreteClassA classA;
			classA.templateMethod();
			printf("\n");

			printf("ConcreteClassB �׽�Ʈ!\n");
			ConcreteClassB classB;
			classB.templateMethod();
			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<���� ���� �׽�Ʈ!>\n\n");

			printf("�ķ�ǰ�� ���� �׽�Ʈ!\n");
			Grocery grocery;
			grocery.Enter();
			printf("\n");

			printf("������ ���� �׽�Ʈ!\n");
			WeaponShop weaponShop;
			weaponShop.Enter();
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