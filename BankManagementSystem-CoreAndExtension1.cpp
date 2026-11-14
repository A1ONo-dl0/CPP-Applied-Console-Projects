#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;
const string FileName = "Client List.txt";

enum enMinueOptions {
	enShowClientList = 1, enAddNewClient = 2, enDeleteSpicificClient = 3,
	enUpdateSpicificClient = 4, enFindSpicificClient = 5, eTransactions = 6, Exit = 7
};

enum enTransactions { eDeposit = 1, eWithdraw = 2, eTotalBalance = 3, MainMenue = 4 };

struct stClientInfo
{
	string AccountNum = "", PinCode = "", Name = "", Phone = "";
	double AccountBalance = 0;
	bool MarkForDelete = false;
	bool MarkForUpdate = false;
};

vector <string> SplitString(string Line, string Seperator)
{
	short pos = 0;
	string sWord = "";
	vector <string> vLine;

	while ((pos = Line.find(Seperator)) != std::string::npos)
	{
		sWord = Line.substr(0, pos);

		if (sWord != "")
		{
			vLine.push_back(sWord);
		}

		Line.erase(0, pos + Seperator.length());
	}

	if (Line != "")
	{
		vLine.push_back(Line);
	}

	return vLine;
}

stClientInfo ConvertDataLineToRecord(const string& Line)
{
	stClientInfo stClient;
	vector <string> vClientLine;
	vClientLine = SplitString(Line, "#//#");

	stClient.AccountNum = vClientLine[0];
	stClient.PinCode = vClientLine[1];
	stClient.Name = vClientLine[2];
	stClient.Phone = vClientLine[3];
	stClient.AccountBalance = stod(vClientLine[4]);

	return stClient;
}

string ConvertClientRecordToLine(stClientInfo stCLient, string Seperator = "#//#")
{
	string DataLine = "";
	DataLine += stCLient.AccountNum + Seperator;
	DataLine += stCLient.PinCode + Seperator;
	DataLine += stCLient.Name + Seperator;
	DataLine += stCLient.Phone + Seperator;
	DataLine += to_string(stCLient.AccountBalance) + Seperator;

	return DataLine;
}

vector <stClientInfo> LoadDataFromFileToVector()
{
	fstream MyFile;
	vector <stClientInfo> vClient;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line = "";
		while (getline(MyFile, Line))
		{
			vClient.push_back(ConvertDataLineToRecord(Line));
		}

		MyFile.close();
	}

	return vClient;
}

void SaveDataFromVectorToFile(vector <stClientInfo>& vClient)
{
	fstream MyFile;
	string DataLine = "";
	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		for (stClientInfo& stClient : vClient)
		{
			if (stClient.MarkForDelete == false)
			{
				DataLine = ConvertClientRecordToLine(stClient);
				MyFile << DataLine << endl;
			}
		}

		MyFile.close();
	}
}

void PrintClientDetails(const stClientInfo& stCLient)
{
	cout << "\nClient (" << stCLient.Name << ") Info...\n\n";
	cout << "Account Number     :" << stCLient.AccountNum << "\n";
	cout << "Pin Code           :" << stCLient.PinCode << "\n";
	cout << "Name               :" << stCLient.Name << "\n";
	cout << "Phone              :" << stCLient.Phone << "\n";
	cout << "Account Balance    :" << stCLient.AccountBalance << endl;
}

bool IsClientAccountNumberRepeated(const string& An, const vector <stClientInfo>& vClient)
{
	for (const stClientInfo& stClient : vClient)
	{
		if (An == stClient.AccountNum)
		{
			return true;
		}
	}
	return false;
}

stClientInfo ReadClientDataFromUser(const vector <stClientInfo>& vClient)
{
	stClientInfo stCLient;
	cout << "Enter :\n";

	cout << "Account Number :";
	getline(cin >> ws, stCLient.AccountNum);

	while (IsClientAccountNumberRepeated(stCLient.AccountNum, vClient))
	{
		cout << "\nClient With Account Numbner [" << stCLient.AccountNum << "] Already Exist!\n";
		cout << "Enter Another One : ";
		getline(cin >> ws, stCLient.AccountNum);
	}

	cout << "\nPin Code :";
	getline(cin, stCLient.PinCode);

	cout << "Name :";
	getline(cin, stCLient.Name);

	cout << "Phone :";
	getline(cin, stCLient.Phone);

	cout << "Account Balance :";
	cin >> stCLient.AccountBalance;

	return stCLient;
}

void ChangeClientDataFromUserToUpdate(stClientInfo& stCLient)
{
	cout << "Enter :\n";

	cout << "Pin Code :";
	getline(cin >> ws, stCLient.PinCode);

	cout << "Name :";
	getline(cin, stCLient.Name);

	cout << "Phone :";
	getline(cin, stCLient.Phone);

	cout << "Account Balance :";
	cin >> stCLient.AccountBalance;
}

string ReadAccountNumber()
{
	string An = "";
	cout << "Enter Account Number?\n";
	cout << "- ";
	cin >> An;

	return An;
}

char ReadYesOrNo(const string& Message)
{
	char a;

	cout << "\n" << Message << "\n";
	cout << "Y/N : ";
	cin >> a;
	do
	{
		if (a != 'Y' && a != 'N' && a != 'y' && a != 'n')
		{
			cout << "\nWrong Input!, Please Enter The Right One...\n";
			cout << "Y/N : ";
			cin >> a;
		}

	} while (a != 'Y' && a != 'N' && a != 'y' && a != 'n');

	return a;
}

void MarkForDeletion(vector <stClientInfo>& vClient, string& AccountNum)
{
	for (stClientInfo& stClient : vClient)
	{
		if (AccountNum == stClient.AccountNum)
		{
			stClient.MarkForDelete = true;
			break;
		}
	}
}

bool IsAccountNumberExist(string AccountNum, vector <stClientInfo>& vClient, stClientInfo& stCLient)
{
	for (stClientInfo& stCl : vClient)
	{
		if (AccountNum == stCl.AccountNum)
		{
			stCLient = stCl;
			return true;
		}
	}

	return false;
}

void AddNewClient(vector <stClientInfo>& vClient)
{
	stClientInfo stCLient;
	stCLient = ReadClientDataFromUser(vClient);

	vClient.push_back(stCLient);

	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		string DataLine = ConvertClientRecordToLine(stCLient);
		MyFile << DataLine << endl;

		MyFile.close();
	}
}

void AddNewCLients(vector <stClientInfo>& vClient)
{
	char ans = 'y';
	do
	{
		AddNewClient(vClient);
		cout << "\nClient Added Successfully." << endl;
		cout << "\ndo you want to add More Clients?\n";
		cout << "Y/N :";
		do
		{
			cin >> ans;
			if (ans != 'Y' && ans != 'N' && ans != 'y' && ans != 'n')
			{
				cout << "\nWrong Input!, Please Enter The Right One...\n";
				cout << "Y/N : ";
				cin >> ans;
			}

		} while (ans != 'Y' && ans != 'N' && ans != 'y' && ans != 'n');

		if (toupper(ans) == 'Y')
		{
			system("cls");
		}

	} while (toupper(ans) == 'Y');
}

void DeleteClient(vector <stClientInfo>& vClient, stClientInfo& stCLient)
{
	string AccountNum = ReadAccountNumber();
	char Ans = 'y';

	if (IsAccountNumberExist(AccountNum, vClient, stCLient))
	{
		PrintClientDetails(stCLient);
		Ans = ReadYesOrNo("\nAre you Sure You Want To Delete This Client?");

		if (Ans == 'y' || Ans == 'Y')
		{
			MarkForDeletion(vClient, AccountNum);
			SaveDataFromVectorToFile(vClient);

			vClient = LoadDataFromFileToVector();

			cout << "\n\nClient (" << stCLient.Name << ") Deleted Successfully!" << endl;
		}
	}
	else
	{
		cout << "\n\nClient With Account Number " << stCLient.AccountNum << " Not Found !" << endl;
	}

}

void UpdateClientData(vector <stClientInfo>& vClient, stClientInfo& stCLient)
{
	string AccountNum = ReadAccountNumber();
	char ans;

	if (IsAccountNumberExist(AccountNum, vClient, stCLient))
	{
		PrintClientDetails(stCLient);
		ans = ReadYesOrNo("\nAre you Sure You Want To Update This Client?");

		if (ans == 'Y' || ans == 'y')
		{
			system("cls");
			for (stClientInfo& stCl : vClient)
			{
				if (AccountNum == stCl.AccountNum)
				{
					stCLient = stCl;
					ChangeClientDataFromUserToUpdate(stCl);
					break;
				}
			}
			SaveDataFromVectorToFile(vClient);

			vClient = LoadDataFromFileToVector();
			cout << "\n\nUpdate Client For (" << stCLient.Name << ") Was Successful!" << endl;
		}
	}
	else
	{
		cout << "\n\nClient With Account Number " << stCLient.AccountNum << " Not Found !" << endl;
	}
}

void FindClient(vector <stClientInfo>& vClient, stClientInfo& stCLient)
{
	string AccountNum = ReadAccountNumber();

	if (IsAccountNumberExist(AccountNum, vClient, stCLient))
	{
		PrintClientDetails(stCLient);

		cout << "\n\nCLient (" << stCLient.Name << ") Founded Successfully!" << endl;
	}
	else
	{
		cout << "\n\nClient With Account Number " << AccountNum << " Not Found !" << endl;
	}
}

void PrintTableHeader(vector <stClientInfo> vClient)
{
	cout <<"\t\t\t\t\t\t Client List (" << vClient.size() << ") Client(s).\n" << endl;
	cout << string(120, char(196)) << endl;

	cout << "| " << setw(16) << left << "Account Number"
		<< "| " << setw(12) << left << "Pin Code"
		<< "| " << setw(35) << left << "Client Name"
		<< "| " << setw(15) << left << "Phone"
		<< "| " << setw(10) << left << "Balance" << " |" << endl;

	cout << string(120, char(196)) << endl;
}

void PrintCurrentLine(stClientInfo stClient)
{
	cout << "| " << setw(16) << left << stClient.AccountNum
		<< "| " << setw(12) << left << stClient.PinCode
		<< "| " << setw(35) << left << stClient.Name
		<< "| " << setw(15) << left << stClient.Phone
		<< "| " << setw(10) << left << stClient.AccountBalance << " |" << endl;
}

void ShowClientList(vector <stClientInfo> vClient)
{
	PrintTableHeader(vClient);

	for (stClientInfo stClient : vClient)
	{
		PrintCurrentLine(stClient);
	}

	cout << "\n" << string(120, char(196)) << endl;
}

void PrintMainMinueScreen()
{
	system("cls");
	cout << "==========================================\n";
	cout << "            Main Minue Screen\n";
	cout << "==========================================\n";

}

enMinueOptions UserChooseFromMinue()
{
	short a = 0;

	cout << "       [1] Show Client List\n";
	cout << "       [2] Add New Client\n";
	cout << "       [3] Delete Spicific Client\n";
	cout << "       [4] Update Spicific Client\n";
	cout << "       [5] Find Spicific Client\n";
	cout << "       [6] Transactions\n";
	cout << "       [7] Exit" << endl;
	cout << "==========================================\n";
	cout << "Choose an Operation From [1 to 7]? ";
	cin >> a;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "\nInvalid Input! , Please enter a valid One:\n\n";
		cout << "Choose an Operation From [1 to 7]? ";
		cin >> a;
	}

	return enMinueOptions(a);
}

void GoBackToMinMinue()
{
	cout << "\n\nPress Any Key To Go Back To The Main Minue...";
	system("pause>0");
	system("cls");
}

void ShowEndProgramScreen()
{
	system("cls");
	cout << "----------------------------------------\n";
	cout << "            Program Ended :-)\n";
	cout << "----------------------------------------\n";

}

void PrintDepositScreen()
{
	system("cls");
	cout << "-----------------------------------\n";
	cout << "              Deposit                \n";
	cout << "-----------------------------------\n";
}

void Deposit(string& An, double Balance ,vector <stClientInfo>& vClient, stClientInfo& stCLient)
{
	char ans = 'y';
	ans = ReadYesOrNo("Are You Sure You Want to Perform This Transaction?");

	if (ans == 'y' || ans == 'Y')
	{
		for (stClientInfo& stClt : vClient)
		{
			if (An == stClt.AccountNum)
			{
				stClt.AccountBalance += Balance;
				stCLient = stClt;
				break;
			}
		}
		cout << "\nDeposit an Amount Done Successful, New Balance is :" << stCLient.AccountBalance << endl;

		SaveDataFromVectorToFile(vClient);
		vClient = LoadDataFromFileToVector();
	}
}

void DepositAmountToClient(vector <stClientInfo>& vClient, stClientInfo& stCLient)
{
	PrintDepositScreen();

	string An = ReadAccountNumber();

	while (!IsAccountNumberExist(An, vClient, stCLient))
	{
		cout << "\nClient With Account Number [" << An << "] doesn't Exist!" << endl;
		An = ReadAccountNumber();
	}

	PrintClientDetails(stCLient);
	double AddBalance = 0;
	cout << "-----------------------------------\n";
	cout << "\nPlease, Enter Deposit Amount :";
	cin >> AddBalance;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "\nInvalid Input! , Please enter a valid One:\n\n";
		cout << "\nPlease, Enter Deposit Amount :";
		cin >> AddBalance;
	}

	Deposit(An, AddBalance, vClient, stCLient);
}

void PrintWithdrawScreen()
{
	system("cls");
	cout << "-----------------------------------\n";
	cout << "             Withdraw           \n";
	cout << "-----------------------------------\n";
}

void Withdraw(string& An,double Balance ,vector <stClientInfo>& vClient, stClientInfo& stCLient)
{
	char ans = 'y';

	do
	{
		if (Balance > stCLient.AccountBalance)
		{
			cout << "Amount Exceeds The Balance, You Only Can Withdraw Up to :" << stCLient.AccountBalance << "\n";
			cout << "Please, Enter Withdraw Amount :";
			cin >> Balance;

			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "\nInvalid Input! , Please enter a valid One:\n\n";
				cout << "\nPlease, Enter Withdraw Amount :";
				cin >>Balance;
			}
		}

	} while (Balance > stCLient.AccountBalance);

	ans = ReadYesOrNo("Are You Sure You Want to Perform This Transaction?");

	if (ans == 'y' || ans == 'Y')
	{
		for (stClientInfo& stClt : vClient)
		{
			if (An == stClt.AccountNum)
			{
				stClt.AccountBalance -= Balance;
				stCLient = stClt;
				break;
			}
		}
		cout << "\nWithdraw an Amount Done Successful, New Balance is :" << stCLient.AccountBalance << endl;
	}

	SaveDataFromVectorToFile(vClient);
	vClient = LoadDataFromFileToVector();
}

void WithdrawAmountFromClient(vector <stClientInfo>& vClient, stClientInfo& stCLient)
{
	PrintWithdrawScreen();

	string An = ReadAccountNumber();

	while (!IsAccountNumberExist(An, vClient, stCLient))
	{
		cout << "\nClient With Account Number [" << An << "] doesn't Exist!" << endl;
		An = ReadAccountNumber();
	}

	PrintClientDetails(stCLient);
	double GetBalance = 0;
	cout << "-----------------------------------\n";
	cout << "\nPlease, Enter Withdraw Amount :";
	cin >> GetBalance;

	while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "\nInvalid Input! , Please enter a valid One:\n\n";
			cout << "\nPlease, Enter Withdraw Amount :";
			cin >> GetBalance;
		}

		
	Withdraw(An, GetBalance, vClient, stCLient);
}

int GetTotalBalance(vector <stClientInfo>& vClient)
{
	int totalBal = 0;
	for (stClientInfo& stclt : vClient)
	{
		totalBal += stclt.AccountBalance;
	}

	return totalBal;
}

void PrintClientsTotalBalance(vector <stClientInfo>& vClient)
{
	system("cls");
	int totalBal = GetTotalBalance(vClient);

	ShowClientList(vClient);

	cout << "\t\t\t\t\t\t   Total Balance = " << totalBal << endl;
}

void PrintTransactionsMenueScreen()
{
	system("cls");
	cout << "======================================\n";
	cout << "   Transactions Minue Screern\n";
	cout << "======================================" << endl;
}

enTransactions UserInputTransactions()
{
	short a = 0; 
	cout << "       [1] Deposit\n";
	cout << "       [2] Withdraw\n";
	cout << "       [3] Total Balance\n";
	cout << "       [4] Main Menue\n";
	cout << "======================================" << endl;
	cout << "Choose an Operation From [1 to 4] ? ";
	cin >> a;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "\nInvalid Input! , Please enter a valid One:\n\n";
		cout << "Choose an Operation From [1 to 4]? ";
		cin >> a;
	}

	return enTransactions(a);
}

void GoBacktoTransactionsMenue()
{
	cout << "\n\nPress Any Key to Go Back to Transactions Menue...";
	system("pause>0");
	system("cls");
}

void TransactionsMenue(vector <stClientInfo>& vClient, stClientInfo& stCLient)
{
	enTransactions TransactionsMenue;

	do
	{
		system("cls");
		PrintTransactionsMenueScreen();
		TransactionsMenue = UserInputTransactions();
		
		system("cls");
		switch (TransactionsMenue)
		{
		case enTransactions::eDeposit:
			DepositAmountToClient(vClient,stCLient);
			GoBacktoTransactionsMenue();
			break;

		case enTransactions::eWithdraw:
			WithdrawAmountFromClient(vClient, stCLient);
			GoBacktoTransactionsMenue();
			break;

		case enTransactions::eTotalBalance:
			PrintClientsTotalBalance(vClient);
			GoBacktoTransactionsMenue();
			break;

		case enTransactions::MainMenue:
			break;
		}

	} while (TransactionsMenue!=enTransactions::MainMenue);


}

void MainMinue(vector <stClientInfo>& vClient)
{
	vClient = LoadDataFromFileToVector();
	stClientInfo stCLient;
	enMinueOptions MinueOptions;

	do
	{
		system("cls");
		PrintMainMinueScreen();
		MinueOptions = UserChooseFromMinue();

		system("cls");
		switch (MinueOptions)
		{
		case enMinueOptions::enShowClientList:

			ShowClientList(vClient);
			GoBackToMinMinue();
			break;

		case enMinueOptions::enAddNewClient:

			AddNewCLients(vClient);
			GoBackToMinMinue();
			break;

		case enMinueOptions::enDeleteSpicificClient:

			DeleteClient(vClient, stCLient);
			GoBackToMinMinue();
			break;

		case enMinueOptions::enUpdateSpicificClient:
			UpdateClientData(vClient, stCLient);
			GoBackToMinMinue();
			break;

		case enMinueOptions::enFindSpicificClient:
			FindClient(vClient, stCLient);
			GoBackToMinMinue();
			break;

		case enMinueOptions::eTransactions:
			TransactionsMenue(vClient, stCLient);
			break;

		case enMinueOptions::Exit:
			break;
		}

	} while (MinueOptions != enMinueOptions::Exit);

	ShowEndProgramScreen();
}


int main()
{
	vector <stClientInfo> vClient;

	MainMinue(vClient);

	system("pause>0");

	return 0;
}
