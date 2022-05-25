#pragma once
#include "INFO.h"
#include "DS/LLQ.h"
#include "DS/PQ.h"
#include "Truck and Cargo/Cargo.h"
#include "Truck and Cargo/Truck.h" //after company
#include "Events/Event.h"

#include "UI/UI_Class.h"
#include <fstream>
#include <string>
using namespace std;
class Truck;
class Event;
class ReadyEvent;
class PromotionEvent;
class CancellationEvent;
class Company
{
private:
	//CARGO LISTS
	/*
	Each Cargo type has its own waiting,
	
	However delivered list has all cargo types
	*/
	LLQ<Cargo*> Wait_NC, Wait_SC; //first come first served
	PQ<Cargo*> Wait_VC; //priority queue
	LLQ<Cargo*> DeliveredCargos; //queue linked

	string DN, DV, DS; //strings for printing delivered separated
	
	//TRUCK LISTS
	/*
	Each truck type	has its own available list.

	Under checkup is for all truck types
	Moving for all truck types
	*/
	LLQ<Truck*> Avail_NT, Avail_VT, Avail_ST;
	PQ<Truck*> Loading_Trucks; //priority queue based on finish load first
	PQ<Truck*> Under_Check; //PQ based on who finished first
	PQ<Truck*> MovingTrucks; //PQ based on next cargo delivery time


	//Events
	LLQ<Event*> EventList;   

	int time; //time in hours is also simulation time
	int N, S, V;//numbers of each type of truck
	int NCcount, SCcount, VCcount; // count number of each type of cargo
	int AutoP, MaxW; //AutoP in days MaxW in hours
	int AutoPcount; // number of cargos auto-promoted
	int MT_N, MT_V, MT_S; //maintenance time of each truck type
	int NTC, STC, VTC; // capacity of each truck type
	string ofname;//output file name
	UI_Class* pUI; //ui pointer
	int movc; //moving cargos count (for printing)
	bool LoadN, LoadS, LoadV; //bool flags to only have 1 type of each truck loading at max

	//*****************************
	//---====UTILITY METHODS====---
	//*****************************
	
	//TODO: Phase2 - checks truck status in Loading, Moving, and Under_Check
	//if front of queue(ie. truck) needs updating
	//moves each of the trucks that needs updating to its new list
	//NOTE:
	// multiple trucks may need moving to another list
	// however, if so, then they should be after each other due to implemented data structure
	void CheckTruckStatus();

	//PHASE-1
	//TODO: to be used in update in case an event is to be done 
	// simply can be Ready::Execute for example
	void ExecuteEvent();

	//TODO: ASSIGNS CARGOS TO TRUCKs OF ITS TYPE OR BASED ON DOCUMENT RULES
	// moves cargos from waiting to moving
	void AssignCargos();


	//Loads From cargo list in truck list if conditions are correct 
	void LoadTrucks(LLQ<Cargo*> * CargoList, LLQ<Truck*>* TruckList, int Cap,bool& flag);
	//Overloaded version (vip cargos are priority queues and have different conditions (no MaxW)
	void LoadTrucks(PQ<Cargo*> * CargoList , LLQ<Truck*>* TruckList,int Cap,bool& flag);

	//PHASE-1
	//TODO: READ FROM INPUT FILE CALLED ONLY IN CONSTRUCTOR
	void ReadFile(string filename);

	
public:
	//Constructor to read from file and set time to 0 
	Company(UI_Class* pUI);


	//PHASE-1 (only part of the implementaion)
	//TODO:
	// increments time
	// Calls AssignCargos()
	// moves cargos/trucks across lists
	// Calls ExecuteEvent()
	// returns false when program is done
	bool UpdateAll(int Global_Time);


	//TODO: to be used form each truck when a cargo is delivered
	// appends a cargo to delivered list
	void AppendDeliveredCargo(Cargo* c);

	//PHASE-1
	//TODO: takes care of all print functions in UI Class
	void PrintStatus();


	//PHASE-1
	//TODO: takes a cargo ID
	// checks normal cargo waiting list and moves if found
	void PromoteCargo(int ID, int ExtraMoney);

	//PHASE-1
	//TODO: takes a cargo ID
	// checks if found then cancels
	void CancelCargo( int ID);

	//PHASE-1
	//TODO: takes a cargo pointer
	//enqueues cargo to its waiting list
	// this method is only called by Read Event
	void AppendWaitingCargo(Cargo* c);

	//TODO: writes output file
	void WriteOutput();
};

