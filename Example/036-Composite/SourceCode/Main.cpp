#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>

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

		class Composite final : public Component
		{
		public:
			using Component::Component;

			virtual ~Composite()
			{
				for (auto& iter : m_vecComponent)
				{
					delete iter;
				}
			}

			void add(Component* pComponent)
			{
				m_vecComponent.push_back(pComponent);
				printf("������Ʈ �߰�: %p\n", pComponent);
			}

			void remove(Component* pComponent)
			{
				const auto& iterEnd = m_vecComponent.cend();
				for (auto iter = m_vecComponent.cbegin(); iter != iterEnd; ++iter)
				{
					if (*iter == pComponent)
					{
						printf("������Ʈ ����: %p\n", *iter);

						delete* iter;
						m_vecComponent.erase(iter);

						break;
					}
				}
			}

			virtual void execute() override
			{
				printf("\n");
				printf("Composite: excute() ȣ��! (%p)\n", this);
				for (auto& iter : m_vecComponent)
				{
					printf("Component �ּ�: %p\n", iter);
					iter->execute();
				}
				printf("\n");
			}

			Component* getComponent(int idx)
			{
				return m_vecComponent[idx];
			}

		private:
			std::vector<Component*> m_vecComponent;
		};

		class Leaf final : public Component
		{
		public:
			using Component::Component;
			virtual ~Leaf() = default;

			virtual void execute() override
			{
				//printf("Leaf�� �ּ�: %p\n", this);
			}
		};
	}

	namespace use_pattern
	{
		class Obj abstract
		{
		public:
			Obj(const std::string& strName) :
				m_strName(strName)
			{

			}

			virtual ~Obj() = default;

			virtual void OnExcute() const abstract;

			const std::string& getName() const
			{
				return m_strName;
			}

		private:
			std::string m_strName;
		};

		class Tree : public Obj
		{
		public:
			using Obj::Obj;
			virtual ~Tree() = default;

			virtual void OnExcute() const override
			{
				printf("���� �߿��� \"%s\" ó��!\n", getName().c_str());
			}
		};

		class Car : public Obj
		{
		public:
			using Obj::Obj;
			virtual ~Car() = default;

			virtual void OnExcute() const override
			{
				printf("���� �߿��� \"%s\" ó��!\n", getName().c_str());
			}
		};

		class ObjGroup final : public Obj
		{
		public:
			using Obj::Obj;

			virtual ~ObjGroup()
			{
				for (auto& iter : m_vecObj)
				{
					delete iter;
				}
			}

			void Add(Obj* pObj)
			{
				m_vecObj.push_back(pObj);
				printf("������Ʈ �߰�: \"%s\"\n", pObj->getName().c_str());
			}

			void Remove(Obj* pObj)
			{
				const auto& iterEnd = m_vecObj.cend();
				for (auto iter = m_vecObj.cbegin(); iter != iterEnd; ++iter)
				{
					if (*iter == pObj)
					{
						printf("������Ʈ ����: \"%s\"\n", pObj->getName().c_str());

						delete* iter;
						m_vecObj.erase(iter);

						break;
					}
				}
			}

			virtual void OnExcute() const override
			{
				printf("\n");
				printf("������Ʈ ó��: %s\n", getName().c_str());

				for (auto& iter : m_vecObj)
				{
					iter->OnExcute();
				}
			}

			Obj* getObj(int idx)
			{
				return m_vecObj[idx];
			}

		private:
			std::vector<Obj*> m_vecObj;
		};
	}
}

namespace unit_test
{
	namespace basic
	{
		void Test()
		{
			printf("<�⺻ Composite �׽�Ʈ!>\n\n");

			Composite mainComposite;
			mainComposite.add(new Leaf());
			mainComposite.add(new Leaf());
			mainComposite.add(new Leaf());
			mainComposite.execute();

			Composite* pSubComposite = new Composite();
			printf("SubComposite �ּ�: %p\n", pSubComposite);

			pSubComposite->add(new Leaf());
			pSubComposite->add(new Leaf());

			printf("\n");
			printf("SubComposite �߰�!\n");
			mainComposite.add(pSubComposite);

			// SubComposite �߰� �� �׽�Ʈ
			mainComposite.execute();

			mainComposite.remove(mainComposite.getComponent(3));
			mainComposite.execute();
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<���� ���� �׽�Ʈ!>\n\n");

			ObjGroup mainObjGroup("���� ������Ʈ �׷�");
			mainObjGroup.Add(new Tree("�ҳ���"));
			mainObjGroup.Add(new Tree("�������"));
			mainObjGroup.Add(new Car("����"));
			mainObjGroup.OnExcute();

			printf("\n");
			ObjGroup* pSubObjGroup = new ObjGroup("���� ������Ʈ �׷�");
			pSubObjGroup->Add(new Tree("�質��"));
			pSubObjGroup->Add(new Car("Ʈ��"));
			
			printf("\n");
			mainObjGroup.Add(pSubObjGroup);

			// ���� ������Ʈ �׷� �߰� �� �׽�Ʈ
			mainObjGroup.OnExcute();

			printf("\n");
			mainObjGroup.Remove(mainObjGroup.getObj(3));
			mainObjGroup.OnExcute();

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