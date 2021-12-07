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

void FrameworkPathfinder::StartUp()
{
	m_strAbsolutePath = __FILE__;

	UINT32 relativePathStartPos = m_strAbsolutePath.rfind('\\');
	relativePathStartPos += 1; // '\\' ����!

	m_strRelativePath = m_strAbsolutePath.substr(0, relativePathStartPos);
}