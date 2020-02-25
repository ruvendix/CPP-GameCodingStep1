// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ����� ��忡���� ���Ǵ� �г��Դϴ�.
// �г� �⺻�����μ� Ŭ���̾�Ʈ������ ��� �޾Ƽ� ShowContents�� �����ؾ� �մϴ�.
// =====================================================================================

#ifndef DEBUG_PANEL__H__
#define DEBUG_PANEL__H__

#include "Common\CommonType.h"
#include "Common\CommonMacro.h"

class DebugPanel
{
	DECLARE_PHOENIX_SINGLETON(DebugPanel);

public:
	void Initialize();
	void ShowContents(Int32 posX, Int32 posY);

private:
	bool m_bShow = true;
};

#endif