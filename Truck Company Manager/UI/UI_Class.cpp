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
	cout << "Selection: ";
	cin >> mode;
	while (mode < 1 || mode>3)
	{
		cout << "invalid entry please try again ";
		cin >> mode;
	}
}

string UI_Class::ReadFileName(string io)
{
	string filename;
	cout << "Please enter the " + io + " file's name: ";
	cin >> filename;
	return filename;
}

void UI_Class::Print(int time, LLQ<Cargo*>& wn, LLQ<Cargo*>& ws, PQ<Cargo*>&wv, string& dn, string& dv, string& ds, LLQ<Truck*>& an, LLQ<Truck*>& av, LLQ<Truck*>& as
	, PQ<Truck*>& l, PQ<Truck*>& uc, PQ<Truck*>& m,int del,int n)
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
		cout << wn.getSize() + ws.getSize() + wv.getSize()<<" ";
		cout << "Waiting Cargos: ";
		cout << "[";
		wn.print();
		cout << "] (";
		ws.print();
		cout << ") {";
		wv.print();
		cout << "}\n";
		cout << "------------------------------------------------------";
		cout << endl << l.getSize() << " " << "Loading Trucks: ";
		l.print();
		cout << "\n------------------------------------------------------";
		cout << endl << an.getSize() + as.getSize() + av.getSize() << " " << "Empty Trucks: ";
		an.print();
		if (an.getSize() != 0 && (as.getSize()!=0 || av.getSize()!=0))
			cout << ",";
		cout<<" ";
		as.print();
		if (av.getSize() != 0 && as.getSize()!=0)
			cout << ",";
		cout<<" ";
		av.print();
		cout << "\n------------------------------------------------------";
		cout << endl << n << " " << "Moving Cargos: ";
		m.print();
		cout << "\n------------------------------------------------------";
		cout << endl << uc.getSize() << " " << "In-Checkup Trucks: ";
		uc.print();
		cout << "\n------------------------------------------------------";
		cout << endl<<del << " Delivered Cargos: ";
		cout << "[";
		cout << dn;
		cout << "] (";
		cout << ds;
		cout << ") {";
		cout << dv;
		cout << "}";
		cout << "\n------------------------------------------------------";
		cout << endl << endl;
	}
}




