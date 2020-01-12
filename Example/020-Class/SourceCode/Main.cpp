// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <memory>

using Int32 = signed __int32;
using Real32 = float;

// �θ� Ŭ��������.
class Parent
{
public:
#pragma region ������ �� �Ҹ���
	Parent() // �⺻ �����ڿ���.
	{
		printf("�θ� ������ ȣ��!\n");
	}

	explicit Parent(Int32 data) :
		m_data(data) // ���� �� �ʱ�ȭ�� �ϴ� ���!
	{
		printf("Int32 �ϳ��� ���ڷ� �޴� �θ� ������ ȣ��!\n");
	}

	explicit Parent(Real32 data) :
		Parent(static_cast<Int32>(data)) // ������ ����
	{
		printf("Real32 �ϳ��� ���ڷ� �޴� �θ� ������ ȣ��!\n");
	}

	// ���� �����ڸ� ����� �Ǹ�
	// �ڵ� �̵� �����ڴ� ��������� �ʾƿ�!
	Parent(const Parent& lVal)
	{
		printf("�θ� ���� ������ ȣ��!\n");
	}

	// �̵� �����ڸ� ����� �Ǹ�
	// �ڵ� ���� �����ڴ� ��������� �ʾƿ�!
	Parent(const Parent&& rVal)
	{
		printf("�θ� �̵� ������ ȣ��!\n");
	}

	virtual ~Parent()
	{
		printf("�θ� �Ҹ��� ȣ��!\n");
	}
#pragma endregion

#pragma region ������
	// getter��� �ؿ�.
	// const�� �׻� �ٿ��ּ���!
	Int32 getData() const
	{
		return m_data;
	}

	// setter��� �ؿ�.
	void setData(Int32 data)
	{
		m_data = data;
	}
#pragma endregion

private:
	Int32 m_data = 0; // static�� �ƴ϶�� ��� �ʱ�ȭ ����!
};

// �ڽ� Ŭ��������.
// �̷��� �θ����׼� ���� �� �״�� ����� ��� "����(�� ����) ���(�޾Ҵ�)"�̶�� �ؿ�.
class Child : public Parent
{
public:
	using Parent::Parent; // ������ ���

#pragma region ������ �� �Ҹ���
	// ��� ���迡���� "�θ� ������ ȣ�� -> �ڽ� ������ ȣ��" �̷� ������ �ſ�!
	Child() :
		Parent() // ��� ���迡���� ������ ȣ�� ���谡 �����־��!
	{
		printf("�ڽ� ������ ȣ��!\n");
	}

	// ��� ���迡���� "�ڽ� �Ҹ��� ȣ�� -> �θ� �Ҹ��� ȣ��" �̷� ������ �ſ�!
	virtual ~Child()
	{
		printf("�ڽ� �Ҹ��� ȣ��!\n");
	}
#pragma endregion

	void CallChildFunc()
	{
		printf("�ڽ� �Լ� ȣ��!\n");
	}
};

// �θ� Ŭ������ �����ϴ� �Լ�����.
Parent CreateParent()
{
	Parent parent;
	printf("\n");
	return parent;
}

// �ڽ� Ŭ������ �����ϴ� �Լ�����.
Child CreateChild()
{
	Child child;
	printf("\n");
	return child;
}

//////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
Int32 main()
{
#if 0
	Parent parent;
	printf("parent�� m_data : %d\n", parent.getData());
#endif

#if 0
	Parent parent(10.02f);
	printf("parent�� m_data : %d\n", parent.getData());
#endif

#if 0
	Parent parent = CreateParent();
	printf("parent�� m_data : %d\n", parent.getData());
#endif

#if 0
	Child child = CreateChild();
	child.setData(13);
	printf("child�� m_data : %d\n", child.getData());
#endif

#if 0
	Parent* pSomething = new Child; // ��ĳ����
	dynamic_cast<Child*>(pSomething)->CallChildFunc(); // �ٿ�ĳ����
	delete pSomething;
#endif

#if 0
	std::unique_ptr<Parent> pSomething = std::make_unique<Child>(); // ��ĳ����
	dynamic_cast<Child*>(pSomething.get())->CallChildFunc(); // �ٿ�ĳ����
#endif

	printf("\n");
	return 0;
}