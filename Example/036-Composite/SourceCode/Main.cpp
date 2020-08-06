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
				printf("컴포넌트 추가: %p\n", pComponent);
			}

			void remove(Component* pComponent)
			{
				const auto& iterEnd = m_vecComponent.cend();
				for (auto iter = m_vecComponent.cbegin(); iter != iterEnd; ++iter)
				{
					if (*iter == pComponent)
					{
						printf("컴포넌트 삭제: %p\n", *iter);

						delete* iter;
						m_vecComponent.erase(iter);

						break;
					}
				}
			}

			virtual void execute() override
			{
				printf("\n");
				printf("Composite: excute() 호출! (%p)\n", this);
				for (auto& iter : m_vecComponent)
				{
					printf("Component 주소: %p\n", iter);
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
				//printf("Leaf의 주소: %p\n", this);
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
				printf("나무 중에서 \"%s\" 처리!\n", getName().c_str());
			}
		};

		class Car : public Obj
		{
		public:
			using Obj::Obj;
			virtual ~Car() = default;

			virtual void OnExcute() const override
			{
				printf("차량 중에서 \"%s\" 처리!\n", getName().c_str());
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
				printf("오브젝트 추가: \"%s\"\n", pObj->getName().c_str());
			}

			void Remove(Obj* pObj)
			{
				const auto& iterEnd = m_vecObj.cend();
				for (auto iter = m_vecObj.cbegin(); iter != iterEnd; ++iter)
				{
					if (*iter == pObj)
					{
						printf("오브젝트 삭제: \"%s\"\n", pObj->getName().c_str());

						delete* iter;
						m_vecObj.erase(iter);

						break;
					}
				}
			}

			virtual void OnExcute() const override
			{
				printf("\n");
				printf("오브젝트 처리: %s\n", getName().c_str());

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
			printf("<기본 Composite 테스트!>\n\n");

			Composite mainComposite;
			mainComposite.add(new Leaf());
			mainComposite.add(new Leaf());
			mainComposite.add(new Leaf());
			mainComposite.execute();

			Composite* pSubComposite = new Composite();
			printf("SubComposite 주소: %p\n", pSubComposite);

			pSubComposite->add(new Leaf());
			pSubComposite->add(new Leaf());

			printf("\n");
			printf("SubComposite 추가!\n");
			mainComposite.add(pSubComposite);

			// SubComposite 추가 후 테스트
			mainComposite.execute();

			mainComposite.remove(mainComposite.getComponent(3));
			mainComposite.execute();
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<패턴 적용 테스트!>\n\n");

			ObjGroup mainObjGroup("메인 오브젝트 그룹");
			mainObjGroup.Add(new Tree("소나무"));
			mainObjGroup.Add(new Tree("사과나무"));
			mainObjGroup.Add(new Car("버스"));
			mainObjGroup.OnExcute();

			printf("\n");
			ObjGroup* pSubObjGroup = new ObjGroup("서브 오브젝트 그룹");
			pSubObjGroup->Add(new Tree("배나무"));
			pSubObjGroup->Add(new Car("트럭"));
			
			printf("\n");
			mainObjGroup.Add(pSubObjGroup);

			// 서브 오브젝트 그룹 추가 후 테스트
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