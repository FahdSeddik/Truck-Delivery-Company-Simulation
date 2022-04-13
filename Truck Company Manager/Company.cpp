#include "Company.h"
#include <iostream>
using namespace std;



#include "Events/CancellationEvent.h" //after company
#include "Events/PromotionEvent.h" //after company
#include "Events/ReadyEvent.h" //after company
Company::Company(UI_Class* pUI) {
	time = 0;
	NCcount = SCcount = VCcount = 0;
	this->pUI = pUI;
	string filename = pUI->ReadFileName();
	ReadFile(filename);

}


//TODO: READ FROM INPUT FILE CALLED ONLY IN CONSTRUCTOR
void Company::ReadFile(string filename)
{
	ifstream inputFile;
	inputFile.open(filename, ios::in); // opens the file for input
	int NS, SS, VS;//speeds of each type of truck
	//int NTC, STC, VTC;//capacity of each tyoe of truck
	int J;// number of trips before need for check-up
	int ID = 0;//ID used to identify each truck
	if (inputFile.is_open()) // checks if file has been opened successfully and ready to be read from
	{
		inputFile >> N >> S >> V; // reads number of trucks frome input file
		inputFile >> NS >> SS >> VS; // reads tuck speed of each type of truck from input file
		inputFile >> NTC >> STC >> VTC;// reads the capacity of each type of truck from input file
		inputFile >> MT_N >> MT_S >> MT_V >> J; // reads check up duration in hours for each type of truck & number of trips before need for check-up from input file
		// create the specified trucks based on read info
		for (int i = 0; i < N; i++)
		{
			Truck* T = new Truck(NTC,NS,J,NT,ID);
			Avail_NT.enqueue(T);
			ID++;
		}

		for (int i = 0; i < S; i++)
		{
			Truck* T = new Truck(STC, SS, J, ST,ID);
			Avail_ST.enqueue(T);
			ID++;
		}

		for (int i = 0; i < V; i++)
		{
			Truck* T = new Truck(VTC, VS, J, VT,ID);
			Avail_VT.enqueue(T);
			ID++;
		}
		//inputFile.ignore(); // ignores blank line
		inputFile >> AutoP >> MaxW; //reads auto promotion limit in days and MaxW in hours
		int n;// number of events
		inputFile >> n;// reads number of events
		// reads events info and create event object then adds it to events list
		for (int i = 0; i < n; i++)
		{
			char State;// the type of event
			int ET;//the time of the event
			int ID;//the ID of the cargo for which the event is to be applied
			int days;
			inputFile >> State;// reads the type of the event
			if(State=='R') // decides how to read the info of the event based on the type of the event
			{

				char TYP;
				int DIST;
				int LT;
				int Cost;
				Cargo_Type type;
				inputFile >> TYP;
				inputFile >> days; // inputs the day part of the time
				inputFile.ignore();// ignores the ":"
				inputFile >> ET;// inputs the hour part of the time
				ET = ET + (days - 1) * 24; // converts the time to be in hours
				inputFile >> ID >> DIST >> LT >> Cost;
				if (TYP=='N')
				{
					type = NC;
					NCcount++;
				}
				else if (TYP == 'S')
				{
					type = SC;
					SCcount++;
				}
				else
				{
					type = VC;
					VCcount++;
				}
				Event* E = new ReadyEvent(ET, ID, type, DIST, LT, Cost);
				EventList.enqueue(E);
			}
			else if (State == 'X')
			{
				inputFile >> days; // inputs the day part of the time
				inputFile.ignore();// ignores the ":"
				inputFile >> ET;// inputs the hour part of the time
				ET = ET + (days-1) * 24; // converts the time to be in hours
				inputFile >> ID;
				Event* E = new CancellationEvent(ET, ID);
				EventList.enqueue(E);
			}
			else if (State == 'P')
			{
				int ExtraMoney;
				inputFile >> days; // inputs the day part of the time
				inputFile.ignore();// ignores the ":"
				inputFile >> ET;// inputs the hour part of the time
				ET = ET + (days - 1) * 24; // converts the time to be in hours
				inputFile >> ID >> ExtraMoney;
				Event* E = new PromotionEvent(ET, ID, ExtraMoney);
				EventList.enqueue(E);
			}

		}
	}
	inputFile.close();
}


//TODO:Phase2 - ASSIGNS CARGOS TO TRUCKs OF ITS TYPE OR BASED ON DOCUMENT RULES
// moves cargos from waiting to moving
void Company:: AssignCargos() {
	Cargo* pC;
	while(Wait_NC.peekFront(pC))
	{
		int x = time - pC->getPrepTime();
		if (x >= (AutoP * 24)) {
			Wait_NC.dequeue(pC);
			pC->setType(VC);
			AppendWaitingCargo(pC);
		}
		else
		{
			break;
		}
	}
	LoadTrucks(&Wait_VC, &Avail_VT, VTC);
	LoadTrucks(&Wait_VC, &Avail_NT, NTC);
	LoadTrucks(&Wait_VC, &Avail_ST, STC);
	LoadTrucks(&Wait_SC, &Avail_ST, STC);
	LoadTrucks(&Wait_NC, &Avail_NT, NTC);
	LoadTrucks(&Wait_NC, &Avail_VT, VTC);

}

void Company::LoadTrucks(PQ<Cargo*>* CargoList, LLQ<Truck*>* TruckList, int Cap)
{
	int temp;
	int t;
	Cargo* pC;
	Truck* pT;
	while (CargoList->peekFront(pC) && TruckList->peekFront(pT))
	{
		temp = CargoList->getSize();
		if (temp >= Cap)
		{
			TruckList->dequeue(pT);
			for (int i = 0; i < Cap; i++)
			{
				CargoList->dequeue(pC);
				pT->AssignCargo(pC);
			}
			int x = pT->CalcLoadTime()+time;
			pT->setMoveTime(x);
			Loading_Trucks.enqueue(pT,-x);	//prio call calc load time in truck
		}
		else if (time - pC->getPrepTime() >= MaxW)
		{
			t = 0;
			while (CargoList->dequeue(pC) && t <= Cap)
			{
				pT->AssignCargo(pC);
				t++;
			}
			int x = pT->CalcLoadTime() + time;
			pT->setMoveTime(x);
			Loading_Trucks.enqueue(pT, -x);	//prio call calc load time in truck
		}
		else
		{
			break;
		}
	}
}

void Company::LoadTrucks(LLQ<Cargo*>* CargoList, LLQ<Truck*>* TruckList, int Cap)
{
	int temp;
	int t;
	Cargo* pC;
	Truck* pT;
	while (CargoList->peekFront(pC) && TruckList->peekFront(pT))
	{
		temp = CargoList->getSize();
		if (temp >= Cap)
		{
			TruckList->dequeue(pT);
			for (int i = 0; i < Cap; i++)
			{
				CargoList->dequeue(pC);
				pT->AssignCargo(pC);
			}
			int x = pT->CalcLoadTime() + time;
			pT->setMoveTime(x);
			pT->incrementActiveTime(x-time);
			Loading_Trucks.enqueue(pT, -x); //prio call calc load time in truck


		}
		else if ((time - pC->getPrepTime()) >= MaxW)
		{
			t = 0;
			while (CargoList->dequeue(pC) && t <= Cap)
			{
				pT->AssignCargo(pC);
				t++;
			}
			int x = pT->CalcLoadTime() + time;
			pT->setMoveTime(x);
			pT->incrementActiveTime(x - time);
			Loading_Trucks.enqueue(pT, -x); //prio call calc load time in truck
		}
		else
		{
			break;
		}
	}
}


//TODO: calls Update of each truck and event
// Calls AssignCargos()
// moves cargos/trucks across lists
// Calls ExecuteEvent()
bool Company::UpdateAll(int Global_Time) {
	time = Global_Time;
	ExecuteEvent();
	CheckTruckStatus();
	AssignCargos();
	if (Wait_NC.isEmpty() && Wait_SC.isEmpty() && Wait_VC.isEmpty() && Loading_Trucks.isEmpty() && MovingTrucks.isEmpty() && Under_Check.isEmpty() && EventList.isEmpty())
		return false;
	return true;
}


//TODO: Phase2 - checks truck status in Loading, Moving, and Under_Check
//if front of queue(ie. truck) needs updating
//moves each of the trucks that needs updating to its new list
//NOTE:
// multiple trucks may need moving to another list
// however, if so, then they should be after each other due to implemented data structure
void Company::CheckTruckStatus()
{
	int temp;
	Truck* pTruck;
	Truck_Type Type;
	// to-do
	//Check front of Available truck if reached maxW then call AssignCargos()


	while (Loading_Trucks.peekFront(pTruck)) {
		temp = pTruck->getMoveTime();
		if (temp <= time)
		{
			Loading_Trucks.dequeue(pTruck);
			temp = pTruck->CalcNextDT(time);
			MovingTrucks.enqueue(pTruck, -temp);
		}
		else
			break;
	}
	while (Under_Check.peekFront(pTruck)) {
		temp = time - pTruck->getLastReturnTime(); //time interval
		Type = pTruck->getTruckType();

		if (Type == NT && temp>=MT_N)
		{
			Under_Check.dequeue(pTruck);
			Avail_NT.enqueue(pTruck);
		}
		else if (Type == ST && temp>= MT_S)
		{
			Under_Check.dequeue(pTruck);
			Avail_ST.enqueue(pTruck);
		}
		else if (Type == VT && temp>= MT_V)
		{
			Under_Check.dequeue(pTruck);
			Avail_VT.enqueue(pTruck);
		}
		else
			break;
	}
	while (MovingTrucks.peekFront(pTruck)) {
		temp = pTruck->getNextDT();
		if (temp == time)
		{
			MovingTrucks.dequeue(pTruck);
			if (pTruck->Update(this, time))
			{
				temp = pTruck->CalcNextDT(time);
				pTruck->incrementActiveTime(temp-time);
				MovingTrucks.enqueue(pTruck, -temp);
			}
			else if (pTruck->NeedsRepairing())
			{
				Type = pTruck->getTruckType();
				int prio;
				if (Type == NT)
				{
					prio = time + MT_N;
				}
				else if (Type == ST)
				{
					prio = time + MT_S;
				}
				else
				{
					prio = time + MT_V;
				}
				Under_Check.enqueue(pTruck, -prio);
			}
			else
			{
				Type = pTruck->getTruckType();
				if (Type == NT)
				{
					Avail_NT.enqueue(pTruck);
				}
				else if (Type == ST)
				{
					Avail_ST.enqueue(pTruck);
				}
				else if (Type == VT)
				{
					Avail_VT.enqueue(pTruck);
				}
			}
		}
		else
			break;
	}

}

//TODO: to be used in update in case an event is to be done
// simply can be Ready::Execute for example
void Company::ExecuteEvent() {
	Event* pE;
	while (EventList.peekFront(pE) && pE->GetTime() == time) {
		EventList.dequeue(pE);
		pE->Execute(this);
	}
}



//TODO: to be used form each truck when a cargo is delivered
// appends a cargo to delivered list
void Company::AppendDeliveredCargo(Cargo* c) {
	c->setDeliveryTime(time);
	DeliveredCargos.enqueue(c);
}

//PHASE-1
//TODO: takes care of all print functions in UI Class
void Company::PrintStatus() {
	pUI->Print(time,Wait_NC,Wait_SC,Wait_VC,DeliveredCargos,Avail_NT,Avail_VT,Avail_ST,Loading_Trucks,Under_Check,MovingTrucks);
}


//PHASE-1
//TODO: takes a cargo ID
// checks normal cargo waiting list and moves if found
void Company::PromoteCargo(int ID,int ExtraMoney) {
	LLQ<Cargo*> tempq;
	Cargo* c;
	while (Wait_NC.dequeue(c)) {
		if (c->getID() == ID) {
			c->setCost(c->getcost() + ExtraMoney);
			int prio = 0; //perform prio calculation
			Wait_VC.enqueue(c, prio);
			break;
		}
		tempq.enqueue(c);
	}

	//make sure to empty all remaining cargos in tempq
	//to maintain order
	while (Wait_NC.dequeue(c))
		tempq.enqueue(c);

	//put back all other cargos in main queue
	while (tempq.dequeue(c))
		Wait_NC.enqueue(c);

}

//PHASE-1
//TODO: takes a cargo ID
// checks if found then cancels
void Company::CancelCargo(int ID) {
	LLQ<Cargo*> tempq;
	Cargo* c;
	//Checks for cargo in waiting (ie. you can cancel the cargo)
	while (Wait_NC.dequeue(c)) {
		if (c->getID() == ID) { //if found
			delete c;
			c = nullptr;
			break;
		}
		tempq.enqueue(c);
	}
	//make sure to empty all remaining cargos in tempq
	//to maintain order
	while (Wait_NC.dequeue(c))
		tempq.enqueue(c);

	//put back all other cargos in main queue
	while (tempq.dequeue(c))
		Wait_NC.enqueue(c);
}

//PHASE-1
//TODO: takes a cargo pointer
//enqueues cargo to its waiting list
// this method is only called by Read Event
void Company::AppendWaitingCargo(Cargo* c) {
	if (!c)
		return;

	if (c->getType() == NC) {
		Wait_NC.enqueue(c);
	}
	else if (c->getType() == VC) {
		int prio = 0; //calculation to be done
		Wait_VC.enqueue(c,prio);
	}
	else if (c->getType() == SC) {
		Wait_SC.enqueue(c);
	}
}


//TODO: writes output file
void Company::WriteOutput() {
	ofstream OutputFile;
	int temp, day;
	int waitTime = 0;
	Cargo* pC;
	OutputFile.open("OutPut.txt", ios::out);
	OutputFile << "CDT\tID\tPT\tWT\tTID" << endl;
	while (DeliveredCargos.dequeue(pC))
	{
		temp = pC->getDeliveryTime();
		day = temp / 24 + 1;
		temp = temp % 24;
		OutputFile << day << ":" << temp << "\t";
		OutputFile << pC->getID() << "\t";
		temp = pC->getPrepTime();
		day = temp / 24 + 1;
		temp = temp % 24;
		OutputFile << day << ":" << temp << "\t";
		temp = pC->getWatingTime();
		day = temp / 24 + 1;
		temp = temp % 24;
		waitTime += temp;
		OutputFile << day << ":" << temp << "\t";
		temp = pC->getTID();
		OutputFile << temp << endl;
	}
	OutputFile << "-------------------------------------------" << endl;
	OutputFile << "-------------------------------------------" << endl;
	OutputFile << "Cargos: " << VCcount + NCcount + SCcount << "[N: " << NCcount << ",S: " << SCcount << ",V: " << VCcount << "]" << endl;
	day = waitTime / 24 + 1;
	temp = waitTime % 24;
	OutputFile << "Cargo Avg Wait = " << day << ":" << temp << endl;
	temp = AutoPcount / (VCcount + NCcount + SCcount) * 100;
	OutputFile << "Auto-promoted Cargos: " << temp << "%" << endl;
	OutputFile << "Trucks: " << N + V + S << "[N: " << N << ",S: " << S << ",V: " << V << "]" << endl;

	OutputFile.close();
}
