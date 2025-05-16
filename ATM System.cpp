#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

const string ClientsFileName = "Clients.txt";

void ShowATMMainMenue();
void LoginATM();
void ShowQuickWithdrawScreen();

struct  sClient
{
	string accountnumber;
	string pincode;
	string name;
	string phone;
	double AccountBalance;
	bool MarkForDelet = false;

};
sClient CurrentClient;



enum EnATMmainscreen
{
	QuickWithdraw = 1, eNormalWithdraw = 2, Deposit = 3, CheckBalance = 4, Logout = 5,

};


void GoBackToATMMainMenueScrren()
{
	cout << "\n\nPress enter of the return to main menue screen";
	system("pause>0");
	ShowATMMainMenue();
}





short ReadATMMainMenueOption()
{
	short number = 0;
	cout << "Please Enter The Number [1} to [5] ?";
	cin >> number;

	return number;
}

short ReadQuickWithdrawMenueScreen()
{
	short number = 0;
	cout << "Please Enter The Number [1} to [9] ?";
	cin >> number;

	return number;
}


//555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555

double totalbalance()
{
	double totalbalance = 0;
	totalbalance = CurrentClient.AccountBalance;
	return totalbalance;

}
void ShowAccountBalance()
{
	cout << "===========================================\n";
	cout << "\t\tBalance screen \n";
	cout << "===========================================\n";
	cout << "| " << setw(15) << left << "account balance : " << totalbalance();

}



string ConvertRecordToLine(sClient clinet, string suplitr = "#//#")
{
	string stClientRecord = "";

	stClientRecord = stClientRecord + clinet.accountnumber + suplitr;
	stClientRecord = stClientRecord + clinet.pincode + suplitr;
	stClientRecord = stClientRecord + clinet.name + suplitr;
	stClientRecord = stClientRecord + clinet.phone + suplitr;
	stClientRecord = stClientRecord + to_string(clinet.AccountBalance) + suplitr;

	return stClientRecord;

}
vector <sClient> SaveCleintsDataToFile(string accounetnumber, vector <sClient>& vclients)
{
	fstream Myfile;
	string dataline;
	Myfile.open(ClientsFileName, ios::out);

	if (Myfile.is_open())
	{
		for (sClient& c : vclients)
		{
			if (c.MarkForDelet == false)
			{
				dataline = ConvertRecordToLine(c);
				Myfile << dataline << endl;
			}


		}

		Myfile.close();
	}

	return vclients;

}
bool ReadDepositAccountBalanceToClient(string accounetnumber, vector <sClient> vclients, double depositamount)
{


	char anwser = 'n';
	cout << "\n\nAre you sure you want Deposit this client? y/n?";
	cin >> anwser;

	if (anwser == 'Y' || anwser == 'y')
	{

		for (sClient& c : vclients)
		{
			if (c.accountnumber == accounetnumber)
			{
				c.AccountBalance = c.AccountBalance + depositamount;
				SaveCleintsDataToFile(accounetnumber, vclients);
				cout << "\n\ndone Successfully. new balance is: " << c.AccountBalance << endl;
				return true;
			}

		}



	}
	return false;

}
vector <string> SplitString(string s1, string dilim)
{
	vector <string> vsplit;

	short pos = 0;
	string sword;

	while ((pos = s1.find(dilim)) != std::string::npos)
	{
		sword = s1.substr(0, pos);
		if (sword != "")
		{
			vsplit.push_back(sword);
		}

		s1.erase(0, pos + dilim.length());

	}

	if (s1 != "")
	{
		vsplit.push_back(s1);
	}

	return vsplit;

}
sClient ConvertLinetoRecord(string line, string Seperator = "#//#")
{
	vector <string> vstringline;
	sClient client;

	vstringline = SplitString(line, Seperator);

	client.accountnumber = vstringline[0];
	client.pincode = vstringline[1];
	client.name = vstringline[2];
	client.phone = vstringline[3];
	client.AccountBalance = stod(vstringline[4]);

	return client;


}
vector <sClient> LoadCleintsDataFromFile(string ClientsFileName)
{
	vector <sClient> vclients;
	fstream Myfile;

	Myfile.open(ClientsFileName, ios::in);
	if (Myfile.is_open())
	{
		string line;
		sClient client;
		while (getline(Myfile, line))
		{
			client = ConvertLinetoRecord(line);

			vclients.push_back(client);
		}


		Myfile.close();

	}



	return vclients;

}
double ReadDepositAmount()
{
	double Amount;
	cout << "enter positive amount multiple '5' ? ";
	cin >> Amount;

	while (Amount <= 0)
	{
		cout << "\nenter positive amount multiple '5' ? ";
		cin >> Amount;
	}

	return Amount;
}
void PerformDepositOption()
{
	double DepositAmount = ReadDepositAmount();
	vector <sClient> vclients = LoadCleintsDataFromFile(ClientsFileName);
	if (ReadDepositAccountBalanceToClient(CurrentClient.accountnumber, vclients, DepositAmount))
	{
		CurrentClient.AccountBalance = CurrentClient.AccountBalance + DepositAmount;

	}

}
void ShowDepositScreen()
{
	cout << "=================================================\n";
	cout << "\t\tDeposit screen \n";
	cout << "=================================================\n";

	PerformDepositOption();

}

int ReadWithDrawAmount()
{
	int Amount;
	cout << "enter withdraw amount multiple '5' ? ";
	cin >> Amount;

	while (Amount % 5 != 0)
	{
		cout << "\nenter withdraw amount multiple '5' ? ";
		cin >> Amount;
	}

	return Amount;
}

void PerformNormalWithdraw()
{
	int WithDrawBalance = ReadWithDrawAmount();

	if (WithDrawBalance > CurrentClient.AccountBalance)
	{
		cout << "\nThe amount exceeds your balance, make another choice.\n";
		cout << "Press Anykey to continue...";
		system("pause>0");
		ShowQuickWithdrawScreen();
		return;

	}

	vector <sClient> vclients = LoadCleintsDataFromFile(ClientsFileName);
	if (ReadDepositAccountBalanceToClient(CurrentClient.accountnumber, vclients, WithDrawBalance * -1))
	{
		CurrentClient.AccountBalance = CurrentClient.AccountBalance - WithDrawBalance;
	}
}
void ShowNormalWithdrawScreen()
{
	system("cls");
	cout << "===========================================\n";
	cout << "\t    Normal Withdraw Screen \n";
	cout << "===========================================\n";

	PerformNormalWithdraw();

}






short getQuickWithDrawAmount(short QuickWithdrawOption)
{

	switch (QuickWithdrawOption)
	{
	case 1:
		return 20;
	case 2:
		return 50;
	case 3:
		return 100;
	case 4:
		return 200;
	case 5:
		return 400;
	case 6:
		return 600;
	case 7:
		return 800;
	case 8:
		return 1000;
	default:
		return 0;
	}

}

void PerformQuickWithdraw(short QuickWithdrawOption)
{
	if (QuickWithdrawOption == 9)
	{
		return;
	}

	short WithDrawBalance = getQuickWithDrawAmount(QuickWithdrawOption);

	if (WithDrawBalance > CurrentClient.AccountBalance)
	{
		cout << "amount exceeds the balance , you can withdraw up to : " << CurrentClient.AccountBalance << endl;
		cout << "Press Anykey to continue...";
		system("pause>0");
		ShowQuickWithdrawScreen();
		return;
	}
	vector <sClient> vclients = LoadCleintsDataFromFile(ClientsFileName);
	if (ReadDepositAccountBalanceToClient(CurrentClient.accountnumber, vclients, WithDrawBalance * -1))
	{
		CurrentClient.AccountBalance = CurrentClient.AccountBalance - WithDrawBalance;
	}


}
void ShowQuickWithdrawScreen()
{
	system("cls");
	cout << "======================================\n";
	cout << "\tQuick Withdraw Screen \n";
	cout << "======================================\n";
	cout << "\t[1] 20 \t\t[2] 50\n";
	cout << "\t[3] 100\t\t[4] 200\n";
	cout << "\t[5] 400\t\t[6] 200\n";
	cout << "\t[7] 800\t\t[8] 1000\n";
	cout << "\t[9] Exit\n";
	cout << "======================================\n";
	cout << setw(15) << left << "Your account balance : " << totalbalance() << endl;

	PerformQuickWithdraw(ReadQuickWithdrawMenueScreen());

}



void PerfromATMMainMenueOption(EnATMmainscreen ATMMenueScreen)
{
	switch (ATMMenueScreen)
	{
	case EnATMmainscreen::QuickWithdraw:
	{
		system("cls");
		ShowQuickWithdrawScreen();
		GoBackToATMMainMenueScrren();
		break;
	}
	case EnATMmainscreen::eNormalWithdraw:
	{
		system("cls");
		ShowNormalWithdrawScreen();
		GoBackToATMMainMenueScrren();
		break;
	}
	case EnATMmainscreen::Deposit:
	{
		system("cls");
		ShowDepositScreen();
		GoBackToATMMainMenueScrren();
		break;
	}
	case EnATMmainscreen::CheckBalance:
	{
		system("cls");
		ShowAccountBalance();
		GoBackToATMMainMenueScrren();
		break;
	}
	case EnATMmainscreen::Logout:
	{
		system("cls");
		LoginATM();
		break;
	}
	}




}

void ShowATMMainMenue()
{
	system("cls");
	cout << "======================================\n";
	cout << "\tATM Maine Menue Screen \n";
	cout << "======================================\n";
	cout << "\t[1] Quick withdraw.\n";
	cout << "\t[2] Normal withdraw.\n";
	cout << "\t[3] Deposit\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "======================================\n";

	PerfromATMMainMenueOption((EnATMmainscreen)ReadATMMainMenueOption());
}




bool FindClientByAccountNumberAndPincode(string accounetnumber, string pincode, sClient& client)
{
	vector <sClient> vclients = LoadCleintsDataFromFile(ClientsFileName);

	for (sClient c : vclients)
	{
		if (c.accountnumber == accounetnumber && c.pincode == pincode)
		{
			client = c;
			return true;
		}

	}


	return false;
}
bool loadClientinfo(string accounetnumber, string pincode)
{
	if (FindClientByAccountNumberAndPincode(accounetnumber, pincode, CurrentClient))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void LoginATM()
{

	bool loginfail = false;
	string NumberAccount, PinCode;

	do
	{

		system("cls");
		cout << "======================================\n";
		cout << "\t      login ATM \n";
		cout << "======================================\n";

		if (loginfail)
		{
			cout << "invalid Username/Password!\n";
		}

		cout << "enter NumberAccount? ";
		cin >> NumberAccount;

		cout << "enter PinCode? ";
		cin >> PinCode;

		loginfail = !loadClientinfo(NumberAccount, PinCode);

	} while (loginfail);

	ShowATMMainMenue();
}

int main()
{

	LoginATM();


	system("pause>0");
	return 0;
}
