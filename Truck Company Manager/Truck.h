#include <iostream>
#include "Cargo.h"
#pragma once
 //general abstract Truck class
class Truck
{
protected:
	int CurCapacity;//current capacity.
	int Capacity;//Number of cargos Truck can carry to be fully loaded.
	int maintenanceTime;//checkup time needed after j number of journeys.
	int speed;//speed of the Truck (KM/hour).
	int deliveryInterval;//time needed to deliver all cargos.
	int J;//Number of journeys after which the Truck needs maintenance
	int currentJourneyCount;//current number of journeys done by the truck
	int CurAssignedCargos;//count of Current assigned cargos (0 initialy)
	Cargo* AssignedCargos[20];//array of pointer(points to the assigned cargos)
public:
	Truck(){};//def constructor.
	virtual~Truck(){};//def constructor.
	virtual void setMaintenanceTime(int MTime)=0;//maintenanceTime setter.
	virtual void setSpeed(int speed)=0;//speed setter.
	virtual int getCurCapacity()=0;//Curent capacity getter.
	virtual	int getMaintenanceTime()=0;//maintenanceTime getter.
	virtual int getSpeed()=0;//speed getter.
	virtual void display()=0;//display data.
	virtual void setJ(int j) = 0;//Number of journeys after which the Truck needs maintenance setter (J)
	virtual int GetJ()=0;//Number of journeys after which the Truck needs maintenance getter (J)
	virtual bool isFull()=0;//checks if the truck is full(max capacity) 
	virtual bool AssignCargo(Cargo *CargoToAssign)=0;//Assign cargo to Truck
	virtual void setCapacity(int TCap) = 0;//capacity setter.
	virtual int getCapacity() = 0;//capacity getter.
	virtual int getDeliveryInterval() = 0;//delivery Interval getter.
	virtual int getCurrentJourneyCount() = 0;//Number of Current journeys
	virtual int getCurrentAssignedCargosCount() = 0;//Number of Current Assigned cargos
	virtual int GetfurthestDeliveryTime() = 0; // getter for max Delivery Time (furthest Delivery Time)
	virtual int GetTotalUnLoadingTime() = 0;//getter for total UnLoading Time of the cargos
};