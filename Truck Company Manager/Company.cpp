#include "Company.h"
#include <iostream>
using namespace std;



#include "Events/CancellationEvent.h" //after company
#include "Events/PromotionEvent.h" //after company
#include "Events/ReadyEvent.h" //after company
Company::Company(UI_Class* pUI) {
	time = 0;
	NCcount = SCcount = VCcount = AutoPcount = 0;
	DN = DV = DS = "";
	this->pUI = pUI;
	string ifilename = pUI->ReadFileName("input");
	ofname = pUI->ReadFileName("output");
	ReadFile(ifilename);
	movc = 0;
	LoadN = LoadS = LoadV = false;
}


//TODO: READ FROM INPUT FILE CALLED ONLY IN CONSTRUCTOR
void Company::ReadFile(string filename)
{
	ifstream inputFile;
	inputFile.open("Input-Output files/"+ filename, ios::in); // opens the file for input
	int NS, SS, VS;//speeds of each type of truck
	//int NTC, STC, VTC;//capacity of each tyoe of truck
	int J;// number of trips before need for check-up
	int ID = 0;//ID used to identify each truck
	if (inputFile.is_open()) // checks if file has been opened successfully and ready to be read from
	{
		inputFile >> N >> S >> V; // reads number of trucks frome input file
		inputFile >> NS >> SS >> VS; // reads tuck speed of each type of truck from input file
		inputFile >> NTC >> STC >> VTC;// reads the capacity of each type of truck from input file
		inputFile >>  J >> MT_N >> MT_S >> MT_V; // reads check up duration in hours for each type of truck & number of trips before need for check-up from input file
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
	while(Wait_NC.peekFront(pC)) //checks normal cargos
	{
		int Wait_interval = time - pC->getPrepTime();
		if (Wait_interval >= (AutoP * 24)) { //if reached autop to promote
			Wait_NC.dequeue(pC);
			pC->setType(VC);//change type
			NCcount--;
			VCcount++;
			AutoPcount++;
			AppendWaitingCargo(pC);
		}
		else
		{
			break;
		}
	}
	if(!LoadV)//Load VIP cargos into VIP trucks
		LoadTrucks(&Wait_VC, &Avail_VT, VTC,LoadV);
	if (Avail_VT.isEmpty()&& !LoadN)//Load VIP cargos into Normal trucks
	{
		LoadTrucks(&Wait_VC, &Avail_NT, NTC,LoadN);
	}
	if (Avail_VT.isEmpty() && Avail_NT.isEmpty() && !LoadS)//Load VIP cargos into Special trucks
	{
		LoadTrucks(&Wait_VC, &Avail_ST, STC,LoadS);
	}
	if(!LoadS)//Load special cargos into special trucks
		LoadTrucks(&Wait_SC, &Avail_ST, STC,LoadS);
	if(!LoadN)//Load normal cargos into normal trucks
		LoadTrucks(&Wait_NC, &Avail_NT, NTC,LoadN);
	if (Avail_NT.isEmpty() && !LoadV)//Load normal cargos into VIP trucks
	{
		LoadTrucks(&Wait_NC, &Avail_VT, VTC,LoadV);
	}

}

void Company::LoadTrucks(PQ<Cargo*>* CargoList, LLQ<Truck*>* TruckList, int Cap,bool& flag)
{
	int temp;
	int t;
	Cargo* pC;
	Truck* pT;
	while (CargoList->peekFront(pC) && TruckList->peekFront(pT) &&!flag)
	{
		temp = CargoList->getSize(); //cargos count
		if (temp >= Cap) //if present more than truck capacity
		{
			TruckList->dequeue(pT);
			for (int i = 0; i < Cap; i++) //load all
			{
				CargoList->dequeue(pC);
				pC->setTID(pT->getID());
				pT->AssignCargo(pC);
			}
			flag = true;
			int finishloadtime = pT->CalcLoadTime()+time; //calculate finish time (loading)
			pT->setMoveTime(finishloadtime);
			Loading_Trucks.enqueue(pT,-finishloadtime);	//enqueue in loading
		}
		else if (EventList.isEmpty()) //not enough cargos for capacity but no events
		{								//this would happen at the end of the program
										//if 2 VIP cargos left but not enough for capacity(no maxW for VIP)
			t = 0;
			while (CargoList->dequeue(pC) && t <= Cap) //load cargos into truck
			{
				pT->AssignCargo(pC);
				pC->setTID(pT->getID());
				t++;
			}
			flag = true;
			int finishloadtime = pT->CalcLoadTime() + time; //calculate finish time (loading)
			pT->setMoveTime(finishloadtime);
			TruckList->dequeue(pT);
			Loading_Trucks.enqueue(pT, -finishloadtime); //enqueue in loading
		}
		else
		{
			break;
		}
	}
}

void Company::LoadTrucks(LLQ<Cargo*>* CargoList, LLQ<Truck*>* TruckList, int Cap,bool& flag)
{
	int temp;
	int t;
	Cargo* pC;
	Truck* pT;
	while (CargoList->peekFront(pC) && TruckList->peekFront(pT) &&!flag)
	{
		temp = CargoList->getSize();//cargos count
		if (temp >= Cap)//if present more than truck capacity
		{
			TruckList->dequeue(pT);
			flag = true;
			for (int i = 0; i < Cap; i++)//load all
			{
				CargoList->dequeue(pC);
				pC->setTID(pT->getID());
				pT->AssignCargo(pC);
			}
			int finishloadtime = pT->CalcLoadTime() + time;//calculate finish time (loading)
			pT->setMoveTime(finishloadtime);
			Loading_Trucks.enqueue(pT, -finishloadtime); //enqueue in loading


		}
		else if ((time - pC->getPrepTime()) >= MaxW) //check for maxW if not enough cargos for capacity
		{
			t = 0;
			while (CargoList->dequeue(pC) && t <= Cap) //load all
			{
				pT->AssignCargo(pC);
				pC->setTID(pT->getID());
				t++;
			}
			flag = true;
			int finishloadtime = pT->CalcLoadTime() + time; //calculate finish time (loading)
			pT->setMoveTime(finishloadtime);
			TruckList->dequeue(pT);
			Loading_Trucks.enqueue(pT, -finishloadtime); //enqueue in loading
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
	bool offhours = time % 24 <=4;
	ExecuteEvent();
	CheckTruckStatus();
	if(!offhours)
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
	while (Loading_Trucks.peekFront(pTruck)) { //checks if loading needs updating
		temp = pTruck->getMoveTime();
		if (temp <= time) //did finish time arrive?
		{
			Loading_Trucks.dequeue(pTruck);
			temp = pTruck->CalcNextDT(time); //calculate first update time (next delivery)
			Truck_Type Tt = pTruck->getTruckType();
			if (Tt == NT) //reset loading boolean for type (1 loading of each type)
				LoadN = false;
			else if (Tt == VT)
				LoadV = false;
			else if (Tt == ST)
				LoadS = false;
			MovingTrucks.enqueue(pTruck, -temp); //enqueue in moving
			movc += pTruck->getAssignedList()->getSize(); //increment counter for moving cargos
		}
		else
			break;
	}
	while (Under_Check.peekFront(pTruck)) { //if under check trucks needs updating
		temp = time - pTruck->getLastReturnTime(); //time interval
		Type = pTruck->getTruckType();

		if (Type == NT && temp>=MT_N) //enqueue in available if passed maintenance time
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
	while (MovingTrucks.peekFront(pTruck)) { //check moving trucks
		temp = pTruck->getNextDT();
		if (temp == time) //if next delivery time arrived (or returned to company)
		{
			MovingTrucks.dequeue(pTruck);
			if (pTruck->Update(this, time)) //update-> true if cargo delivery event ////  ->false if return to company
			{
				temp = pTruck->CalcNextDT(time); //calc next delivery and enqueue back
				MovingTrucks.enqueue(pTruck, -temp);
			}
			else if (pTruck->NeedsRepairing()) //if returned to company check if need repairing
			{
				Type = pTruck->getTruckType();
				int prio;
				if (Type == NT) //calc finish maintenance time (prio in undercheck)
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
				Under_Check.enqueue(pTruck, -prio); //enqueue in maintenance
			}
			else //doesnt need maintenance
			{
				Type = pTruck->getTruckType();
				if (Type == NT) //enqueue in available
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
	c->setDeliveryTime(time); //set delivery time
	DeliveredCargos.enqueue(c); //enqueue in delivered cargos
	Cargo_Type ct = c->getType();
	if (ct == NC) { //edit delivered strings (for printing)
		if (DN.empty())
			DN += to_string(c->getID());
		else
			DN += "," + to_string(c->getID());
	}
	else if (ct == VC) {
		if (DV.empty())
			DV += to_string(c->getID());
		else
			DV += "," + to_string(c->getID());
	}
	else if (ct == SC) {
		if (DS.empty())
			DS += to_string(c->getID());
		else
			DS += "," + to_string(c->getID());
	}
	movc--; //decrement moving cargos count (for printing)
}

//PHASE-1
//TODO: takes care of all print functions in UI Class
void Company::PrintStatus() {
	//Sends all needed information to print
	/*
	This includes: 
	-Global Time
	-Waiting cargos lists
	-Delivered strings
	-Available Trucks
	-Loading ,Under Check, and Moving trucks
	-Number of delivered cargos
	-moving cargos count
	*/
	pUI->Print(time,Wait_NC,Wait_SC,Wait_VC,DN,DV,DS,Avail_NT,Avail_VT,Avail_ST,Loading_Trucks,Under_Check,MovingTrucks,DeliveredCargos.getSize(),movc);
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
			c->setType(VC);
			int prio = 5 * c->getcost() - 3 * c->getDeliveryDistance() - 2 * c->getPrepTime();
			Wait_VC.enqueue(c, prio);
			NCcount--;
			VCcount++;
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
			NCcount--;
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

	if (c->getType() == NC) { //checks type and append accordingly
		Wait_NC.enqueue(c);
	}
	else if (c->getType() == VC) {
		int prio = 5 * c->getcost() - 3 * c->getDeliveryDistance() - 2 * c->getPrepTime(); //prio equation
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
	OutputFile.open("Input-Output files/"+ofname, ios::out);
	OutputFile << "CDT\tID\tPT\tWT\tTID" << endl;
	while (DeliveredCargos.dequeue(pC)) //printing delivered cargos
	{
		temp = pC->getDeliveryTime(); 
		day = temp / 24 + 1;
		temp = temp % 24;
		OutputFile << day << ":" << temp << "\t";//delivery time
		OutputFile << pC->getID() << "\t"; //ID
		temp = pC->getPrepTime();
		day = temp / 24 + 1;
		temp = temp % 24;
		OutputFile << day << ":" << temp << "\t";//preparation time
		temp = pC->getWatingTime();
		waitTime += temp;
		day = temp / 24;
		temp = temp % 24;
		OutputFile << day << ":" << temp << "\t";//waiting time
		temp = pC->getTID();
		OutputFile << temp << endl;//truck ID
	}
	OutputFile << "-------------------------------------------" << endl;
	OutputFile << "-------------------------------------------" << endl;
	OutputFile << "Cargos: " << VCcount + NCcount + SCcount << "[N: " << NCcount << ",S: " << SCcount << ",V: " << VCcount << "]" << endl;//cargos counts
	waitTime = waitTime / (NCcount + VCcount + SCcount);
	day = waitTime / 24;
	temp = waitTime % 24;
	OutputFile << "Cargo Avg Wait = " << day << ":" << temp << endl; //avg wait
	temp = round((float)AutoPcount / (VCcount + NCcount + SCcount) * 100);
	OutputFile << "Auto-promoted Cargos: " << temp << "%" << endl;//autop
	OutputFile << "Trucks: " << N + V + S << "[N: " << N << ",S: " << S << ",V: " << V << "]" << endl;//number of trucks
	float activetime = 0, utilization = 0;
	Truck* t;
	while (Avail_NT.dequeue(t)) {// calculates all utilization and active times
		utilization+=t->CalculateTruckUtlization(time);
		activetime += t->getActiveTime();
	}
	while (Avail_VT.dequeue(t)) {
		utilization += t->CalculateTruckUtlization(time);
		activetime += t->getActiveTime();
	}
	while (Avail_ST.dequeue(t)) {
		utilization += t->CalculateTruckUtlization(time);
		activetime += t->getActiveTime();
	}
	activetime = (activetime / (N + V + S)); //calcs avg active
	utilization = utilization / (N + V + S) *100; //calcs avg util
	OutputFile << "Avg Active time = " << (int)activetime / 24 << ":" << (int)activetime % 24 << endl;
	OutputFile << "Avg utilization = " << round(utilization) << "%" << endl;
	OutputFile.close();
}
