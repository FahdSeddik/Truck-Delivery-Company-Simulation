#pragma once
#include <iostream>
#include "Cargo.h"
#include "../INFO.h"

 
class Truck
{
private:
	//DATA MEMBERS TO BE READ FROM FILE
	int Capacity;//TC Number of cargos Truck can carry to be fully loaded.
	int speed;//speed of the Truck (KM/hour).
	int J;//Number of journeys after which the Truck needs maintenance
	Truck_Type Ttype; //type of truck


	//DATA MEMBERS CHANGES THROUGHOUT PROGRAM
	int CurCapacity;//current capacity.
	int deliveryInterval;//time needed to deliver all cargos.
	int currentJourneyCount;//current number of journeys done by the truck
	Cargo** AssignedCargos; //array of pointers (points to the assigned cargos)
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



	//PRIVATE SETTERS
	void setSpeed(int speed);//speed setter.
	void setJ(int j);//Number of journeys after which the Truck needs maintenance setter (J)
	void setCapacity(int TCap);//capacity setter.


public:


	Truck(int CAP,int SPEED,int JBM,Truck_Type TT);//def constructor.
	~Truck();//destructor.
	//Truck(Truck& T);//copy constructor

	//GETTERS
	int getCurCapacity();//Curent capacity getter.
	int getCapacity();//capacity getter.
	int getDeliveryInterval();//delivery Interval getter. //returns data member.
	int getCurrentJourneyCount();//Number of Current journeys .
	int getCurrentAssignedCargosCount();//Number of Current Assigned cargos.
	int getSpeed();//Truck Speed Getter.
	int getActiveTime();//getter for active time
					//time a truck is loading or in delivering cargos,
				   //doesn't include time for a truck to return after delivery
	Truck_Type getTruckType();//type of truck getter.



	//METHODS
	bool isFull();//checks if the truck is full(max capacity) 
	bool AssignCargo(Cargo* CargoToAssign);//Assign cargo to Truck
	bool NeedsRepairing();//return journeycount % J;
	void  CalculateTruckUtlization(int SimTime);//Calculated the percentage
	void update();//update status of the truck

	//called when company class moves truck to moving trucks list
	void CalculateDeliveryTime(); //calculates DT and set el data member

	//Update method to be called from company
	void Update(int Global_Time);


};