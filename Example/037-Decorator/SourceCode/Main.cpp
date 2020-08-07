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
        class Component abstract
        {
        public:
            Component() = default;
            virtual ~Component() = default;

            virtual void execute() abstract;
        };

        class ConcreteComponent : public Component
        {
        public:
            using Component::Component;
            virtual ~ConcreteComponent() = default;

            virtual void execute() override
            {
                printf("ConcreteComponent::execute()\t%p\n", this);
            }
        };

        class BaseDecorator : public Component
        {
        public:
            // �̷��� �������� ���ڷ� �ʱ�ȭ�ϸ� ���� ������ ��, ������ ����?
            BaseDecorator(Component* c)
            {
                wrappee = c;
            }

            virtual ~BaseDecorator()
            {
                if (wrappee != nullptr)
                {
                    delete wrappee;
                }
            }

            virtual void execute() override
            {
                printf("BaseDecorator::execute()\t%p\n", this);
                wrappee->execute();               
            }

            // ���� �ֱٿ� ����� ����� ������ �� ���!
            Component* release()
            {
                Component* pComponent = wrappee;

                wrappee = nullptr;
                printf("��� ����: %p\n", this);

                return pComponent;
            }

        private:
            Component* wrappee = nullptr;
        };

        class ConcreteDecorator : public BaseDecorator
        {
        public:
            using BaseDecorator::BaseDecorator;
            virtual ~ConcreteDecorator() = default;

            virtual void execute() override
            {
                printf("ConcreteDecorator::execute()\t%p\n", this);

                // �θ� �Լ����� ȣ���ϴ� �� ���ƿ�!
                printf("=========================================\n");
                BaseDecorator::execute();
                printf("=========================================\n");

                extra();
            }

            void extra()
            {
                printf("ConcreteDecorator::extra()\t%p\n", this);
            }
        };
	}

    namespace use_pattern
    {
        class Actor abstract
        {
        public:
            Actor() = default;
            virtual ~Actor() = default;

            virtual void OnUpdate() abstract;

            int getHP() const
            {
                return m_HP;
            }

            void setHP(int HP)
            {
                m_HP = HP;
            }

        private:
            int m_HP = 0;
        };

        class Player : public Actor
        {
        public:
            using Actor::Actor;
            virtual ~Player() = default;

            virtual void OnUpdate() override
            {
                printf("���� ������� ���� ������ ������!\n");
                printf("�÷��̾��� HP: %d\n", getHP());
            }
        };

        class ActorDecorator : public Actor
        {
        public:
            ActorDecorator(Actor* pActor)
            {
                m_pActor = pActor;
            }

            virtual ~ActorDecorator()
            {
                if (m_pActor != nullptr)
                {
                    delete m_pActor;
                }
            }

            virtual void OnUpdate() override
            {
                m_pActor->OnUpdate();
            }

            Actor* Deactivate()
            {
                Actor* pActor = m_pActor;

                m_pActor = nullptr;
                printf("���� ���� ȿ�� ����!\n");

                return pActor;
            }

            Actor* getActor() const
            {
                return m_pActor;
            }

        private:
            Actor* m_pActor = nullptr;
        };

        class BuffDecorator : public ActorDecorator
        {
        public:
            using ActorDecorator::ActorDecorator;
            virtual ~BuffDecorator() = default;
        };

        class DebuffDecorator : public ActorDecorator
        {
        public:
            using ActorDecorator::ActorDecorator;
            virtual ~DebuffDecorator() = default;
        };

        class TripleHP : public BuffDecorator
        {
        public:
            using BuffDecorator::BuffDecorator;
            virtual ~TripleHP() = default;

            virtual void OnUpdate() override
            {
                printf("=========================================\n");
                BuffDecorator::OnUpdate();
                printf("=========================================\n");

                IncreaseHP();
            }

            void IncreaseHP()
            {
                printf("HP�� 3��� �þ�� ���� ����!\n");

                // ������ ������ ���� ����̹Ƿ� �����͸� �̿��Ѵٸ� ��������� �ؿ�!
                setHP(getActor()->getHP() * 3);

                printf("�÷��̾��� HP: %d\n", getHP());
            }
        };

        class HalfHP : public DebuffDecorator
        {
        public:
            using DebuffDecorator::DebuffDecorator;
            virtual ~HalfHP() = default;

            virtual void OnUpdate() override
            {
                printf("=========================================\n");
                DebuffDecorator::OnUpdate();
                printf("=========================================\n");

                DecreaseHP();
            }

            void DecreaseHP()
            {
                printf("HP�� �������� �پ��� ����� ����!\n");

                // ������ ������ ���� ����̹Ƿ� �����͸� �̿��Ѵٸ� ��������� �ؿ�!
                setHP(getActor()->getHP() / 2);

                printf("�÷��̾��� HP: %d\n", getHP());
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
            printf("<�⺻ Decorator �׽�Ʈ!>\n\n");

            printf("���� ��ü ����!\n");
            printf("#########################################\n");
            Component* pComponent = new ConcreteComponent();
            pComponent->execute();
            printf("#########################################\n\n");

            printf("ù ��° ConcreteDecorator ����!\n");
            printf("#########################################\n");
            Component* pDecoratorComponent = new ConcreteDecorator(pComponent);
            pDecoratorComponent->execute();
            printf("#########################################\n\n");

            printf("�� ��° ConcreteDecorator ����!\n"); // ���� Ŭ����!
            printf("#########################################\n");
            Component* pNewDecoratorComponent = new ConcreteDecorator(pDecoratorComponent);
            pNewDecoratorComponent->execute();
            printf("#########################################\n\n");

            printf("�� ��° ConcreteDecorator ����!\n");
            printf("#########################################\n");
            Component* pOldDecoratorComponent = dynamic_cast<BaseDecorator*>(pNewDecoratorComponent)->release();
            pOldDecoratorComponent->execute();
            delete pOldDecoratorComponent; // pDecoratorComponent�� ����!
            printf("#########################################\n\n");
		}
	}

    namespace use_pattern
    {
        void Test()
        {
            printf("<���� ���� �׽�Ʈ!>\n\n");

            printf("�÷��̾� ��ü ����!\n");
            printf("#########################################\n");
            Actor* pActor = new Player();
            pActor->setHP(100);
            pActor->OnUpdate();
            printf("#########################################\n\n");

            printf("TripleHP ����!\n");
            printf("#########################################\n");
            Actor* pBuff = new TripleHP(pActor);
            pBuff->OnUpdate();
            printf("#########################################\n\n");

            printf("HalfHP ����!\n");
            printf("#########################################\n");
            Actor* pDebuff = new HalfHP(pBuff);
            pDebuff->OnUpdate();
            printf("#########################################\n\n");

            printf("HalfHP ����!\n");
            printf("#########################################\n");
            pBuff = dynamic_cast<ActorDecorator*>(pDebuff)->Deactivate();
            pBuff->OnUpdate();
            delete pBuff;
            printf("#########################################\n\n");
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