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
const int32 GO_BACK  = 1;
const int32 INVALID_VALUE = -1;

const int32 MAX_ITEM_TYPE_COUNT = 13;
const int32 MAX_PLAYER_MONEY    = 9999;
const int32 MAX_PLAYER_INVENTORY_CAPACITY = 4;

const int32 ACTION_BUY  = 1;
const int32 ACTION_SELL = 2;
const int32 ACTION_EXIT = 3;

const int32 CATEGORY_POTION  = 1;
const int32 CATEGORY_GROCERY = 2;
const int32 CATEGORY_CAMPING = 3;
const int32 SHOP_ITEM_CATEGORY_END = CATEGORY_CAMPING + 1;

const int32 POTION_TYPE_COUNT  = 4;
const int32 GROCERY_TYPE_COUNT = 5;
const int32 CAMPING_TYPE_COUNT = 4;

const int32 INVENTORY_INFO_COUNT     = 2;
const int32 INVENTORY_ITEM_ID_IDX    = 0;
const int32 INVENTORY_ITEM_COUNT_IDX = 1;

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
// ������ �ҽ� �ڵ带 �� �� �����ϰ� ����� �� �߿��ϴϱ��.
// =======================================================================
int32 g_playerMoney = 2000;
int32 g_playerInventory[MAX_PLAYER_INVENTORY_CAPACITY][INVENTORY_INFO_COUNT];
int32 g_playerCurrentInventoryIdx; // ������ �κ��丮�� ä�� �� ���Ǵϱ� �� ����صμ���!

//////////////////////////////////////////////////////////////////////////
// �̹� ������Ʈ�� �ʿ��� �Լ��� �����ҰԿ�.
// =======================================================================
// ��ƿ��Ƽ �Լ� ����̿���.
// ��ƿ��Ƽ �Լ��� ��� ������Ʈ������ ����� �� �־�� ����!
void  PauseApp();
void  ClearConsoleScreen();
void  ClearStdInputBuffer();
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
void  ShowItemTable(const int32 itemTable[], int32 count, bool bSell);
int32 BuyItem(const int32 itemTable[], int32 count);
int32 SellItem(const int32 itemTable[], int32 count); // ���� �Լ��� �������.

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
		return "NoItem";
	}
	return g_itemDBForName[foundIdx];
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
int32 FindAlreadyPossessionItemIdx(int32 itemID)
{
	// ���� ���� �ִ� �����ۿ����� ã�ƾ� �ؿ�.
	for (int32 i = 0; i < g_playerCurrentInventoryIdx; ++i)
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
		// ������ ī�װ��� ���� ���� ������ �������� �޶�����.
		// ������ �ڷᱸ���� ����ϰ� ���� ������...
		// �� ī�װ��� �ش�Ǵ� ������ ID ����� ���������Կ�... (�ϵ� �ڵ�)
		switch (selectedCategoryNum)
		{
		case CATEGORY_POTION:
		{
			int32 potionItems[POTION_TYPE_COUNT] = { 0x00001000, 0x00001001, 0x00001002, 0x00001003 };
			ShowItemTable(potionItems, POTION_TYPE_COUNT, false);
			returnValue = BuyItem(potionItems, POTION_TYPE_COUNT);
			break;
		}
		case CATEGORY_GROCERY:
		{
			int32 groceryItems[GROCERY_TYPE_COUNT] = { 0x00002000, 0x00002001, 0x00002002, 0x00002003, 0x00002004 };
			ShowItemTable(groceryItems, GROCERY_TYPE_COUNT, false);
			returnValue = BuyItem(groceryItems, GROCERY_TYPE_COUNT);
			break;
		}
		case CATEGORY_CAMPING:
		{
			int32 campingItems[CAMPING_TYPE_COUNT] = { 0x00003000, 0x00003001, 0x00003002, 0x00003003 };
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
		// �κ��丮�� 2���� �迭�̹Ƿ� ������ ID�� ���� �̾Ƽ� 1���� �迭�� ������ �ؿ�.
		// 2���� �迭�� �Լ� ���ڷ� �����Ϸ��� �����͸� �˾ƾ� �ϹǷ�...
		int32 itemIDTable[MAX_PLAYER_INVENTORY_CAPACITY];
		for (int32 i = 0; i < MAX_PLAYER_INVENTORY_CAPACITY; ++i)
		{
			if (g_playerInventory[i][INVENTORY_ITEM_ID_IDX] != NO_VALUE)
			{
				itemIDTable[i] = g_playerInventory[i][INVENTORY_ITEM_ID_IDX];
			}
		}

		// ���� �κ��丮 �ε����� ���� ���� �ִ� ������ ������ ���� �ǹ��ؿ�.
		// �̸��� �򰥸� �� ������ �̸��� �ٽ� ���ҰԿ�.
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
// �κ��丮�� ���� �� �� ��� �����ϴٴ� �ŷ��� ����!
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

		// ����� ���ڿ��� ���� �������Ѿ� UI�� ��Ʈ������ �ʾƿ�!
		printf("�� %d.%-18s�� %4d�� %4d��\n", i + 1, strItemName.c_str(), itemPrice, itemPossessionCount);
	}

	printf("����������������������������������������������������������������������\n");
	printf("�� ������ : %-4d                   ��\n", g_playerMoney);
	printf("����������������������������������������������������������������������\n");
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
		if (g_playerCurrentInventoryIdx >= MAX_PLAYER_INVENTORY_CAPACITY)
		{
			printf("�� �̻� �������� ���� �� �����...\n");
			return 0;
		}

		// ������ �ִ� ������ ������ ������ �ؿ�
		memset(&g_playerInventory[g_playerCurrentInventoryIdx][INVENTORY_ITEM_ID_IDX], 0, sizeof(int32) * 2);

		// �κ��丮�� ������ ������ �����ؿ�.
		g_playerInventory[g_playerCurrentInventoryIdx][INVENTORY_ITEM_ID_IDX] = selectedItemID;
		++g_playerInventory[g_playerCurrentInventoryIdx][INVENTORY_ITEM_COUNT_IDX];

		// ���� �κ��丮 �ε����� �̵��ؾ� �ؿ�!
		++g_playerCurrentInventoryIdx;
	}

	// ������� �Դٸ� �������� ������ �Ŵϱ� �÷��̾��� ���� ó���ؾ߰���?
	g_playerMoney -= selectedItemPrice;
	g_playerMoney = ClampNum(g_playerMoney, 0, MAX_PLAYER_MONEY);

	std::string strSelectedItemName = FindItemNameInDB(selectedItemID);
	printf("�Է��� ��ȣ�� %d�� ������(%s)�� �����ϼ̾��~\n", selectedItemNum, strSelectedItemName.c_str());
	return 0;
}

// ���� ���������� �������� �Ǹ��ϴ� �Լ��� �����Կ�.
int32 SellItem(const int32 itemTable[], int32 count)
{
	printf("�Ǹ��ϰ� ���� �������� ��ȣ�� �Է����ּ���. (������ 80%% �Ǹ�, ������ ��ȣ�� ó������ ���ư���)\n");

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
			--g_playerCurrentInventoryIdx;
		}
	}

	// ������� �Դٸ� �������� �Ǹ��� �Ŵϱ� �÷��̾��� ���� �����ؾ߰���?
	g_playerMoney += (int32)(selectedItemPrice * 0.80f);
	g_playerMoney = ClampNum(g_playerMoney, 0, MAX_PLAYER_MONEY);

	std::string strSelectedItemName = FindItemNameInDB(selectedItemID);
	printf("�Է��� ��ȣ�� %d�� ������(%s)�� �Ǹ��ϼ̾��~\n", selectedItemNum, strSelectedItemName.c_str());
	return 0;
}
