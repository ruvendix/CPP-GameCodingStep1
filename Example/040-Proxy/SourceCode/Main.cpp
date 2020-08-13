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
				printf("Service ��ü �Ҹ�!\n");
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

				// Proxy�� ó���� �� ���� �۾��̶�� Service���� �����ϱ�!
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
					printf("Service ��ü �Ҹ�!\n");
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

				// ���Ⱑ Protection Proxy�� �ٽ�!
				virtual void Use(EAccessLevel accessLevel) override
				{
					printf("Proxy::Use()\n");

					if (accessLevel == EAccessLevel::MANAGER || accessLevel == EAccessLevel::CEO)
					{
						m_pService->Use(accessLevel);
					}
					else if (accessLevel == EAccessLevel::NEWBIE)
					{
						printf("������ ���� ����!\n");
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
					printf("Service ��ü �Ҹ�!\n");
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
						m_pService = new Service(); // ���Ⱑ Virtual Proxy�� �ٽ�!
						printf("Service ���� �ʱ�ȭ!\n");
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
					// Remote Proxy �׽�Ʈ�� ���� �ּ� Ǯ���ּ���.
					//printf("Service ��ü �Ҹ�!\n");
				}

				virtual void Use() override
				{
					printf("Service::Use()\n");
				}
			};

			// ���������� �� ���� �ִٰ� �����ҰԿ�.
			// �����δ� ������ ���� ��û�ؾ� �մϴ�.
			Service g_service;

			class ServiceProxy : public IService
			{
			public:
				using IService::IService;
				virtual ~ServiceProxy() = default;

				virtual void Use() override
				{
					printf("Proxy::Use()\n");

					// �� �κ��� Remote Proxy�� �ٽ�!
					if (IsConnected() == false)
					{
						return;
					}

					printf("�������� �ִ� Service�� ȣ��!\n");
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
					printf("Service ��ü �Ҹ�!\n");
				}

				void Use() const
				{
					printf("Service::Use()\n");
				}

				// ���� ī��Ʈ���� Strong�� Weak�� �ִµ� ���⼭�� Strong�� �̿��ҰԿ�.
				// �������� m_refCnt�� ���� ����ϴ��� �ƴϳ��Դϴ�.

				void IncreaseStrongRef()
				{
					++m_refCnt;
					printf("���� ī��Ʈ ����! (���簪: %d, �ּ�: %p)\n", m_refCnt, this);
				}

				void DecreaseStrongRef()
				{
					--m_refCnt;
					printf("���� ī��Ʈ ����! (���簪: %d, �ּ�: %p)\n", m_refCnt, this);

					if (m_refCnt <= 0)
					{
						delete this; // ���� ī��Ʈ������ ����ϼ���!
					}
				}

			private:
				int m_refCnt = 0; // ���� ī��Ʈ
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
						// �̹� ��ü�� ���� ���ε� ���� ���� ��ü�� ���� ���� ������ �����մϴ�.
						if (m_pService == ref.m_pService)
						{
							printf("�̹� ���� ���� ��ü!\n");
							return *this;
						}
						else
						{
							printf("���ο� ��ü�� �������Ƿ� ���� ��ü�� ���� ī��Ʈ ����!\n");
							m_pService->DecreaseStrongRef();
						}
					}

					m_pService = ref.m_pService;
					m_pService->IncreaseStrongRef();

					return *this;
				}

				// Smart Proxy������ ���� ���� ������ ������ �ʼ��Դϴ�!
				Service* operator->()
				{
					return m_pService;
				}

				// Smart Proxy������ ��� ���� ������ ������ �ʼ��Դϴ�!
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
				printf("Image ��ü �Ҹ�!\n");
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
					m_pService = new Image(); // ���Ⱑ Virtual Proxy�� �ٽ�!
					printf("Image ���� �ʱ�ȭ!\n");
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
			printf("<�⺻ Proxy �׽�Ʈ!>\n\n");
			
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
				printf("<��ȣ ���Ͻ� �׽�Ʈ!>\n\n");

				ServiceProxy serviceProxy(new Service());

				printf("������ ���� ��û!\n");
				serviceProxy.Use(EAccessLevel::NEWBIE);
				printf("\n");

				printf("�������� ���� ��û!\n");
				serviceProxy.Use(EAccessLevel::MANAGER);
				printf("\n");

				printf("CEO�� ���� ��û!\n");
				serviceProxy.Use(EAccessLevel::CEO);
				printf("\n");
			}
		}

		namespace virtual_proxy
		{
			void Test()
			{
				printf("<���� ���Ͻ� �׽�Ʈ!>\n\n");

				ServiceProxy serviceProxy;
				serviceProxy.Use();

				printf("\n");
			}
		}

		namespace remote_proxy
		{
			void Test()
			{
				printf("<���� ���Ͻ� �׽�Ʈ!>\n\n");

				ServiceProxy serviceProxy;
				serviceProxy.Use();

				printf("\n");
			}
		}

		namespace smart_proxy
		{
			void Test()
			{
				printf("<����Ʈ ���Ͻ� �׽�Ʈ!>\n\n");

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
			printf("<���� ���� �׽�Ʈ!>\n\n");

			ImageProxy imageProxy;
			imageProxy.Draw();

			printf("\n");
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
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