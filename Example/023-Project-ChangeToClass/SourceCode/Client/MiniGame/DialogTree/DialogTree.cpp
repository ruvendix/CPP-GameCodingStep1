// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 대화 트리입니다.
// 대화 노드를 생성하고 연결하는 등의 처리를 합니다.
// =====================================================================================

#include "PCH.h"
#include "DialogTree.h"

DialogTree::DialogTree()
{
	m_spRootNode = std::make_shared<DialogNode>();
}