// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
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
			static Singleton& getInstance() // 이렇게 하면 객체를 복사하지 않고 반환할 수 있어요!
			{
				if (instance == nullptr)
				{					
					instance = new Singleton(); // 객체를 생성하는 부분입니다!
					printf("Singleton: 객체 생성!\n");
				}

				printf("Singleton: 객체 반환!\n");
				return *instance;
			}

		private:
			static Singleton* instance;
		};

		// static은 초기화가 필수에요!
		Singleton* Singleton::instance = nullptr;
	}

	namespace meyers_singleton
	{
		class MeyersSingleton
		{
		public:
			static MeyersSingleton& I()
			{
				static MeyersSingleton instance; // C++11 이상에서는 지역 static이 Thread-Safe해요!
				return instance;
			}

			// 복사 연산과 이동 연산을 막습니다.
			MeyersSingleton(const MeyersSingleton&) = delete;
			MeyersSingleton(const MeyersSingleton&&) = delete;
			MeyersSingleton& operator=(const MeyersSingleton&) = delete;
			MeyersSingleton&& operator=(const MeyersSingleton&&) = delete;

			void ShowData()
			{
				printf("Data: %d\n", m_data);
			}

		private:
			// 외부에서의 생성과 소멸을 막습니다.
			MeyersSingleton() = default;
			~MeyersSingleton() = default;

			int m_data = 0; // 원하는 데이터를 넣으면 됩니다.
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
					new(m_pInst) PhoenixSingleton; // #include <new> 필요
					std::atexit(Destroy); // #include <cstdlib> 필요
					m_bDead = true;
				}

				if (m_pInst == nullptr)
				{
					Create();
				}

				return *m_pInst;
			}

			// 복사 연산과 이동 연산을 막습니다.
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

			int m_data = 0; // 원하는 데이터를 넣으면 됩니다.
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

			// 복사 연산과 이동 연산을 막습니다.
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

			static std::unique_ptr<ThreadSafeSingleton> m_spInst; // #include <memory> 필요
			static std::once_flag m_onceFlag; // #include <mutex> 필요

			int m_data = 0; // 원하는 데이터를 넣으면 됩니다.
		};

		std::unique_ptr<ThreadSafeSingleton> ThreadSafeSingleton::m_spInst = nullptr;
		std::once_flag ThreadSafeSingleton::m_onceFlag;
	}

	namespace use_pattern
	{
		class GameObj
		{
		public:
			// Singleton의 대상이 되는 클래스도 외부 생성 및 소멸을 막는 게 좋아요!
			friend class GameObjMgr;

			void ShowName() const
			{
				printf("이름: %s\n", m_strName.c_str());
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
				static GameObjMgr instance; // C++11 이상에서는 지역 static이 Thread-Safe해요!
				return instance;
			}

			// 복사 연산과 이동 연산을 막습니다.
			GameObjMgr(const GameObjMgr&) = delete;
			GameObjMgr(const GameObjMgr&&) = delete;
			GameObjMgr& operator=(const GameObjMgr&) = delete;
			GameObjMgr&& operator=(const GameObjMgr&&) = delete;

			void CreateAndAddGameObj(const std::string& strName)
			{
				m_vecGameObj.push_back(new GameObj(strName));
				printf("\"%s\" 추가!\n", strName.c_str());
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
			printf("<기본 Singleton 테스트!>\n\n");
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
			printf("<MeyersSingleton 테스트!>\n\n");
			MeyersSingleton::I().ShowData();
			printf("\n");
		}
	}

	namespace phoenix_singleton
	{
		void Test()
		{
			printf("<PhoenixSingleton 테스트!>\n\n");
			PhoenixSingleton::I().ShowData();
			printf("\n");
		}
	}

	namespace thread_safe_singleton
	{
		void Test()
		{
			printf("<ThreadSafeSingleton 테스트!>\n\n");
			ThreadSafeSingleton::I().ShowData();
			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<패턴 적용 테스트!>\n\n");

			GameObjMgr::I().CreateAndAddGameObj("좀비");
			GameObjMgr::I().CreateAndAddGameObj("스켈레톤");
			GameObjMgr::I().CreateAndAddGameObj("자이언트 웜");
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