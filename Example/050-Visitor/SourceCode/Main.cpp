// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
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

			// ElementA만의 함수
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

			// ElementB만의 함수
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

			// 부모 클래스의 인터페이스에 전부 제공해야 해요!
			// 어떤 객체가 전달되었는지 정확하게 알아야 합니다!
			virtual void visit(ElementA* e) abstract;
			virtual void visit(ElementB* e) abstract;
		};

		class ConcreteVisitorA : public Visitor
		{
		public:
			ConcreteVisitorA() = default;
			virtual ~ConcreteVisitorA() = default;

			// 부모 클래스의 인터페이스에 전부 제공해야 해요!
			// 어떤 객체가 전달되었는지 정확하게 알아야 합니다!
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

			// 부모 클래스의 인터페이스에 전부 제공해야 해요!
			// 어떤 객체가 전달되었는지 정확하게 알아야 합니다!
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

			// Functor처럼 () 연산자를 오버라이딩해야 해요!
			void operator()(ElementA& elementA)
			{
				printf("ConcreteVisitorA의 ElementA 방문!\n");
				elementA.FeatureA();
			}

			// Functor처럼 () 연산자를 오버라이딩해야 해요!
			void operator()(ElementB& elementB)
			{
				printf("ConcreteVisitorA의 ElementB 방문!\n");
				elementB.FeatureB();
			}
		};

		class ConcreteVisitorB : public Visitor
		{
		public:
			ConcreteVisitorB() = default;
			virtual ~ConcreteVisitorB() = default;

			// Functor처럼 () 연산자를 오버라이딩해야 해요!
			void operator()(ElementA& elementA)
			{
				printf("ConcreteVisitorA의 ElementA 방문!\n");
				elementA.FeatureA();
			}

			// Functor처럼 () 연산자를 오버라이딩해야 해요!
			void operator()(ElementB& elementB)
			{
				printf("ConcreteVisitorB의 ElementB 방문!\n");
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
				printf("고블린의 지상 공격!\n");
			}
		};

		class Shark : public IMonster
		{
		public:
			Shark() = default;
			virtual ~Shark() = default;

			void SeaAttack()
			{
				printf("상어의 해상 공격!\n");
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
				printf("고블린 공격력 강화!\n");
				goblin.GroundAttack();
			}

			void operator()(Shark& shark)
			{
				printf("상어 공격력 강화!\n");
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
			printf("<기본 Visitor 테스트!>\n\n");

			Element* pElementA = new ElementA();
			Element* pElementB = new ElementB();
			
#pragma region ConcreteVisitorA 테스트
			Visitor* pVisitor = new ConcreteVisitorA();
			printf("ConcreteVisitorA가 ElementA를 방문합니다!\n");
			pElementA->accept(pVisitor);

			printf("\n");
			printf("ConcreteVisitorA가 ElementB를 방문합니다!\n");
			pElementB->accept(pVisitor);
#pragma endregion

			delete pVisitor;
			pVisitor = new ConcreteVisitorB();
			printf("\n\n");

#pragma region ConcreteVisitorB 테스트
			printf("ConcreteVisitorB가 ElementA를 방문합니다!\n");
			pElementA->accept(pVisitor);

			printf("\n");
			printf("ConcreteVisitorB가 ElementB를 방문합니다!\n");
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
			printf("<패턴 변형 테스트!>\n\n");

			// 템플릿으로 공용체를 사용한다고 생각하면 됩니다!
			std::variant<ElementA, ElementB> variant;

			variant = ElementA();
			ConcreteVisitorA visitorA = ConcreteVisitorA();
			printf("ConcreteVisitorA가 ElementA를 방문합니다!\n");
			std::visit(visitorA, variant);
			printf("\n");

			variant = ElementB();
			printf("ConcreteVisitorA가 ElementB를 방문합니다!\n");
			std::visit(visitorA, variant);
			printf("\n\n");

			variant = ElementA();
			ConcreteVisitorB visitorB = ConcreteVisitorB();
			printf("ConcreteVisitorB가 ElementA를 방문합니다!\n");
			std::visit(visitorB, variant);
			printf("\n");

			variant = ElementB();
			printf("ConcreteVisitorB가 ElementB를 방문합니다!\n");
			std::visit(visitorB, variant);
			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<패턴 적용 테스트!>\n\n");

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
// 프로그램이 시작되는 곳이에요.
int main()
{
	//unit_test::basic::Test();
	//unit_test::variation::Test();

	//unit_test::use_pattern::Test();
	return 0;
}