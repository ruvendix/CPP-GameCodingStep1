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
        class Prototype abstract
        {
        public:
            Prototype() = default;
            virtual ~Prototype() = default;

            // �⺻ ���� �����ڸ� �̿��ص� ������...
            // ���� �����ϴ� ��찡 �� ���ƿ�!
            // abstract Ŭ���������� ���� �ǹ� �����ϴ�.
            Prototype(const Prototype&)
            {
                printf("Prototype: ���� ������ ȣ��!\n");
            }

            // ���� �����ڸ� ȣ���ϴ� �Լ��Դϴ�.
            virtual Prototype* clone() abstract;
        };

        class ConcretePrototype : public Prototype
        {
        public:
            ConcretePrototype() = default;
            virtual ~ConcretePrototype() = default;

            // ���� Ŭ���������� ���� ������ ������ �ʿ��ؿ�!
            ConcretePrototype(const ConcretePrototype& ref) :
                Prototype(ref) // �θ� ���� ������ ȣ�� �ʼ�!
            {
                *this = ref;
                printf("ConcretePrototype: ���� ������ ȣ��!\n");
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
                printf("SubclassPrototype: ���� ������ ȣ��!\n");
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
        class Monster // �Ϲ� Ŭ������ �����غ��Կ�.
        {
        public:
            Monster() = default;
            virtual ~Monster() = default;

            Monster(const Monster& ref)
            {
                m_HP = ref.getHP();
                m_MP = ref.getMP();

                printf("Monster ���� ������ ȣ��!\n");
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
                printf("RedEvil ���� ������ ȣ��!\n");
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
            printf("<�⺻ Prototype �׽�Ʈ!>\n\n");

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
            printf("<���� ���� �׽�Ʈ!>\n\n");

            RedEvil redEvil;
            redEvil.setHP(100);
            redEvil.setMP(150);
            redEvil.setMoney(50);

            printf("RedEvil�� ����\n");
            printf("HP: %d\tMP: %d\t��: %d\n",
                redEvil.getHP(), redEvil.getMP(), redEvil.getMoney());
            printf("\n");

            RedEvil* pNewRedEvil = redEvil.Clone();

            printf("���ο� RedEvil�� ����\n");
            printf("HP: %d\tMP: %d\t��: %d\n",
                pNewRedEvil->getHP(), pNewRedEvil->getMP(), pNewRedEvil->getMoney());

            delete pNewRedEvil;

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