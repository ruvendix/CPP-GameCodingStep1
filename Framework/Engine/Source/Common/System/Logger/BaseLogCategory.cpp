// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �α� ī�װ��� ����Դϴ�.
// =====================================================================================
#include "EnginePCH.h"
#include "BaseLogCategory.h"

Bool BaseLogCategory::CheckActivate() const
{
    if (m_bActivation == true)
    {
        return true;
    }

    return false;
}
