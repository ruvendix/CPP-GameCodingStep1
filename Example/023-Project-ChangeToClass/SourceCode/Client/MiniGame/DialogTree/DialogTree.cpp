// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��ȭ Ʈ���Դϴ�.
// ��ȭ ��带 �����ϰ� �����ϴ� ���� ó���� �մϴ�.
// =====================================================================================

#include "PCH.h"
#include "DialogTree.h"

DialogTree::DialogTree()
{
	m_spRootNode = std::make_shared<DialogNode>();
}