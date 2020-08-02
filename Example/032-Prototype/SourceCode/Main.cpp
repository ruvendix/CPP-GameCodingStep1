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
        class Prototype abstract
        {
        public:
            Prototype() = default;
            virtual ~Prototype() = default;

            // 기본 복사 생성자를 이용해도 되지만...
            // 따로 구현하는 경우가 더 많아요!
            // abstract 클래스에서는 딱히 의미 없습니다.
            Prototype(const Prototype&)
            {
                printf("Prototype: 복사 생성자 호출!\n");
            }

            // 복사 생성자를 호출하는 함수입니다.
            virtual Prototype* clone() abstract;
        };

        class ConcretePrototype : public Prototype
        {
        public:
            ConcretePrototype() = default;
            virtual ~ConcretePrototype() = default;

            // 구현 클래스에서는 복사 생성자 구현이 필요해요!
            ConcretePrototype(const ConcretePrototype& ref) :
                Prototype(ref) // 부모 복사 생성자 호출 필수!
            {
                *this = ref;
                printf("ConcretePrototype: 복사 생성자 호출!\n");
            }

            virtual ConcretePrototype* clone() override
            {
                return (new ConcretePrototype(*this));
            }

        private:
            int field1 = 0;
        };

        class SubclassPrototype : public ConcretePrototype
        {
        public:
            SubclassPrototype() = default;
            virtual ~SubclassPrototype() = default;

            SubclassPrototype(const SubclassPrototype& ref) :
                ConcretePrototype(ref)
            {
                *this = ref;
                printf("SubclassPrototype: 복사 생성자 호출!\n");
            }

            virtual SubclassPrototype* clone() override
            {
                return (new SubclassPrototype(*this));
            }

        private:
            int field2 = 0;
        };
    }

    namespace use_pattern
    {
        class Monster // 일반 클래스로 구현해볼게요.
        {
        public:
            Monster() = default;
            virtual ~Monster() = default;

            Monster(const Monster& ref)
            {
                m_HP = ref.getHP();
                m_MP = ref.getMP();

                printf("Monster 복사 생성자 호출!\n");
            }

            virtual Monster* Clone()
            {
                return (new Monster(*this));
            }

            int getHP() const
            {
                return m_HP;
            }

            int getMP() const
            {
                return m_MP;
            }

            void setHP(int HP)
            {
                m_HP = HP;
            }

            void setMP(int MP)
            {
                m_MP = MP;
            }

        private:
            int m_HP = 0;
            int m_MP = 0;
        };

        class RedEvil : public Monster
        {
        public:
            RedEvil() = default;
            virtual ~RedEvil() = default;

            RedEvil(const RedEvil& ref) :
                Monster(ref)
            {
                m_money = ref.getMoney();
                printf("RedEvil 복사 생성자 호출!\n");
            }

            virtual RedEvil* Clone() override
            {
                return (new RedEvil(*this));
            }

            int getMoney() const
            {
                return m_money;
            }

            void setMoney(int money)
            {
                m_money = money;
            }

        private:
            int m_money = 0;
        };
    }
}

namespace unit_test
{
    namespace basic
    {
        void Test()
        {
            printf("<기본 Prototype 테스트!>\n\n");

            ConcretePrototype concretePrototype;
            Prototype* pPrototype = concretePrototype.clone();
            delete pPrototype;

            printf("\n");

            SubclassPrototype subclassPrototype;
            pPrototype = subclassPrototype.clone();
            delete pPrototype;

            printf("\n");
        }
    }

    namespace use_pattern
    {
        void Test()
        {
            printf("<패턴 적용 테스트!>\n\n");

            RedEvil redEvil;
            redEvil.setHP(100);
            redEvil.setMP(150);
            redEvil.setMoney(50);

            printf("RedEvil의 스펙\n");
            printf("HP: %d\tMP: %d\t돈: %d\n",
                redEvil.getHP(), redEvil.getMP(), redEvil.getMoney());
            printf("\n");

            RedEvil* pNewRedEvil = redEvil.Clone();

            printf("새로운 RedEvil의 스펙\n");
            printf("HP: %d\tMP: %d\t돈: %d\n",
                pNewRedEvil->getHP(), pNewRedEvil->getMP(), pNewRedEvil->getMoney());

            delete pNewRedEvil;

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