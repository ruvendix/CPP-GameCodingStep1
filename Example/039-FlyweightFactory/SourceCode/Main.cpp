// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
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
			// Ŭ���� ���̾�׷������� ���°� �ϳ��� ���� �ǹ��մϴ�!
			// ��Ȱ���� �����Ͱ� ���ٸ� int ��� Ŭ������ ����ü�� �־�� �ؿ�!
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
					printf("Flyweight ����!\n");
				}
				else
				{
					printf("Flyweight ��Ȱ��!\n");
				}

				return cache[repeatingState];
			}

		private:
			Flyweight* cache[10];
		};

		// Flyweight ���丮 ��ü ����!
		FlyweightFactory factory;

		class Context
		{
		public:
			Context(int repeatingState, int uniqueState) :
				uniqueState(uniqueState)
			{
				flyweight = factory.getFlyweight(repeatingState);
				printf("Context ����!\n");
			}

			~Context() = default;

			void operation()
			{
				flyweight->operation(uniqueState);
			}

		private:
			// Ŭ���� ���̾�׷������� ���°� �ϳ��� ���� �ǹ��մϴ�!
			// ������ �����Ͱ� ���ٸ� int ��� Ŭ������ ����ü�� �־�� �ؿ�.
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
				printf("<���� ����>\n");
				printf("����: %s\n", m_pIntrinsicInfo->strColor.c_str());
				printf("�̹���: %s\n", m_pIntrinsicInfo->strImage.c_str());
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

			// Flyweight�� ��Ȱ���� ��ü�� ���ٸ� �����ؾ� �ϹǷ�
			// ��ȸ�� ������ ���ÿ� �����ϴ� �Լ��� �ʿ��մϴ�.
			ParticleFlyweight* FindOrCreateFlyweight(const std::string& strKey,
				const ParticleIntrinsicInfo& intrinsicInfo)
			{
				const auto& iter = m_mapFlyweight.find(strKey);
				if (iter == m_mapFlyweight.cend())
				{
					ParticleFlyweight* pFlyweight = new ParticleFlyweight(intrinsicInfo);
					m_mapFlyweight.insert(std::make_pair(strKey, pFlyweight));
					printf("ParticleFlyweight ����!\n");

					return pFlyweight;
				}

				printf("ParticleFlyweight ��Ȱ��!\n");
				return iter->second;
			}

		private:
			std::unordered_map<std::string, ParticleFlyweight*> m_mapFlyweight;
		};

		// Flyweight ���丮 ��ü ����!
		ParticleFlyweightFactory g_particleFlyWeightFactory;

		class Particle
		{
		public:
			// ���� ���� �����Ͱ� ���ٸ� Flyweight�� Ű������ �����ؾ� �ϴµ�,
			// Ű���� �ش��ϴ� Flyweight�� ���� ���� ����ؼ� ���� ���µ� �����ؾ� �մϴ�.
			Particle(const std::string strKey, const ParticleIntrinsicInfo& intrinsicInfo,
				const ParticleExtrinsicInfo& extrinsicInfo)
			{
				m_pExtrinsicInfo = new ParticleExtrinsicInfo();
				*m_pExtrinsicInfo = extrinsicInfo;

				m_pFlyweight = g_particleFlyWeightFactory.FindOrCreateFlyweight(strKey, intrinsicInfo);
				printf("Particle ����!\n\n");
			}

			// m_pFlyweight�� �����ϴ� ��ü�ϱ� �����ϸ� ���ؿ�!
			// ���� �ڵ������� �̷� ��� ���۷��� ī������ ���ҽ�ŵ�ϴ�.
			~Particle()
			{
				delete m_pExtrinsicInfo;
			}

			void ShowInfo()
			{
				printf("<�ܺ� ����>\n");
				printf("��ǥ: (%d, %d)\n", m_pExtrinsicInfo->x, m_pExtrinsicInfo->y);
				printf("�ӵ�: %d\n\n", m_pExtrinsicInfo->speed);

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
			printf("<�⺻ Flyweight �׽�Ʈ!>\n\n");

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
			printf("<���� ���� �׽�Ʈ!>\n\n");

			// ������ ���� ���¸� �����ҰԿ�.
			ParticleIntrinsicInfo intrinsicInfo;
			intrinsicInfo.strColor = "������";
			intrinsicInfo.strImage = "Bullet.png"; // ���� �ڵ������� ���� �̹��� ��θ� �־�� �ؿ�!

#pragma region ù ��° ��ƼŬ
			printf("========================================\n");

			// ���� ����� �ܺ� ���¸� �����ҰԿ�.
			// �򰥸� �� �����ϱ� ��ü�� ���� ����ڽ��ϴ�.
			ParticleExtrinsicInfo extrinsicInfo1;
			extrinsicInfo1.x = 10;
			extrinsicInfo1.y = 12;
			extrinsicInfo1.speed = 15;

			Particle particle1("RedParticle", intrinsicInfo, extrinsicInfo1);
			particle1.ShowInfo();
			printf("========================================\n");
#pragma endregion

#pragma region �� ��° ��ƼŬ
			ParticleExtrinsicInfo extrinsicInfo2;
			extrinsicInfo2.x = 60;
			extrinsicInfo2.y = 22;
			extrinsicInfo2.speed = 8;

			Particle particle2("RedParticle", intrinsicInfo, extrinsicInfo2);
			particle2.ShowInfo();
			printf("========================================\n");
#pragma endregion

#pragma region �� ��° ��ƼŬ
			intrinsicInfo.strColor = "�Ķ���";

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
// ���α׷��� ���۵Ǵ� ���̿���.
int main()
{
	//unit_test::basic::Test();
	
	//unit_test::use_pattern::Test();
	return 0;
}