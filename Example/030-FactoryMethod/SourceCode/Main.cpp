// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>

namespace unit_test
{
    namespace basic
    {
        class Product abstract // interface라는 의미입니다. (추상 클래스에도 사용 가능)
        {
        public:
            Product() = default;
            virtual ~Product() = default;

            virtual void doStuff() abstract;
        };

        class ConcreteProductA : public Product // Concrete는 "구현"을 의미합니다.
        {
        public:
            using Product::Product; // 생성자 상속, 이러면 자식은 부모 생성자를 이용할 수 있어요!
            virtual ~ConcreteProductA() = default;

            virtual void doStuff() override
            {
                printf("ConcreteProductA: doStuff 호출!\n");
            }
        };

        class ConcreteProductB : public Product
        {
        public:
            using Product::Product;
            virtual ~ConcreteProductB() = default;

            virtual void doStuff() override
            {
                printf("ConcreteProductB: doStuff 호출!\n");
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

            // 함수의 반환형은 오버로딩 조건이 아니에요!
            // 따라서 오버라이딩으로 인식됩니다.
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
        class Product abstract // interface로 표현하기 위해!
        {
        public:
            Product() = default;
            virtual ~Product() = default;
        };

        class ConcreteProduct : public Product // Concrete는 "구현"을 의미합니다.
        {
            friend class ConcreteCreator;

        public:
            void TestFunc()
            {
                printf("상품 테스트!\n");
            }

            // Factory Method로만 생성 가능하게 제한해야 해요!
        private:
            using Product::Product; // 생성자 상속, 이러면 자식은 부모 생성자를 이용할 수 있어요!
            virtual ~ConcreteProduct() = default;
        };

        // 객체로 생성할 필요 없어요.
        class ConcreteCreator
        {
        public:
            // ConcreteCreator::factoryMethod() 이렇게 사용합니다.
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
                printf("괴물의 공격!\n");
            }

        private:
            Monster() = default;
            ~Monster() = default;
        };

        class MonsterFactory // 몬스터 주식회사?!
        {
        public:
            static Monster* CreateMonster()
            {
                printf("괴물 생성!\n");
                return new Monster();
            }

            static void DeleteMonster(Monster* pMonster)
            {
                printf("괴물 삭제!\n");
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
            printf("<기본 FactoryMethod 테스트!>\n\n");
            
            Creator* pCreator = nullptr;
            Product* pProduct = nullptr;

            // ConcreteCreatorA를 테스트합니다.
            pCreator = new ConcreteCreatorA();
            pProduct = pCreator->createProduct();
            pProduct->doStuff();
            delete pProduct;
            delete pCreator;

            // ConcreteCreatorB를 테스트합니다.
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
            printf("<간단한 FactoryMethod 테스트!>\n\n");
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
            printf("<패턴 적용 테스트!>\n\n");
            Monster* pMonster = MonsterFactory::CreateMonster();
            pMonster->Attack();
            MonsterFactory::DeleteMonster(pMonster);
            printf("\n");
        }
    }
}

//////////////////////////////////////////////////////////////////////////
// 프로그램이 시작되는 곳이에요.
int main()
{
    //unit_test::basic::Test();
    //unit_test::simple::Test();
    
    //unit_test::use_pattern::Test();
    return 0;
}