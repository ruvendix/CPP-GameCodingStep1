// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ���� Ŭ������ ��Ÿ���� �뵵�Դϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonMacro.h"

class RClass
{
	GENERATE_HIERARCHY_COMMON(RClass);

public:
	RClass() = default;
	virtual ~RClass() = default;

	virtual void StartUp();
	virtual void InitClassMetadata() { }

	bool IsUpperClass(RClass* pUpper);

	RClass* GetClass() const { return m_pClass; }
	void SetClass(RClass* pClass) { m_pClass = pClass; }

	RClass* GetParentClass() const { return m_pParentClass; }
	void SetParentClass(RClass* pParentClass) { m_pParentClass = pParentClass; }

private:
	RClass* m_pClass = nullptr;
	RClass* m_pParentClass = nullptr;
};