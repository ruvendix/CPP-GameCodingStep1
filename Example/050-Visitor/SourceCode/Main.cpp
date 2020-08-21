// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <cstdlib>
#include <variant>
#include <vector>

namespace unit_test
{
	namespace basic
	{
		class Visitor;

		class Element abstract
		{
		public:
			Element() = default;
			virtual ~Element() = default;

			virtual void accept(Visitor* v) abstract;
		};

		class ElementA : public Element
		{
		public:
			ElementA() = default;
			virtual ~ElementA() = default;

			virtual void accept(Visitor* v) override;

			// ElementA���� �Լ�
			void featureA()
			{
				printf("ElementA::featureA()\n");
			}
		};

		class ElementB : public Element
		{
		public:
			ElementB() = default;
			virtual ~ElementB() = default;

			virtual void accept(Visitor* v) override;

			// ElementB���� �Լ�
			void featureB()
			{
				printf("ElementB::featureB()\n");
			}
		};

		class Visitor abstract
		{
		public:
			Visitor() = default;
			virtual ~Visitor() = default;

			// �θ� Ŭ������ �������̽��� ���� �����ؾ� �ؿ�!
			// � ��ü�� ���޵Ǿ����� ��Ȯ�ϰ� �˾ƾ� �մϴ�!
			virtual void visit(ElementA* e) abstract;
			virtual void visit(ElementB* e) abstract;
		};

		class ConcreteVisitorA : public Visitor
		{
		public:
			ConcreteVisitorA() = default;
			virtual ~ConcreteVisitorA() = default;

			// �θ� Ŭ������ �������̽��� ���� �����ؾ� �ؿ�!
			// � ��ü�� ���޵Ǿ����� ��Ȯ�ϰ� �˾ƾ� �մϴ�!
			virtual void visit(ElementA* e) override
			{
				printf("ConcreteVisitorA::visit(ElementA* e)\n");
				e->featureA();
			}

			virtual void visit(ElementB* e) override
			{
				printf("ConcreteVisitorA::visit(ElementB* e)\n");
				e->featureB();
			}
		};

		class ConcreteVisitorB : public Visitor
		{
		public:
			ConcreteVisitorB() = default;
			virtual ~ConcreteVisitorB() = default;

			// �θ� Ŭ������ �������̽��� ���� �����ؾ� �ؿ�!
			// � ��ü�� ���޵Ǿ����� ��Ȯ�ϰ� �˾ƾ� �մϴ�!
			virtual void visit(ElementA* e) override
			{
				printf("ConcreteVisitorB::visit(ElementA* e)\n");
				e->featureA();
			}

			virtual void visit(ElementB* e) override
			{
				printf("ConcreteVisitorB::visit(ElementB* e)\n");
				e->featureB();
			}
		};

		void ElementA::accept(Visitor* v)
		{
			v->visit(this);
		}

		void ElementB::accept(Visitor* v)
		{
			v->visit(this);
		}
	}

	namespace variation
	{
		class Element abstract
		{
		public:
			Element() = default;
			virtual ~Element() = default;
		};

		class ElementA : public Element
		{
		public:
			ElementA() = default;
			virtual ~ElementA() = default;

			void FeatureA()
			{
				printf("ElementA::FeatureA()\n");
			}
		};

		class ElementB : public Element
		{
		public:
			ElementB() = default;
			virtual ~ElementB() = default;

			void FeatureB()
			{
				printf("ElementB::FeatureB()\n");
			}
		};

		class Visitor abstract
		{
		public:
			Visitor() = default;
			virtual ~Visitor() = default;
		};

		class ConcreteVisitorA : public Visitor
		{
		public:
			ConcreteVisitorA() = default;
			virtual ~ConcreteVisitorA() = default;

			// Functoró�� () �����ڸ� �������̵��ؾ� �ؿ�!
			void operator()(ElementA& elementA)
			{
				printf("ConcreteVisitorA�� ElementA �湮!\n");
				elementA.FeatureA();
			}

			// Functoró�� () �����ڸ� �������̵��ؾ� �ؿ�!
			void operator()(ElementB& elementB)
			{
				printf("ConcreteVisitorA�� ElementB �湮!\n");
				elementB.FeatureB();
			}
		};

		class ConcreteVisitorB : public Visitor
		{
		public:
			ConcreteVisitorB() = default;
			virtual ~ConcreteVisitorB() = default;

			// Functoró�� () �����ڸ� �������̵��ؾ� �ؿ�!
			void operator()(ElementA& elementA)
			{
				printf("ConcreteVisitorA�� ElementA �湮!\n");
				elementA.FeatureA();
			}

			// Functoró�� () �����ڸ� �������̵��ؾ� �ؿ�!
			void operator()(ElementB& elementB)
			{
				printf("ConcreteVisitorB�� ElementB �湮!\n");
				elementB.FeatureB();
			}
		};
	}

	namespace use_pattern
	{
		class IMonster abstract
		{
		public:
			IMonster() = default;
			virtual ~IMonster() = default;
		};

		class Goblin : public IMonster
		{
		public:
			Goblin() = default;
			virtual ~Goblin() = default;

			void GroundAttack()
			{
				printf("����� ���� ����!\n");
			}
		};

		class Shark : public IMonster
		{
		public:
			Shark() = default;
			virtual ~Shark() = default;

			void SeaAttack()
			{
				printf("����� �ػ� ����!\n");
			}
		};

		class Visitor abstract
		{
		public:
			Visitor() = default;
			virtual ~Visitor() = default;
		};

		class MonsterPowerUp : public Visitor
		{
		public:
			MonsterPowerUp() = default;
			virtual ~MonsterPowerUp() = default;

			void operator()(Goblin& goblin)
			{
				printf("��� ���ݷ� ��ȭ!\n");
				goblin.GroundAttack();
			}

			void operator()(Shark& shark)
			{
				printf("��� ���ݷ� ��ȭ!\n");
				shark.SeaAttack();
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
			printf("<�⺻ Visitor �׽�Ʈ!>\n\n");

			Element* pElementA = new ElementA();
			Element* pElementB = new ElementB();
			
#pragma region ConcreteVisitorA �׽�Ʈ
			Visitor* pVisitor = new ConcreteVisitorA();
			printf("ConcreteVisitorA�� ElementA�� �湮�մϴ�!\n");
			pElementA->accept(pVisitor);

			printf("\n");
			printf("ConcreteVisitorA�� ElementB�� �湮�մϴ�!\n");
			pElementB->accept(pVisitor);
#pragma endregion

			delete pVisitor;
			pVisitor = new ConcreteVisitorB();
			printf("\n\n");

#pragma region ConcreteVisitorB �׽�Ʈ
			printf("ConcreteVisitorB�� ElementA�� �湮�մϴ�!\n");
			pElementA->accept(pVisitor);

			printf("\n");
			printf("ConcreteVisitorB�� ElementB�� �湮�մϴ�!\n");
			pElementB->accept(pVisitor);
#pragma endregion

			delete pVisitor;
			delete pElementA;
			delete pElementB;

			printf("\n");
		}
	}

	namespace variation
	{
		void Test()
		{
			printf("<���� ���� �׽�Ʈ!>\n\n");

			// ���ø����� ����ü�� ����Ѵٰ� �����ϸ� �˴ϴ�!
			std::variant<ElementA, ElementB> variant;

			variant = ElementA();
			ConcreteVisitorA visitorA = ConcreteVisitorA();
			printf("ConcreteVisitorA�� ElementA�� �湮�մϴ�!\n");
			std::visit(visitorA, variant);
			printf("\n");

			variant = ElementB();
			printf("ConcreteVisitorA�� ElementB�� �湮�մϴ�!\n");
			std::visit(visitorA, variant);
			printf("\n\n");

			variant = ElementA();
			ConcreteVisitorB visitorB = ConcreteVisitorB();
			printf("ConcreteVisitorB�� ElementA�� �湮�մϴ�!\n");
			std::visit(visitorB, variant);
			printf("\n");

			variant = ElementB();
			printf("ConcreteVisitorB�� ElementB�� �湮�մϴ�!\n");
			std::visit(visitorB, variant);
			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<���� ���� �׽�Ʈ!>\n\n");

			std::variant<Goblin, Shark> variantMonster = Goblin();
			std::get<Goblin>(variantMonster).GroundAttack();
			printf("\n");

			std::visit(MonsterPowerUp(), variantMonster);
			printf("\n\n");

			variantMonster = Shark();
			std::get<Shark>(variantMonster).SeaAttack();
			printf("\n");

			std::visit(MonsterPowerUp(), variantMonster);
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