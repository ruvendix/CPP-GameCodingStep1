// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <windows.h>
#include <string>
#include <array>

using int32  = signed __int32;
using real32 = float;

//////////////////////////////////////////////////////////////////////////
// 이번 프로젝트에 필요한 전역상수를 정의할게요.
// =======================================================================
const int32 NO_VALUE = 0;
const int32 GO_BACK = 1;
const int32 INVALID_VALUE = -1;

const int32 MAX_ITEM_TYPE_COUNT = 13;
const int32 MAX_PLAYER_MONEY = 9999;
const int32 MAX_PLAYER_INVENTORY_CAPACITY = 4;

const int32 ACTION_BUY = 1;
const int32 ACTION_SELL = 2;
const int32 ACTION_EXIT = 3;

const int32 CATEGORY_POTION = 1;
const int32 CATEGORY_GROCERY = 2;
const int32 CATEGORY_CAMPING = 3;
const int32 SHOP_ITEM_CATEGORY_END = CATEGORY_CAMPING + 1;

const int32 POTION_TYPE_COUNT = 4;
const int32 GROCERY_TYPE_COUNT = 5;
const int32 CAMPING_TYPE_COUNT = 4;

const int32 INVENTORY_INFO_COUNT = 2;
const int32 INVENTORY_ITEM_ID_IDX = 0;
const int32 INVENTORY_ITEM_COUNT_IDX = 1;

// 플레이어의 인벤토리와 잡화 상점이 참고할 아이템 데이터베이스(Database, 줄여서 DB)에요.
// 좀 더 효율적으로 관리하려면 클래스와 자료구조를 적용해야 하는데 지금은 생략할게요.
const std::array<int32, MAX_ITEM_TYPE_COUNT> g_itemDBForID =
{
	0x00001000, 0x00001001, 0x00001002, 0x00001003,
	0x00002000, 0x00002001, 0x00002002, 0x00002003, 0x00002004,
	0x00003000, 0x00003001, 0x00003002, 0x00003003
};

const std::array<std::string, MAX_ITEM_TYPE_COUNT> g_itemDBForName =
{
	"평범한 회복약", "쓸만한 회복약", "특제 회복약", "만병통치약",
	"계란", "돼지고기", "소고기", "소금", "후추",
	"야영텐트", "가스 토치", "손전등", "침낭"
};

const std::array<int32, MAX_ITEM_TYPE_COUNT> g_itemDBForPrice =
{
	10, 50, 100, 200,
	5, 10, 20, 5, 5,
	150, 100, 50, 150
};

//////////////////////////////////////////////////////////////////////////
// 이번 프로젝트에 필요한 전역변수를 정의할게요.
// 전역변수는 되도록이면 사용하지 않으려고 하지만...
// 지금은 소스 코드를 좀 더 간단하게 만드는 게 중요하니까요.
// =======================================================================
int32 g_playerMoney = 2000;
int32 g_playerInventoryEmptyIdx; // 비어있는 인덱스에 아이템 정보를 넣을게요!
std::array<std::array<int32, INVENTORY_INFO_COUNT>, MAX_PLAYER_INVENTORY_CAPACITY> g_playerInventory;

//////////////////////////////////////////////////////////////////////////
// 이번 프로젝트에 필요한 함수를 선언할게요.
// =======================================================================
// 유틸리티 함수 목록이에요.
// 유틸리티 함수는 어느 프로젝트에서나 사용할 수 있어야 하죠!
void  PauseApp();
void  ClearConsoleScreen();
void  ClearStdInputBuffer();
void  MoveConsolePosition(int32 x, int32 y);
COORD TakeCurrentConsolePosition();
bool  InputNumAutoRange(_Out_ int32& num, int32 minNum, int32 maxNum);
int32 ClampNum(int32 num, int32 minNum, int32 maxNum);

// 아이템 DB 검색 함수 목록이에요.
std::string FindItemNameInDB(int32 itemID);
int32       FindItemIdxInDB(int32 itemID); // 요 녀석이 핵심 함수에요!
int32       FindItemPriceInDB(int32 itemID);
int32       FindAlreadyPossessionItemIdx(int32 itemID); // 요 녀석은 인벤토리의 핵심 함수에요!
int32       FindItemPossessionCountInInventory(int32 itemID);

// 잡화 상점 관련 함수 목록이에요.
bool  EnterMiscellaneousShop();
int32 ShowBuyItemMenu();
int32 ShowSellItemMenu();

// 플레이어 관련 함수 목록이에요.
void ShowPlayerInventory(int32 x, int32 y, bool bSell);
std::array<int32, MAX_PLAYER_INVENTORY_CAPACITY> TakePlayerInventoryOnlyItemID();

// 템플릿 함수 목록이에요.
// 아이템 정보를 보여주는 함수에요.
// 인벤토리와 상점 둘 다 사용 가능하다는 매력이 있죠!
template <typename int32 itemCount>
void ShowItemTable(int32 x, int32 y, const std::array<int32, itemCount>& itemTable, bool bSell)
{
	MoveConsolePosition(x, y);
	printf("┏━━━━━━━━━━━━━━━━━━━━━┳━━━━━┳━━━━━┓");
	MoveConsolePosition(x, ++y);
	printf("┃ 이름                ┃ 가격┃ 소지┃");
	MoveConsolePosition(x, ++y);
	printf("┣━━━━━━━━━━━━━━━━━━━━━╋━━━━━╋━━━━━┫");

	for (int32 i = 0; i < itemCount; ++i)
	{
		std::string strItemName = FindItemNameInDB(itemTable[i]);

		int32 itemPrice = FindItemPriceInDB(itemTable[i]);
		if (bSell == true)
		{
			itemPrice = (int32)(itemPrice * 0.80f);
		}

		int32 itemPossessionCount = FindItemPossessionCountInInventory(itemTable[i]);

		// 출력할 문자열의 수를 고정시켜야 UI가 흐트러지지 않아요!
		MoveConsolePosition(x, ++y);
		printf("┃ %d.%-18s┃ %4d┃ %4d┃", i + 1, strItemName.c_str(), itemPrice, itemPossessionCount);
	}

	MoveConsolePosition(x, ++y);
	printf("┣━━━━━━━━━━━━━━━━━━━━━┻━━━━━┻━━━━━┫");
	MoveConsolePosition(x, ++y);
	printf("┃ 소지금 : %-4d                   ┃", g_playerMoney);
	MoveConsolePosition(x, ++y);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	
	MoveConsolePosition(0, ++y);
}

template <typename int32 itemCount>
int32 BuyItem(const std::array<int32, itemCount>& itemTable)
{
	printf("구매하고 싶은 아이템의 번호를 입력해주세요. (마지막 번호는 처음으로 돌아가기)\n");

	int32 endSelectionNum = itemCount + 1;
	int32 selectedItemNum = NO_VALUE;
	while (InputNumAutoRange(selectedItemNum, 1, endSelectionNum) == false)
	{
		printf("다시 입력해주세요!\n");
	}

	if (selectedItemNum == endSelectionNum)
	{
		return GO_BACK;
	}

	int32 selectedItemID = itemTable[selectedItemNum - 1];
	int32 selectedItemPrice = FindItemPriceInDB(selectedItemID);

	if (g_playerMoney < selectedItemPrice)
	{
		printf("소지금 \"%d\"원으로는 \"%d\"원의 아이템을 구매할 수 없어요!\n", g_playerMoney, selectedItemPrice);
		return 0;
	}

	// 인벤토리에 이미 있는 아이템인지 확인해야 해요!
	int32 foundIdx = FindAlreadyPossessionItemIdx(selectedItemID);
	if (foundIdx != INVALID_VALUE)
	{
		// 이미 소지 중인 아이템이면 개수만 올려요.
		++g_playerInventory[foundIdx][INVENTORY_ITEM_COUNT_IDX];
	}
	else
	{
		// 인벤토리가 꽉 찼는지 확인해야 해요!
		if (g_playerInventoryEmptyIdx >= MAX_PLAYER_INVENTORY_CAPACITY)
		{
			printf("더 이상 아이템을 가질 수 없어요...\n");
			return 0;
		}

		// 이전에 있던 아이템 정보는 날려야 해요
		memset(&g_playerInventory[g_playerInventoryEmptyIdx][INVENTORY_ITEM_ID_IDX], 0, sizeof(int32) * 2);

		// 인벤토리에 아이템 정보를 저장해요.
		g_playerInventory[g_playerInventoryEmptyIdx][INVENTORY_ITEM_ID_IDX] = selectedItemID;
		++g_playerInventory[g_playerInventoryEmptyIdx][INVENTORY_ITEM_COUNT_IDX];

		// 다음 인벤토리 인덱스로 이동해야 해요!
		++g_playerInventoryEmptyIdx;
	}

	// 여기까지 왔다면 아이템을 구매한 거니까 플레이어의 돈을 처리해야겠죠?
	g_playerMoney -= selectedItemPrice;
	g_playerMoney = ClampNum(g_playerMoney, 0, MAX_PLAYER_MONEY);

	std::string strSelectedItemName = FindItemNameInDB(selectedItemID);
	printf("입력한 번호인 %d번 아이템(%s)을 구매하셨어요~\n", selectedItemNum, strSelectedItemName.c_str());
	return 0;
}

template <typename int32 itemCount>
int32 SellItem(const std::array<int32, itemCount>& itemTable)
{
	printf("판매하고 싶은 아이템의 번호를 입력해주세요. (원가의 80%% 판매, 마지막 번호는 처음으로 돌아가기)\n");

	int32 endSelectionNum = itemCount + 1;
	int32 selectedItemNum = NO_VALUE;
	while (InputNumAutoRange(selectedItemNum, 1, endSelectionNum) == false)
	{
		printf("다시 입력해주세요!\n");
	}

	if (selectedItemNum == endSelectionNum)
	{
		return GO_BACK;
	}

	int32 selectedItemID = itemTable[selectedItemNum - 1];
	int32 selectedItemPrice = FindItemPriceInDB(selectedItemID);

	// 인벤토리에 아이템이 있어야 팔 수 있겠죠?
	int32 foundIdx = FindAlreadyPossessionItemIdx(selectedItemID);
	if (foundIdx != INVALID_VALUE)
	{
		--g_playerInventory[foundIdx][INVENTORY_ITEM_COUNT_IDX];
		if (g_playerInventory[foundIdx][INVENTORY_ITEM_COUNT_IDX] <= 0)
		{
			// 이 경우는 아이템을 전부 팔았을 때니까 인벤토리를 조정해야 해요!
			// 찾은 인덱스 다음부터 배열의 끝까지를 땡겨서 전부 복사할게요.
			// 이렇게 되면 배열에 쓰레기값이 들어가게 되는데 실제로 접근할 때 사용되는
			// 인덱스는 쓰레기값까지 찾지 않으므로 문제는 없어요.
			// 이 부분이 핵심인데 조금 어려우므로 이해가 되지 않으면 천천히 보세요.
			memcpy(&g_playerInventory[foundIdx][INVENTORY_ITEM_ID_IDX],
				&g_playerInventory[foundIdx + 1][INVENTORY_ITEM_ID_IDX],
				sizeof(int32) * 2 * (MAX_PLAYER_INVENTORY_CAPACITY - foundIdx - 1));

			// 아이템을 판매해서 더 이상 소지 중이 아니라면 이전 인벤토리 인덱스로 이동해야 해요.
			--g_playerInventoryEmptyIdx;
		}
	}

	// 여기까지 왔다면 아이템을 판매한 거니까 플레이어의 돈을 정산해야겠죠?
	g_playerMoney += (int32)(selectedItemPrice * 0.80f);
	g_playerMoney = ClampNum(g_playerMoney, 0, MAX_PLAYER_MONEY);

	std::string strSelectedItemName = FindItemNameInDB(selectedItemID);
	printf("입력한 번호인 %d번 아이템(%s)을 판매하셨어요~\n", selectedItemNum, strSelectedItemName.c_str());
	return 0;
}



// 프로그램이 시작되는 곳이에요.
int32 main()
{
	//////////////////////////////////////////////////////////////////////////
	// 프로젝트 - 잡화 상점을 만들어볼게요~
	//////////////////////////////////////////////////////////////////////////

	// 잡화 상점에 들어가는 부분이에요.
	while (EnterMiscellaneousShop() == true)
	{
		// 반환값이 false면 잡화 상점에서 나가요.
	}

	return EXIT_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// 아까 선언했던 유틸리티 함수들을 만들어볼게요~

// 응용 프로그램을 잠시 멈추는 함수에요.
void PauseApp()
{
	std::system("pause");
}

// 콘솔창을 깨끗하게 지워주는 함수에요.
void ClearConsoleScreen()
{
	std::system("cls");
}

// 표준 입력 버퍼를 비워주는 함수에요.
void ClearStdInputBuffer()
{
	char ch = '0'; // EOF나 '\n'만 아니면 괜찮아요.

	// 표준 입력 버퍼를 비우는 방법이에요.
	// std::fflush(stdin)도 있지만, 표준에는 적합하지 않아서 생략할게요.
	while ((ch != EOF) && (ch != '\n'))
	{
		ch = getchar();
	}
}

void MoveConsolePosition(int32 x, int32 y)
{
	COORD pos = { static_cast<short>(x), static_cast<short>(y) };
	::SetConsoleCursorPosition(::GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

COORD TakeCurrentConsolePosition()
{
	COORD pos = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	::ZeroMemory(&consoleScreenBufferInfo, sizeof(consoleScreenBufferInfo));

	::GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleScreenBufferInfo);
	pos.X = consoleScreenBufferInfo.dwCursorPosition.X;
	pos.Y = consoleScreenBufferInfo.dwCursorPosition.Y;

	return pos;
}

// 숫자를 입력 받음과 동시에 입력 범위를 벗어나면 자동 조절해주는 함수에요.
bool InputNumAutoRange(_Out_ int32& num, int32 minNum, int32 maxNum)
{
	// 최솟값이 최댓값보다 크다면 둘을 바꿔줘야 해요! (swap)
	if (minNum > maxNum)
	{
		std::swap(minNum, maxNum);
	}

	printf("입력 범위를 벗어나면 자동 조절됩니다. (%d ~ %d)\n", minNum, maxNum);
	printf("> ");

	int32 inputResult = scanf_s("%d", &num);
	printf("\n");
	ClearStdInputBuffer();

	if (inputResult == 0)
	{
		printf("정수만 입력 가능해요!\n");
		return false;
	}

	num = ClampNum(num, minNum, maxNum);
	return true;
}

// 숫자를 제한된 범위로 고정시켜주는 함수에요.
int32 ClampNum(int32 num, int32 minNum, int32 maxNum)
{
	int32 resultNum = num;

	if (resultNum < minNum)
	{
		resultNum = minNum;
	}
	else if (resultNum > maxNum)
	{
		resultNum = maxNum;
	}

	return resultNum;
}

//////////////////////////////////////////////////////////////////////////
// 아까 선언했던 아이템 DB 검색 함수들을 만들어볼게요~

// DB에서의 아이템 인덱스를 찾아주는 함수에요.
int32 FindItemIdxInDB(int32 itemID)
{
	// 이런 걸 순차탐색이라고 하는데 실제로 사용되고 있는 DB는 순차탐색을 사용하면 망해요...
	// 탐색 알고리즘에는 여러가지가 있는데 일단은 순차탐색만 사용할게요.
	for (int32 i = 0; i < MAX_ITEM_TYPE_COUNT; ++i)
	{
		// 아이템 ID끼리 비교하는 게 제일 정확해요!
		if (g_itemDBForID[i] == itemID)
		{
			return i;
		}
	}

	return INVALID_VALUE;
}

// DB에서 아이템 이름을 찾아주는 함수에요.
std::string FindItemNameInDB(int32 itemID)
{
	int32 foundIdx = FindItemIdxInDB(itemID);
	if (foundIdx == INVALID_VALUE)
	{
		return "";
	}
	return g_itemDBForName.at(foundIdx);
}

// DB에서 아이템 가격을 찾아주는 함수에요.
int32 FindItemPriceInDB(int32 itemID)
{
	int32 foundIdx = FindItemIdxInDB(itemID);
	if (foundIdx == INVALID_VALUE)
	{
		return NO_VALUE;
	}
	return g_itemDBForPrice.at(foundIdx);
}

// 인벤토리에 아이템이 이미 있는지 확인해주는 함수에요.
int32 FindAlreadyPossessionItemIdx(int32 itemID)
{
	// 현재 갖고 있는 아이템에서만 찾아야 해요.
	for (int32 i = 0; i < g_playerInventoryEmptyIdx; ++i)
	{
		if (g_playerInventory[i][INVENTORY_ITEM_ID_IDX] == itemID)
		{
			return i;
		}
	}
	return INVALID_VALUE;
}

// 인벤토리에 있는 아이템 개수를 가져오는 함수에요.
int32 FindItemPossessionCountInInventory(int32 itemID)
{
	// 인벤토리에 아이템이 있어야 아이템 개수를 알아낼 수 있겠죠?
	int32 foundItemIdx = FindAlreadyPossessionItemIdx(itemID);
	if (foundItemIdx != INVALID_VALUE)
	{
		return g_playerInventory[foundItemIdx][INVENTORY_ITEM_COUNT_IDX];
	}
	return NO_VALUE;
}

//////////////////////////////////////////////////////////////////////////
// 여기서부터는 본격적으로 잡화 상점을 구현하게 되요.
// 먼저 잡화 상점에 들어가는 함수부터 만들고 간단하게 테스트를 해보죠!

bool EnterMiscellaneousShop()
{
	printf("잡화 상점에 오신 걸 환영해요~!\n");
	printf("무슨 일로 오셨나요? (1.구입  2.판매  3.나가기)\n\n");

	int32 selectedActionNum = NO_VALUE;
	while (InputNumAutoRange(selectedActionNum, ACTION_BUY, ACTION_EXIT) == false)
	{
		printf("다시 입력해주세요!\n");
	}

	switch (selectedActionNum)
	{
	case ACTION_BUY:
	{
		if (ShowBuyItemMenu() == GO_BACK)
		{
			ClearConsoleScreen();
			return true;
		}

		break;
	}
	case ACTION_SELL:
	{
		if (ShowSellItemMenu() == GO_BACK)
		{
			ClearConsoleScreen();
			return true;
		}

		break;
	}
	case ACTION_EXIT:
	{
		printf("안녕히 가세요~\n");
		return false;
	}
	}

	PauseApp();
	ClearConsoleScreen();
	return true;
}

// 기본 메뉴는 잘 구현된 것 같네요~
// 이제 핵심 기능인 구매와 판매 기능을 만들어볼게요~

// 구매 메뉴를 보여주는 함수에요.
int32 ShowBuyItemMenu()
{
	printf("어떤 아이템에 관심 있으세요? (1.물약  2.식료품  3.야외용품  4.뒤로)\n");

	int32 selectedCategoryNum = NO_VALUE;
	while (InputNumAutoRange(selectedCategoryNum, CATEGORY_POTION, SHOP_ITEM_CATEGORY_END) == false)
	{
		printf("다시 입력해주세요!\n");
	}

	if (selectedCategoryNum == SHOP_ITEM_CATEGORY_END)
	{
		return GO_BACK;
	}

	int32 returnValue = NO_VALUE;
	while (returnValue != GO_BACK)
	{
		COORD currentPos = TakeCurrentConsolePosition();
		ShowPlayerInventory(50, currentPos.Y - 1, false); // y좌표가 필요하므로...
		MoveConsolePosition(currentPos.X, currentPos.Y);

		// 선택한 카테고리에 따라 구매 가능한 아이템이 달라져요.
		// 지금은 자료구조를 사용하고 있지 않으니...
		// 각 카테고리에 해당되는 아이템 ID 목록을 때려박을게요... (하드 코딩)
		switch (selectedCategoryNum)
		{
		case CATEGORY_POTION:
		{
			std::array<int32, POTION_TYPE_COUNT> potionItems = { 0x00001000, 0x00001001, 0x00001002, 0x00001003 };
			ShowItemTable(currentPos.X, currentPos.Y, potionItems, false);
			returnValue = BuyItem(potionItems);
			break;
		}
		case CATEGORY_GROCERY:
		{
			std::array<int32, GROCERY_TYPE_COUNT> groceryItems = { 0x00002000, 0x00002001, 0x00002002, 0x00002003, 0x00002004 };
			ShowItemTable(currentPos.X, currentPos.Y, groceryItems, false);
			returnValue = BuyItem(groceryItems);
			break;
		}
		case CATEGORY_CAMPING:
		{
			std::array<int32, CAMPING_TYPE_COUNT> campingItems = { 0x00003000, 0x00003001, 0x00003002, 0x00003003 };
			ShowItemTable(currentPos.X, currentPos.Y, campingItems, false);
			returnValue = BuyItem(campingItems);
			break;
		}
		}

		if (returnValue != GO_BACK)
		{
			PauseApp();
		}

		ClearConsoleScreen();
	}

	return returnValue;
}

// 판매 메뉴를 보여주는 함수에요.
int32 ShowSellItemMenu()
{
	int32 returnValue = NO_VALUE;
	while (returnValue != GO_BACK)
	{
		COORD currentPos = TakeCurrentConsolePosition();
		ShowPlayerInventory(0, currentPos.Y - 1, true);
		
		// 현재 인벤토리 인덱스는 현재 갖고 있는 아이템 종류의 수를 의미해요.
		// 이름이 헷갈릴 수 있으니 이름을 다시 정할게요.
		int32 currentInventoryItemCount = g_playerInventoryEmptyIdx;
		if (currentInventoryItemCount <= NO_VALUE)
		{
			printf("판매할 아이템이 없어요...\n");
			returnValue = GO_BACK;
			PauseApp();
		}
		else
		{
			returnValue = SellItem(TakePlayerInventoryOnlyItemID());
		}

		if (returnValue != GO_BACK)
		{
			PauseApp();
		}

		ClearConsoleScreen();
	}

	return returnValue;
}

void ShowPlayerInventory(int32 x, int32 y, bool bSell)
{
	MoveConsolePosition(x, y);
	ShowItemTable(x, ++y, TakePlayerInventoryOnlyItemID(), bSell);
}

std::array<int32, MAX_PLAYER_INVENTORY_CAPACITY> TakePlayerInventoryOnlyItemID()
{
	// 인벤토리는 2차원 배열이므로 아이템 ID만 따로 뽑아서 1차원 배열로 만들어야 해요.
	// 2차원 배열을 함수 인자로 전달하려면 포인터를 알아야 하므로...
	std::array<int32, MAX_PLAYER_INVENTORY_CAPACITY> itemIDTable;
	for (int32 i = 0; i < MAX_PLAYER_INVENTORY_CAPACITY; ++i)
	{
		itemIDTable[i] = g_playerInventory[i][INVENTORY_ITEM_ID_IDX];
	}
	return itemIDTable;
}