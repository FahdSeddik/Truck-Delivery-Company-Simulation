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
#include <fstream>
#include <string>
using namespace std;

class Company
{
private:
	//CARGO LISTS
	/*
	Each Cargo type has its own waiting,
	
	However moving list and delivered list has all cargo types
	*/
	LLQ<Cargo*> Wait_NC, Wait_SC; //first come first served
	PQ<Cargo*> Wait_VC; //priority queues  array or tree (load when you have truck cap)
	//LLQ<Cargo*> Loading_NC,Loading_VC,Loading_SC; //Queue for loading time is constant for each type
	PQ<Cargo*> MovingCargos; //PQ sorted based on deliverytime of each cargo
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
	

public:
	//Constructor to read from file and set time to 0 
	Company() {
		time = 0;
		//ReadFile("");
	}


	//TODO: READ FROM INPUT FILE CALLED ONLY IN CONSTRUCTOR
	void ReadFile(ifstream& input, string filename);


	//TODO: ASSIGNS CARGOS TO TRUCKs OF ITS TYPE OR BASED ON DOCUMENT RULES
	// moves cargos from waiting to moving
	// returns false if there are no available cargos to assign (ie. empty cargo list)
	bool AssignCargos();


	//TODO: 
	// increments time
	// calls Update of each truck 
	// Calls AssignCargos()
	// moves cargos/trucks across lists
	// Calls ExecuteEvent()
	// returns false when program is done
	bool UpdateAll();

	//TODO: to be used in update in case an event is to be done 
	// simply can be Ready::Execute for example
	void ExecuteEvent();

	//TODO: to be used form each truck when a cargo is delivered
	// appends a cargo to delivered list
	void AppendDeliveredCargo(Cargo* c);
};

