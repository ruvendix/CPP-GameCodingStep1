// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <string>

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

const int32 INVENTORY_ITEM_INFO_COUNT = 2;
const int32 INVENTORY_ITEM_ID_IDX = 0;
const int32 INVENTORY_ITEM_COUNT_IDX = 1;

const int32 ACTION_BUY  = 1;
const int32 ACTION_SELL = 2;
const int32 ACTION_EXIT = 3;

const int32 CATEGORY_POTION  = 1;
const int32 CATEGORY_GROCERY = 2;
const int32 CATEGORY_CAMPING = 3;
const int32 SHOP_MENU_END = CATEGORY_CAMPING + 1;

const int32 POTION_TYPE_COUNT  = 4;
const int32 GROCERY_TYPE_COUNT = 5;
const int32 CAMPING_TYPE_COUNT = 4;

// 플레이어의 인벤토리와 잡화 상점이 참고할 아이템 데이터베이스(Database, 줄여서 DB)에요.
// 좀 더 효율적으로 관리하려면 클래스와 자료구조를 적용해야 하는데 지금은 생략할게요.
const int32 g_itemDBForID[MAX_ITEM_TYPE_COUNT] =
{
	0x00001000, 0x00001001, 0x00001002, 0x00001003,
	0x00002000, 0x00002001, 0x00002002, 0x00002003, 0x00002004,
	0x00003000, 0x00003001, 0x00003002, 0x00003003
};

const std::string g_itemDBForName[MAX_ITEM_TYPE_COUNT] =
{
	"평범한 회복약", "쓸만한 회복약", "특제 회복약", "만병통치약",
	"계란", "돼지고기", "소고기", "소금", "후추",
	"야영텐트", "가스 토치", "손전등", "침낭"
};

const int32 g_itemDBForPrice[MAX_ITEM_TYPE_COUNT] =
{
	10, 50, 100, 200,
	5, 10, 20, 5, 5,
	150, 100, 50, 150
};

//////////////////////////////////////////////////////////////////////////
// 이번 프로젝트에 필요한 전역변수를 선언할게요.
// 전역변수는 되도록이면 사용하지 않으려고 하지만...
// 지금은 소스 코드를 좀 더 간단하게 만들어야 해서요.
// =======================================================================
int32 g_playerMoney = 5000;
int32 g_playerCurrentInventoryIdx;
int32 g_playerInventory[MAX_PLAYER_INVENTORY_CAPACITY][INVENTORY_ITEM_INFO_COUNT];

//////////////////////////////////////////////////////////////////////////
// 이번 프로젝트에 필요한 함수를 선언할게요.
// =======================================================================
// 유틸리티 함수 목록이에요.
// 유티리티 함수는 어느 프로젝트에서나 사용할 수 있어야 해요!
void  PauseApp();
void  ClearConsoleScreen();
void  ClearStdInput();
bool  InputNumAutoRange(_Out_ int32& num, int32 minNum, int32 maxNum);
int32 ClampNum(int32 num, int32 minNum, int32 maxNum);

// 검색 함수 목록이에요.
const std::string FindItemNameInDB(int32 itemID);
int32 FindItemIdxInDB(int32 itemID);
int32 FindItemPriceInDB(int32 itemID);
int32 FindAlreadyPossessItemIdx(int32 itemID);
int32 FindItemPossessionCountInInventory(int32 itemID);

// 상점 관련 함수 목록이에요.
bool  EnterMiscellaneousShop();
int32 ShowBuyItemMenu();
int32 ShowSellItemMenu();
void  ShowItemTable(const int32 itemTable[], int32 count, bool bSell);
int32 BuyItem(const int32 itemTable[], int32 count);
int32 SellItem(const int32 itemTable[], int32 count);

int main()
{
	//////////////////////////////////////////////////////////////////////////
	// 프로젝트 - 잡화 상점을 만들어봐요~
	//////////////////////////////////////////////////////////////////////////

	// 상점에 들어갈게요.
	while (EnterMiscellaneousShop() == true)
	{
		// 반환값이 false면 상점을 나가요.
	}

	return EXIT_SUCCESS;
}

// 응용 프로그램을 잠시 멈추는 함수에요.
void PauseApp()
{
	std::system("pause");
}

// 콘솔창을 깨끗하게 지워주는 함수에요.
void ClearConsoleScreen()
{
	std::system("cls"); // 비주얼 스튜디오에서만 사용 가능해요.
}

// 표준 입력 버퍼를 비워주는 함수에요.
void ClearStdInput()
{
	char ch = '0'; // EOF와 '\n'만 아니면 됨!

	// 표준 입력 버퍼를 비우는 방법이에요.
	// std::fflush(stdin)은 표준에 적합하지 않아서 사용하지 않을게요.
	while ((ch != EOF) && (ch != '\n'))
	{
		ch = getchar();
	};
}

// 숫자를 입력 받음과 동시에 입력 범위를 벗어나면 자동 조절해주는 함수에요.
bool InputNumAutoRange(_Out_ int32& num, int32 minNum, int32 maxNum)
{
	if (minNum > maxNum)
	{
		minNum = maxNum;
	}

	printf("입력 범위를 벗어나면 자동 조절됩니다. (%d ~ %d)\n", minNum, maxNum);
	printf("> ");
	int32 inputResult = scanf_s("%d", &num);
	printf("\n");
	ClearStdInput();

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

	if (num < minNum)
	{
		resultNum = minNum;
	}
	else if (num > maxNum)
	{
		resultNum = maxNum;
	}

	return resultNum;
}

// DB에서 아이템 이름을 찾아주는 함수에요.
const std::string FindItemNameInDB(int32 itemID)
{
	int32 foundIdx = FindItemIdxInDB(itemID);
	if (foundIdx == INVALID_VALUE)
	{
		return "NoItem";
	}

	return g_itemDBForName[foundIdx];
}

// DB에서의 아이템 인덱스를 찾아주는 함수에요.
int32 FindItemIdxInDB(int32 itemID)
{
	int32 foundIdx = INVALID_VALUE;
	for (int32 i = 0; i < MAX_ITEM_TYPE_COUNT; ++i)
	{
		// 아이템 ID끼리 비교하는 게 제일 정확해요.
		if (g_itemDBForID[i] == itemID)
		{
			foundIdx = i;
		}
	}

	return foundIdx;
}

// DB에서 아이템 가격을 찾아주는 함수에요.
int32 FindItemPriceInDB(int32 itemID)
{
	int32 foundIdx = FindItemIdxInDB(itemID);
	if (foundIdx == INVALID_VALUE)
	{
		return INVALID_VALUE;
	}

	return g_itemDBForPrice[foundIdx];
}

// 인벤토리에 아이템이 이미 있는지 확인해주는 함수에요.
int32 FindAlreadyPossessItemIdx(int32 itemID)
{
	for (int32 i = 0; i < MAX_PLAYER_INVENTORY_CAPACITY; ++i)
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
	// 인벤토리에 아이템이 있어야 아이템 개수를 가져올 수 있어요.
	int32 foundItemIdx = FindAlreadyPossessItemIdx(itemID);
	if (foundItemIdx != INVALID_VALUE)
	{
		return g_playerInventory[foundItemIdx][INVENTORY_ITEM_COUNT_IDX];
	}

	return 0;
}

// 잡화 상점에 들어가는 함수에요.
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

// 구매 메뉴를 보여주는 함수에요.
int32 ShowBuyItemMenu()
{
	printf("어떤 아이템에 관심 있으세요? (1.물약  2.식료품  3.야외용품  4.뒤로)\n");

	int32 selectedCategoryNum = NO_VALUE;
	while (InputNumAutoRange(selectedCategoryNum, CATEGORY_POTION, SHOP_MENU_END) == false)
	{
		printf("다시 입력해주세요!\n");
	}

	if (selectedCategoryNum == SHOP_MENU_END)
	{
		return GO_BACK;
	}

	int32 returnValue = NO_VALUE;
	while (returnValue != GO_BACK)
	{
		// 선택한 카테고리에 따라 구매 가능한 아이템이 달라져요.
		// 지금은 자료구조를 사용하지 않아서 각 카테고리에 해당되는 아이템 ID 목록을 때려박았어요. (하드 코딩)
		switch (selectedCategoryNum)
		{
		case CATEGORY_POTION:
		{
			int32 potionItems[POTION_TYPE_COUNT] = { 0x00001000 , 0x00001001, 0x00001002, 0x00001003 };
			ShowItemTable(potionItems, POTION_TYPE_COUNT, false);
			returnValue = BuyItem(potionItems, POTION_TYPE_COUNT);
			break;
		}
		case CATEGORY_GROCERY:
		{
			int32 groceryItems[GROCERY_TYPE_COUNT] = { 0x00002000 , 0x00002001, 0x00002002, 0x00002003, 0x00002004 };
			ShowItemTable(groceryItems, GROCERY_TYPE_COUNT, false);
			returnValue = BuyItem(groceryItems, GROCERY_TYPE_COUNT);
			break;
		}
		case CATEGORY_CAMPING:
		{
			int32 campingItems[CAMPING_TYPE_COUNT] = { 0x00003000 , 0x00003001, 0x00003002, 0x00003003 };
			ShowItemTable(campingItems, CAMPING_TYPE_COUNT, false);
			returnValue = BuyItem(campingItems, CAMPING_TYPE_COUNT);
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
		// 인벤토리는 2차원 배열이므로 아이템 ID만 따로 뽑아서 1차원 배열로 만들게요.
		// 2차원 배열을 함수 인자로 전달하려면 포인터를 알아야 해서요...
		int32 itemIDTable[MAX_PLAYER_INVENTORY_CAPACITY];
		for (int32 i = 0; i < MAX_PLAYER_INVENTORY_CAPACITY; ++i)
		{
			if (g_playerInventory[i][INVENTORY_ITEM_ID_IDX] != NO_VALUE)
			{
				itemIDTable[i] = g_playerInventory[i][INVENTORY_ITEM_ID_IDX];
			}
		}

		// 현재 인벤토리 인덱스는 현재 갖고 있는 아이템 종류의 수를 의미해요.
		// 이름이 헷갈릴 수 있으니 이름을 다시 정했어요.
		int32 currentInventoryItemCount = g_playerCurrentInventoryIdx;
		if (currentInventoryItemCount > NO_VALUE)
		{
			ShowItemTable(itemIDTable, currentInventoryItemCount, true);
			returnValue = SellItem(itemIDTable, currentInventoryItemCount);
		}
		else
		{
			printf("판매할 아이템이 없어요...\n");
			returnValue = GO_BACK;
			PauseApp();
		}

		if (returnValue != GO_BACK)
		{
			PauseApp();
		}

		ClearConsoleScreen();
	}

	return returnValue;
}

// 아이템 정보를 보여주는 함수에요.
// 인벤토리와 상점 둘 다 사용 가능해요.
void ShowItemTable(const int32 itemTable[], int32 count, bool bSell)
{
	printf("┏━━━━━━━━━━━━━━━━━━━━━┳━━━━━┳━━━━━┓\n");
	printf("┃ 이름                ┃ 가격┃ 소지┃\n");
	printf("┣━━━━━━━━━━━━━━━━━━━━━╋━━━━━╋━━━━━┫\n");

	for (int32 i = 0; i < count; ++i)
	{
		std::string strItemName = FindItemNameInDB(itemTable[i]);
		
		int32 itemPrice = FindItemPriceInDB(itemTable[i]);
		if (bSell == true)
		{
			itemPrice = (int32)(itemPrice * 0.80f);
		}

		int32 itemPossessionCount = FindItemPossessionCountInInventory(itemTable[i]);

		// 출력할 문자열의 수를 고정시키는 방법이에요.
		printf("┃ %d.%-18s┃ %4d┃ %4d┃\n", i + 1, strItemName.c_str(), itemPrice, itemPossessionCount);
	}

	printf("┣━━━━━━━━━━━━━━━━━━━━━┻━━━━━┻━━━━━┫\n");
	printf("┃ 소지금 : %-4d                   ┃\n", g_playerMoney);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n");
}

// 아이템을 구매하는 함수에요.
int32 BuyItem(const int32 itemTable[], int32 count)
{
	printf("구매하고 싶은 아이템의 번호를 입력해주세요. (마지막 번호는 처음으로 돌아가기)\n");

	int32 endSelectionNum = count + 1;
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

	// 인벤토리에 이미 있는 아이템인지 확인 필요!
	int32 foundIdx = FindAlreadyPossessItemIdx(selectedItemID);
	if (foundIdx != INVALID_VALUE)
	{
		// 이미 소지 중인 아이템이면 개수만 늘려요.
		++g_playerInventory[foundIdx][INVENTORY_ITEM_COUNT_IDX];
	}
	else
	{
		if (g_playerCurrentInventoryIdx >= MAX_PLAYER_INVENTORY_CAPACITY)
		{
			printf("더 이상 아이템을 가질 수 없어요...\n");
			return 0;
		}

		// 인벤토리에 아이템 정보를 저장해요.
		g_playerInventory[g_playerCurrentInventoryIdx][INVENTORY_ITEM_ID_IDX] = selectedItemID;
		++g_playerInventory[g_playerCurrentInventoryIdx][INVENTORY_ITEM_COUNT_IDX];

		// 다음 인벤토리 인덱스로 이동해요.
		++g_playerCurrentInventoryIdx;
	}

	g_playerMoney -= selectedItemPrice;
	g_playerMoney = ClampNum(g_playerMoney, 0, MAX_PLAYER_MONEY);

	printf("입력한 번호인 %d번 아이템을 구매하셨어요~\n", selectedItemNum);
	return 0;
}

// 아이템을 판매하는 함수에요.
int32 SellItem(const int32 itemTable[], int32 count)
{
	printf("판매하고 싶은 아이템의 번호를 입력해주세요. (원가의 80%%로 판매, 마지막 번호는 처음으로 돌아가기)\n");

	int32 endSelectionNum = count + 1;
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

	// 인벤토리에 이미 있는 아이템인지 확인 필요!
	int32 foundIdx = FindAlreadyPossessItemIdx(selectedItemID);
	if (foundIdx != INVALID_VALUE)
	{
		--g_playerInventory[foundIdx][1];
		if (g_playerInventory[foundIdx][1] <= 0)
		{
			// 찾은 인덱스 다음부터 배열의 끝까지를 땡겨서 복사해요.
			memcpy(&g_playerInventory[foundIdx][INVENTORY_ITEM_ID_IDX],
				&g_playerInventory[foundIdx + 1][INVENTORY_ITEM_ID_IDX],
				2 * sizeof(int32) * (MAX_PLAYER_INVENTORY_CAPACITY - foundIdx - 1));

			// 아이템을 판매해서 더 이상 소지 중이 아니라면 이전 인벤토리 인덱스로 이동해요.
			--g_playerCurrentInventoryIdx;
		}
	}

	g_playerMoney += (int32)(selectedItemPrice * 0.80f);
	g_playerMoney = ClampNum(g_playerMoney, 0, 9999);

	printf("입력한 번호인 %d번 아이템을 판매하셨어요~\n", selectedItemNum);
	return 0;
}