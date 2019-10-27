// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <windows.h>
#include <string>
#include <array>

using int32  = signed __int32;
using real32 = float;

//////////////////////////////////////////////////////////////////////////
// �̹� ������Ʈ�� �ʿ��� ��������� �����ҰԿ�.
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

// �÷��̾��� �κ��丮�� ��ȭ ������ ������ ������ �����ͺ��̽�(Database, �ٿ��� DB)����.
// �� �� ȿ�������� �����Ϸ��� Ŭ������ �ڷᱸ���� �����ؾ� �ϴµ� ������ �����ҰԿ�.
const std::array<int32, MAX_ITEM_TYPE_COUNT> g_itemDBForID =
{
	0x00001000, 0x00001001, 0x00001002, 0x00001003,
	0x00002000, 0x00002001, 0x00002002, 0x00002003, 0x00002004,
	0x00003000, 0x00003001, 0x00003002, 0x00003003
};

const std::array<std::string, MAX_ITEM_TYPE_COUNT> g_itemDBForName =
{
	"����� ȸ����", "������ ȸ����", "Ư�� ȸ����", "������ġ��",
	"���", "�������", "�Ұ��", "�ұ�", "����",
	"�߿���Ʈ", "���� ��ġ", "������", "ħ��"
};

const std::array<int32, MAX_ITEM_TYPE_COUNT> g_itemDBForPrice =
{
	10, 50, 100, 200,
	5, 10, 20, 5, 5,
	150, 100, 50, 150
};

//////////////////////////////////////////////////////////////////////////
// �̹� ������Ʈ�� �ʿ��� ���������� �����ҰԿ�.
// ���������� �ǵ����̸� ������� �������� ������...
// ������ �ҽ� �ڵ带 �� �� �����ϰ� ����� �� �߿��ϴϱ��.
// =======================================================================
int32 g_playerMoney = 2000;
int32 g_playerInventoryEmptyIdx; // ����ִ� �ε����� ������ ������ �����Կ�!
std::array<std::array<int32, INVENTORY_INFO_COUNT>, MAX_PLAYER_INVENTORY_CAPACITY> g_playerInventory;

//////////////////////////////////////////////////////////////////////////
// �̹� ������Ʈ�� �ʿ��� �Լ��� �����ҰԿ�.
// =======================================================================
// ��ƿ��Ƽ �Լ� ����̿���.
// ��ƿ��Ƽ �Լ��� ��� ������Ʈ������ ����� �� �־�� ����!
void  PauseApp();
void  ClearConsoleScreen();
void  ClearStdInputBuffer();
void  MoveConsolePosition(int32 x, int32 y);
COORD TakeCurrentConsolePosition();
bool  InputNumAutoRange(_Out_ int32& num, int32 minNum, int32 maxNum);
int32 ClampNum(int32 num, int32 minNum, int32 maxNum);

// ������ DB �˻� �Լ� ����̿���.
std::string FindItemNameInDB(int32 itemID);
int32       FindItemIdxInDB(int32 itemID); // �� �༮�� �ٽ� �Լ�����!
int32       FindItemPriceInDB(int32 itemID);
int32       FindAlreadyPossessionItemIdx(int32 itemID); // �� �༮�� �κ��丮�� �ٽ� �Լ�����!
int32       FindItemPossessionCountInInventory(int32 itemID);

// ��ȭ ���� ���� �Լ� ����̿���.
bool  EnterMiscellaneousShop();
int32 ShowBuyItemMenu();
int32 ShowSellItemMenu();

// �÷��̾� ���� �Լ� ����̿���.
void ShowPlayerInventory(int32 x, int32 y, bool bSell);
std::array<int32, MAX_PLAYER_INVENTORY_CAPACITY> TakePlayerInventoryOnlyItemID();

// ���ø� �Լ� ����̿���.
// ������ ������ �����ִ� �Լ�����.
// �κ��丮�� ���� �� �� ��� �����ϴٴ� �ŷ��� ����!
template <typename int32 itemCount>
void ShowItemTable(int32 x, int32 y, const std::array<int32, itemCount>& itemTable, bool bSell)
{
	MoveConsolePosition(x, y);
	printf("����������������������������������������������������������������������");
	MoveConsolePosition(x, ++y);
	printf("�� �̸�                �� ���ݦ� ������");
	MoveConsolePosition(x, ++y);
	printf("����������������������������������������������������������������������");

	for (int32 i = 0; i < itemCount; ++i)
	{
		std::string strItemName = FindItemNameInDB(itemTable[i]);

		int32 itemPrice = FindItemPriceInDB(itemTable[i]);
		if (bSell == true)
		{
			itemPrice = (int32)(itemPrice * 0.80f);
		}

		int32 itemPossessionCount = FindItemPossessionCountInInventory(itemTable[i]);

		// ����� ���ڿ��� ���� �������Ѿ� UI�� ��Ʈ������ �ʾƿ�!
		MoveConsolePosition(x, ++y);
		printf("�� %d.%-18s�� %4d�� %4d��", i + 1, strItemName.c_str(), itemPrice, itemPossessionCount);
	}

	MoveConsolePosition(x, ++y);
	printf("����������������������������������������������������������������������");
	MoveConsolePosition(x, ++y);
	printf("�� ������ : %-4d                   ��", g_playerMoney);
	MoveConsolePosition(x, ++y);
	printf("����������������������������������������������������������������������");
	
	MoveConsolePosition(0, ++y);
}

template <typename int32 itemCount>
int32 BuyItem(const std::array<int32, itemCount>& itemTable)
{
	printf("�����ϰ� ���� �������� ��ȣ�� �Է����ּ���. (������ ��ȣ�� ó������ ���ư���)\n");

	int32 endSelectionNum = itemCount + 1;
	int32 selectedItemNum = NO_VALUE;
	while (InputNumAutoRange(selectedItemNum, 1, endSelectionNum) == false)
	{
		printf("�ٽ� �Է����ּ���!\n");
	}

	if (selectedItemNum == endSelectionNum)
	{
		return GO_BACK;
	}

	int32 selectedItemID = itemTable[selectedItemNum - 1];
	int32 selectedItemPrice = FindItemPriceInDB(selectedItemID);

	if (g_playerMoney < selectedItemPrice)
	{
		printf("������ \"%d\"�����δ� \"%d\"���� �������� ������ �� �����!\n", g_playerMoney, selectedItemPrice);
		return 0;
	}

	// �κ��丮�� �̹� �ִ� ���������� Ȯ���ؾ� �ؿ�!
	int32 foundIdx = FindAlreadyPossessionItemIdx(selectedItemID);
	if (foundIdx != INVALID_VALUE)
	{
		// �̹� ���� ���� �������̸� ������ �÷���.
		++g_playerInventory[foundIdx][INVENTORY_ITEM_COUNT_IDX];
	}
	else
	{
		// �κ��丮�� �� á���� Ȯ���ؾ� �ؿ�!
		if (g_playerInventoryEmptyIdx >= MAX_PLAYER_INVENTORY_CAPACITY)
		{
			printf("�� �̻� �������� ���� �� �����...\n");
			return 0;
		}

		// ������ �ִ� ������ ������ ������ �ؿ�
		memset(&g_playerInventory[g_playerInventoryEmptyIdx][INVENTORY_ITEM_ID_IDX], 0, sizeof(int32) * 2);

		// �κ��丮�� ������ ������ �����ؿ�.
		g_playerInventory[g_playerInventoryEmptyIdx][INVENTORY_ITEM_ID_IDX] = selectedItemID;
		++g_playerInventory[g_playerInventoryEmptyIdx][INVENTORY_ITEM_COUNT_IDX];

		// ���� �κ��丮 �ε����� �̵��ؾ� �ؿ�!
		++g_playerInventoryEmptyIdx;
	}

	// ������� �Դٸ� �������� ������ �Ŵϱ� �÷��̾��� ���� ó���ؾ߰���?
	g_playerMoney -= selectedItemPrice;
	g_playerMoney = ClampNum(g_playerMoney, 0, MAX_PLAYER_MONEY);

	std::string strSelectedItemName = FindItemNameInDB(selectedItemID);
	printf("�Է��� ��ȣ�� %d�� ������(%s)�� �����ϼ̾��~\n", selectedItemNum, strSelectedItemName.c_str());
	return 0;
}

template <typename int32 itemCount>
int32 SellItem(const std::array<int32, itemCount>& itemTable)
{
	printf("�Ǹ��ϰ� ���� �������� ��ȣ�� �Է����ּ���. (������ 80%% �Ǹ�, ������ ��ȣ�� ó������ ���ư���)\n");

	int32 endSelectionNum = itemCount + 1;
	int32 selectedItemNum = NO_VALUE;
	while (InputNumAutoRange(selectedItemNum, 1, endSelectionNum) == false)
	{
		printf("�ٽ� �Է����ּ���!\n");
	}

	if (selectedItemNum == endSelectionNum)
	{
		return GO_BACK;
	}

	int32 selectedItemID = itemTable[selectedItemNum - 1];
	int32 selectedItemPrice = FindItemPriceInDB(selectedItemID);

	// �κ��丮�� �������� �־�� �� �� �ְ���?
	int32 foundIdx = FindAlreadyPossessionItemIdx(selectedItemID);
	if (foundIdx != INVALID_VALUE)
	{
		--g_playerInventory[foundIdx][INVENTORY_ITEM_COUNT_IDX];
		if (g_playerInventory[foundIdx][INVENTORY_ITEM_COUNT_IDX] <= 0)
		{
			// �� ���� �������� ���� �Ⱦ��� ���ϱ� �κ��丮�� �����ؾ� �ؿ�!
			// ã�� �ε��� �������� �迭�� �������� ���ܼ� ���� �����ҰԿ�.
			// �̷��� �Ǹ� �迭�� �����Ⱚ�� ���� �Ǵµ� ������ ������ �� ���Ǵ�
			// �ε����� �����Ⱚ���� ã�� �����Ƿ� ������ �����.
			// �� �κ��� �ٽ��ε� ���� �����Ƿ� ���ذ� ���� ������ õõ�� ������.
			memcpy(&g_playerInventory[foundIdx][INVENTORY_ITEM_ID_IDX],
				&g_playerInventory[foundIdx + 1][INVENTORY_ITEM_ID_IDX],
				sizeof(int32) * 2 * (MAX_PLAYER_INVENTORY_CAPACITY - foundIdx - 1));

			// �������� �Ǹ��ؼ� �� �̻� ���� ���� �ƴ϶�� ���� �κ��丮 �ε����� �̵��ؾ� �ؿ�.
			--g_playerInventoryEmptyIdx;
		}
	}

	// ������� �Դٸ� �������� �Ǹ��� �Ŵϱ� �÷��̾��� ���� �����ؾ߰���?
	g_playerMoney += (int32)(selectedItemPrice * 0.80f);
	g_playerMoney = ClampNum(g_playerMoney, 0, MAX_PLAYER_MONEY);

	std::string strSelectedItemName = FindItemNameInDB(selectedItemID);
	printf("�Է��� ��ȣ�� %d�� ������(%s)�� �Ǹ��ϼ̾��~\n", selectedItemNum, strSelectedItemName.c_str());
	return 0;
}



// ���α׷��� ���۵Ǵ� ���̿���.
int32 main()
{
	//////////////////////////////////////////////////////////////////////////
	// ������Ʈ - ��ȭ ������ �����Կ�~
	//////////////////////////////////////////////////////////////////////////

	// ��ȭ ������ ���� �κ��̿���.
	while (EnterMiscellaneousShop() == true)
	{
		// ��ȯ���� false�� ��ȭ �������� ������.
	}

	return EXIT_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// �Ʊ� �����ߴ� ��ƿ��Ƽ �Լ����� �����Կ�~

// ���� ���α׷��� ��� ���ߴ� �Լ�����.
void PauseApp()
{
	std::system("pause");
}

// �ܼ�â�� �����ϰ� �����ִ� �Լ�����.
void ClearConsoleScreen()
{
	std::system("cls");
}

// ǥ�� �Է� ���۸� ����ִ� �Լ�����.
void ClearStdInputBuffer()
{
	char ch = '0'; // EOF�� '\n'�� �ƴϸ� �����ƿ�.

	// ǥ�� �Է� ���۸� ���� ����̿���.
	// std::fflush(stdin)�� ������, ǥ�ؿ��� �������� �ʾƼ� �����ҰԿ�.
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

// ���ڸ� �Է� ������ ���ÿ� �Է� ������ ����� �ڵ� �������ִ� �Լ�����.
bool InputNumAutoRange(_Out_ int32& num, int32 minNum, int32 maxNum)
{
	// �ּڰ��� �ִ񰪺��� ũ�ٸ� ���� �ٲ���� �ؿ�! (swap)
	if (minNum > maxNum)
	{
		std::swap(minNum, maxNum);
	}

	printf("�Է� ������ ����� �ڵ� �����˴ϴ�. (%d ~ %d)\n", minNum, maxNum);
	printf("> ");

	int32 inputResult = scanf_s("%d", &num);
	printf("\n");
	ClearStdInputBuffer();

	if (inputResult == 0)
	{
		printf("������ �Է� �����ؿ�!\n");
		return false;
	}

	num = ClampNum(num, minNum, maxNum);
	return true;
}

// ���ڸ� ���ѵ� ������ ���������ִ� �Լ�����.
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
// �Ʊ� �����ߴ� ������ DB �˻� �Լ����� �����Կ�~

// DB������ ������ �ε����� ã���ִ� �Լ�����.
int32 FindItemIdxInDB(int32 itemID)
{
	// �̷� �� ����Ž���̶�� �ϴµ� ������ ���ǰ� �ִ� DB�� ����Ž���� ����ϸ� ���ؿ�...
	// Ž�� �˰��򿡴� ���������� �ִµ� �ϴ��� ����Ž���� ����ҰԿ�.
	for (int32 i = 0; i < MAX_ITEM_TYPE_COUNT; ++i)
	{
		// ������ ID���� ���ϴ� �� ���� ��Ȯ�ؿ�!
		if (g_itemDBForID[i] == itemID)
		{
			return i;
		}
	}

	return INVALID_VALUE;
}

// DB���� ������ �̸��� ã���ִ� �Լ�����.
std::string FindItemNameInDB(int32 itemID)
{
	int32 foundIdx = FindItemIdxInDB(itemID);
	if (foundIdx == INVALID_VALUE)
	{
		return "";
	}
	return g_itemDBForName.at(foundIdx);
}

// DB���� ������ ������ ã���ִ� �Լ�����.
int32 FindItemPriceInDB(int32 itemID)
{
	int32 foundIdx = FindItemIdxInDB(itemID);
	if (foundIdx == INVALID_VALUE)
	{
		return NO_VALUE;
	}
	return g_itemDBForPrice.at(foundIdx);
}

// �κ��丮�� �������� �̹� �ִ��� Ȯ�����ִ� �Լ�����.
int32 FindAlreadyPossessionItemIdx(int32 itemID)
{
	// ���� ���� �ִ� �����ۿ����� ã�ƾ� �ؿ�.
	for (int32 i = 0; i < g_playerInventoryEmptyIdx; ++i)
	{
		if (g_playerInventory[i][INVENTORY_ITEM_ID_IDX] == itemID)
		{
			return i;
		}
	}
	return INVALID_VALUE;
}

// �κ��丮�� �ִ� ������ ������ �������� �Լ�����.
int32 FindItemPossessionCountInInventory(int32 itemID)
{
	// �κ��丮�� �������� �־�� ������ ������ �˾Ƴ� �� �ְ���?
	int32 foundItemIdx = FindAlreadyPossessionItemIdx(itemID);
	if (foundItemIdx != INVALID_VALUE)
	{
		return g_playerInventory[foundItemIdx][INVENTORY_ITEM_COUNT_IDX];
	}
	return NO_VALUE;
}

//////////////////////////////////////////////////////////////////////////
// ���⼭���ʹ� ���������� ��ȭ ������ �����ϰ� �ǿ�.
// ���� ��ȭ ������ ���� �Լ����� ����� �����ϰ� �׽�Ʈ�� �غ���!

bool EnterMiscellaneousShop()
{
	printf("��ȭ ������ ���� �� ȯ���ؿ�~!\n");
	printf("���� �Ϸ� ���̳���? (1.����  2.�Ǹ�  3.������)\n\n");

	int32 selectedActionNum = NO_VALUE;
	while (InputNumAutoRange(selectedActionNum, ACTION_BUY, ACTION_EXIT) == false)
	{
		printf("�ٽ� �Է����ּ���!\n");
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
		printf("�ȳ��� ������~\n");
		return false;
	}
	}

	PauseApp();
	ClearConsoleScreen();
	return true;
}

// �⺻ �޴��� �� ������ �� ���׿�~
// ���� �ٽ� ����� ���ſ� �Ǹ� ����� �����Կ�~

// ���� �޴��� �����ִ� �Լ�����.
int32 ShowBuyItemMenu()
{
	printf("� �����ۿ� ���� ��������? (1.����  2.�ķ�ǰ  3.�߿ܿ�ǰ  4.�ڷ�)\n");

	int32 selectedCategoryNum = NO_VALUE;
	while (InputNumAutoRange(selectedCategoryNum, CATEGORY_POTION, SHOP_ITEM_CATEGORY_END) == false)
	{
		printf("�ٽ� �Է����ּ���!\n");
	}

	if (selectedCategoryNum == SHOP_ITEM_CATEGORY_END)
	{
		return GO_BACK;
	}

	int32 returnValue = NO_VALUE;
	while (returnValue != GO_BACK)
	{
		COORD currentPos = TakeCurrentConsolePosition();
		ShowPlayerInventory(50, currentPos.Y - 1, false); // y��ǥ�� �ʿ��ϹǷ�...
		MoveConsolePosition(currentPos.X, currentPos.Y);

		// ������ ī�װ��� ���� ���� ������ �������� �޶�����.
		// ������ �ڷᱸ���� ����ϰ� ���� ������...
		// �� ī�װ��� �ش�Ǵ� ������ ID ����� ���������Կ�... (�ϵ� �ڵ�)
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

// �Ǹ� �޴��� �����ִ� �Լ�����.
int32 ShowSellItemMenu()
{
	int32 returnValue = NO_VALUE;
	while (returnValue != GO_BACK)
	{
		COORD currentPos = TakeCurrentConsolePosition();
		ShowPlayerInventory(0, currentPos.Y - 1, true);
		
		// ���� �κ��丮 �ε����� ���� ���� �ִ� ������ ������ ���� �ǹ��ؿ�.
		// �̸��� �򰥸� �� ������ �̸��� �ٽ� ���ҰԿ�.
		int32 currentInventoryItemCount = g_playerInventoryEmptyIdx;
		if (currentInventoryItemCount <= NO_VALUE)
		{
			printf("�Ǹ��� �������� �����...\n");
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
	// �κ��丮�� 2���� �迭�̹Ƿ� ������ ID�� ���� �̾Ƽ� 1���� �迭�� ������ �ؿ�.
	// 2���� �迭�� �Լ� ���ڷ� �����Ϸ��� �����͸� �˾ƾ� �ϹǷ�...
	std::array<int32, MAX_PLAYER_INVENTORY_CAPACITY> itemIDTable;
	for (int32 i = 0; i < MAX_PLAYER_INVENTORY_CAPACITY; ++i)
	{
		itemIDTable[i] = g_playerInventory[i][INVENTORY_ITEM_ID_IDX];
	}
	return itemIDTable;
}