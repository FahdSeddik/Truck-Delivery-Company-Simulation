#include "UI_Class.h"
#include <Windows.h>

UI_Class::UI_Class()
{
	cout << " Choose the desired program mode" << endl << "1- Interactive mode" << endl << "2- Step-by-step mode" << endl << "3- Silent mode";
	cin >> mode;
	while (mode < 1 || mode>3)
	{
		cout << "invalid entry please try again ";
		cin >> mode;
	}
}

void UI_Class::Print()
{
	switch (mode)
	{

	case(1):
		/*while(smth)
		{
			
			print out current time
			cin.ignore();
			print out information
		}
		break;
		*/
	case(2):
		/*while(smth)
		{
			print out current time
			Sleep(1000);
			print out information
		}
		break;
		*/

	case(3):
		cout << "Silent Mode " << endl;
		cout << "Simulation Starts... " << endl;
		cout << "Simulation end, Output file create " << endl;
	}
}