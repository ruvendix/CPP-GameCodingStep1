// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �Լ��� ���� �ɷ��� �����մϴ�.
// ���� �Լ��� ���� �ɷ��� ���ÿ� ������ �� �ֽ��ϴ�.
// =====================================================================================

#ifndef PERFORMANCE_PROFILE_MGR__H__
#define PERFORMANCE_PROFILE_MGR__H__

#include "Element\NameTag.h"
#include "Timer\StopwatchTimer.h"

DECLARE_LOG_CATEGORY(PerformanceProfileMgr);

struct PerformanceProfileInfo
{
	std::string strFuncSig; // �����Ǵ� �Լ��� ���� (�̸� ����)
	StopwatchTimer stopwatchTimer; // ���� �ð� ����
	Real32 totalPerformanceTime = 0.0f; // �� ���� �ð�
	Uint32 callCnt = 0; // ȣ�� Ƚ��
	Uint32 inputDataCnt = 0; // �Էµ� �ֿ� ������ ����
};

class PerformanceProfileMgr
{
	DECLARE_PHOENIX_SINGLETON(PerformanceProfileMgr);

public:
	void Start(const std::string_view& szFuncSig, Int32 ID, Int32 inputDataCnt = 0);
	void End(Int32 ID); // �����Ǵ� �Լ��� �ĺ��� ���� ID (__COUNTER__ Ȱ��)
	void Report();

private:
	std::unordered_map<Uint32, PerformanceProfileInfo*> m_mapPerformanceProfileInfo;
};

#endif