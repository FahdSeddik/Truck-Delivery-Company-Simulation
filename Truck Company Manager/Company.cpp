#include "Company.h"
#include <iostream>
#include <fstream>
using namespace std;



//TODO: READ FROM INPUT FILE CALLED ONLY IN CONSTRUCTOR
void Company::ReadFile(ifstream & inputFile, string filename)
{
	inputFile.open(filename, ios::in); // opens the file for input 
	int N, S, V;//numbers of each type of truck
	int NS, SS, VS;//speeds of each type of truck
	int NTC, STC, VTC;//capacity of each tyoe of truck
	int J;// number of trips before need for check-up
	if (inputFile.is_open()) // checks if file has been opened successfully and ready to be read from
	{
		inputFile >> N >> S >> V; // reads number of trucks frome input file
		inputFile >> NS >> SS >> VS; // reads tuck speed of each type of truck from input file
		inputFile >> NTC >> STC >> VTC;// reads the capacity of each type of truck from input file
		inputFile >> MT_N >> MT_S >> MT_V >> J; // reads check up duration in hours for each type of truck & number of trips before need for check-up from input file
		// create the specified trucks based on read info
		for (int i = 0; i < N; i++)
		{
			Truck* T = new Truck(NTC,NS,J,NT);
			Avail_NT.enqueue(T);
		}

		for (int i = 0; i < S; i++)
		{
			Truck* T = new Truck(STC, SS, J, ST);
			Avail_ST.enqueue(T);
		}

		for (int i = 0; i < V; i++)
		{
			Truck* T = new Truck(VTC, VS, J, VT);
			Avail_VT.enqueue(T);
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
			inputFile >> State;// reads the type of the event
			if(State=='R') // decides how to read the info of the event based on the type of the event
			{
				char TYP;
				int DIST;
				int LT;
				int Cost;
				inputFile >> TYP >> ET >> ID >> DIST >> LT >> Cost;
				Event* E = new ReadyEvent(ET, ID, TYP, DIST, LT, Cost, State);
				EventList.enqueue(E);
			}
			else if (State == 'X')
			{
				inputFile >> ET >> ID;
				Event* E = new CancellationEvent(ET, ID, State);
				EventList.enqueue(E);
			}
			else if (State == 'P')
			{
				int ExtraMoney;
				inputFile >> ET >> ID >> ExtraMoney;
				Event* E = new PromotionEvent(ET, ID, ExtraMoney, State);
				EventList.enqueue(E);
			}
			
		}
	}
	inputFile.close();
}


//TODO: ASSIGNS CARGOS TO TRUCKs OF ITS TYPE OR BASED ON DOCUMENT RULES
// moves cargos from waiting to moving
// returns false if there are no available cargos to assign (ie. empty cargo list)
bool Company:: AssignCargos() {

}


//TODO: calls Update of each truck and event
// Calls AssignCargos()
// moves cargos/trucks across lists
// Calls ExecuteEvent()
bool Company::UpdateAll() {

}

//TODO: to be used in update in case an event is to be done 
// simply can be Ready::Execute for example
void Company::ExecuteEvent() {

}

