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
        class ProductA abstract
        {
        public:
            ProductA() = default;
            virtual ~ProductA() = default;
        };

        class ConcreteProductA1 : public ProductA
        {
        private:
            friend class ConcreteFactoryA;

            using ProductA::ProductA;
            virtual ~ConcreteProductA1() = default;
        };

        class ConcreteProductA2 : public ProductA
        {
        private:
            friend class ConcreteFactoryB;

            using ProductA::ProductA;
            virtual ~ConcreteProductA2() = default;
        };

        class ProductB abstract
        {
        public:
            ProductB() = default;
            virtual ~ProductB() = default;
        };

        class ConcreteProductB1 : public ProductB
        {
        private:
            friend class ConcreteFactoryA;

            using ProductB::ProductB;
            virtual ~ConcreteProductB1() = default;
        };

        class ConcreteProductB2 : public ProductB
        {
        private:
            friend class ConcreteFactoryB;

            using ProductB::ProductB;
            virtual ~ConcreteProductB2() = default;
        };

        class AbstractFactory abstract
        {
        public:
            AbstractFactory() = default;
            virtual ~AbstractFactory() = default;

            virtual ProductA* createProductA() abstract;
            virtual ProductB* createProductB() abstract;
        };

        class ConcreteFactoryA : public AbstractFactory
        {
        public:
            using AbstractFactory::AbstractFactory;
            virtual ~ConcreteFactoryA() = default;

            virtual ConcreteProductA1* createProductA() override
            {
                printf("ConcreteProductA1 ����!\n");
                return new ConcreteProductA1();
            }

            virtual ConcreteProductB1* createProductB() override
            {
                printf("ConcreteProductB1 ����!\n");
                return new ConcreteProductB1();
            }
        };

        class ConcreteFactoryB : public AbstractFactory
        {
        public:
            using AbstractFactory::AbstractFactory;
            virtual ~ConcreteFactoryB() = default;

            virtual ConcreteProductA2* createProductA() override
            {
                printf("ConcreteProductA2 ����!\n");
                return new ConcreteProductA2();
            }

            virtual ConcreteProductB2* createProductB() override
            {
                printf("ConcreteProductB2 ����!\n");
                return new ConcreteProductB2();
            }
        };
    }

    namespace use_pattern
    {
        class GroundBase abstract
        {
        public:
            GroundBase() = default;
            virtual ~GroundBase() = default;
        };

        class GrassGround : public GroundBase
        {
        private:
            friend class SummerTheme;

            using GroundBase::GroundBase;
            virtual ~GrassGround() = default;
        };

        class SnowGround : public GroundBase
        {
        private:
            friend class SummerTheme;

            using GroundBase::GroundBase;
            virtual ~SnowGround() = default;
        };

        class TreeBase abstract
        {
        public:
            TreeBase() = default;
            virtual ~TreeBase() = default;
        };

        class SummerTree : public TreeBase
        {
        private:
            friend class WinterTheme;

            using TreeBase::TreeBase;
            virtual ~SummerTree() = default;
        };

        class WinterTree : public TreeBase
        {
        private:
            friend class WinterTheme;

            using TreeBase::TreeBase;
            virtual ~WinterTree() = default;
        };

        class ThemeBase abstract
        {
        public:
            ThemeBase() = default;
            virtual ~ThemeBase() = default;

            virtual GroundBase* CreateGround() abstract;
            virtual TreeBase* CreateTree() abstract;
        };

        class SummerTheme : public ThemeBase
        {
        public:
            using ThemeBase::ThemeBase;
            virtual ~SummerTheme() = default;

            virtual GrassGround* CreateGround() override
            {
                printf("�ĸ��ĸ��� �ʿ� ����!\n");
                return new GrassGround();
            }

            virtual SummerTree* CreateTree() override
            {
                printf("���� ���� ����!\n");
                return new SummerTree();
            }
        };

        class WinterTheme : public ThemeBase
        {
        public:
            using ThemeBase::ThemeBase;
            virtual ~WinterTheme() = default;

            virtual SnowGround* CreateGround() override
            {
                printf("�� ���� �� ����!\n");
                return new SnowGround();
            }

            virtual WinterTree* CreateTree() override
            {
                printf("�ܿ� ���� ����!\n");
                return new WinterTree();
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
            printf("<�⺻ Abstract Factory �׽�Ʈ!>\n\n");
            
            AbstractFactory* pProductFactory = nullptr;

            pProductFactory = new ConcreteFactoryA();            
            ProductA* pProductA = pProductFactory->createProductA();
            ProductB* pProductB = pProductFactory->createProductB();

            delete pProductA;
            delete pProductB;
            delete pProductFactory;

            printf("\n");

            pProductFactory = new ConcreteFactoryB();
            pProductA = pProductFactory->createProductA();
            pProductB = pProductFactory->createProductB();

            delete pProductA;
            delete pProductB;
            delete pProductFactory;

            printf("\n");
        }
    }

    namespace use_pattern
    {
        void Test()
        {
            printf("<���� ���� �׽�Ʈ!>\n\n");
            
            ThemeBase* pTheme = nullptr;
            GroundBase* pGround = nullptr;
            TreeBase* pTree = nullptr;

#pragma region ���� �׸� �׽�Ʈ
            printf("���� �׸��� �����ҰԿ�!\n");
            
            pTheme = new SummerTheme();
            pGround = pTheme->CreateGround();
            pTree = pTheme->CreateTree();

            delete pTheme;
            delete pGround;
            delete pTree;
#pragma endregion

            printf("\n");

#pragma region �ܿ� �׸� �׽�Ʈ
            printf("�ܿ� �׸��� �����ҰԿ�!\n");

            pTheme = new WinterTheme();
            pGround = pTheme->CreateGround();
            pTree = pTheme->CreateTree();

            delete pTheme;
            delete pGround;
            delete pTree;
#pragma endregion

            printf("\n");
        }
    }
}

//////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
int main()
{
    unit_test::basic::Test();
    //unit_test::use_pattern::Test();

	return 0;
}