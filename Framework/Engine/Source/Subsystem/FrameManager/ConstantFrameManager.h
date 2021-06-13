// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ������ Ÿ�� �Ŵ����Դϴ�.
// =====================================================================================
#pragma once

#include "IFrameManager.h"
#include "Utility/Time/Stopwatch.h"
#include "Utility/Time/Timer.h"

// ���� ����
class ConstantFrameManagerInside;

class ConstantFrameManager final : public IFrameManager
{
	ONLY_SUBSYSTEM_CTOR(ConstantFrameManager);

public:
	virtual void SetUp() override;
	virtual void CleanUp() override;

	virtual void UpdateFrameTime() override;

private:
	std::unique_ptr<ConstantFrameManagerInside> m_spInside = nullptr;
};