// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 대화 노드입니다.
// 다음 대화 노드 연결을 잊으면 안 됩니다!
// =====================================================================================

#ifndef DIALOG_NODE_H__
#define DIALOG_NODE_H__

#include "Common\CommonType.h"
#include "Common\CommonNecessary.h"

struct DialogInfo
{
	std::string strSpeaker;
	std::string strScript;
};

class DialogNode
{
public:
#pragma region 생성자 및 소멸자
	DialogNode() = default;
	virtual ~DialogNode() = default;

	DialogNode(const std::string_view& szSpeaker, const std::string_view& szScript);
#pragma endregion

	virtual void Draw(Int32 x, Int32 y) const;
	virtual std::shared_ptr<DialogNode> FindNextNode() const;

	void setNextNode(const std::shared_ptr<DialogNode>& spNextNode)
	{
		m_spNextNode = spNextNode;
	}

private:
	std::unique_ptr<DialogInfo> m_spInfo; // 기본 대사 정보
	std::shared_ptr<DialogNode> m_spNextNode;
};

#endif