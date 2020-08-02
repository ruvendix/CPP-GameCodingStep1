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
        class Product abstract // interface��� �ǹ��Դϴ�. (�߻� Ŭ�������� ��� ����)
        {
        public:
            Product() = default;
            virtual ~Product() = default;

            virtual void doStuff() abstract;
        };

        class ConcreteProductA : public Product // Concrete�� "����"�� �ǹ��մϴ�.
        {
        public:
            using Product::Product; // ������ ���, �̷��� �ڽ��� �θ� �����ڸ� �̿��� �� �־��!
            virtual ~ConcreteProductA() = default;

            virtual void doStuff() override
            {
                printf("ConcreteProductA: doStuff ȣ��!\n");
            }
        };

        class ConcreteProductB : public Product
        {
        public:
            using Product::Product;
            virtual ~ConcreteProductB() = default;

            virtual void doStuff() override
            {
                printf("ConcreteProductB: doStuff ȣ��!\n");
            }
        };

        class Creator
        {
        public:
            Creator() = default;
            virtual ~Creator() = default;

            virtual Product* createProduct() abstract;
            void someOperation() { }
        };

        class ConcreteCreatorA : public Creator
        {
        public:
            using Creator::Creator;
            virtual ~ConcreteCreatorA() = default;

            // �Լ��� ��ȯ���� �����ε� ������ �ƴϿ���!
            // ���� �������̵����� �νĵ˴ϴ�.
            virtual ConcreteProductA* createProduct() override
            {
                return new ConcreteProductA();
            }
        };

        class ConcreteCreatorB : public Creator
        {
        public:
            using Creator::Creator;
            virtual ~ConcreteCreatorB() = default;

            virtual ConcreteProductB* createProduct() override
            {
                return new ConcreteProductB();
            }
        };
    }

    namespace simple
    {
        class Product abstract // interface�� ǥ���ϱ� ����!
        {
        public:
            Product() = default;
            virtual ~Product() = default;
        };

        class ConcreteProduct : public Product // Concrete�� "����"�� �ǹ��մϴ�.
        {
            friend class ConcreteCreator;

        public:
            void TestFunc()
            {
                printf("��ǰ �׽�Ʈ!\n");
            }

            // Factory Method�θ� ���� �����ϰ� �����ؾ� �ؿ�!
        private:
            using Product::Product; // ������ ���, �̷��� �ڽ��� �θ� �����ڸ� �̿��� �� �־��!
            virtual ~ConcreteProduct() = default;
        };

        // ��ü�� ������ �ʿ� �����.
        class ConcreteCreator
        {
        public:
            // ConcreteCreator::factoryMethod() �̷��� ����մϴ�.
            static ConcreteProduct* factoryMethod()
            {
                return new ConcreteProduct();
            }

            static void FreeProduct(Product* pProduct)
            {
                delete pProduct;
            }
        };
    }

    namespace use_pattern
    {
        class Monster
        {
            friend class MonsterFactory;

        public:
            void Attack()
            {
                printf("������ ����!\n");
            }

        private:
            Monster() = default;
            ~Monster() = default;
        };

        class MonsterFactory // ���� �ֽ�ȸ��?!
        {
        public:
            static Monster* CreateMonster()
            {
                printf("���� ����!\n");
                return new Monster();
            }

            static void DeleteMonster(Monster* pMonster)
            {
                printf("���� ����!\n");
                delete pMonster;
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
            printf("<�⺻ FactoryMethod �׽�Ʈ!>\n\n");
            
            Creator* pCreator = nullptr;
            Product* pProduct = nullptr;

            // ConcreteCreatorA�� �׽�Ʈ�մϴ�.
            pCreator = new ConcreteCreatorA();
            pProduct = pCreator->createProduct();
            pProduct->doStuff();
            delete pProduct;
            delete pCreator;

            // ConcreteCreatorB�� �׽�Ʈ�մϴ�.
            pCreator = new ConcreteCreatorB();
            pProduct = pCreator->createProduct();
            pProduct->doStuff();
            delete pProduct;
            delete pCreator;

            printf("\n");
        }
    }

    namespace simple
    {
        void Test()
        {
            printf("<������ FactoryMethod �׽�Ʈ!>\n\n");
            ConcreteProduct* pConcreteProduct = ConcreteCreator::factoryMethod();
            pConcreteProduct->TestFunc();
            ConcreteCreator::FreeProduct(pConcreteProduct);
            printf("\n");
        }
    }

    namespace use_pattern
    {
        void Test()
        {
            printf("<���� ���� �׽�Ʈ!>\n\n");
            Monster* pMonster = MonsterFactory::CreateMonster();
            pMonster->Attack();
            MonsterFactory::DeleteMonster(pMonster);
            printf("\n");
        }
    }
}

//////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
int main()
{
    //unit_test::basic::Test();
    //unit_test::simple::Test();
    
    //unit_test::use_pattern::Test();
    return 0;
}