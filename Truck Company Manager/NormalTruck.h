#pragma once
#include "Truck.h"
//Normal Truck class
class NormalTruck :public Truck
{
	public:
	NormalTruck();//def constructor.
	virtual~NormalTruck();//def destructor.
	virtual int getCurCapacity();//capacity getter.
	virtual void setCapacity(int TCap);//capacity setter.
	virtual int getCapacity();//capacity getter.
	virtual void setMaintenanceTime(int MTime);//maintenanceTime setter.
	virtual void setSpeed(int speed);//speed setter.
	virtual	int getMaintenanceTime();//maintenanceTime getter.
	virtual int getSpeed();//speed getter.
	virtual void setJ(int j);//Number of journeys after which the Truck needs maintenance setter (J)
	virtual int GetJ();//Number of journeys after which the Truck needs maintenance getter (J)
	virtual bool isFull();//checks if the truck is full(max capacity) 
	virtual bool AssignCargo(Cargo* CargoToAssign);//Assign cargo to Truck
	virtual void display();//display data.
	virtual int getDeliveryInterval();//delivery Interval getter.
	virtual int getCurrentJourneyCount();//Number of Current journeys
	virtual int getCurrentAssignedCargosCount();//Number of Current Assigned cargos
	virtual int GetfurthestDeliveryTime(); // getter for max Delivery Time (furthest Delivery Time)
	virtual int GetTotalUnLoadingTime();//getter for total UnLoading Time of the cargos
};