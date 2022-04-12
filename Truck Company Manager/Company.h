#pragma once
#include "INFO.h"
#include "Truck and Cargo/Truck.h"
#include "Truck and Cargo/Cargo.h"
#include "DS/LLBag.h"
#include "DS/LLQ.h"
#include "DS/PQ.h"
#include "Events/CancellationEvent.h"
#include "Events/PromotionEvent.h"
#include "Events/ReadyEvent.h"
#include "DS/Linked_List.h"
#include "UI/UI_Class.h"
#include <fstream>
#include <string>
using namespace std;

class Company
{
private:
	//CARGO LISTS
	/*
	Each Cargo type has its own waiting,
	
	However delivered list has all cargo types
	*/
	LLQ<Cargo*> Wait_NC, Wait_SC; //first come first served
	PQ<Cargo*> Wait_VC; //priority queues  array or tree (load when you have truck cap)
	//LLQ<Cargo*> Loading_NC,Loading_VC,Loading_SC; //Queue for loading time is constant for each type
	LLQ<Cargo*> DeliveredCargos; //queue linked

	
	//TRUCK LISTS
	/*
	Each truck type	has its own available list.

	Under checkup is for all truck types
	Moving for all truck types
	*/
	LLQ<Truck*> Avail_NT, Avail_VT, Avail_ST;
	LLQ<Truck*> Loading_NT, Loading_VT, Loading_ST;
	PQ<Truck*> Under_Check; //PQ based on who finished first
	PQ<Truck*> MovingTrucks; //PQ based on next cargo delivery time

	


	//Events
	LLQ<Event*> EventList;   // to be implemented

	int time; //time in hours is also simulation time

	int AutoP, MaxW; //in hours
	int MT_N, MT_V, MT_S; //maintenance time of each truck type
	
	UI_Class* pUI;


	//*****************************
	//---====UTILITY METHODS====---
	//*****************************
	
	//TODO: checks truck status in Loading, Moving, and Under_Check
	//if front of queue(ie. truck) needs updating
	//moves each of the trucks that needs updating to its new list
	//NOTE:
	// multiple trucks may need moving to another list
	// however, if so, then they should be after each other due to implemented data structure
	void CheckTruckStatus();

	//TODO: to be used in update in case an event is to be done 
	// simply can be Ready::Execute for example
	void ExecuteEvent();

	//TODO: ASSIGNS CARGOS TO TRUCKs OF ITS TYPE OR BASED ON DOCUMENT RULES
	// moves cargos from waiting to moving
	// returns false if there are no available cargos to assign (ie. empty cargo list)
	bool AssignCargos();

	//TODO: READ FROM INPUT FILE CALLED ONLY IN CONSTRUCTOR
	void ReadFile(string filename);


public:
	//Constructor to read from file and set time to 0 
	Company(UI_Class * pUI) {
		time = 0;
		this->pUI = pUI;
		string filename = pUI->ReadFileName();
		ReadFile(filename);
	}


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


	//TODO: takes care of all print functions in UI Class
	void PrintStatus();


	//TODO: takes a cargo ID
	// checks normal cargo waiting list and moves if found
	void PromoteCargo(int ID);

	//TODO: takes a cargo ID
	// checks if found then cancels
	void CancelCargo(Cargo_Type CT, int ID);

	//TODO: takes a cargo pointer
	//enqueues cargo to its waiting list
	// this method is only called by Read Event
	void AppendWaitingCargo(Cargo* c);

	//TODO: writes output file
	void WriteOutput();
};

