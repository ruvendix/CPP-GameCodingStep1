// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ����� ��忡���� ���Ǵ� �г��Դϴ�.
// �г� �⺻�����μ� Ŭ���̾�Ʈ������ ��� �޾Ƽ� ShowContents�� �����ؾ� �մϴ�.
// =====================================================================================

#ifndef DEBUG_PANEL_CONTROLLER__H__
#define DEBUG_PANEL_CONTROLLER__H__

#include "Common\CommonType.h"
#include "Common\CommonMacro.h"

class DebugPanelController
{
	DECLARE_PHOENIX_SINGLETON(DebugPanelController);

public:
	void Initialize();
	void PollInput();
	void ShowContents(Int32 x, Int32 y);

private:
	bool m_bShow = true;
};

#endif