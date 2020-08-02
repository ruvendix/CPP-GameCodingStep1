// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>

namespace unit_test
{
	namespace basic
	{
		class Product1 final
		{
		public:
			Product1() = default;
			~Product1() = default;

			void TestFunc()
			{
				printf("Product1: TestFunc() ȣ��!\n");
			}
		};

		class Product2 final
		{
		public:
			Product2() = default;
			~Product2() = default;

			void TestFunc()
			{
				printf("Product2: TestFunc() ȣ��!\n");
			}
		};

		class Builder abstract
		{
		public:
			Builder() = default;
			virtual ~Builder() = default;

			virtual void buildStepA() abstract;
			virtual void buildStepB() abstract;
			virtual void buildStepZ() abstract;

			virtual void reset() abstract;
		};

		class ConcreteBuilder1 final : public Builder
		{
		public:
			using Builder::Builder;
			virtual ~ConcreteBuilder1() = default;

			virtual void buildStepA() override
			{
				printf("Product1: buildStepA!\n");
			}

			virtual void buildStepB() override
			{
				printf("Product1: buildStepB!\n");
			}

			virtual void buildStepZ() override
			{
				printf("Product1: buildStepZ!\n");
			}

			virtual void reset() override
			{
				result = Product1();
				printf("Product1 �ʱ�ȭ!\n");
			}

			Product1& getResult()
			{
				return result;
			}

		private:
			Product1 result;
		};

		class ConcreteBuilder2 final : public Builder
		{
		public:
			using Builder::Builder;
			virtual ~ConcreteBuilder2() = default;

			virtual void buildStepA() override
			{
				printf("Product2: buildStepA!\n");
			}

			virtual void buildStepB() override
			{
				printf("Product2: buildStepB!\n");
			}

			virtual void buildStepZ() override
			{
				printf("Product2: buildStepZ!\n");
			}

			virtual void reset() override
			{
				result = Product2();
				printf("Product2 �ʱ�ȭ!\n");
			}

			Product2& getResult()
			{
				return result;
			}

		private:
			Product2 result;
		};

		enum class EBuildType
		{
			SIMPLE = 0,
			PERFECT,
		};

		class Director final
		{
		public:
			Director(Builder* builder)
			{
				this->builder = builder;
			}

			~Director()
			{
				delete builder;
			}

			void changeBuilder(Builder* builder)
			{
				if (this->builder != nullptr)
				{
					delete this->builder;
				}

				this->builder = builder;
			}

			void make(EBuildType buildType)
			{
				builder->reset();

				if (buildType == EBuildType::SIMPLE)
				{
					builder->buildStepA();
				}
				else if (buildType == EBuildType::PERFECT)
				{
					builder->buildStepA();
					builder->buildStepB();
					builder->buildStepZ();
				}
			}

		private:
			Builder* builder = nullptr;
		};
	}

	namespace variation
	{
		class Product abstract
		{
		public:
			Product() = default;
			virtual ~Product() = default;

			virtual void OnTest() abstract;
		};

		class ConcreteProductA final : public Product
		{
		public:
			using Product::Product;
			~ConcreteProductA() = default;

			virtual void OnTest() override
			{
				printf("ConcreteProductA: TestFunc() ȣ��!\n");
			}
		};

		class ConcreteProductB final : public Product
		{
		public:
			using Product::Product;
			~ConcreteProductB() = default;

			virtual void OnTest() override
			{
				printf("ConcreteProductB: TestFunc() ȣ��!\n");
			}
		};

		class Builder abstract
		{
		public:
			Builder() = default;
			virtual ~Builder() = default;

			virtual Builder& OnCreateProduct() abstract;
			virtual Builder& OnBuildPartA() abstract;
			virtual Builder& OnBuildPartB() abstract;
			virtual Builder& OnBuildPartC() abstract;
			virtual Builder& OnReset() abstract;	

			virtual Product& OnResult() abstract;

			Product* getProduct() const
			{
				return m_pProduct;
			}

			void setProduct(Product* pProduct)
			{
				if (m_pProduct != nullptr)
				{
					delete m_pProduct;
				}

				m_pProduct = pProduct;
			}

		private:
			Product* m_pProduct = nullptr;
		};

		class ConcreteBuilder1 final : public Builder
		{
		public:
			using Builder::Builder;
			virtual ~ConcreteBuilder1() = default;

			virtual Builder& OnCreateProduct() override
			{
				setProduct(new ConcreteProductA());
				return *this;
			}
			
			virtual Builder& OnBuildPartA() override
			{
				printf("ConcreteBuilder1: OnBuildPartA() ȣ��!\n");
				return *this;
			}

			virtual Builder& OnBuildPartB() override
			{
				printf("ConcreteBuilder1: OnBuildPartB() ȣ��!\n");
				return *this;
			}

			virtual Builder& OnBuildPartC() override
			{
				printf("ConcreteBuilder1: OnBuildPartC() ȣ��!\n");
				return *this;
			}

			virtual Builder& OnReset() override
			{
				Product* pProduct = getProduct();
				if (pProduct != nullptr)
				{
					delete pProduct;
				}

				setProduct(new ConcreteProductA());
				printf("ConcreteProductA �ʱ�ȭ!\n");

				return *this;
			}

			virtual ConcreteProductA& OnResult() override
			{
				return *(dynamic_cast<ConcreteProductA*>(getProduct()));
			}
		};

		class ConcreteBuilder2 final : public Builder
		{
		public:
			using Builder::Builder;
			virtual ~ConcreteBuilder2() = default;

			virtual Builder& OnCreateProduct() override
			{
				setProduct(new ConcreteProductB());
				return *this;
			}

			virtual Builder& OnBuildPartA() override
			{
				printf("ConcreteBuilder2: OnBuildPartA() ȣ��!\n");
				return *this;
			}

			virtual Builder& OnBuildPartB() override
			{
				printf("ConcreteBuilder2: OnBuildPartB() ȣ��!\n");
				return *this;
			}

			virtual Builder& OnBuildPartC() override
			{
				printf("ConcreteBuilder2: OnBuildPartC() ȣ��!\n");
				return *this;
			}

			virtual Builder& OnReset() override
			{
				Product* pProduct = getProduct();
				if (pProduct != nullptr)
				{
					delete pProduct;
				}

				setProduct(new ConcreteProductB());
				printf("ConcreteProductB �ʱ�ȭ!\n");

				return *this;
			}

			virtual ConcreteProductB& OnResult() override
			{
				return *(dynamic_cast<ConcreteProductB*>(getProduct()));
			}
		};

		enum class EBuildType
		{
			SIMPLE = 0,
			PERFECT,
		};

		class Director final
		{
		public:
			Director(Builder* pBuilder)
			{
				m_pBuilder = pBuilder;
			}

			~Director()
			{
				delete m_pBuilder;
			}

			void changeBuilder(Builder* pBuilder)
			{
				if (m_pBuilder != nullptr)
				{
					delete m_pBuilder;
				}

				m_pBuilder = pBuilder;
			}

			void make(EBuildType buildType)
			{
				m_pBuilder->OnReset();

				if (buildType == EBuildType::SIMPLE)
				{
					m_pBuilder->OnCreateProduct().
						OnBuildPartA();
				}
				else if (buildType == EBuildType::PERFECT)
				{
					m_pBuilder->OnCreateProduct().
						OnBuildPartA().
						OnBuildPartB().
						OnBuildPartC();
				}
			}

		private:
			Builder* m_pBuilder = nullptr;
		};
	}

	namespace use_pattern
	{
		class Robot abstract
		{
		public:
			Robot() = default;
			virtual ~Robot() = default;

			virtual void OnAttack() abstract;
		};

		class MiniRobot final : public Robot
		{
		public:
			using Robot::Robot;
			~MiniRobot() = default;

			virtual void OnAttack() override
			{
				printf("MiniRobot: ����!\n");
			}
		};

		class HugeRobot final : public Robot
		{
		public:
			using Robot::Robot;
			~HugeRobot() = default;

			virtual void OnAttack() override
			{
				printf("HugeRobot: ����!\n");
			}
		};

		class RobotBuilder abstract
		{
		public:
			RobotBuilder() = default;
			virtual ~RobotBuilder() = default;

			virtual RobotBuilder& OnCreateRobot() abstract;
			virtual RobotBuilder& OnEquipWeapon() abstract;
			virtual RobotBuilder& OnEquipWing() abstract;
			virtual RobotBuilder& OnEquipShield() abstract;
			virtual RobotBuilder& OnReset() abstract;

			virtual Robot& OnResult() abstract;

			Robot* getRobot() const
			{
				return m_pRobot;
			}

			void setRobot(Robot* pRobot)
			{
				if (m_pRobot != nullptr)
				{
					delete m_pRobot;
				}

				m_pRobot = pRobot;
			}

		private:
			Robot* m_pRobot = nullptr;
		};

		class MiniRobotBuilder final : public RobotBuilder
		{
		public:
			using RobotBuilder::RobotBuilder;
			virtual ~MiniRobotBuilder() = default;

			virtual RobotBuilder& OnCreateRobot() override
			{
				setRobot(new MiniRobot());
				return *this;
			}

			virtual RobotBuilder& OnEquipWeapon() override
			{
				printf("MiniRobotBuilder: ���� ����!\n");
				return *this;
			}

			virtual RobotBuilder& OnEquipWing() override
			{
				printf("MiniRobotBuilder: ���� ����!\n");
				return *this;
			}

			virtual RobotBuilder& OnEquipShield() override
			{
				printf("MiniRobotBuilder: ���� ����!\n");
				return *this;
			}

			virtual RobotBuilder& OnReset() override
			{
				Robot* pRobot = getRobot();
				if (pRobot != nullptr)
				{
					delete pRobot;
				}

				setRobot(new MiniRobot());
				printf("MiniRobot �ʱ�ȭ!\n");

				return *this;
			}

			virtual MiniRobot& OnResult() override
			{
				return *(dynamic_cast<MiniRobot*>(getRobot()));
			}
		};

		class HugeRobotBuilder final : public RobotBuilder
		{
		public:
			using RobotBuilder::RobotBuilder;
			virtual ~HugeRobotBuilder() = default;

			virtual RobotBuilder& OnCreateRobot() override
			{
				setRobot(new HugeRobot());
				return *this;
			}

			virtual RobotBuilder& OnEquipWeapon() override
			{
				printf("HugeRobotBuilder: ���� ����!\n");
				return *this;
			}

			virtual RobotBuilder& OnEquipWing() override
			{
				printf("HugeRobotBuilder: ���� ����!\n");
				return *this;
			}

			virtual RobotBuilder& OnEquipShield() override
			{
				printf("HugeRobotBuilder: ���� ����!\n");
				return *this;
			}

			virtual RobotBuilder& OnReset() override
			{
				Robot* pRobot = getRobot();
				if (pRobot != nullptr)
				{
					delete pRobot;
				}

				setRobot(new HugeRobot());
				printf("HugeRobot �ʱ�ȭ!\n");

				return *this;
			}

			virtual HugeRobot& OnResult() override
			{
				return *(dynamic_cast<HugeRobot*>(getRobot()));
			}
		};

		enum class EBuildType
		{
			SIMPLE = 0,
			PERFECT,
		};

		class Director final
		{
		public:
			Director(RobotBuilder* pRobotBuilder)
			{
				m_pRobotBuilder = pRobotBuilder;
			}

			~Director()
			{
				delete m_pRobotBuilder;
			}

			void changeBuilder(RobotBuilder* pRobotBuilder)
			{
				if (m_pRobotBuilder != nullptr)
				{
					delete m_pRobotBuilder;
				}

				m_pRobotBuilder = pRobotBuilder;
			}

			void make(EBuildType buildType)
			{
				m_pRobotBuilder->OnReset();

				if (buildType == EBuildType::SIMPLE)
				{
					m_pRobotBuilder->OnCreateRobot().
						OnEquipWeapon();
				}
				else if (buildType == EBuildType::PERFECT)
				{
					m_pRobotBuilder->OnCreateRobot().
						OnEquipWeapon().
						OnEquipWing().
						OnEquipShield();
				}
			}

		private:
			RobotBuilder* m_pRobotBuilder = nullptr;
		};
	}
}

namespace unit_test
{
	namespace basic
	{
		void Test()
		{
			printf("<�⺻ Builder �׽�Ʈ!>\n\n");

			Director director(nullptr);

#pragma region ù ��° ����
			ConcreteBuilder1* pConcreteBuilder1 = new ConcreteBuilder1();
			
			director.changeBuilder(pConcreteBuilder1);
			director.make(EBuildType::SIMPLE);;

			Product1 product1 = pConcreteBuilder1->getResult();
			product1.TestFunc();
#pragma endregion

			printf("\n");

#pragma region �� ��° ����
			ConcreteBuilder2* pConcreteBuilder2 = new ConcreteBuilder2();
			
			director.changeBuilder(pConcreteBuilder2);
			director.make(EBuildType::PERFECT);

			Product2 product2 = pConcreteBuilder2->getResult();
			product2.TestFunc();
#pragma endregion

			printf("\n");
		}
	}

	namespace variation
	{
		void Test()
		{
			printf("<���� Builder �׽�Ʈ!>\n\n");

			Director director(nullptr);

#pragma region ù ��° ����
			ConcreteBuilder1* pConcreteBuilder1 = new ConcreteBuilder1();

			director.changeBuilder(pConcreteBuilder1);
			director.make(EBuildType::SIMPLE);;

			pConcreteBuilder1->OnResult().OnTest();
#pragma endregion

			printf("\n");

#pragma region �� ��° ����
			ConcreteBuilder2* pConcreteBuilder2 = new ConcreteBuilder2();

			director.changeBuilder(pConcreteBuilder2);
			director.make(EBuildType::PERFECT);

			pConcreteBuilder2->OnResult().OnTest();
#pragma endregion

			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<���� ���� �׽�Ʈ!>\n\n");

			Director director(nullptr);

#pragma region ù ��° ����
			MiniRobotBuilder* pMiniRobotBuilder = new MiniRobotBuilder();

			director.changeBuilder(pMiniRobotBuilder);
			director.make(EBuildType::SIMPLE);;

			pMiniRobotBuilder->OnResult().OnAttack();
#pragma endregion

			printf("\n");

#pragma region �� ��° ����
			HugeRobotBuilder* pHugeRobotBuilder = new HugeRobotBuilder();

			director.changeBuilder(pHugeRobotBuilder);
			director.make(EBuildType::PERFECT);

			pHugeRobotBuilder->OnResult().OnAttack();
#pragma endregion

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