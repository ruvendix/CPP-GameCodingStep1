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
		class ServiceInterface abstract
		{
		public:
			ServiceInterface() = default;
			virtual ~ServiceInterface() = default;

			virtual void operation() abstract;
		};

		class Service : public ServiceInterface
		{
		public:
			using ServiceInterface::ServiceInterface;
			
			virtual ~Service()
			{
				printf("Service 객체 소멸!\n");
			}

			virtual void operation() override
			{
				printf("Service::operation()\n");
			}
		};

		class Proxy : public ServiceInterface
		{
		public:
			Proxy(Service* s)
			{
				realService = s;
			}

			virtual ~Proxy()
			{
				if (realService != nullptr)
				{
					delete realService;
				}
			}

			bool checkAccess()
			{
				return true;
			}

			virtual void operation() override
			{
				printf("Proxy::operation()\n");

				// Proxy가 처리할 수 없는 작업이라면 Service에게 전달하기!
				if (checkAccess())
				{
					realService->operation();
				}
			}

		private:
			Service* realService = nullptr;
		};
	}

	namespace variation
	{
		namespace protection_proxy
		{
			enum class EAccessLevel
			{
				NEWBIE = 0,
				MANAGER,
				CEO,
			};

			class IService abstract
			{
			public:
				IService() = default;
				virtual ~IService() = default;

				virtual void Use(EAccessLevel accessLevel) abstract;
			};

			class Service : public IService
			{
			public:
				using IService::IService;

				virtual ~Service()
				{
					printf("Service 객체 소멸!\n");
				}

				virtual void Use(EAccessLevel accessLevel) override
				{
					printf("Service::Use()\n");
				}
			};

			class ServiceProxy : public IService
			{
			public:
				ServiceProxy(Service* pService)
				{
					m_pService = pService;
				}

				virtual ~ServiceProxy()
				{
					if (m_pService != nullptr)
					{
						delete m_pService;
					}
				}

				// 여기가 Protection Proxy의 핵심!
				virtual void Use(EAccessLevel accessLevel) override
				{
					printf("Proxy::Use()\n");

					if (accessLevel == EAccessLevel::MANAGER || accessLevel == EAccessLevel::CEO)
					{
						m_pService->Use(accessLevel);
					}
					else if (accessLevel == EAccessLevel::NEWBIE)
					{
						printf("신입은 권한 없음!\n");
					}
				}

			private:
				Service* m_pService = nullptr;
			};
		}

		namespace virtual_proxy
		{
			class IService abstract
			{
			public:
				IService() = default;
				virtual ~IService() = default;

				virtual void Use() abstract;
			};

			class Service : public IService
			{
			public:
				using IService::IService;

				virtual ~Service()
				{
					printf("Service 객체 소멸!\n");
				}

				virtual void Use() override
				{
					printf("Service::Use()\n");
				}
			};

			class ServiceProxy : public IService
			{
			public:
				using IService::IService;

				virtual ~ServiceProxy()
				{
					if (m_pService != nullptr)
					{
						delete m_pService;
					}
				}

				virtual void Use() override
				{
					printf("Proxy::Use()\n");

					if (m_pService == nullptr)
					{
						m_pService = new Service(); // 여기가 Virtual Proxy의 핵심!
						printf("Service 지연 초기화!\n");
					}

					m_pService->Use();
				}

			private:
				Service* m_pService = nullptr;
			};
		}

		namespace remote_proxy
		{
			class IService abstract
			{
			public:
				IService() = default;
				virtual ~IService() = default;

				virtual void Use() abstract;
			};

			class Service : public IService
			{
			public:
				using IService::IService;

				virtual ~Service()
				{
					// Remote Proxy 테스트할 때만 주석 풀어주세요.
					//printf("Service 객체 소멸!\n");
				}

				virtual void Use() override
				{
					printf("Service::Use()\n");
				}
			};

			// 물리적으로 먼 곳에 있다고 가정할게요.
			// 실제로는 서버를 통해 요청해야 합니다.
			Service g_service;

			class ServiceProxy : public IService
			{
			public:
				using IService::IService;
				virtual ~ServiceProxy() = default;

				virtual void Use() override
				{
					printf("Proxy::Use()\n");

					// 이 부분이 Remote Proxy의 핵심!
					if (IsConnected() == false)
					{
						return;
					}

					printf("원격지에 있는 Service를 호출!\n");
					g_service.Use();
				}

				bool IsConnected() const
				{
					return true;
				}
			};
		}

		namespace smart_proxy
		{
			class Service
			{
			public:
				Service() = default;

				virtual ~Service()
				{
					printf("Service 객체 소멸!\n");
				}

				void Use() const
				{
					printf("Service::Use()\n");
				}

				// 참조 카운트에는 Strong과 Weak가 있는데 여기서는 Strong만 이용할게요.
				// 차이점은 m_refCnt를 직접 사용하느냐 아니냐입니다.

				void IncreaseStrongRef()
				{
					++m_refCnt;
					printf("참조 카운트 증가! (현재값: %d, 주소: %p)\n", m_refCnt, this);
				}

				void DecreaseStrongRef()
				{
					--m_refCnt;
					printf("참조 카운트 감소! (현재값: %d, 주소: %p)\n", m_refCnt, this);

					if (m_refCnt <= 0)
					{
						delete this; // 참조 카운트에서만 사용하세요!
					}
				}

			private:
				int m_refCnt = 0; // 참조 카운트
			};

			class ServiceProxy
			{
			public:
				ServiceProxy(Service* pService)
				{
					m_pService = pService;
					m_pService->IncreaseStrongRef();
				}

				virtual ~ServiceProxy()
				{
					if (m_pService != nullptr)
					{
						m_pService->DecreaseStrongRef();
					}					
				}

				ServiceProxy& operator=(const ServiceProxy& ref)
				{
					if (m_pService != nullptr)
					{
						// 이미 객체를 공유 중인데 새로 들어온 객체도 같을 때는 연산을 무시합니다.
						if (m_pService == ref.m_pService)
						{
							printf("이미 공유 중인 객체!\n");
							return *this;
						}
						else
						{
							printf("새로운 객체가 들어왔으므로 이전 객체의 참조 카운트 감소!\n");
							m_pService->DecreaseStrongRef();
						}
					}

					m_pService = ref.m_pService;
					m_pService->IncreaseStrongRef();

					return *this;
				}

				// Smart Proxy에서는 간접 참조 연산자 재정의 필수입니다!
				Service* operator->()
				{
					return m_pService;
				}

				// Smart Proxy에서는 멤버 접근 연산자 재정의 필수입니다!
				Service& operator*()
				{
					return *m_pService;
				}

			private:
				Service* m_pService = nullptr;
			};
		}
	}

	namespace use_pattern
	{
		class IImage abstract
		{
		public:
			IImage() = default;
			virtual ~IImage() = default;

			virtual void Draw() abstract;
		};

		class Image : public IImage
		{
		public:
			using IImage::IImage;

			virtual ~Image()
			{
				printf("Image 객체 소멸!\n");
			}

			virtual void Draw() override
			{
				printf("Image::Draw()\n");
			}
		};

		class ImageProxy : public IImage
		{
		public:
			using IImage::IImage;

			virtual ~ImageProxy()
			{
				if (m_pService != nullptr)
				{
					delete m_pService;
				}
			}

			virtual void Draw() override
			{
				printf("ImageProxy::Draw()\n");

				if (m_pService == nullptr)
				{
					m_pService = new Image(); // 여기가 Virtual Proxy의 핵심!
					printf("Image 지연 초기화!\n");
				}

				m_pService->Draw();
			}

		private:
			Image* m_pService = nullptr;
		};
	}
}

namespace unit_test
{
	namespace basic
	{
		void Test()
		{
			printf("<기본 Proxy 테스트!>\n\n");
			
			Proxy proxy(new Service());
			proxy.operation();

			printf("\n");
		}
	}

	namespace variation
	{
		namespace protection_proxy
		{
			void Test()
			{
				printf("<보호 프록시 테스트!>\n\n");

				ServiceProxy serviceProxy(new Service());

				printf("신입의 접근 요청!\n");
				serviceProxy.Use(EAccessLevel::NEWBIE);
				printf("\n");

				printf("관리자의 접근 요청!\n");
				serviceProxy.Use(EAccessLevel::MANAGER);
				printf("\n");

				printf("CEO의 접근 요청!\n");
				serviceProxy.Use(EAccessLevel::CEO);
				printf("\n");
			}
		}

		namespace virtual_proxy
		{
			void Test()
			{
				printf("<가상 프록시 테스트!>\n\n");

				ServiceProxy serviceProxy;
				serviceProxy.Use();

				printf("\n");
			}
		}

		namespace remote_proxy
		{
			void Test()
			{
				printf("<원격 프록시 테스트!>\n\n");

				ServiceProxy serviceProxy;
				serviceProxy.Use();

				printf("\n");
			}
		}

		namespace smart_proxy
		{
			void Test()
			{
				printf("<스마트 프록시 테스트!>\n\n");

				ServiceProxy serviceProxy(new Service());
				serviceProxy->Use();
				printf("\n");

				ServiceProxy newServiceProxy(new Service());
				serviceProxy = newServiceProxy;
				serviceProxy = newServiceProxy;

				printf("\n");
			}
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<패턴 적용 테스트!>\n\n");

			ImageProxy imageProxy;
			imageProxy.Draw();

			printf("\n");
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// 프로그램이 시작되는 곳이에요.
int main()
{
	//unit_test::basic::Test();

	//unit_test::variation::protection_proxy::Test();
	//unit_test::variation::virtual_proxy::Test();
	//unit_test::variation::remote_proxy::Test();
	//unit_test::variation::smart_proxy::Test();
	
	//unit_test::use_pattern::Test();
	return 0;
}