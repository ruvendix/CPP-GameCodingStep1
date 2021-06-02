// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Framework ���� ��θ� �˾Ƴ��� �뵵�Դϴ�.
// �����ϰ� ���������� ����մϴ�.
// =====================================================================================
#include "EnginePCH.h"
#include "FrameworkPathfinder.h"

std::string FrameworkPathfinder::m_strPath;
Uint32 FrameworkPathfinder::m_folderPathLength;

void FrameworkPathfinder::SetUp()
{
	m_strPath = __FILE__;
	m_folderPathLength = m_strPath.rfind('\\');
	m_folderPathLength += 1; // '\\' ����!
}