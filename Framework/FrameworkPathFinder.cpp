// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// Framework 폴더 경로를 알아내는 용도입니다.
// 유일하게 전역변수로 사용합니다.
// =====================================================================================
#include "EnginePCH.h"
#include "FrameworkPathfinder.h"

std::string FrameworkPathfinder::m_strPath;
Uint32 FrameworkPathfinder::m_folderPathLength;

void FrameworkPathfinder::SetUp()
{
	m_strPath = __FILE__;
	m_folderPathLength = m_strPath.rfind('\\');
	m_folderPathLength += 1; // '\\' 포함!
}