#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

enum enQuestionLevel { Easy = 1, Mid = 2, Hard = 3, Mix1 = 4 };
enum enOperationType { Add = 1, Sub = 2, Multi = 3, Div = 4, Mix2 = 5 };

struct stQuestionInfo
{
	short FirstNum = 0, SecondNum = 0;
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	short PlayerAns = 0, CorrectAns = 0;
	bool AnswerResult = true;
	string OpertaionSympol = "";
};

struct stQuezzInfo
{
	stQuestionInfo QuestionsList[100];
	short NumberOfQuestions = 0;
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	short RightAns = 0, WrongAns = 0;
	bool IsPass = true;
};

short ReadNumberOfQuestions(string Message)
{
	short num;
	do
	{
		cout << setw(75) << Message << "\n";
		cout << setw(54) << "Enter: ";
		cin >> num;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "\n"<< setw(85) <<"Invalid Input! , Please enter a valid number: \n";
			cout << setw(54) << "Enter: ";
			cin >> num;
		}

		if (num <= 0)
			cout << "\n" << setw(82) <<"Wrong,Please ENter a Positive Number.\n\n";
	} while (num <= 0);

	system("cls");

	return num;
}

short RandomNumber(short from, short to)
{
	short RandNum = rand() % (to - from + 1) + from;
	return RandNum;
}

enOperationType ReadOperationType()
{
	short x;
	do
	{
		cout << "\n" << setw(75) <<"Enter Type of Operation?\n";
		cout << setw(58) << "[1] Add\n";
		cout << setw(58) << "[2] Sub\n";
		cout << setw(60) << "[3] Multi\n";
		cout << setw(58) << "[4] Div\n";
		cout << setw(58) << "[5] Mix\n";
		cout << setw(57) << "Enter: ";
		cin >> x;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "\n" << setw(85) <<"Invalid Input! , Please enter a valid number: \n";
			cout << setw(57) << "Enter: ";
			cin >> x;
		}

		if (x < 1 || x>5)
			cout << "\n" << setw(82) <<"Wrong,Please Enter a Correct Operation.\n\n";

	} while (x < 1 || x>5);

	cout << setw(86) << string(53, (char)196) << endl;

	return enOperationType(x);
}

enQuestionLevel ReadQuestionLevel()
{
	short x;
	do
	{
		cout << setw(75) << "Enter Level of Question?\n";
		cout << setw(59) << "[1] Easy\n";
		cout << setw(58) << "[2] Mid\n";
		cout << setw(59) << "[3] Hard\n";
		cout << setw(58) << "[4] Mix\n";
		cout << setw(57) << "Enter: ";
		cin >> x;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "\n" << setw(85) <<"Invalid Input! , Please enter a valid number: \n";
			cout << setw(57) << "Enter: ";
			cin >> x;
		}

		if (x < 1 || x>4)
			cout << "\n" << setw(82) <<"Wrong,Please Enter a Correct Level.\n\n";

	} while (x < 1 || x>4);

	cout << string(53, (char)196) << endl;

	system("cls");

	return enQuestionLevel(x);
}

string GetOperationSympol(enOperationType OperType)
{
	string OpType[4] = { "+","-","*","/" };
	switch (OperType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Multi:
		return "*";
	case enOperationType::Div:
		return "/";
	case enOperationType::Mix2:
		return OpType[RandomNumber(0, 3)];
	default:
		return "";
	}
}

short TheRightAnswer(short Num1, short Num2, enOperationType OpType, string OpertaionSympol)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Num1 + Num2;
	case enOperationType::Sub:
		return Num1 - Num2;
	case enOperationType::Multi:
		return Num1 * Num2;
	case enOperationType::Div:
		if (Num1 >= Num2)
			return Num1 / Num2;
		else
			return 0;
	case enOperationType::Mix2:
		if (OpertaionSympol == "+")
		{
			return Num1 + Num2;
		}
		else if (OpertaionSympol == "-")
		{
			return Num1 - Num2;
		}
		else if (OpertaionSympol == "*")
		{
			return Num1 * Num2;
		}
		else
		{
			if (Num1 > Num2)
				return Num1 / Num2;
			else
				return 0;
		}
	}
}

stQuestionInfo GenerateQuestion(stQuezzInfo& QuezzInfo)
{
	stQuestionInfo QuestionInfo;

	QuestionInfo.OperationType = QuezzInfo.OperationType;
	QuestionInfo.QuestionLevel = QuezzInfo.QuestionLevel;

	if (QuestionInfo.QuestionLevel == enQuestionLevel::Mix1)
	{
		QuestionInfo.QuestionLevel = enQuestionLevel(RandomNumber(1, 3));
	}

	switch (QuestionInfo.QuestionLevel)
	{
	case enQuestionLevel::Easy:
		QuestionInfo.FirstNum = RandomNumber(1, 10);
		QuestionInfo.SecondNum = RandomNumber(1, 10);
		break;
	case enQuestionLevel::Mid:
		QuestionInfo.FirstNum = RandomNumber(10, 50);
		QuestionInfo.SecondNum = RandomNumber(10, 50);
		break;
	case enQuestionLevel::Hard:
		QuestionInfo.FirstNum = RandomNumber(50, 100);
		QuestionInfo.SecondNum = RandomNumber(50, 100);
		break;
	}

	QuestionInfo.OpertaionSympol = GetOperationSympol(QuestionInfo.OperationType);
	QuestionInfo.CorrectAns = TheRightAnswer(QuestionInfo.FirstNum, QuestionInfo.SecondNum, QuestionInfo.OperationType, QuestionInfo.OpertaionSympol);

	return QuestionInfo;
}

void GenerateQuestions(stQuezzInfo& QuezzInfo)
{
	for (short i = 0; i < QuezzInfo.NumberOfQuestions; i++)
	{
		QuezzInfo.QuestionsList[i] = GenerateQuestion(QuezzInfo);
	}
}

void PrintQuestion(stQuezzInfo QuezzInfo, short QuestionNumber)
{
	cout << "\n" << setw(57) << "Question [" << QuestionNumber + 1 << "/" << QuezzInfo.NumberOfQuestions << "]\n";
	cout << "\n" << setw(55) << QuezzInfo.QuestionsList[QuestionNumber].FirstNum << "\n";
	cout << setw(55) << QuezzInfo.QuestionsList[QuestionNumber].SecondNum;
	cout << setw(4) << QuezzInfo.QuestionsList[QuestionNumber].OpertaionSympol << "\n";
	cout << setw(58) << string(8, (char)196) << endl;
}

string ReadPlayerAnswer()
{
	string AnsInput;
	cout << setw(53) << "";
	cin >> AnsInput;
	return AnsInput;
}

void CorrectTheAnswer(stQuezzInfo& QuezzInfo, short QuestionNumber)
{
	if (QuezzInfo.QuestionsList[QuestionNumber].PlayerAns == QuezzInfo.QuestionsList[QuestionNumber].CorrectAns)
	{
		QuezzInfo.QuestionsList[QuestionNumber].AnswerResult = true;
		QuezzInfo.RightAns++;

		cout << "\n" << setw(63) <<"Right Answer :-)\n";
		if (QuestionNumber != QuezzInfo.NumberOfQuestions - 1)
			system("color 2F");
	}
	else
	{
		QuezzInfo.QuestionsList[QuestionNumber].AnswerResult = false;
		QuezzInfo.WrongAns++;

		cout << "\n" << setw(63) <<"Wrong Answer :-(\n";
		cout << setw(63) << "The Righ Answer is: " << QuezzInfo.QuestionsList[QuestionNumber].CorrectAns << "\n";
		if (QuestionNumber != QuezzInfo.NumberOfQuestions - 1)
			system("color 4F");
		cout << "\a";
	}
}

void ASkAndCorrectTheAnswer(stQuezzInfo& QuezzInfo)
{
	for (short i = 0; i < QuezzInfo.NumberOfQuestions; i++)
	{
		PrintQuestion(QuezzInfo, i);

		string PlayerAnswer = ReadPlayerAnswer();

		if (PlayerAnswer == "end" || PlayerAnswer == "End" || PlayerAnswer == "END")
		{
			cout << "\nGame Ended By User.\n";
			break;
		}

		QuezzInfo.QuestionsList[i].PlayerAns = stoi(PlayerAnswer);
		CorrectTheAnswer(QuezzInfo, i);
	}

	if (QuezzInfo.NumberOfQuestions > 0)
	{
		QuezzInfo.IsPass = (QuezzInfo.RightAns >= QuezzInfo.WrongAns);
	}
	else
	{
		QuezzInfo.IsPass = false;
	}
}

void GetPassedOrFailedScreen(bool IsPass)
{
	if (IsPass)
	{
		cout << "\n" << setw(83) << string(53, (char)196) << "\n";
		cout << setw(65) << "You Passed :-)\n";
		system("color 2F");
		cout << setw(83) << string(53, (char)196) << "\n" << endl;
	}
	else
	{
		cout << "\n" << setw(83) << string(53, (char)196) << "\n";
		cout << setw(65) << "You Failed :-(\n";
		system("color 4F");
		cout << setw(83) << string(53, (char)196) << "\n" << endl;
	}
}

string GetTheTypeOfOperation(enOperationType Type)
{
	switch (Type)
	{
	case enOperationType::Add:
		return "Add";
	case enOperationType::Sub:
		return "Sub";
	case enOperationType::Multi:
		return "Multi";
	case enOperationType::Div:
		return "Div";
	case enOperationType::Mix2:
		return "Mix";
	}

	return "";
}

string GetTheLevelOfQuestion(enQuestionLevel Level)
{
	switch (Level)
	{
	case enQuestionLevel::Easy:
		return "Easy";
	case enQuestionLevel::Mid:
		return "Mid";
	case enQuestionLevel::Hard:
		return "Hard";
	case enQuestionLevel::Mix1:
		return "Mix";
	}

	return "";
}

void PrintFinallResult(stQuezzInfo QuezzInfo)
{
	if (QuezzInfo.RightAns + QuezzInfo.WrongAns != QuezzInfo.NumberOfQuestions)
	{
		cout << "\n";
	}
	else
	{
		GetPassedOrFailedScreen(QuezzInfo.IsPass);

	}
	cout<< "\n" << setw(50) << string(20, (char)196) << "Final Results" << string(20, (char)196) << "\n";
	cout<< "\n" << setw(61) <<"Number of Questions       : " << QuezzInfo.NumberOfQuestions << "\n";
	cout << setw(61) << "Operation Type            : " << GetTheTypeOfOperation(QuezzInfo.OperationType) << endl;
	cout << setw(61) << "Questions Level           : " << GetTheLevelOfQuestion(QuezzInfo.QuestionLevel) << "\n";
	cout << setw(61) << "Number of Right Answers   : " << QuezzInfo.RightAns << "\n";
	cout << setw(61) << "Number of Wrong Answers   : " << QuezzInfo.WrongAns << "\n";
	cout << setw(82) << string(53, (char)196) << endl;
}

void PlayMathGame()
{
	stQuezzInfo QuezzInfo;
	QuezzInfo.NumberOfQuestions = ReadNumberOfQuestions("How Many Questions You Want?");
	QuezzInfo.OperationType = ReadOperationType();
	QuezzInfo.QuestionLevel = ReadQuestionLevel();

	GenerateQuestions(QuezzInfo);
	ASkAndCorrectTheAnswer(QuezzInfo);
	PrintFinallResult(QuezzInfo);
}

void ResetScreen()
{
	system("cls");
	system("color 07");
}

void PrintQuezzIsOverScreen()
{
	cout << "\n\n\n\n\t\t\t\t\t\t  +++QUEZZ IS OVER+++\n\n" << endl;
}

void StartGame()
{
	char Play = 'Y';

	do
	{
		ResetScreen();
		PlayMathGame();

		do
		{
			cout << setw(60) << "do you Want to Play Again?\n";
			cout << setw(37) << "Y/N\n";
			cout << setw(40) << "Enter: ";
			cin >> Play;
			if (Play != 'Y' && Play != 'N' && Play != 'y' && Play != 'n')
				cout << "\n" << setw(82) <<"Wrong,Please Enter Yes or No.\n\n";

		} while (Play != 'Y' && Play != 'N' && Play != 'y' && Play != 'n');

	} while (Play == 'Y' || Play == 'y');

	system("color 07");
	system("cls");
	PrintQuezzIsOverScreen();
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}