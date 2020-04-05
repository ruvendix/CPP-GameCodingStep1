// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2���� ���Ǵ� �⺻ ���� ������Ʈ�Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "StaticObject_BattleSimulator2.h"

StaticObj_BattleSimulator2::StaticObj_BattleSimulator2(EStaticObjID staticObjID) :
	m_staticObjID(staticObjID)
{

}

EErrorType StaticObj_BattleSimulator2::OnPreSaveFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::SAVE_FILE_FAIL);
	fwrite(&m_staticObjID, sizeof(m_staticObjID), 1, pFileStream);

	return EErrorType::NONE;
}
