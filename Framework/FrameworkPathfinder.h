// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// Framework 폴더 경로를 알아내는 용도입니다.
// __FILE__ 매크로에 맞춰져있습니다.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "Common/CommonType.h"

class FrameworkPathfinder final
{
public:
	void StartUp();

	const std::string& GetAbsolutePath() const { return m_strAbsolutePath; }
	const std::string& GetRelativePath() const { return m_strRelativePath; }

	UINT32 GetRelativePathStartPos() const { return m_strRelativePath.length(); }

private:
	friend class PathManager;

	FrameworkPathfinder() = default;
	~FrameworkPathfinder() = default;

	std::string m_strAbsolutePath;
	std::string m_strRelativePath;
};