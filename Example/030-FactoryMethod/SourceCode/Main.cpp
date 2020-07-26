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
        class Product abstract // interface�� ǥ���ϱ� ����!
        {
        public:
            Product() = default;
            virtual ~Product() = default;
        };

        class ConcreteProduct : public Product // Concrete�� "����"�� �ǹ��մϴ�.
        {
        public:
            using Product::Product; // ������ ���, �̷��� �ڽ��� �θ� �����ڸ� �̿��� �� �־��!
            virtual ~ConcreteProduct() = default;

            void TestFunc()
            {
                printf("��ǰ �׽�Ʈ!\n");
            }
        };

        class Creato
        {
        public:
            Creato() = default;
            virtual ~Creato() = default;

            virtual Product* factoryMethod() abstract;
            void anOperation() { }
        };

        class ConcreteCreator : public Creato
        {
        public:
            using Creato::Creato;
            virtual ~ConcreteCreator() = default;

            // �Լ��� ��ȯ���� �����ε� ������ �ƴϿ���!
            // ���� �������̵����� �νĵ˴ϴ�.
            virtual ConcreteProduct* factoryMethod() override
            {
                return new ConcreteProduct();
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
                return new Monster();
            }

            static void DeleteMonster(Monster* pMonster)
            {
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
            printf("�⺻ FactoryMethod �׽�Ʈ!\n");
            ConcreteCreator concreteCreator;
            ConcreteProduct* pConcreteProduct = concreteCreator.factoryMethod();
            pConcreteProduct->TestFunc();
            delete pConcreteProduct;
            printf("\n");
        }
    }

    namespace simple
    {
        void Test()
        {
            printf("������ FactoryMethod �׽�Ʈ!\n");
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
            printf("���� ���� �׽�Ʈ!\n");
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