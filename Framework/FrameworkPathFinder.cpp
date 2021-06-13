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

void FrameworkPathfinder::SetUp()
{
	m_strAbsolutePath = __FILE__;

	m_relativePathStartPos = m_strAbsolutePath.rfind('\\');
	m_relativePathStartPos += 1; // '\\' ����!

	m_strAbsolutePath = m_strAbsolutePath.substr(0, m_relativePathStartPos);
}