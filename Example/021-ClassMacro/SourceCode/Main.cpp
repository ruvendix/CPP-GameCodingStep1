// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <crtdbg.h>
#include <cstdio>
#include <memory>

using Int32 = signed __int32;
using Real32 = float;

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__ )                                            
#endif

#define SAFE_DELETE(ptr)\
	if (ptr != nullptr)\
	{\
		delete ptr;\
		ptr = nullptr;\
	}

// ���� �� �̵��� �����ϴ� ��ũ�ο���. (Copy Semantics, Move Semantics)
#define NON_COPYABLE_CLASS(TClass)\
public:\
	TClass(const TClass&) = delete;\
	TClass(const TClass&&) = delete;\
	TClass& operator=(const TClass&) = delete;\
	TClass&& operator=(const TClass&&) = delete;

// �ܺο����� ���� �� �Ҹ��� ���� ��ũ�ο���. (�⺻ �����ڸ� ����)
// ������ ��� ���迡���� ���� �����ϰ� ����� �ؿ�.
#define NON_EXTERNAL_CLASS(TClass)\
protected:\
	TClass() = default;\
	virtual ~TClass() = default;

class NonCopyableParent
{
	NON_COPYABLE_CLASS(NonCopyableParent);

public:
	NonCopyableParent() = default;
	virtual ~NonCopyableParent() = default;
};

class NonCopyableChild : NonCopyableParent
{
public:
	NonCopyableChild() = default;
	virtual ~NonCopyableChild() = default;
};

class NonExternalParent
{
	NON_EXTERNAL_CLASS(NonExternalParent);

public:
	// �θ� �����ؼ� ��ȯ�ϴ� �Լ�����.
	static NonExternalParent* Create()
	{
		printf("�θ� �����߾��!\n");
		return new NonExternalParent;
	}

	// ������ �θ� �����ϴ� �Լ�����.
	static void Delete(NonExternalParent* pParent)
	{
		printf("�θ� �����߾��!\n");
		delete pParent;
	}
};

class NonExternalChild : NonExternalParent
{
public:
	NonExternalChild() = default;
	virtual ~NonExternalChild() = default;

	static NonExternalParent* CreateParent()
	{
		printf("�ڽĿ��� �θ� �����ҰԿ�!\n");

		// ��� ���迡���� �����ڿ� ������ �� �����!
		//NonExternalParent parent;
		//NonExternalParent* pParent = new NonExternalParent;
		//std::unique_ptr<NonExternalParent> spParent = std::make_unique<NonExternalParent>();

		// �θ��� �Լ��� �̿��ϸ� �̷��� ������ �� �־��!
		return NonExternalParent::Create();
	}
};

// NON_COPYABLE_CLASS�� NON_EXTERNAL_CLASS�� ���� �̱��� Ŭ��������.
// �ν��Ͻ��� �����ϴ� �κ��� ��� ���� ������...
// �̱����� ���ǰ� �ν��Ͻ� ������ �����ϴ� ���̹Ƿ� �ּ��� 1���� ������ �ؿ�.
class Singleton
{
	NON_COPYABLE_CLASS(Singleton);
	NON_EXTERNAL_CLASS(Singleton);

public:
	static Singleton* I() // ���� ȣ��ǹǷ� ������ ª�� �̸�����! (I�� Instance�� ����)
	{
		if (m_pInst == nullptr)
		{
			m_pInst = new Singleton;
		}

		return m_pInst;
	}

	static void Destroy() // �ܺο��� �Ҹ��ڿ� ������ �� �����Ƿ� ���� ��������� �ؿ�!
	{
		SAFE_DELETE(m_pInst);
	}

	void Log()
	{
		printf("�̱��� �׽�Ʈ �α�!\n");
	}

private:
	static Singleton* m_pInst;
};

Singleton* Singleton::m_pInst = nullptr;

//////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
Int32 main()
{
	// �޸� ������ Ȯ���ϴ� ����̿���.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#if 0 // NON_COPYABLE_CLASS�� �׽�Ʈ�غ��Կ�.	
	NonCopyableParent firstParent;
	NonCopyableParent secondParent;
	//firstParent = secondParent; // ���� ������ �������!

	NonCopyableChild firstChild;
	NonCopyableChild secondChild;
	//firstChild = secondChild; // ��� ���赵 ������!
#endif

#if 0 // NON_EXTERNAL_CLASS�� �׽�Ʈ�غ��Կ�.
	//NonExternalParent parent; // �ܺο����� ������ �������!
	NonExternalChild child; // ��� ������ �����ؿ�!

	//NonExternalParent* pParent = new NonExternalParent; // �����Ҵ絵 ������!
	NonExternalChild* pChild = new NonExternalChild; // ��� ������ �����ؿ�!
	SAFE_DELETE(pChild);

	//std::unique_ptr<NonExternalParent> spParent = std::make_unique<NonExternalParent>(); // ����Ʈ �����͵� ������!
	std::unique_ptr<NonExternalChild> spChild = std::make_unique<NonExternalChild>(); // ��� ������ �����ؿ�!

	// �ܺο����� �θ��� �Լ��� �̿��ؼ� ������ �� �־��!
	// ������ �Ҹ굵 ��������� ����...
	NonExternalParent* pParent = NonExternalParent::Create();
	NonExternalParent::Delete(pParent);

	// �����ϱ� ���������� �ܺο����� �ڽ��� �Լ��� �̿��ؼ� ������ ���� �־��!
	// �̷��� ���� ������ �״�� �̿��ϴ� ����� ���� �Ǵ� ����Ͷ�� ����.
	// �ٸ� ���� ǥ���ϸ� �������̽��� ����� ������ �Ѵٰ� �ؿ�.
	NonExternalParent* pParentFromChild = NonExternalChild::CreateParent();
	NonExternalParent::Delete(pParentFromChild);
#endif

#if 0 // NON_COPYABLE_CLASS�� NON_EXTERNAL_CLASS�� ����� �̱����� �����帱�Կ�.
	//Singleton singleton; // �ܺο��� ������ �� �����!
	Singleton* pSingleton = Singleton::I(); // �����ͷ� ������ ���� �־��!
	//delete pSingleton; // ������ �ܺο����� ������ �� �����!

	Singleton::I()->Log(); // �̱����� �Լ� ȣ�� ����̿���!
	Singleton::Destroy(); // �̱����� �ܺο��� ������ �� �����Ƿ� �̷��� ��������� �ؿ�!
#endif

	return 0;
}