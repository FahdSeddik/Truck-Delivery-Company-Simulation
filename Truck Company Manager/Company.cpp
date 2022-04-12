#include "Company.h"
#include <iostream>
using namespace std;



//TODO: READ FROM INPUT FILE CALLED ONLY IN CONSTRUCTOR
void Company::ReadFile(string filename)
{
	ifstream inputFile;
	inputFile.open(filename, ios::in); // opens the file for input 
	int N, S, V;//numbers of each type of truck
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
		inputFile.ignore(); // ignores blank line
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
				inputFile >> TYP;
				inputFile >> days; // inputs the day part of the time
				inputFile.ignore();// ignores the ":"
				inputFile >> ET;// inputs the hour part of the time
				ET = ET + days * 24; // converts the time to be in hours
				inputFile >> ID >> DIST >> LT >> Cost;
				Event* E = new ReadyEvent(ET, ID, TYP, DIST, LT, Cost, State);
				EventList.enqueue(E);
			}
			else if (State == 'X')
			{
				inputFile >> days; // inputs the day part of the time
				inputFile.ignore();// ignores the ":"
				inputFile >> ET;// inputs the hour part of the time
				ET = ET + days * 24; // converts the time to be in hours
				inputFile >> ID;
				Event* E = new CancellationEvent(ET, ID, State);
				EventList.enqueue(E);
			}
			else if (State == 'P')
			{
				int ExtraMoney;
				inputFile >> days; // inputs the day part of the time
				inputFile.ignore();// ignores the ":"
				inputFile >> ET;// inputs the hour part of the time
				ET = ET + days * 24; // converts the time to be in hours
				inputFile >> ID >> ExtraMoney;
				Event* E = new PromotionEvent(ET, ID, ExtraMoney, State);
				EventList.enqueue(E);
			}
			
		}
	}
	inputFile.close();
}


//TODO: ASSIGNS CARGOS TO TRUCKs OF ITS TYPE OR BASED ON DOCUMENT RULES
// moves cargos from waiting to moving
void Company:: AssignCargos() {
	int temp1, t;
	Cargo* pC;
	Truck* pT;
	if (Avail_VT.peekFront(pT)) {
		temp1 = Wait_VC.getSize();
		t = time - pT->getLastReturnTime();
		if (temp1 >= VTC)
		{
			Avail_VT.dequeue(pT);
			for (int i = 0; i < VTC; i++)
			{
				Wait_VC.dequeue(pC);
				pT->AssignCargo(pC);
			}
			pT->setMoveTime(time);
			temp1 = pT->CalculateDeliveryTime();
			MovingTrucks.enqueue(pT, -temp1);
		}
		else if (t >= MaxW && temp1 > 0)
		{
			while (Wait_VC.dequeue(pC))
			{
				pT->AssignCargo(pC);
			}
			pT->setMoveTime(time);
			temp1 = pT->CalculateDeliveryTime();
			MovingTrucks.enqueue(pT, -temp1);
		}
	}
	if (Avail_ST.peekFront(pT)) {
		temp1 = Wait_SC.getSize();
		t = time - pT->getLastReturnTime();
		if (temp1 >= STC)
		{
			Avail_ST.dequeue(pT);
			for (int i = 0; i < STC; i++)
			{
				Wait_SC.dequeue(pC);
				pT->AssignCargo(pC);
			}
			temp1 = pT->CalculateDeliveryTime();
			MovingTrucks.enqueue(pT, -temp1);
		}
		else if (t >= MaxW && temp1 > 0)
		{
			while (Wait_SC.dequeue(pC))
			{
				pT->AssignCargo(pC);
			}
			pT->setMoveTime(time);
			temp1 = pT->CalculateDeliveryTime();
			MovingTrucks.enqueue(pT, -temp1);
		}
	}
	if (Avail_NT.peekFront(pT)) {
		temp1 = Wait_NC.getSize();
		t = time - pT->getLastReturnTime();
		if (temp1 >= NTC || t >= MaxW)
		{
			Avail_NT.dequeue(pT);
			for (int i = 0; i < NTC; i++)
			{
				Wait_NC.dequeue(pC);
				pT->AssignCargo(pC);
			}
			temp1 = pT->CalculateDeliveryTime();
			MovingTrucks.enqueue(pT, -temp1);
		}
		else if (t >= MaxW && temp1 > 0)
		{
			while (Wait_NC.dequeue(pC))
			{
				pT->AssignCargo(pC);
			}
			pT->setMoveTime(time);
			temp1 = pT->CalculateDeliveryTime();
			MovingTrucks.enqueue(pT, -temp1);
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
	if (Wait_NC.isEmpty() && Wait_SC.isEmpty() && Wait_VC.isEmpty() && Loading_NT.isEmpty() && Loading_ST.isEmpty() && Loading_VT.isEmpty() && MovingTrucks.isEmpty() && Under_Check.isEmpty())
		return false;
	return true;
}

void Company::CheckTruckStatus()
{
	int temp;
	Truck* pTruck;
	Truck_Type Type;
	// to-do 
	//Check front of Available truck if reached maxW then call AssignCargos()

	if (Loading_NT.peekFront(pTruck)) {
		temp = pTruck->getMoveTime();
		if (temp >= time)
		{
			Loading_NT.dequeue(pTruck);
			temp = pTruck->CalcNextDT();
			MovingTrucks.enqueue(pTruck, -temp);
		}
	}
	if (Loading_ST.peekFront(pTruck)) {
		temp = pTruck->getMoveTime();
		if (temp >= time)
		{
			Loading_ST.dequeue(pTruck);
			temp = pTruck->CalcNextDT();
			MovingTrucks.enqueue(pTruck, -temp);
		}
	}
	if (Loading_VT.peekFront(pTruck)) {
		temp = pTruck->getMoveTime();
		if (temp >= time)
		{
			Loading_VT.dequeue(pTruck);
			temp = pTruck->CalcNextDT();
			MovingTrucks.enqueue(pTruck, -temp);
		}
	}
	if (Under_Check.peekFront(pTruck)) {
		temp = pTruck->getFinishCheck();
		if (temp >= time)
		{
			Under_Check.dequeue(pTruck);
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
	if (MovingTrucks.peekFront(pTruck)) {
		temp = pTruck->getNextDT();
		if (temp >= time)
		{
			MovingTrucks.dequeue(pTruck);
			if (pTruck->Update(this, time))
			{
				temp = pTruck->CalcNextDT();
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
				else if (Type == VT)
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
	}

}

//TODO: to be used in update in case an event is to be done 
// simply can be Ready::Execute for example
void Company::ExecuteEvent() {
	Event* pE;
	EventList.peekFront(pE);
	if (pE->GetTime() >= time)
		pE->Execute(this);
}

