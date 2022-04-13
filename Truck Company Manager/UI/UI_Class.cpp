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

void UI_Class::Print(int time, LLQ<Cargo*> wn, LLQ<Cargo*> ws, PQ<Cargo*>wv, LLQ<Cargo*> dc, LLQ<Truck*> an, LLQ<Truck*> av, LLQ<Truck*> as
	, LLQ<Truck*> ln, LLQ<Truck*> lv, LLQ<Truck*> ls, PQ<Truck*> uc, PQ<Truck*> m)
{
	Cargo* c;
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
		cin.ignore();
		cout << "Current Time (Day:Hour): " << time / 24 << ":" << time % 24 << endl;
		cout << "Waiting Cargos: ";
		
		cout << "[";
		while (wn.dequeue(c)) {
			if (wn.isEmpty()) {
				cout << c->getID();
				break;
			}
			cout << c->getID() << ",";
		}
		cout << "]";
		cout << "(";
		while (ws.dequeue(c)) {
			if (ws.isEmpty()) {
				cout << c->getID();
				break;
			}
			cout << c->getID() << ",";
		}
		cout << ")";
		cout << "{";
		while (wv.dequeue(c)) {
			if (wv.isEmpty()) {
				cout << c->getID();
				break;
			}
			cout << c->getID() << ",";
		}
		cout << "}"<<endl;
		cout << "------------------------------------------------------";
		cout <<endl<< "Loading Trucks: ";
		PrintTruckList(ln);
		PrintTruckList(ls);
		PrintTruckList(lv);
		cout << "\n------------------------------------------------------";
		cout<<endl << "Empty Trucks: ";
		PrintTruckList(an);
		PrintTruckList(av);
		PrintTruckList(as);
		cout << "\n------------------------------------------------------";
		cout << endl << "Moving Cargos: ";
		PrintTruckListP(m);
		cout << "\n------------------------------------------------------";
		cout << endl << "In-Checkup Trucks: ";
		PrintTruckListP(uc);
		cout << "\n------------------------------------------------------";
		cout << endl << "Delivered Cargos: ";
		PrintCargoList(dc);
		cout << "\n------------------------------------------------------";
		cout << endl << endl;
		break;
	case(2):
		/*while(smth)
		{
			print out current time
			Sleep(1000);
			print out information
		}
		break;
		*/
		cout << "Current Time (Day:Hour): " << time / 24 << ":" << time % 24 << endl;
		cout << "Waiting Cargos: ";

		cout << "[";
		while (wn.dequeue(c)) {
			if (wn.isEmpty()) {
				cout << c->getID();
				break;
			}
			cout << c->getID() << ",";
		}
		cout << "]";
		cout << "(";
		while (ws.dequeue(c)) {
			if (ws.isEmpty()) {
				cout << c->getID();
				break;
			}
			cout << c->getID() << ",";
		}
		cout << ")";
		cout << "{";
		while (wv.dequeue(c)) {
			if (wv.isEmpty()) {
				cout << c->getID();
				break;
			}
			cout << c->getID() << ",";
		}
		cout << "}" << endl;
		cout << "------------------------------------------------------";
		cout << endl << "Loading Trucks: ";
		PrintTruckList(ln);
		PrintTruckList(ls);
		PrintTruckList(lv);
		cout << "\n------------------------------------------------------";
		cout << endl << "Empty Trucks: ";
		PrintTruckList(an);
		PrintTruckList(av);
		PrintTruckList(as);
		cout << "\n------------------------------------------------------";
		cout << endl << "Moving Cargos: ";
		PrintTruckListP(m);
		cout << "\n------------------------------------------------------";
		cout << endl << "In-Checkup Trucks: ";
		PrintTruckListP(uc);
		cout << "\n------------------------------------------------------";
		cout << endl << "Delivered Cargos: ";
		PrintCargoList(dc);
		cout << "\n------------------------------------------------------";
		cout << endl << endl;
		Sleep(1000);
		break;
	case(3):
		if (!pSilent) {
			cout << "Silent Mode " << endl;
			cout << "Simulation Starts... " << endl;
			cout << "Simulation end, Output file create " << endl;
			pSilent = true;
		}
		break;
	}
}




//TODO: takes a truck list copy and its name
	//prints it with appropriate format
void UI_Class::PrintTruckList(LLQ<Truck*>& tl) {
	Truck* t;
	while (tl.dequeue(t)) {
		if (t->getCurrentAssignedCargosCount() == 0) {
			if (t->getTruckType() == NT) {
				cout << "[" << t->getID() << "]"<<" ";
			}
			else if (t->getTruckType() == VT) {
				cout << "{" << t->getID() << "}" << " ";
			}
			else if (t->getTruckType() == ST) {
				cout << "(" << t->getID() << ")" << " ";
			}
		}
		else {
			cout << t->getID();
			int* ids = t->getCargoIDs();
			if (t->getTruckType() == NT) {
				cout << "[";
				for (int i = 0; i < t->getCurrentAssignedCargosCount()-1; i++) {
					cout << ids[i] << ",";
				}
				cout<<"]" << " ";
			}
			else if (t->getTruckType() == VT) {
				cout << "{";
				for (int i = 0; i < t->getCurrentAssignedCargosCount() - 1; i++) {
					cout << ids[i] << ",";
				}
				cout << "}" << " ";
			}
			else if (t->getTruckType() == ST) {
				cout << "(";
				for (int i = 0; i < t->getCurrentAssignedCargosCount() - 1; i++) {
					cout << ids[i] << ",";
				}
				cout << ")" << " ";
			}
		}
	}
}
void UI_Class::PrintTruckListP(PQ<Truck*>& tl) {
	Truck* t;
	while (tl.dequeue(t)) {
		if (t->getCurrentAssignedCargosCount() == 0) {
			if (t->getTruckType() == NT) {
				cout << "[" << t->getID() << "]" << " ";
			}
			else if (t->getTruckType() == VT) {
				cout << "{" << t->getID() << "}" << " ";
			}
			else if (t->getTruckType() == ST) {
				cout << "(" << t->getID() << ")" << " ";
			}
		}
		else {
			cout << t->getID();
			int* ids = t->getCargoIDs();
			if (t->getTruckType() == NT) {
				cout << "[";
				for (int i = 0; i < t->getCurrentAssignedCargosCount() - 1; i++) {
					cout << ids[i] << ",";
				}
				cout << "]" << " ";
			}
			else if (t->getTruckType() == VT) {
				cout << "{";
				for (int i = 0; i < t->getCurrentAssignedCargosCount() - 1; i++) {
					cout << ids[i] << ",";
				}
				cout << "}" << " ";
			}
			else if (t->getTruckType() == ST) {
				cout << "(";
				for (int i = 0; i < t->getCurrentAssignedCargosCount() - 1; i++) {
					cout << ids[i] << ",";
				}
				cout << ")" << " ";
			}
		}
	}
}
//TODO: take a cargo list copy and its name
//prints it with appropriate format
void UI_Class::PrintCargoList(LLQ<Cargo*>& cl) {
	Cargo* c;
	while (cl.dequeue(c)) {
		if (c->getType() == NC) {
			cout << "[" << c->getID() << "]" << " ";
		}
		else if (c->getType() == VC) {
			cout << "[" << c->getID() << "]" << " ";
		}
		else if (c->getType() == SC) {
			cout << "[" << c->getID() << "]" << " ";
		}
	}
}
void UI_Class::PrintCargoListP(PQ<Cargo*>& cl) {
	Cargo* c;
	while (cl.dequeue(c)) {
		if (c->getType() == NC) {
			cout << "[" << c->getID() << "]" << " ";
		}
		else if (c->getType() == VC) {
			cout << "[" << c->getID() << "]" << " ";
		}
		else if (c->getType() == SC) {
			cout << "[" << c->getID() << "]" << " ";
		}
	}
}