// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 계층 관계 클래스를 나타내는 용도입니다.
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