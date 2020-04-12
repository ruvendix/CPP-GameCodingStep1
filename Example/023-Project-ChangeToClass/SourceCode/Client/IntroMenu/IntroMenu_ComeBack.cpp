// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʈ�� �޴� ������ ���ƿ��� ���ݴϴ�.
// ���� ���ӿ��� ��� �����մϴ�.
// =====================================================================================

#include "PCH.h"
#include "IntroMenu_ComeBack.h"

#include "Manager\SceneManager.h"
#include "Scene\IntroMenuScene.h"

EErrorType IntroMenu_ComeBack::OnExcute()
{
	SceneMgr::I()->CreateScene<IntroMenuScene>(ECreateType::NEXT);
	return EErrorType::NOTHING;
}