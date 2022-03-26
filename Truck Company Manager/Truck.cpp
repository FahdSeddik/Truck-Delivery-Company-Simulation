#include "Truck.h"
Truck::Truck(int CAP, int MAINT, int SPEED, int JBM, Truck_Type TT)
{
	Capacity = CAP;
	maintenanceTime = MAINT;
	speed = SPEED;
	J = JBM;
	Ttype = TT;
}//constructor.

Truck::~Truck()
{
	
}//def destructor.


//GETTERS
int Truck::getCapacity()
{
	return Capacity;
};//capacity getter.

int Truck::getCurCapacity()
{
	return CurCapacity;
};//Current capacity getter.

int Truck::getMaintenanceTime()
{
	return maintenanceTime;
};//maintenanceTime getter.

int Truck::getSpeed()
{
	return speed;
};//speed getter.


int  Truck::getDeliveryInterval()
{
	return deliveryInterval;
};//delivery Interval getter.

int Truck::getCurrentJourneyCount()
{
	return currentJourneyCount;
};//Number of Current journeys

int Truck::getCurrentAssignedCargosCount()
{
	return CurAssignedCargos;
};//Number of Current Assigned cargos



bool Truck::isFull()
{
	return CurCapacity == Capacity;
};//checks if the truck is full(max capacity) 

bool Truck::AssignCargo(Cargo * CargoToAssign)
{
	if (isFull())//if full return false
		return false;
	AssignedCargos[CurAssignedCargos] = CargoToAssign;//add the cargo to the array
	//update delivery Interval after each assign
	//deliveryInterval=(Delivery distance of the furthest cargo/truck speed)+sum of unload times of 
	//all its cargos+time to come back(Delivery distance of the furthest cargo)
	deliveryInterval = ((GetfurthestDeliveryTime() / speed) + GetTotalUnLoadingTime() + GetfurthestDeliveryTime());
	CurAssignedCargos++;//incrementing current Assigned Cargos Count by 1
	return true;//succesfully assigned

};//Assign cargo to Truck


int Truck::GetfurthestDeliveryTime()
{
	int furthestDeliveryTime = -9999;//getting the furthest delivery to calculate deliveryInterval
								//setting initialy with a verylow value to get max(futhest delivery time)
	for (int i = 0; i < getCurrentAssignedCargosCount(); i++)
	{
		if ((AssignedCargos[i]->getDeliveryDistance()) > furthestDeliveryTime)//getting the furthest delivery to calculate deliveryInterval
			furthestDeliveryTime = AssignedCargos[i]->getDeliveryDistance();
	}
	return furthestDeliveryTime;
}; // getter for max Delivery Time (furthest Delivery Time)

int Truck::GetTotalUnLoadingTime()
{
	int totalUnLoadingTime = 0;//total UnLoading Time of the cargos
	for (int i = 0; i < getCurrentAssignedCargosCount(); i++)
	{
		totalUnLoadingTime = totalUnLoadingTime + AssignedCargos[i]->getLoad_Unload_Time();
	}
	return totalUnLoadingTime;
};//getter for total UnLoading Time of the cargos




//SETTERS
void Truck::setCapacity(int TCap)
{
	Capacity = TCap;
};//capacity setter.

void Truck::setMaintenanceTime(int MTime)
{
	maintenanceTime = MTime;
};//maintenanceTime setter.

void Truck::setSpeed(int speed)
{
	this->speed = speed;
};//speed setter.


void Truck::setJ(int j)
{
	J = j;
};//Number of journeys after which the Truck needs maintenance setter (J)
