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
            // 이렇게 생성자의 인자로 초기화하면 집합 관계라는 거, 이제는 알죠?
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

            // 가장 최근에 적용된 기능을 해제할 때 사용!
            Component* release()
            {
                Component* pComponent = wrappee;

                wrappee = nullptr;
                printf("기능 해제: %p\n", this);

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

                // 부모 함수부터 호출하는 게 좋아요!
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
                printf("버프 적용되지 않은 순수한 데이터!\n");
                printf("플레이어의 HP: %d\n", getHP());
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
                printf("적용 중인 효과 해제!\n");

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
                printf("HP가 3배로 늘어나는 버프 적용!\n");

                // 꼬리에 꼬리를 무는 방식이므로 데이터를 이용한다면 복사해줘야 해요!
                setHP(getActor()->getHP() * 3);

                printf("플레이어의 HP: %d\n", getHP());
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
                printf("HP가 절반으로 줄어드는 디버프 적용!\n");

                // 꼬리에 꼬리를 무는 방식이므로 데이터를 이용한다면 복사해줘야 해요!
                setHP(getActor()->getHP() / 2);

                printf("플레이어의 HP: %d\n", getHP());
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
            printf("<기본 Decorator 테스트!>\n\n");

            printf("원본 객체 생성!\n");
            printf("#########################################\n");
            Component* pComponent = new ConcreteComponent();
            pComponent->execute();
            printf("#########################################\n\n");

            printf("첫 번째 ConcreteDecorator 적용!\n");
            printf("#########################################\n");
            Component* pDecoratorComponent = new ConcreteDecorator(pComponent);
            pDecoratorComponent->execute();
            printf("#########################################\n\n");

            printf("두 번째 ConcreteDecorator 적용!\n"); // 같은 클래스!
            printf("#########################################\n");
            Component* pNewDecoratorComponent = new ConcreteDecorator(pDecoratorComponent);
            pNewDecoratorComponent->execute();
            printf("#########################################\n\n");

            printf("두 번째 ConcreteDecorator 해제!\n");
            printf("#########################################\n");
            Component* pOldDecoratorComponent = dynamic_cast<BaseDecorator*>(pNewDecoratorComponent)->release();
            pOldDecoratorComponent->execute();
            delete pOldDecoratorComponent; // pDecoratorComponent와 같음!
            printf("#########################################\n\n");
		}
	}

    namespace use_pattern
    {
        void Test()
        {
            printf("<패턴 적용 테스트!>\n\n");

            printf("플레이어 객체 생성!\n");
            printf("#########################################\n");
            Actor* pActor = new Player();
            pActor->setHP(100);
            pActor->OnUpdate();
            printf("#########################################\n\n");

            printf("TripleHP 적용!\n");
            printf("#########################################\n");
            Actor* pBuff = new TripleHP(pActor);
            pBuff->OnUpdate();
            printf("#########################################\n\n");

            printf("HalfHP 적용!\n");
            printf("#########################################\n");
            Actor* pDebuff = new HalfHP(pBuff);
            pDebuff->OnUpdate();
            printf("#########################################\n\n");

            printf("HalfHP 해제!\n");
            printf("#########################################\n");
            pBuff = dynamic_cast<ActorDecorator*>(pDebuff)->Deactivate();
            pBuff->OnUpdate();
            delete pBuff;
            printf("#########################################\n\n");
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