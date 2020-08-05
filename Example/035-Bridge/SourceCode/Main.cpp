#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>

namespace unit_test
{
	namespace basic
	{
		class Implementation abstract
		{
		public:
			Implementation() = default;
			virtual ~Implementation() = default;

			virtual void method1() abstract;
			virtual void method2() abstract;
			virtual void method3() abstract;
		};

		class ConcreteImplementation : public Implementation
		{
		public:
			using Implementation::Implementation;
			virtual ~ConcreteImplementation() = default;

			virtual void method1() override
			{
				printf("ConcreteImplementation: method1() ȣ��!\n");
			}

			virtual void method2() override
			{
				printf("ConcreteImplementation: method2() ȣ��!\n");
			}

			virtual void method3() override
			{
				printf("ConcreteImplementation: method3() ȣ��!\n");
			}
		};

		class Abstraction abstract
		{
		public:
			Abstraction(Implementation* pI)
			{
				i = pI;
			}

			virtual ~Abstraction()
			{
				delete i;
			}

			virtual void feature1() abstract;
			virtual void feature2() abstract;

			Implementation* getI() const
			{
				return i;
			}

		private:
			Implementation* i = nullptr;
		};

		class RefinedAbstraction : public Abstraction
		{
		public:
			using Abstraction::Abstraction;
			virtual ~RefinedAbstraction() = default;

			virtual void feature1() override
			{
				getI()->method1();
			}

			virtual void feature2() override
			{
				getI()->method1();
				getI()->method2();
				getI()->method3();
			}

			void feature3()
			{
				printf("RefinedAbstraction���� �ִ� feature3()!\n");
			}
		};
	}

	namespace use_pattern
	{
		class Monster abstract
		{
		public:
			Monster() = default;
			virtual ~Monster() = default;

			virtual void OnAttack() abstract;
		};

		class AnimalMonster : public Monster
		{
		public:
			using Monster::Monster;
			virtual ~AnimalMonster() = default;

			virtual void OnAttack() override
			{
				printf("������ ������ ����!\n");
			}
		};

		class PlantMonster : public Monster
		{
		public:
			using Monster::Monster;
			virtual ~PlantMonster() = default;

			virtual void OnAttack() override
			{
				printf("�Ĺ��� ������ ����!\n");
			}
		};

		class MonsterSpawner abstract
		{
		public:
			MonsterSpawner() = default;
			virtual ~MonsterSpawner() = default;

			virtual Monster* CreateMonster() abstract;
		};

		class AnimalMonsterSpawner : public MonsterSpawner
		{
		public:
			using MonsterSpawner::MonsterSpawner;
			virtual ~AnimalMonsterSpawner() = default;

			virtual AnimalMonster* CreateMonster() override
			{
				printf("������ ���� ����!\n");
				return (new AnimalMonster());
			}
		};

		class PlantMonsterSpawner : public MonsterSpawner
		{
		public:
			using MonsterSpawner::MonsterSpawner;
			virtual ~PlantMonsterSpawner() = default;

			virtual PlantMonster* CreateMonster() override
			{
				printf("�Ĺ��� ���� ����!\n");
				return (new PlantMonster());
			}
		};

		class Dungeon abstract
		{
		public:
			Dungeon(MonsterSpawner* pSpawner)
			{
				m_pSpawner = pSpawner;
			}

			virtual ~Dungeon()
			{
				delete m_pSpawner;
			}

			virtual Monster* SpawnMonster() abstract;

			MonsterSpawner* getMonsterSpawner() const
			{
				return m_pSpawner;
			}

		private:
			MonsterSpawner* m_pSpawner = nullptr;
		};

		class ForestDungeon final : public Dungeon
		{
		public:
			using Dungeon::Dungeon;
			virtual ~ForestDungeon() = default;

			virtual Monster* SpawnMonster() override
			{
				printf("�� �������� ���� ����!\n");
				return (getMonsterSpawner()->CreateMonster());
			}
		};

		class CaveDungeon final : public Dungeon
		{
		public:
			using Dungeon::Dungeon;
			virtual ~CaveDungeon() = default;

			virtual Monster* SpawnMonster() override
			{
				printf("���� �������� ���� ����!\n");
				return (getMonsterSpawner()->CreateMonster());
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
			printf("<�⺻ Bridge �׽�Ʈ!>\n\n");

			Abstraction* pAbstraction = new RefinedAbstraction(new ConcreteImplementation());

			pAbstraction->feature1();
			printf("\n");
			pAbstraction->feature2();

			delete pAbstraction;
			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<���� ���� �׽�Ʈ!>\n\n");

			Monster* pMonster = nullptr;
			Dungeon* pDungeon = nullptr;

#pragma region �� ���� �׽�Ʈ
			pDungeon = new ForestDungeon(new AnimalMonsterSpawner());
			pMonster = pDungeon->SpawnMonster();
			pMonster->OnAttack();

			delete pMonster;
			delete pDungeon;

			printf("\n");

			pDungeon = new ForestDungeon(new PlantMonsterSpawner());
			pMonster = pDungeon->SpawnMonster();
			pMonster->OnAttack();

			delete pMonster;
			delete pDungeon;
#pragma endregion

			printf("\n");

#pragma region ���� ���� �׽�Ʈ
			pDungeon = new CaveDungeon(new AnimalMonsterSpawner());
			pMonster = pDungeon->SpawnMonster();
			pMonster->OnAttack();

			delete pMonster;
			delete pDungeon;

			printf("\n");

			pDungeon = new CaveDungeon(new PlantMonsterSpawner());
			pMonster = pDungeon->SpawnMonster();
			pMonster->OnAttack();

			delete pMonster;
			delete pDungeon;
#pragma endregion

			printf("\n");
		}
	}
}

int main()
{
	//unit_test::basic::Test();

	//unit_test::use_pattern::Test();
	return 0;
}