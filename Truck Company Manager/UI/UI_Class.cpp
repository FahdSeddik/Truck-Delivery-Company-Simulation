#include "UI_Class.h"
#include <Windows.h>
#include "../Truck and Cargo/Cargo.h"
#include "../Truck and Cargo/Truck.h"
#include "../Company.h"
void UI_Class::PrintSilent()const
{
	cout << "Silent Mode " << endl;
	cout << "Simulation Starts... " << endl;
	cout << "Simulation end, Output file create " << endl;
}
void UI_Class::PrintWaiting(Company* pComp)const
{
	LLQ<Cargo*>const* N = pComp->getWaitNC();
	LLQ<Cargo*>const* S = pComp->getWaitSC();
	MaxHeap<Cargo*>const* V = pComp->getWaitVC();
	cout << N->getSize() + S->getSize() + V->getSize() << " ";
	cout << "Waiting Cargos: ";
	cout << "[";
	N->print();
	cout << "] (";
	S->print();
	cout << ") {";
	V->print();
	cout << "}\n";
	cout << "------------------------------------------------------";
}
void UI_Class::PrintLoading(Company* pComp)const
{
	PQ<Truck*>const* l = pComp->getLoadingT();
	cout << endl << l->getSize() << " " << "Loading Trucks: ";
	l->print();
	cout << "\n------------------------------------------------------";
}
void UI_Class::PrintEmpty(Company* pComp) const
{
	LLQ<Truck*>const* an = pComp->getAvailNT();
	LLQ<Truck*>const* as = pComp->getAvailST();
	LLQ<Truck*>const* av = pComp->getAvailVT();
	cout << endl << an->getSize() + as->getSize() + av->getSize() << " " << "Empty Trucks: ";
	an->print();
	if (an->getSize() != 0 && (as->getSize() != 0 || av->getSize() != 0))
		cout << ",";
	cout << " ";
	as->print();
	if (av->getSize() != 0 && as->getSize() != 0)
		cout << ",";
	cout << " ";
	av->print();
	cout << "\n------------------------------------------------------";
}
void UI_Class::PrintMoving(Company* pComp,int n)const
{
	PQ<Truck*>const* m = pComp->getMovingT();
	cout << endl << n << " " << "Moving Cargos: ";
	m->print();
	cout << "\n------------------------------------------------------";
}
void UI_Class::PrintInCheckUp(Company* pComp)const
{
	LLQ<Truck*>const* unt = pComp->getUNT();
	LLQ<Truck*>const* ust = pComp->getUST();
	LLQ<Truck*>const* uvt = pComp->getUVT();
	cout << endl << unt->getSize()+ust->getSize()+uvt->getSize() << " " << "In-Checkup Trucks: ";
	unt->print();
	if (unt->getSize() != 0 && (ust->getSize() != 0 || uvt->getSize() != 0))
		cout << ",";
	cout << " ";
	ust->print();
	if (uvt->getSize() != 0 && ust->getSize() != 0)
		cout << ",";
	cout << " ";
	uvt->print();
	cout << "\n------------------------------------------------------";
}
void UI_Class::PrintDelivered(string dn,string ds,string dv,int del)const
{
	cout << endl << del << " Delivered Cargos: ";
	cout << "[";
	cout << dn;
	cout << "] (";
	cout << ds;
	cout << ") {";
	cout << dv;
	cout << "}";
	cout << "\n------------------------------------------------------";
}
UI_Class::UI_Class()
{

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

void UI_Class::Print(Company* pComp, string& dn, string& dv, string& ds,int del,int n)const
{
	if(mode==1)
		cin.ignore();
	if (mode == 2)
		Sleep(1000);
	int time = pComp->getGlobalTime();
	cout << "Current Time (Day:Hour): " << 1 + (time / 24) << ":" << time % 24 << endl;
	PrintWaiting(pComp);
	PrintLoading(pComp);
	PrintEmpty(pComp);
	PrintMoving(pComp, n);
	PrintInCheckUp(pComp);
	PrintDelivered(dn, ds, dv, del);
	cout << endl << endl;
}

int UI_Class::getMode() const
{
	return mode;
}




