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
	LLBag<Cargo*> MovingCargos_NC, MovingCargos_SC, MovingCargos_VC; //Bag and remove cargos when delivered   (know delivered from each truck)
	LLQ<Cargo*> DeliveredCargos; //queue linked

	
	//TRUCK LISTS
	/*
	Each truck type	has its own available list.

	Under checkup is for all truck types
	Moving for all truck types
	*/
	LLQ<Truck*> Avail_NT, Avail_VT, Avail_ST;
	Linked_List<Truck*> NotAvailTrucks; //Linked-List to traverse and call update    TO ADDD AN INTERFACEEE

	////LoadingTrucks;  //Linked-List use find by index to access Truck* Find(i)
	////Under_Check; //LL based on checkup time needed
	////PQ<Truck*> MovingTrucks; //priority queue based on return time

	


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
	// calls Update of each truck and event
	// Calls AssignCargos()
	// moves cargos/trucks across lists
	// Calls ExecuteEvent()
	// returns false when program is done
	bool UpdateAll();

	//TODO: to be used in update in case an event is to be done 
	// simply can be Ready::Execute for example
	void ExecuteEvent();

	

};

