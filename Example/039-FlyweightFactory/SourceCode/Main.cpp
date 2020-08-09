// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <string>
#include <unordered_map>

namespace unit_test
{
	namespace basic
	{
		class Flyweight
		{
		public:
			Flyweight(int repeatingState) :
				repeatingState(repeatingState)
			{

			}

			~Flyweight() = default;

			void operation(int uniqueState)
			{
				printf("repeatingState: %d\n", repeatingState);
				printf("uniqueState: %d\n", uniqueState);
			}

			int getRepeatingState() const
			{
				return repeatingState;
			}

			void setRepeatingState(int repeatingState)
			{
				this->repeatingState = repeatingState;
			}

		private:
			// 클래스 다이어그램에서는 상태가 하나일 때를 의미합니다!
			// 재활용할 데이터가 많다면 int 대신 클래스나 구조체를 넣어야 해요!
			int repeatingState = 0;
		};

		class FlyweightFactory
		{
		public:
			FlyweightFactory() = default;
			
			~FlyweightFactory()
			{
				for (int i = 0; i < 10; ++i)
				{
					if (cache[i] != nullptr)
					{
						delete cache[i];
					}
				}
			}

			Flyweight* getFlyweight(int repeatingState)
			{
				if (cache[repeatingState] == nullptr)
				{
					cache[repeatingState] = new Flyweight(repeatingState);
					printf("Flyweight 생성!\n");
				}
				else
				{
					printf("Flyweight 재활용!\n");
				}

				return cache[repeatingState];
			}

		private:
			Flyweight* cache[10];
		};

		// Flyweight 팩토리 객체 생성!
		FlyweightFactory factory;

		class Context
		{
		public:
			Context(int repeatingState, int uniqueState) :
				uniqueState(uniqueState)
			{
				flyweight = factory.getFlyweight(repeatingState);
				printf("Context 생성!\n");
			}

			~Context() = default;

			void operation()
			{
				flyweight->operation(uniqueState);
			}

		private:
			// 클래스 다이어그램에서는 상태가 하나일 때를 의미합니다!
			// 고유한 데이터가 많다면 int 대신 클래스나 구조체를 넣어야 해요.
			int uniqueState = 0;

			Flyweight* flyweight = nullptr;
		};
	}

	namespace use_pattern
	{
		struct ParticleIntrinsicInfo
		{
			std::string strColor;
			std::string strImage;
		};

		struct ParticleExtrinsicInfo
		{
			int x = 0;
			int y = 0;
			int speed = 0;
		};

		class ParticleFlyweight
		{
		public:
			ParticleFlyweight(const ParticleIntrinsicInfo& intrinsicInfo)
			{
				m_pIntrinsicInfo = new ParticleIntrinsicInfo();
				*m_pIntrinsicInfo = intrinsicInfo;
			}

			~ParticleFlyweight()
			{
				delete m_pIntrinsicInfo;
			}

			void ShowInfo()
			{
				printf("<내부 정보>\n");
				printf("색상: %s\n", m_pIntrinsicInfo->strColor.c_str());
				printf("이미지: %s\n", m_pIntrinsicInfo->strImage.c_str());
			}

		private:
			ParticleIntrinsicInfo* m_pIntrinsicInfo = nullptr;
		};

		class ParticleFlyweightFactory
		{
		public:
			ParticleFlyweightFactory() = default;

			~ParticleFlyweightFactory()
			{
				for (auto& iter : m_mapFlyweight)
				{
					if (iter.second != nullptr)
					{
						delete iter.second;
					}
				}
			}

			// Flyweight는 재활용할 객체가 없다면 생성해야 하므로
			// 조회와 생성이 동시에 존재하는 함수가 필요합니다.
			ParticleFlyweight* FindOrCreateFlyweight(const std::string& strKey,
				const ParticleIntrinsicInfo& intrinsicInfo)
			{
				const auto& iter = m_mapFlyweight.find(strKey);
				if (iter == m_mapFlyweight.cend())
				{
					ParticleFlyweight* pFlyweight = new ParticleFlyweight(intrinsicInfo);
					m_mapFlyweight.insert(std::make_pair(strKey, pFlyweight));
					printf("ParticleFlyweight 생성!\n");

					return pFlyweight;
				}

				printf("ParticleFlyweight 재활용!\n");
				return iter->second;
			}

		private:
			std::unordered_map<std::string, ParticleFlyweight*> m_mapFlyweight;
		};

		// Flyweight 팩토리 객체 생성!
		ParticleFlyweightFactory g_particleFlyWeightFactory;

		class Particle
		{
		public:
			// 내부 상태 데이터가 많다면 Flyweight를 키값으로 관리해야 하는데,
			// 키값에 해당하는 Flyweight가 없을 때를 대비해서 내부 상태도 전달해야 합니다.
			Particle(const std::string strKey, const ParticleIntrinsicInfo& intrinsicInfo,
				const ParticleExtrinsicInfo& extrinsicInfo)
			{
				m_pExtrinsicInfo = new ParticleExtrinsicInfo();
				*m_pExtrinsicInfo = extrinsicInfo;

				m_pFlyweight = g_particleFlyWeightFactory.FindOrCreateFlyweight(strKey, intrinsicInfo);
				printf("Particle 생성!\n\n");
			}

			// m_pFlyweight는 공유하는 객체니까 해제하면 망해요!
			// 게임 코딩에서는 이럴 경우 레퍼런스 카운팅을 감소시킵니다.
			~Particle()
			{
				delete m_pExtrinsicInfo;
			}

			void ShowInfo()
			{
				printf("<외부 정보>\n");
				printf("좌표: (%d, %d)\n", m_pExtrinsicInfo->x, m_pExtrinsicInfo->y);
				printf("속도: %d\n\n", m_pExtrinsicInfo->speed);

				m_pFlyweight->ShowInfo();
			}

		private:
			ParticleExtrinsicInfo* m_pExtrinsicInfo = nullptr;
			ParticleFlyweight* m_pFlyweight = nullptr;
		};
	}
}

namespace unit_test
{
	namespace basic
	{
		void Test()
		{
			printf("<기본 Flyweight 테스트!>\n\n");

			Context context1(0, 1);
			context1.operation();
			printf("\n");

			Context context2(0, 2);
			context2.operation();
			printf("\n");

			Context context3(1, 2);
			context3.operation();
			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<패턴 적용 테스트!>\n\n");

			// 공용할 내부 상태를 설정할게요.
			ParticleIntrinsicInfo intrinsicInfo;
			intrinsicInfo.strColor = "빨간색";
			intrinsicInfo.strImage = "Bullet.png"; // 게임 코딩에서는 실제 이미지 경로를 넣어야 해요!

#pragma region 첫 번째 파티클
			printf("========================================\n");

			// 각자 사용할 외부 상태를 설정할게요.
			// 헷갈릴 수 있으니까 객체는 따로 만들겠습니다.
			ParticleExtrinsicInfo extrinsicInfo1;
			extrinsicInfo1.x = 10;
			extrinsicInfo1.y = 12;
			extrinsicInfo1.speed = 15;

			Particle particle1("RedParticle", intrinsicInfo, extrinsicInfo1);
			particle1.ShowInfo();
			printf("========================================\n");
#pragma endregion

#pragma region 두 번째 파티클
			ParticleExtrinsicInfo extrinsicInfo2;
			extrinsicInfo2.x = 60;
			extrinsicInfo2.y = 22;
			extrinsicInfo2.speed = 8;

			Particle particle2("RedParticle", intrinsicInfo, extrinsicInfo2);
			particle2.ShowInfo();
			printf("========================================\n");
#pragma endregion

#pragma region 세 번째 파티클
			intrinsicInfo.strColor = "파란색";

			ParticleExtrinsicInfo extrinsicInfo3;
			extrinsicInfo3.x = 40;
			extrinsicInfo3.y = 74;
			extrinsicInfo3.speed = 13;

			Particle particle3("BlueParticle", intrinsicInfo, extrinsicInfo3);
			particle3.ShowInfo();
			printf("========================================\n");
#pragma endregion

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