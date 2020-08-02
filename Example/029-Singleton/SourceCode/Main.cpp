// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <cstdlib>
#include <new>
#include <memory>
#include <mutex>
#include <vector>
#include <string>

namespace unit_test
{
	namespace basic
	{
		class Singleton
		{
		public:
			static Singleton& getInstance() // �̷��� �ϸ� ��ü�� �������� �ʰ� ��ȯ�� �� �־��!
			{
				if (instance == nullptr)
				{					
					instance = new Singleton(); // ��ü�� �����ϴ� �κ��Դϴ�!
					printf("Singleton: ��ü ����!\n");
				}

				printf("Singleton: ��ü ��ȯ!\n");
				return *instance;
			}

		private:
			static Singleton* instance;
		};

		// static�� �ʱ�ȭ�� �ʼ�����!
		Singleton* Singleton::instance = nullptr;
	}

	namespace meyers_singleton
	{
		class MeyersSingleton
		{
		public:
			static MeyersSingleton& I()
			{
				static MeyersSingleton instance; // C++11 �̻󿡼��� ���� static�� Thread-Safe�ؿ�!
				return instance;
			}

			// ���� ����� �̵� ������ �����ϴ�.
			MeyersSingleton(const MeyersSingleton&) = delete;
			MeyersSingleton(const MeyersSingleton&&) = delete;
			MeyersSingleton& operator=(const MeyersSingleton&) = delete;
			MeyersSingleton&& operator=(const MeyersSingleton&&) = delete;

			void ShowData()
			{
				printf("Data: %d\n", m_data);
			}

		private:
			// �ܺο����� ������ �Ҹ��� �����ϴ�.
			MeyersSingleton() = default;
			~MeyersSingleton() = default;

			int m_data = 0; // ���ϴ� �����͸� ������ �˴ϴ�.
		};
	}

	namespace phoenix_singleton
	{
		class PhoenixSingleton
		{
		public:
			static void Create()
			{
				static PhoenixSingleton inst;
				m_pInst = &inst;
			}

			static void Destroy()
			{
				m_pInst->~PhoenixSingleton();
			}

			static PhoenixSingleton& I()
			{
				if (m_bDead == true)
				{
					Create();
					new(m_pInst) PhoenixSingleton; // #include <new> �ʿ�
					std::atexit(Destroy); // #include <cstdlib> �ʿ�
					m_bDead = true;
				}

				if (m_pInst == nullptr)
				{
					Create();
				}

				return *m_pInst;
			}

			// ���� ����� �̵� ������ �����ϴ�.
			PhoenixSingleton(const PhoenixSingleton&) = delete;
			PhoenixSingleton(const PhoenixSingleton&&) = delete;
			PhoenixSingleton& operator=(const PhoenixSingleton&) = delete;
			PhoenixSingleton&& operator=(const PhoenixSingleton&&) = delete;

			void ShowData()
			{
				printf("Data: %d\n", m_data);
			}

		private:
			PhoenixSingleton() = default;
			~PhoenixSingleton() = default;

			static bool m_bDead;
			static PhoenixSingleton* m_pInst;

			int m_data = 0; // ���ϴ� �����͸� ������ �˴ϴ�.
		};

		bool PhoenixSingleton::m_bDead = false;
		PhoenixSingleton* PhoenixSingleton::m_pInst = nullptr;
	}

	namespace thread_safe_singleton
	{
		class ThreadSafeSingleton
		{
		public:

			static ThreadSafeSingleton& I()
			{
				std::call_once(m_onceFlag,
					[]()
					{
						m_spInst.reset(new ThreadSafeSingleton(PassKey()));
					});
				return *m_spInst;
			}

			// ���� ����� �̵� ������ �����ϴ�.
			ThreadSafeSingleton(const ThreadSafeSingleton&) = delete;
			ThreadSafeSingleton(const ThreadSafeSingleton&&) = delete;
			ThreadSafeSingleton& operator=(const ThreadSafeSingleton&) = delete;
			ThreadSafeSingleton&& operator=(const ThreadSafeSingleton&&) = delete;

			void ShowData()
			{
				printf("Data: %d\n", m_data);
			}

		private:
			class PassKey
			{
			private:
				friend class ThreadSafeSingleton;

				PassKey() = default;
				~PassKey() = default;
			};

			explicit ThreadSafeSingleton(const PassKey& passKey) { }

			static std::unique_ptr<ThreadSafeSingleton> m_spInst; // #include <memory> �ʿ�
			static std::once_flag m_onceFlag; // #include <mutex> �ʿ�

			int m_data = 0; // ���ϴ� �����͸� ������ �˴ϴ�.
		};

		std::unique_ptr<ThreadSafeSingleton> ThreadSafeSingleton::m_spInst = nullptr;
		std::once_flag ThreadSafeSingleton::m_onceFlag;
	}

	namespace use_pattern
	{
		class GameObj
		{
		public:
			// Singleton�� ����� �Ǵ� Ŭ������ �ܺ� ���� �� �Ҹ��� ���� �� ���ƿ�!
			friend class GameObjMgr;

			void ShowName() const
			{
				printf("�̸�: %s\n", m_strName.c_str());
			}

		private:
			GameObj() = default;
			~GameObj() = default;

			explicit GameObj(const std::string& strName) :
				m_strName(strName)
			{

			}

			std::string m_strName;
		};

		class GameObjMgr
		{
		public:
			static GameObjMgr& I()
			{
				static GameObjMgr instance; // C++11 �̻󿡼��� ���� static�� Thread-Safe�ؿ�!
				return instance;
			}

			// ���� ����� �̵� ������ �����ϴ�.
			GameObjMgr(const GameObjMgr&) = delete;
			GameObjMgr(const GameObjMgr&&) = delete;
			GameObjMgr& operator=(const GameObjMgr&) = delete;
			GameObjMgr&& operator=(const GameObjMgr&&) = delete;

			void CreateAndAddGameObj(const std::string& strName)
			{
				m_vecGameObj.push_back(new GameObj(strName));
				printf("\"%s\" �߰�!\n", strName.c_str());
			}

			void ShowGameObjNameTable()
			{
				for (auto& iter : m_vecGameObj)
				{
					if (iter == nullptr)
					{
						continue;
					}

					iter->ShowName();
				}
			}

		private:
			GameObjMgr()
			{
				m_vecGameObj.reserve(8);
			}

			~GameObjMgr()
			{
				for (auto& iter : m_vecGameObj)
				{
					delete iter;
					iter = nullptr;
				}
			}

			std::vector<GameObj*> m_vecGameObj;
		};
	}
}

namespace unit_test
{
	namespace basic
	{
		void Test()
		{
			printf("<�⺻ Singleton �׽�Ʈ!>\n\n");
			Singleton::getInstance();
			Singleton::getInstance();
			Singleton::getInstance();
			printf("\n");
		}
	}

	namespace meyers_singleton
	{
		void Test()
		{
			printf("<MeyersSingleton �׽�Ʈ!>\n\n");
			MeyersSingleton::I().ShowData();
			printf("\n");
		}
	}

	namespace phoenix_singleton
	{
		void Test()
		{
			printf("<PhoenixSingleton �׽�Ʈ!>\n\n");
			PhoenixSingleton::I().ShowData();
			printf("\n");
		}
	}

	namespace thread_safe_singleton
	{
		void Test()
		{
			printf("<ThreadSafeSingleton �׽�Ʈ!>\n\n");
			ThreadSafeSingleton::I().ShowData();
			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<���� ���� �׽�Ʈ!>\n\n");

			GameObjMgr::I().CreateAndAddGameObj("����");
			GameObjMgr::I().CreateAndAddGameObj("���̷���");
			GameObjMgr::I().CreateAndAddGameObj("���̾�Ʈ ��");
			printf("\n");

			GameObjMgr::I().ShowGameObjNameTable();
			printf("\n");
		}
	}
}

int main()
{
	//unit_test::basic::Test();
	//unit_test::meyers_singleton::Test();
	//unit_test::phoenix_singleton::Test();
	//unit_test::thread_safe_singleton::Test();

	unit_test::use_pattern::Test();
	return 0;
}