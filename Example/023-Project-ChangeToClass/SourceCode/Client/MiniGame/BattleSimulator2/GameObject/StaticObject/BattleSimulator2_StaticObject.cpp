// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2���� ���Ǵ� �⺻ ���� ������Ʈ�Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "BattleSimulator2_StaticObject.h"

BattleSimulator2_StaticObj::BattleSimulator2_StaticObj(EStaticObjID objID) :
	m_objID(objID)
{

}

EErrorType BattleSimulator2_StaticObj::OnPreSaveFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::SAVE_FILE_FAIL);
	fwrite(&m_objID, sizeof(m_objID), 1, pFileStream);

	return EErrorType::NONE;
}
