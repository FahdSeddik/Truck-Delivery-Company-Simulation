#pragma once
#include "Cargo.h"
#include "../INFO.h"
#include "../Company.h"
#include <iostream>
using namespace std;

class Company; //forward declaration
class Truck;
ostream& operator<<(ostream& os, Truck& t);

class Truck
{
private:
	//DATA MEMBERS TO BE READ FROM FILE
	int Capacity;//TC Number of cargos Truck can carry to be fully loaded.
	int speed;//speed of the Truck (KM/hour).
	int J;//Number of journeys after which the Truck needs maintenance
	Truck_Type Ttype; //type of truck
	int ID; //unique ID for truck


	//DATA MEMBERS CHANGES THROUGHOUT PROGRAM
	
	int deliveryInterval;//time needed to deliver all cargos.
	int currentJourneyCount;//current number of journeys done by the truck
	int furthestDistance;
	int CurAssignedCargos;//count of Current assigned cargos (0 initialy)
	int MoveTime;//the time at which the truck carrying the cargo starts to move.
	int activeTime;//time a truck is loading or in delivering cargos,
				   //doesn't include time for a truck to return after delivery
	int TruckUtlization;//percentage%
						//TDC/(TC*N)*(TAT/TSim)
						//N not equal 0
						 //TDC TOTAl Cargos delivered by this truck
						//TC truck capacity
						//N total delivery journeys of this truck
						//tAt total truck active time
						//TSim total simulation time
	int TotalCargosDel;//TDC TOTAl Cargos delivered by this truck

	PQ<Cargo*> AssignedCargos; //priority queue sorted based on cargo distance

	


	//PRIVATE SETTERS
	void setSpeed(int speed);//speed setter.
	void setJ(int j);//Number of journeys after which the Truck needs maintenance setter (J)
	void setCapacity(int TCap);//capacity setter.

public:


	Truck(int CAP,int SPEED,int JBM,Truck_Type TT,int Id);//def constructor.
	~Truck();//destructor.
	//Truck(Truck& T);//copy constructor

	//GETTERS
	int getCapacity();//capacity getter.
	int getDeliveryInterval();//delivery Interval getter. //returns data member.
	int getCurrentJourneyCount();//Number of Current journeys .
	int getCurrentAssignedCargosCount();//Number of Current Assigned cargos.
	int getSpeed();//Truck Speed Getter.
	int getActiveTime();//getter for active time
					//time a truck is loading or in delivering cargos,
				   //doesn't include time for a truck to return after delivery
	int getID();//getter for ID
	Truck_Type getTruckType();//type of truck getter.
	

	int* getCargoIDs();
	//SETTERS
	void UpdateLastReturnTime(int LastReturn);
	void setMoveTime(int time);
	void incrementActiveTime(int time);
	//METHODS
	bool isFull();//checks if the truck is full(max capacity) 
	bool AssignCargo(Cargo* CargoToAssign);//Assign cargo to Truck and increments cargos assigned if it did
	bool NeedsRepairing();//return journeycount % J;
	int  CalculateTruckUtlization(int SimTime);//Calculated the percentage


	//TODO: calculates loading time 
	// goes through cargos and adds up loading times
	int CalcLoadTime();
	//TODO: (could be called Action time)
	// calculate next cargo delivery time and returns it
	//if finished cargos then calculate the return time to company
	int CalcNextDT(int GT);

	//int CalculateDeliveryTime(); //calculates DT and set el data member

	//Update method to be called from company
	// checks first if there is cargo to be delivered in Global_Time
	// if so call AppendDeliveredCargo() method in Company passing the cargo and return true
	// if no cargos to deliver then this means it has returned (ie. finished cargos)
	// return false in this case
	//bool Update(Company* C,int Global_Time);

	
};

