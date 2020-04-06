// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2에서 사용되는 기본 동적 오브젝트입니다.
// =====================================================================================

#include "PCH.h"
#include "BattleSimulator2_DynamicObject.h"

BattleSimulator2_DynamicObj::BattleSimulator2_DynamicObj(EDynamicObjID objID) :
	m_objID(objID)
{

}

EErrorType BattleSimulator2_DynamicObj::OnPreSaveFile(FILE* pFileStream)
{
	CHECK_NULLPTR_RETURN(pFileStream, EErrorType::SAVE_FILE_FAIL);
	fwrite(&m_objID, sizeof(m_objID), 1, pFileStream);

	return EErrorType::NONE;
}
