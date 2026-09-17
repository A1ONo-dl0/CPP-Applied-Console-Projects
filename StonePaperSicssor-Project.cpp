#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enWhatChoise { Stone = 1, Paper = 2, Sicssor = 3 };
enum enWhoWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short int Round;
	enWhatChoise PlayerChoise, ComputerChoise;
	enWhoWinner WhoWinner;
	string WinnerName;
};

struct stGameResultInfo
{
	short int Round = 0;
	short int PlayerWinTimes = 0;
	short int ComputerWinTimes = 0;
	short int DrawTimes = 0;
	string WinnerName = "";
};

short ReadPositiveNumber(string Message)
{
	short num;
	do
	{
		cout << Message << "\n";
		cout << "Enter: ";
		cin >> num;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "\nInvalid Input! , Please enter a valid number: ";
			cin >> num;
		}

		system("cls");

		if (num <= 0)
			cout << "\nWrong,Please Enter a Positive Number?\n\n";
	} while (num <= 0);

	return num;
}

short RandomNumber(short from, short to)
{
	short RandNum = rand() % (to - from + 1) + from;
	return RandNum;
}

enWhatChoise PlayerPlay()
{
	short x;
	do
	{
		cout << "\nEnter:\n";
		cout << "[1] Stone\n" << "[2] Paper\n" << "[3] Sicssor\n";
		cout << "Your Chooise = ";
		cin >> x;
		if (x < 1 || x > 3)
			cout << "\nWrong,Please Enter from 1 to 3\n\n";
	} while (x < 1 || x > 3);

	return enWhatChoise(x);
}

enWhoWinner WhoWinThisRound(stRoundInfo ThisRound)
{
	if (ThisRound.PlayerChoise == ThisRound.ComputerChoise)
		return enWhoWinner::Draw;

	switch (ThisRound.PlayerChoise)
	{
	case enWhatChoise::Stone:
		if (ThisRound.ComputerChoise == enWhatChoise::Paper)
		{
			return enWhoWinner::Computer;
		}
		break;
	case enWhatChoise::Paper:
		if (ThisRound.ComputerChoise == enWhatChoise::Sicssor)
		{
			return enWhoWinner::Computer;
		}
		break;
	case enWhatChoise::Sicssor:
		if (ThisRound.ComputerChoise == enWhatChoise::Stone)
		{
			return enWhoWinner::Computer;
		}
		break;
	}

	return enWhoWinner::Player;
}

string GetWinnerName(enWhoWinner WinnerName)
{
	if (WinnerName == enWhoWinner::Computer)
		return "Computer";
	else if (WinnerName == enWhoWinner::Player)
		return "Player";
	else
		return "Draw";
}

string WinnerName(short PlayerWin, short ComputerWin, short Draw)
{
	if (PlayerWin < ComputerWin)
		return "Computer";
	else if (PlayerWin > ComputerWin)
		return "Player";
	else
		return"Draw";
}

string PlayerComputerChoise(enWhatChoise Choise)
{
	switch (Choise)
	{
	case enWhatChoise::Paper:
		return "Paper";
	case enWhatChoise::Stone:
		return "Stone";
	case enWhatChoise::Sicssor:
		return "Sicssor";
	}

	return "";
}

void ShowRoundResult(stRoundInfo RoundInfo)
{
	cout << "\nRound (" << RoundInfo.Round << ")\n";
	cout << "Player: " << PlayerComputerChoise(RoundInfo.PlayerChoise);
	cout << " | Computer: " << PlayerComputerChoise(RoundInfo.ComputerChoise);
	cout << "\nWinner is: {" << RoundInfo.WinnerName << "}" << endl;
}

stGameResultInfo FillGameResult(short Rounds, short PlayerWin, short ComputerWin, short Draw, string WinnerName)
{
	stGameResultInfo GameFinalResult;
	GameFinalResult.Round = Rounds;
	GameFinalResult.PlayerWinTimes = PlayerWin;
	GameFinalResult.ComputerWinTimes = ComputerWin;
	GameFinalResult.DrawTimes = Draw;
	GameFinalResult.WinnerName = WinnerName;

	return GameFinalResult;
}

stGameResultInfo PlayGame(short Rounds)
{
	stRoundInfo RoundInfo;
	short PlayerWin = 0, Computerwin = 0, Draw = 0;
	for (short i = 1; i <= Rounds; i++)
	{
		RoundInfo.Round = i;
		RoundInfo.PlayerChoise = PlayerPlay();
		RoundInfo.ComputerChoise = enWhatChoise(RandomNumber(1, 3));
		RoundInfo.WhoWinner = WhoWinThisRound(RoundInfo);
		RoundInfo.WinnerName = GetWinnerName(RoundInfo.WhoWinner);

		switch (RoundInfo.WhoWinner)
		{
		case enWhoWinner::Computer:
			Computerwin++;
			system("color 4F");
			cout << "\a";
			break;
		case enWhoWinner::Player:
			PlayerWin++;
			system("color 2F");
			break;
		case enWhoWinner::Draw:
			Draw++;
			system("color 6F");
			break;
		}

		ShowRoundResult(RoundInfo);
	}

	return FillGameResult(Rounds, PlayerWin, Computerwin, Draw, WinnerName(PlayerWin, Computerwin, Draw));
}

void ShowGameFinalResult(stGameResultInfo FinalResult)
{
	cout << "\n\n\t\t\t\t____________________{Game Result}_____________________\n";
	cout << "\n\t\t\t\tGame Rounds\t\t: " << FinalResult.Round << "\n";
	cout << "\t\t\t\tPlayer won times\t: " << FinalResult.PlayerWinTimes << "\n";
	cout << "\t\t\t\tComputer won times\t: " << FinalResult.ComputerWinTimes << "\n";
	cout << "\t\t\t\tDraw times\t\t: " << FinalResult.DrawTimes << "\n";
	cout << "\t\t\t\tThe Final Winner is\t: " << FinalResult.WinnerName << "\n";
	cout << "\t\t\t\t_______________________________________________________" << endl;
}

void ShowGameOverScreen()
{
	cout << "\n\n\t\t\t\t__________________________________________________________\n";
	cout << "        \n\t\t\t\t\t\t  +++G a m e  O v e r+++\n";
	cout << "\t\t\t\t__________________________________________________________\n";
}

void RessetScreen()
{
	system("cls");
	system("color 07");
}

void ScreenColorResult(stGameResultInfo GameResult)
{
	if (GameResult.WinnerName == "Player")
	{
		system("color 2F");
	}
	else if (GameResult.WinnerName == "Computer")
	{
		system("color 4F");
		cout << "\a";
	}
	else
	{
		system("color 6F");
	}
}

void StartGame()
{
	char Continue = 'Y';
	do
	{
		RessetScreen();
		stGameResultInfo GameResult = PlayGame(ReadPositiveNumber("How Many Rounds?"));
		ScreenColorResult(GameResult);
		ShowGameFinalResult(GameResult);

		cout << "\t\t\t\tDo you Want Play Again?\n";
		cout << "\t\t\t\tY/N\n";
		cout << "\t\t\t\tEnter: ";
		cin >> Continue;

	} while (Continue == 'Y' || Continue == 'y');

	system("color 07");
	ShowGameOverScreen();
}

int main()
{
	srand((unsigned)time(NULL));


	StartGame();


	return 0;
}