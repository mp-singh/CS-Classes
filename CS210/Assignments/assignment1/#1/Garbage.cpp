bool found = false;

case 'a': case 'A'://accesss account
{
	cout << endl << "Please enter the name of the account you wish to accesss: ";
	cin >> name1;
	cout << "Please enter the password for this account: ";
	cin >> pass;
	cout << endl;

	int counter = 0;
	for(counter=0; counter<MAX; counter++)
	{	
		account[counter].getPassword(tempPass);

		if(pass == tempPass && name1 == account[counter].getName())
		{
			cout << "Accesss granted." << endl;
			cout << endl;
			found = true;

		}
	}

	if(found)
	{
		cout << "Please make a selection: ";
		choice2=check(2);
		while(found)
						// while(choice2 !='r' && choice2 !='R')
		{
			switch(choice2)
			{
			case 'd': case 'D'://Deposit money
			{
				account[i].deposit();
				printOptions();
				cout <<endl<< "Please make a selection: ";
				choice2=check(2);
			}
			break;

			case 'w': case 'W'://Withdraw money
			{
				account[i].withdraw();
				printOptions();
				cout <<endl <<  "Please make a selection: ";
				choice2=check(2);
			}
			break;

			case 'p': case 'P'://Print Balance
			{
				account[i].printBalance();
				printOptions();
				cout << endl << "Please make a selection: ";
				choice2=check(2);
			}
			break;
		}
	}
	else
	{
		cout << "Incorrect account name or password." << endl; 
		printMenu();
		cout << "Please make a selection: ";
		choice1=check(1);
	}

	// case 'a': case 'A'://accesss account
			// {
			// 	cout << endl << "Please enter the name of the account you wish to accesss: ";
			// 	cin >> name1;
			// 	cout << "Please enter the password for this account: ";
			// 	cin >> pass;
			// 	cout << endl;

			// 	for(int i=0; i<MAX; i++)
			// 	{	
			// 		account[i].getPassword(tempPass);

			// 		if(pass == tempPass && name1 == account[i].getName())
			// 		{
			// 			cout << "Accesss granted." << endl;
			// 			cout << endl;
			// 			cout << "Please enter one of the following options." << endl;
			// 			printOptions();
			// 			cout << endl;
			// 			cout << "Please make a selection: ";
			// 			choice2=check(2);
			// 			while(found)
			// 			// while(choice2 !='r' && choice2 !='R')
			// 			{
			// 				switch(choice2)
			// 				{
			// 					case 'd': case 'D'://Deposit money
			// 					{
			// 						account[i].deposit();
			// 						printOptions();
			// 						cout <<endl<< "Please make a selection: ";
			// 						choice2=check(2);
			// 					}
			// 					break;

			// 					case 'w': case 'W'://Withdraw money
			// 					{
			// 						account[i].withdraw();
			// 						printOptions();
			// 						cout <<endl <<  "Please make a selection: ";
			// 						choice2=check(2);
			// 					}
			// 					break;

			// 					case 'p': case 'P'://Print Balance
			// 					{
			// 						account[i].printBalance();
			// 						printOptions();
			// 						cout << endl << "Please make a selection: ";
			// 						choice2=check(2);
			// 					}
			// 					break;
			// 				}
			// 			}
			// 		}
			// 	}
			// 	cout << "Incorrect account name or password." << endl; 
			// 	printMenu();
			// 	cout << "Please make a selection: ";
			// 	choice1=check(1);