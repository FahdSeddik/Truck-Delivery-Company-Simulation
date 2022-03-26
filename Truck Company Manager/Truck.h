#pragma once
#include <iostream>
#include "Cargo.h"
#include "INFO.h"

 
class Truck
{
private:
	//TO BE READ FROM FILE
	int Capacity;//Number of cargos Truck can carry to be fully loaded.
	int maintenanceTime;//checkup time needed after j number of journeys.
	int speed;//speed of the Truck (KM/hour).
	int J;//Number of journeys after which the Truck needs maintenance
	Truck_Type Ttype; //type of truck


	//CHANGES THROUGHOUT PROGRAM
	int CurCapacity;//current capacity.
	int deliveryInterval;//time needed to deliver all cargos.
	int currentJourneyCount;//current number of journeys done by the truck
	Cargo** AssignedCargos; //array of pointers (points to the assigned cargos)
	int CurAssignedCargos;//count of Current assigned cargos (0 initialy)

	//SETTERS
	void setMaintenanceTime(int MTime);//maintenanceTime setter.
	void setSpeed(int speed);//speed setter.
	void setJ(int j);//Number of journeys after which the Truck needs maintenance setter (J)
	void setCapacity(int TCap);//capacity setter.


	int GetfurthestDeliveryTime(); // getter for max Delivery Time (furthest Delivery Time)
public:


	Truck(int CAP,int MAINT,int SPEED,int JBM,Truck_Type TT);//def constructor.
	~Truck();//destructor.


	//GETTERS
	int getCurCapacity();//Curent capacity getter.
	int getMaintenanceTime();//maintenanceTime getter.
	int getSpeed();//speed getter. //redundant
	int getCapacity();//capacity getter.
	int getDeliveryInterval();//delivery Interval getter. //returns data member
	int getCurrentJourneyCount();//Number of Current journeys 
	int getCurrentAssignedCargosCount();//Number of Current Assigned cargos
	int GetTotalUnLoadingTime();//getter for total UnLoading Time of the cargos


	//METHODS
	bool isFull();//checks if the truck is full(max capacity) 
	bool AssignCargo(Cargo* CargoToAssign);//Assign cargo to Truck
	bool NeedsRepairing();//Number of journeys after which the Truck needs maintenance getter (J)
	//return journeycount % J;

	//called when company class moves truck to moving trucks list
	void CalculateDeliveryTime(); //calculates DT and set el data member


};