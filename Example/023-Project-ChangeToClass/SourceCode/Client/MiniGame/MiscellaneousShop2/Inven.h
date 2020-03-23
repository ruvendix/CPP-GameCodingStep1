// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 플레이어의 인벤토리입니다.
// 지금은 상점 아이템만 저장할 수 있습니다.
// ItemDB와는 다르게 vector를 이용합니다. (인벤토리 개수는 정해져있으므로!)
// =====================================================================================

#ifndef PLAYER_INVEN_H__
#define PLAYER_INVEN_H__

#include "Common\CommonType.h"
#include "Common\CommonNecessary.h"

class ItemBase;

struct InvenItemInfo
{
	ItemBase* pItem = nullptr;
	Int32 cnt = 0;
};

class Inven
{
public:
#pragma region 생성자 및 소멸자
	Inven() = default;
	virtual ~Inven();
#pragma endregion

	InvenItemInfo* FindInvenItemInfo(const std::string& strItemNameTag) const;
	void AddInvenItemInfo(const ItemBase* pItem);
	void DeleteInvenItemInfo(const std::string& strItemNameTag);
	void DrawInven(Int32 x, Int32 y) const;
	void DrawInvenForSell(Int32 x, Int32 y) const;
	bool IsFull() const;

private:
	Int32 m_maxInvenSize = 5; // 인벤에 담을 수 있는 개수는 5개
	std::vector<InvenItemInfo*> m_vecInvenItemInfo;
};

#endif