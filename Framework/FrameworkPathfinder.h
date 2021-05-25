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
	static void SetUp()
	{
		m_strPath = __FILE__;
		m_folderPathLength = m_strPath.rfind('\\');
		m_folderPathLength += 1; // '\\' 포함!
	}

	static const std::string& GetPath()
	{
		return m_strPath;
	}

	static Uint32 GetFolderPathLength()
	{
		return m_folderPathLength;
	}

private:
	FrameworkPathfinder() = default;
	~FrameworkPathfinder() = default;

	static std::string m_strPath;
	static Uint32 m_folderPathLength;
};