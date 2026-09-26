#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

struct stProduct
{
	string name = "";
	double Price = 0; 
	short quantity = 0;
};

struct stInventory
{
	vector <stProduct> Itemes;
	string Currency = "";
	int TotalVal = 0, CurrentVal = 0;
};


short ReadTheQuantity()
{
	short Quantity = 0;
	do
	{
		cout << "\nQuantity? ";
		cin >> Quantity;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "\nInvalid Input! , Please enter a valid number:\n";
			cout << "Enter: ";
			cin >> Quantity;
		}

		if (Quantity < 0)
		{
			cout << "\nPlease Enter a Vailed Quantity!\n";
			cout << "--------------------------------\n";
		}
	} while (Quantity < 0);

	cout << "\n" << string(25, (char)196) << endl;

	return Quantity;
}

int ReadThePrice()
{
	int Price = 0;
	do
	{
		cout << "Price? ";
		cin >> Price;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "\nInvalid Input! , Please enter a valid number:\n";
			cout << "Enter: ";
			cin >> Price;
		}

		if (Price < 0)
		{
			cout << "\nPlease Enter a Vailed Price!\n";
			cout << "-----------------------------\n";
		}
	} while (Price < 0);
	cout << "\n" << string(25, (char)196) << endl;

	return Price;
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
	stProduct Temp;

	do
	{
		cout << "Please,Enter the Items?\n";
		cout << string(25, (char)196) << endl;

		bool IsThereNum;
		do
		{
			cin >> Temp.name;
			IsThereNum = ContainsNumbers(Temp.name);
			if (IsThereNum)
			{
				cout << "\nWrong Input!, Please Enter a Valid Input :-)\n\n";
				cout << "------------------------------------------------\n";
			}
		} while (IsThereNum);

		cout<<"\n" << string(25, (char)196) << "\n";
		cout << endl;
		Temp.Price = ReadThePrice();
		Temp.quantity = ReadTheQuantity();

		Inv.Itemes.push_back(Temp);

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
	
	for (const stProduct& Product : Inv.Itemes)
	{
		Total += Product.Price * Product.quantity;
	}

	return Total;
}

void SaleProduct(stProduct& Product, short& Quantity)
{
	Product.quantity -= Quantity;
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

		for (stProduct& Product : Inv.Itemes)
		{
			if (ProductName == Product.name)
			{
				if (Quantity <= Product.quantity)
				{
					check++;
					SaleProduct(Product, Quantity);
					break;
				}
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
	if (Inv.Itemes.empty())
	{
		return "No products available";
	}

	float Price = Inv.Itemes.at(0).Price;
	string CheapestItem = Inv.Itemes.at(0).name;

	for (const stProduct& Product : Inv.Itemes)
	{
		if (Product.Price < Price)
		{
			Price = Product.Price;
			CheapestItem = Product.name;
		}
	}

	return CheapestItem;
}

string MostExpensiveProduct(stInventory& inventory)
{
	if (inventory.Itemes.empty())
	{
		return "No products available";
	}

	string MostExp = inventory.Itemes.at(0).name;
	float Price = inventory.Itemes.at(0).Price;

	for (const stProduct& Product : inventory.Itemes)
	{
		if (Product.Price > Price)
		{
			Price = Product.Price;
			MostExp = Product.name;
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

	for (const stProduct& Product : Inv.Itemes)
	{
		cout << "\t\t\t\t  " << left << setw(15) << Product.name
			<< " | " << setw(15) << Product.Price
			<< " | " << setw(15) << Product.quantity << endl;
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

	cout << "\n\nTotal Items: " << inventory.Itemes.size() << endl;
	cout << "Total Sales For Today: " << inventory.TotalVal - inventory.CurrentVal << " " << inventory.Currency << endl;
	cout << "Total Remaining Inventory Value: " << inventory.CurrentVal << " " << inventory.Currency << endl;
	cout << "Cheapest Product: " << CheapestProduct(inventory) << endl;
	cout << "Most Expensive Product: " << MostExpensiveProduct(inventory) << endl;

	PrintInventory(inventory);
	cout << endl;

	return 0;
}