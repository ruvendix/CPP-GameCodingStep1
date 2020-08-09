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
        class Subsystem1
        {
        public:
            Subsystem1() = default;
            ~Subsystem1() = default;

            void operation()
            {
                printf("Subsystem1::operation()\n");
            }
        };

        class Subsystem2
        {
        public:
            Subsystem2() = default;
            ~Subsystem2() = default;

            void operation()
            {
                printf("Subsystem2::operation()\n");
            }
        };

        class AdditionalFacade
        {
        public:
            AdditionalFacade() = default;
            ~AdditionalFacade() = default;

            void anotherOperation()
            {
                printf("AdditionalFacade::anotherOperation()\n");
            }
        };

        class Facade
        {
        public:
            Facade() = default;
            ~Facade() = default;

            void subsystemOperation()
            {
                printf("Facade::subsystemOperation()\n");

                linksToSubsystemObject1.operation();
                linksToSubsystemObject2.operation();

                optionalAdditionalFacade.anotherOperation();                
            }

        private:
            Subsystem1 linksToSubsystemObject1;
            Subsystem2 linksToSubsystemObject2;

            AdditionalFacade optionalAdditionalFacade;
        };
	}

    namespace use_pattern
    {
        class TextureMgr
        {
        public:
            TextureMgr() = default;
            ~TextureMgr() = default;

            void LoadTexture()
            {
                printf("TextureMgr::LoadTexture()\n");
            }
        };

        class SoundMgr
        {
        public:
            SoundMgr() = default;
            ~SoundMgr() = default;

            void LoadSound()
            {
                printf("SoundMgr::LoadSound()\n");
            }
        };

        class AnimationMgr
        {
        public:
            AnimationMgr() = default;
            ~AnimationMgr() = default;

            void LoadAnimation()
            {
                printf("AnimationMgr::LoadAnimation()\n");
            }
        };

        class ResourceFacade
        {
        public:
            ResourceFacade() = default;
            ~ResourceFacade() = default;

            void LoadResource()
            {
                printf("��� ���ҽ��� �ε��մϴ�.\n");

                m_textureMgr.LoadTexture();
                m_soundMgr.LoadSound();
                m_animationMgr.LoadAnimation();
            }

        private:
            TextureMgr m_textureMgr;
            SoundMgr m_soundMgr;
            AnimationMgr m_animationMgr;
        };
    }
}

namespace unit_test
{
    namespace basic
    {
        void Test()
        {
            printf("<�⺻ Facade �׽�Ʈ!>\n\n");

            Facade facade;
            facade.subsystemOperation();

            printf("\n");
        }
    }

    namespace use_pattern
    {
        void Test()
        {
            printf("<���� ���� �׽�Ʈ!>\n\n");

            ResourceFacade resourceFacade;
            resourceFacade.LoadResource();

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