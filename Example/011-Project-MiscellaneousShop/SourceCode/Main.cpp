// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <string>

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

// �÷��̾��� �κ��丮�� ��ȭ ������ ������ ������ �����ͺ��̽�(Database, �ٿ��� DB)����.
// �� �� ȿ�������� �����Ϸ��� Ŭ������ �ڷᱸ���� �����ؾ� �ϴµ� ������ �����ҰԿ�.
const int32 g_itemDBForID[MAX_ITEM_TYPE_COUNT] =
{
	0x00001000, 0x00001001, 0x00001002, 0x00001003,
	0x00002000, 0x00002001, 0x00002002, 0x00002003, 0x00002004,
	0x00003000, 0x00003001, 0x00003002, 0x00003003
};

const std::string g_itemDBForName[MAX_ITEM_TYPE_COUNT] =
{
	"����� ȸ����", "������ ȸ����", "Ư�� ȸ����", "������ġ��",
	"���", "�������", "�Ұ��", "�ұ�", "����",
	"�߿���Ʈ", "���� ��ġ", "������", "ħ��"
};

const int32 g_itemDBForPrice[MAX_ITEM_TYPE_COUNT] =
{
	10, 50, 100, 200,
	5, 10, 20, 5, 5,
	150, 100, 50, 150
};

//////////////////////////////////////////////////////////////////////////
// �̹� ������Ʈ�� �ʿ��� ���������� �����ҰԿ�.
// ���������� �ǵ����̸� ������� �������� ������...
// ������ �ҽ� �ڵ带 �� �� �����ϰ� ������ �ؼ���.
// =======================================================================
int32 g_playerMoney = 5000;
int32 g_playerCurrentInventoryIdx;
int32 g_playerInventory[MAX_PLAYER_INVENTORY_CAPACITY][INVENTORY_ITEM_INFO_COUNT];

//////////////////////////////////////////////////////////////////////////
// �̹� ������Ʈ�� �ʿ��� �Լ��� �����ҰԿ�.
// =======================================================================
// ��ƿ��Ƽ �Լ� ����̿���.
// ��Ƽ��Ƽ �Լ��� ��� ������Ʈ������ ����� �� �־�� �ؿ�!
void  PauseApp();
void  ClearConsoleScreen();
void  ClearStdInput();
bool  InputNumAutoRange(_Out_ int32& num, int32 minNum, int32 maxNum);
int32 ClampNum(int32 num, int32 minNum, int32 maxNum);

// �˻� �Լ� ����̿���.
const std::string FindItemNameInDB(int32 itemID);
int32 FindItemIdxInDB(int32 itemID);
int32 FindItemPriceInDB(int32 itemID);
int32 FindAlreadyPossessItemIdx(int32 itemID);
int32 FindItemPossessionCountInInventory(int32 itemID);

// ���� ���� �Լ� ����̿���.
bool  EnterMiscellaneousShop();
int32 ShowBuyItemMenu();
int32 ShowSellItemMenu();
void  ShowItemTable(const int32 itemTable[], int32 count, bool bSell);
int32 BuyItem(const int32 itemTable[], int32 count);
int32 SellItem(const int32 itemTable[], int32 count);

int main()
{
	//////////////////////////////////////////////////////////////////////////
	// ������Ʈ - ��ȭ ������ ��������~
	//////////////////////////////////////////////////////////////////////////

	// ������ ���Կ�.
	while (EnterMiscellaneousShop() == true)
	{
		// ��ȯ���� false�� ������ ������.
	}

	return EXIT_SUCCESS;
}

// ���� ���α׷��� ��� ���ߴ� �Լ�����.
void PauseApp()
{
	std::system("pause");
}

// �ܼ�â�� �����ϰ� �����ִ� �Լ�����.
void ClearConsoleScreen()
{
	std::system("cls"); // ���־� ��Ʃ��������� ��� �����ؿ�.
}

// ǥ�� �Է� ���۸� ����ִ� �Լ�����.
void ClearStdInput()
{
	char ch = '0'; // EOF�� '\n'�� �ƴϸ� ��!

	// ǥ�� �Է� ���۸� ���� ����̿���.
	// std::fflush(stdin)�� ǥ�ؿ� �������� �ʾƼ� ������� �����Կ�.
	while ((ch != EOF) && (ch != '\n'))
	{
		ch = getchar();
	};
}

// ���ڸ� �Է� ������ ���ÿ� �Է� ������ ����� �ڵ� �������ִ� �Լ�����.
bool InputNumAutoRange(_Out_ int32& num, int32 minNum, int32 maxNum)
{
	if (minNum > maxNum)
	{
		minNum = maxNum;
	}

	printf("�Է� ������ ����� �ڵ� �����˴ϴ�. (%d ~ %d)\n", minNum, maxNum);
	printf("> ");
	int32 inputResult = scanf_s("%d", &num);
	printf("\n");
	ClearStdInput();

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

// DB���� ������ �̸��� ã���ִ� �Լ�����.
const std::string FindItemNameInDB(int32 itemID)
{
	int32 foundIdx = FindItemIdxInDB(itemID);
	if (foundIdx == INVALID_VALUE)
	{
		return "NoItem";
	}

	return g_itemDBForName[foundIdx];
}

// DB������ ������ �ε����� ã���ִ� �Լ�����.
int32 FindItemIdxInDB(int32 itemID)
{
	int32 foundIdx = INVALID_VALUE;
	for (int32 i = 0; i < MAX_ITEM_TYPE_COUNT; ++i)
	{
		// ������ ID���� ���ϴ� �� ���� ��Ȯ�ؿ�.
		if (g_itemDBForID[i] == itemID)
		{
			foundIdx = i;
		}
	}

	return foundIdx;
}

// DB���� ������ ������ ã���ִ� �Լ�����.
int32 FindItemPriceInDB(int32 itemID)
{
	int32 foundIdx = FindItemIdxInDB(itemID);
	if (foundIdx == INVALID_VALUE)
	{
		return INVALID_VALUE;
	}

	return g_itemDBForPrice[foundIdx];
}

// �κ��丮�� �������� �̹� �ִ��� Ȯ�����ִ� �Լ�����.
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

// �κ��丮�� �ִ� ������ ������ �������� �Լ�����.
int32 FindItemPossessionCountInInventory(int32 itemID)
{
	// �κ��丮�� �������� �־�� ������ ������ ������ �� �־��.
	int32 foundItemIdx = FindAlreadyPossessItemIdx(itemID);
	if (foundItemIdx != INVALID_VALUE)
	{
		return g_playerInventory[foundItemIdx][INVENTORY_ITEM_COUNT_IDX];
	}

	return 0;
}

// ��ȭ ������ ���� �Լ�����.
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

// ���� �޴��� �����ִ� �Լ�����.
int32 ShowBuyItemMenu()
{
	printf("� �����ۿ� ���� ��������? (1.����  2.�ķ�ǰ  3.�߿ܿ�ǰ  4.�ڷ�)\n");

	int32 selectedCategoryNum = NO_VALUE;
	while (InputNumAutoRange(selectedCategoryNum, CATEGORY_POTION, SHOP_MENU_END) == false)
	{
		printf("�ٽ� �Է����ּ���!\n");
	}

	if (selectedCategoryNum == SHOP_MENU_END)
	{
		return GO_BACK;
	}

	int32 returnValue = NO_VALUE;
	while (returnValue != GO_BACK)
	{
		// ������ ī�װ��� ���� ���� ������ �������� �޶�����.
		// ������ �ڷᱸ���� ������� �ʾƼ� �� ī�װ��� �ش�Ǵ� ������ ID ����� �����ھҾ��. (�ϵ� �ڵ�)
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

// �Ǹ� �޴��� �����ִ� �Լ�����.
int32 ShowSellItemMenu()
{
	int32 returnValue = NO_VALUE;
	while (returnValue != GO_BACK)
	{
		// �κ��丮�� 2���� �迭�̹Ƿ� ������ ID�� ���� �̾Ƽ� 1���� �迭�� ����Կ�.
		// 2���� �迭�� �Լ� ���ڷ� �����Ϸ��� �����͸� �˾ƾ� �ؼ���...
		int32 itemIDTable[MAX_PLAYER_INVENTORY_CAPACITY];
		for (int32 i = 0; i < MAX_PLAYER_INVENTORY_CAPACITY; ++i)
		{
			if (g_playerInventory[i][INVENTORY_ITEM_ID_IDX] != NO_VALUE)
			{
				itemIDTable[i] = g_playerInventory[i][INVENTORY_ITEM_ID_IDX];
			}
		}

		// ���� �κ��丮 �ε����� ���� ���� �ִ� ������ ������ ���� �ǹ��ؿ�.
		// �̸��� �򰥸� �� ������ �̸��� �ٽ� ���߾��.
		int32 currentInventoryItemCount = g_playerCurrentInventoryIdx;
		if (currentInventoryItemCount > NO_VALUE)
		{
			ShowItemTable(itemIDTable, currentInventoryItemCount, true);
			returnValue = SellItem(itemIDTable, currentInventoryItemCount);
		}
		else
		{
			printf("�Ǹ��� �������� �����...\n");
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

// ������ ������ �����ִ� �Լ�����.
// �κ��丮�� ���� �� �� ��� �����ؿ�.
void ShowItemTable(const int32 itemTable[], int32 count, bool bSell)
{
	printf("����������������������������������������������������������������������\n");
	printf("�� �̸�                �� ���ݦ� ������\n");
	printf("����������������������������������������������������������������������\n");

	for (int32 i = 0; i < count; ++i)
	{
		std::string strItemName = FindItemNameInDB(itemTable[i]);
		
		int32 itemPrice = FindItemPriceInDB(itemTable[i]);
		if (bSell == true)
		{
			itemPrice = (int32)(itemPrice * 0.80f);
		}

		int32 itemPossessionCount = FindItemPossessionCountInInventory(itemTable[i]);

		// ����� ���ڿ��� ���� ������Ű�� ����̿���.
		printf("�� %d.%-18s�� %4d�� %4d��\n", i + 1, strItemName.c_str(), itemPrice, itemPossessionCount);
	}

	printf("����������������������������������������������������������������������\n");
	printf("�� ������ : %-4d                   ��\n", g_playerMoney);
	printf("����������������������������������������������������������������������\n\n");
}

// �������� �����ϴ� �Լ�����.
int32 BuyItem(const int32 itemTable[], int32 count)
{
	printf("�����ϰ� ���� �������� ��ȣ�� �Է����ּ���. (������ ��ȣ�� ó������ ���ư���)\n");

	int32 endSelectionNum = count + 1;
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

	// �κ��丮�� �̹� �ִ� ���������� Ȯ�� �ʿ�!
	int32 foundIdx = FindAlreadyPossessItemIdx(selectedItemID);
	if (foundIdx != INVALID_VALUE)
	{
		// �̹� ���� ���� �������̸� ������ �÷���.
		++g_playerInventory[foundIdx][INVENTORY_ITEM_COUNT_IDX];
	}
	else
	{
		if (g_playerCurrentInventoryIdx >= MAX_PLAYER_INVENTORY_CAPACITY)
		{
			printf("�� �̻� �������� ���� �� �����...\n");
			return 0;
		}

		// �κ��丮�� ������ ������ �����ؿ�.
		g_playerInventory[g_playerCurrentInventoryIdx][INVENTORY_ITEM_ID_IDX] = selectedItemID;
		++g_playerInventory[g_playerCurrentInventoryIdx][INVENTORY_ITEM_COUNT_IDX];

		// ���� �κ��丮 �ε����� �̵��ؿ�.
		++g_playerCurrentInventoryIdx;
	}

	g_playerMoney -= selectedItemPrice;
	g_playerMoney = ClampNum(g_playerMoney, 0, MAX_PLAYER_MONEY);

	printf("�Է��� ��ȣ�� %d�� �������� �����ϼ̾��~\n", selectedItemNum);
	return 0;
}

// �������� �Ǹ��ϴ� �Լ�����.
int32 SellItem(const int32 itemTable[], int32 count)
{
	printf("�Ǹ��ϰ� ���� �������� ��ȣ�� �Է����ּ���. (������ 80%%�� �Ǹ�, ������ ��ȣ�� ó������ ���ư���)\n");

	int32 endSelectionNum = count + 1;
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

	// �κ��丮�� �̹� �ִ� ���������� Ȯ�� �ʿ�!
	int32 foundIdx = FindAlreadyPossessItemIdx(selectedItemID);
	if (foundIdx != INVALID_VALUE)
	{
		--g_playerInventory[foundIdx][1];
		if (g_playerInventory[foundIdx][1] <= 0)
		{
			// ã�� �ε��� �������� �迭�� �������� ���ܼ� �����ؿ�.
			memcpy(&g_playerInventory[foundIdx][INVENTORY_ITEM_ID_IDX],
				&g_playerInventory[foundIdx + 1][INVENTORY_ITEM_ID_IDX],
				2 * sizeof(int32) * (MAX_PLAYER_INVENTORY_CAPACITY - foundIdx - 1));

			// �������� �Ǹ��ؼ� �� �̻� ���� ���� �ƴ϶�� ���� �κ��丮 �ε����� �̵��ؿ�.
			--g_playerCurrentInventoryIdx;
		}
	}

	g_playerMoney += (int32)(selectedItemPrice * 0.80f);
	g_playerMoney = ClampNum(g_playerMoney, 0, 9999);

	printf("�Է��� ��ȣ�� %d�� �������� �Ǹ��ϼ̾��~\n", selectedItemNum);
	return 0;
}