#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct stProduct
{
	string name = "";
	double Price = 0; 
	short quantity = 0;
};

struct stInventory
{
	stProduct Itemes[100];
	string Currency = "";
	int TotalVal = 0, CurrentVal = 0;
	short ItemCounter = 0;
};


void ReadTheQuantity(stInventory& Inv)
{
	do
	{
		cout << "\nQuantity? ";
		cin >> Inv.Itemes[Inv.ItemCounter].quantity;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "\nInvalid Input! , Please enter a valid number:\n";
			cout << "Enter: ";
			cin >> Inv.Itemes[Inv.ItemCounter].quantity;
		}

		if (Inv.Itemes[Inv.ItemCounter].quantity < 0)
		{
			cout << "\nPlease Enter a Vailed Quantity!\n";
			cout << "--------------------------------\n";
		}
	} while (Inv.Itemes[Inv.ItemCounter].quantity < 0);

	cout << "\n" << string(25, (char)196) << endl;
}

void ReadThePrice(stInventory& Inv)
{
	do
	{
		cout << "Price? ";
		cin >> Inv.Itemes[Inv.ItemCounter].Price;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "\nInvalid Input! , Please enter a valid number:\n";
			cout << "Enter: ";
			cin >> Inv.Itemes[Inv.ItemCounter].Price;
		}

		if (Inv.Itemes[Inv.ItemCounter].Price < 0)
		{
			cout << "\nPlease Enter a Vailed Price!\n";
			cout << "-----------------------------\n";
		}
	} while (Inv.Itemes[Inv.ItemCounter].Price < 0);
	cout << "\n" << string(25, (char)196) << endl;

}

bool ContainsNumbers(string& str)
{
	if (str.empty())
	{
		return false;
	}

	for (char& chr : str)
	{
		if (isdigit(chr))
			return true;
	}

	return false;
}

void ReadCurrency(stInventory& Inv)
{
	bool IsThereNum;
	do
	{
		cout << "Please,Enter the Currency?\n";
		cout << string(25, (char)196) << endl;
		cin >> Inv.Currency;
		IsThereNum = ContainsNumbers(Inv.Currency);
		if (IsThereNum)
		{
			cout << "\nWrong Input!, Please Enter a Valid Input :-)\n\n";
			cout << "------------------------------------------------\n";
		}

	} while (IsThereNum);

	system("cls");
}

void ReadItems(stInventory& Inv)
{
	char Continue = 'Y';

	do
	{
		cout << "Please,Enter the Items?\n";
		cout << string(25, (char)196) << endl;

		bool IsThereNum;
		do
		{
			cin >> Inv.Itemes[Inv.ItemCounter].name;
			IsThereNum = ContainsNumbers(Inv.Itemes[Inv.ItemCounter].name);
			if (IsThereNum)
			{
				cout << "\nWrong Input!, Please Enter a Valid Input :-)\n\n";
				cout << "------------------------------------------------\n";
			}
		} while (IsThereNum);

		cout<<"\n" << string(25, (char)196) << "\n";
		cout << endl;
		ReadThePrice(Inv);
		ReadTheQuantity(Inv);
		Inv.ItemCounter++;
		if (Inv.ItemCounter >= 100)
			break;
		do
		{
			cout << "More?\n";
			cout << "Y/N\n";
			cout << "Enter: ";
			cin >> Continue;
			if (Continue != 'y' && Continue != 'n' && Continue != 'Y' && Continue != 'N')
			{
				cout << "\nWrong!, Please Enter Yes or No\n\n";
			}
		
		} while (Continue != 'y' && Continue != 'n' && Continue != 'Y' && Continue != 'N');

		system("cls");
	} while (Continue == 'y' || Continue == 'Y');
}

float TotalValue(const stInventory& Inv)
{
	float Total = 0;
	for (short i = 0; i < Inv.ItemCounter; i++)
	{
		Total += Inv.Itemes[i].Price * Inv.Itemes[i].quantity;
	}

	return Total;
}

void SaleProduct(stInventory& Inv, short counter, short Quantity)
{
	Inv.Itemes[counter].quantity -= Quantity;
}

void ChooseProducts(stInventory &Inv)
{
	string ProductName = "";
	short Quantity = 0;
	char A = 'Y';
	cout << "\n\n";
	do
	{
		cout << "Sale (Product Name): ";
		cin >> ProductName;
		cout << "\nQuantity: ";
		cin >> Quantity;
		short check = 0;
		for (short i = 0; i < Inv.ItemCounter; i++)
		{
			if (ProductName == Inv.Itemes[i].name)
				if (Quantity <= Inv.Itemes[i].quantity)
				{
					check++;
					SaleProduct(Inv, i, Quantity);
					break;
				}
		}

		if (check == 0)
		{
			cout << "\nThere is No Product in This Name\n";
			cout << "Or Not Enough Quantity\n\n";
		}

		do
		{
			cout << "\n\nAnother?\n";
			cout << "Y/N\n";
			cout << "Enter: ";
			cin >> A;
			cout << "------------------\n";
			if (A != 'Y' && A != 'N' && A != 'y' && A != 'n')
				cout << "\nWrong,Please Enter Yes or No.\n\n";

		} while (A != 'Y' && A != 'N' && A != 'y' && A != 'n');

		cout << "\n";

	} while (A == 'Y' || A == 'y');

	Inv.CurrentVal = TotalValue(Inv);
}

string CheapestProduct(const stInventory& Inv)
{
	float Price = Inv.Itemes[0].Price;
	string CheapestItem = Inv.Itemes[0].name;
	for (short i = 1; i < Inv.ItemCounter; i++)
	{
		if (Inv.Itemes[i].Price < Price)
		{
			Price = Inv.Itemes[i].Price;
			CheapestItem = Inv.Itemes[i].name;
		}
	}

	return CheapestItem;
}

string MostExpensiveProduct(stInventory& inventory)
{
	string MostExp = inventory.Itemes[0].name;
	float Price = inventory.Itemes[0].Price;

	for (short i = 0; i < inventory.ItemCounter; i++)
	{
		if (inventory.Itemes[i].Price > Price)
		{
			MostExp = inventory.Itemes[i].name;
			Price = inventory.Itemes[i].Price;
		}
	}
	return MostExp;
}

void PrintInventory(stInventory& Inv)
{
	cout << "\n\t\t\t\t\t\t\tInventory\n";
	cout << "\t\t\t\t" << string(54, (char)196) << endl;

	cout << "\t\t\t\t  " << left << setw(15) << "Product"
		<< " | " << setw(15) << "Price"
		<< " | " << setw(15) << "Quantity" << endl;

	cout << "\t\t\t\t" << string(54, (char)196) << endl;

	for (short i = 0; i < Inv.ItemCounter; i++)
	{
		cout << "\t\t\t\t  " << left << setw(15) << Inv.Itemes[i].name
			<< " | " << setw(15) << Inv.Itemes[i].Price
			<< " | " << setw(15) << Inv.Itemes[i].quantity << endl;
	}

	cout << "\t\t\t\t" << string(54, (char)196) << endl;

	Inv.TotalVal = TotalValue(Inv);

	cout << "\t\t\t\t\t Total Value in Inventory = " << Inv.TotalVal << " " << Inv.Currency << endl;
}

int main()
{
	stInventory inventory;

	ReadCurrency(inventory);
	ReadItems(inventory);
	system("cls");
	PrintInventory(inventory);
	ChooseProducts(inventory);

	cout << "\n\nTotal Items: " << inventory.ItemCounter << endl;
	cout << "Total Sales For Today: " << inventory.TotalVal - inventory.CurrentVal << " " << inventory.Currency << endl;
	cout << "Total Remaining Inventory Value: " << inventory.CurrentVal << " " << inventory.Currency << endl;
	cout << "Cheapest Product: " << CheapestProduct(inventory) << endl;
	cout << "Most Expensive Product: " << MostExpensiveProduct(inventory) << endl;

	PrintInventory(inventory);
	cout << endl;

	return 0;
}