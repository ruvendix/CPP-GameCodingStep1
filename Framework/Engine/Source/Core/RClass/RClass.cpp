// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ���� Ŭ������ ��Ÿ���� �뵵�Դϴ�.
// =====================================================================================
#include "EnginePCH.h"
#include "RClass.h"

void RClass::StartUp()
{
	InitClassMetadata();
}

bool RClass::IsUpperClass(RClass* pUpper) // �ڽ� �������� ��
{
	bool bRet = false;
	for (RClass* p = this; p != nullptr; p = p->GetParentClass())
	{
		if (p == pUpper)
		{
			bRet = true;
			break;
		}
	}

	return bRet;
}