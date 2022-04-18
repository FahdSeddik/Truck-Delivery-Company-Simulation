#include "UI_Class.h"
#include <Windows.h>
#include "../Truck and Cargo/Cargo.h"
#include "../Truck and Cargo/Truck.h"
UI_Class::UI_Class()
{
	pSilent = false;

	cout << " Choose the desired program mode" << endl 
		<< "1- Interactive mode" << endl 
		<< "2- Step-by-step mode" << endl 
		<< "3- Silent mode" <<endl;

	cin >> mode;
	while (mode < 1 || mode>3)
	{
		cout << "invalid entry please try again ";
		cin >> mode;
	}
}

string UI_Class::ReadFileName()
{
	string filename;
	cout << "Please enter the input file's name: ";
	cin >> filename;
	return filename;
}

void UI_Class::Print(int time, LLQ<Cargo*>& wn, LLQ<Cargo*>& ws, PQ<Cargo*>&wv, LLQ<Cargo*>& dn, LLQ<Cargo*>& dv, LLQ<Cargo*>& ds, LLQ<Truck*>& an, LLQ<Truck*>& av, LLQ<Truck*>& as
	, PQ<Truck*>& l, PQ<Truck*>& uc, PQ<Truck*>& m)
{
	if (mode == 3) {
		if (!pSilent) {
			cout << "Silent Mode " << endl;
			cout << "Simulation Starts... " << endl;
			cout << "Simulation end, Output file create " << endl;
			pSilent = true;
		}
	}
	else{
		if(mode==1)
			cin.ignore();
		if (mode == 2)
			Sleep(1000);
		cout << "Current Time (Day:Hour): " << 1 + (time / 24) << ":" << time % 24 << endl;
		cout << "Waiting Cargos: ";
		cout << "[";
		wn.print();
		cout << "] (";
		ws.print();
		cout << ") {";
		wv.print();
		cout << "}\n";
		cout << "------------------------------------------------------";
		cout << endl << "Loading Trucks: ";
		l.print();
		cout << "\n------------------------------------------------------";
		cout << endl << "Empty Trucks: ";
		an.print();
		as.print();
		av.print();
		cout << "\n------------------------------------------------------";
		cout << endl << "Moving Cargos: ";
		m.print();
		cout << "\n------------------------------------------------------";
		cout << endl << "In-Checkup Trucks: ";
		uc.print();
		cout << "\n------------------------------------------------------";
		cout << endl << "Delivered Cargos: ";
		cout << "[";
		dn.print();
		cout << "] (";
		ds.print();
		cout << ") {";
		dv.print();
		cout << "}";
		cout << "\n------------------------------------------------------";
		cout << endl << endl;
	}
}




