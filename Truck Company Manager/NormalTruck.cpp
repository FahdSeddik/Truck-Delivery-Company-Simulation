#include "NormalTruck.h"
NormalTruck::NormalTruck()
{
	deliveryInterval = 0;
	currentJourneyCount = 0;
	CurAssignedCargos = 0;
	CurCapacity = 0;
	std::cout << "normal const" << std::endl;
}//def constructor.

NormalTruck::~NormalTruck()
{
	std::cout << "normal dest" << std::endl;
}//def destructor.

void NormalTruck::setCapacity(int TCap)
	{
	Capacity = TCap;
	};//capacity setter.

void NormalTruck::setMaintenanceTime(int MTime)
	{
	maintenanceTime = MTime;
	};//maintenanceTime setter.

void NormalTruck::setSpeed(int speed)
	{
	this->speed = speed;
	};//speed setter.

int NormalTruck::getCapacity()
	{
	return Capacity;
	};//capacity getter.

int NormalTruck::getCurCapacity()
{
	return CurCapacity;
};//Current capacity getter.

int NormalTruck::getMaintenanceTime()
	{
	return maintenanceTime;
	};//maintenanceTime getter.

int NormalTruck::getSpeed()
	{
	return speed;
	};//speed getter.

void NormalTruck::display()
{
	std::cout << "printing Normal Truck data" << std::endl;
	std::cout << "Truck current capacity: " << getCurCapacity() << std::endl;
	std::cout <<"Truck max capacity: "<<getCapacity()<<std::endl;
	std::cout << "Truck Maintenance time: " << getMaintenanceTime() << std::endl;
	std::cout << "Truck speed: " << getSpeed() << std::endl;
	std::cout << "Truck Delivery interval: " << getDeliveryInterval() << std::endl;
	std::cout << "Truck Current number of journeys: " << getCurrentJourneyCount() << std::endl;
	std::cout << "Truck max number of journeys before a maintenace: " << GetJ() << std::endl;
	std::cout << "Count of Current assigned cargos : " << getCurrentAssignedCargosCount()<< std::endl;
	std::cout << "printing Data of Assigned Cargos" << std::endl;
	for (int i = 0;i < getCurrentAssignedCargosCount();i++)
	{
		AssignedCargos[i]->display();
	}
};//display data.

void NormalTruck::setJ(int j)
{
	J = j;
};//Number of journeys after which the Truck needs maintenance setter (J)

int NormalTruck::GetJ()
{
	return J;
};//Number of journeys after which the Truck needs maintenance getter (J)

bool NormalTruck::isFull()
{
	return CurCapacity == Capacity;
};//checks if the truck is full(max capacity) 

bool NormalTruck::AssignCargo(Cargo * CargoToAssign)
{
	if (isFull())//if full return false
		return false;
	AssignedCargos[CurAssignedCargos] = CargoToAssign;//add the cargo to the array
	//update delivery Interval after each assign
	//deliveryInterval=(Delivery distance of the furthest cargo/truck speed)+sum of unload times of all its cargos+time to come back(Delivery distance of the furthest cargo)
	deliveryInterval = ((GetfurthestDeliveryTime() / speed) + GetTotalUnLoadingTime() + GetfurthestDeliveryTime());
	CurAssignedCargos++;//incrementing current Assigned Cargos Count by 1
	return true;//succesfully assigned

};//Assign cargo to Truck

int  NormalTruck::getDeliveryInterval()
{
	return deliveryInterval;
};//delivery Interval getter.

int NormalTruck::getCurrentJourneyCount()
{
	return currentJourneyCount;
};//Number of Current journeys

int NormalTruck::getCurrentAssignedCargosCount()
{
	return CurAssignedCargos;
};//Number of Current Assigned cargos

int NormalTruck::GetfurthestDeliveryTime()
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

int NormalTruck::GetTotalUnLoadingTime()
{
	int totalUnLoadingTime = 0;//total UnLoading Time of the cargos
	for (int i = 0; i < getCurrentAssignedCargosCount(); i++)
	{
		totalUnLoadingTime = totalUnLoadingTime + AssignedCargos[i]->getLoad_Unload_Time();
	}
	return totalUnLoadingTime;
};//getter for total UnLoading Time of the cargos