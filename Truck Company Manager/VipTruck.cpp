#include "VipTruck.h"
VipTruck::VipTruck()
{
	deliveryInterval = 0;
	currentJourneyCount = 0;
	CurAssignedCargos = 0;
	CurCapacity = 0;
	std::cout << "vip const" << std::endl;
}//def constructor.

VipTruck::~VipTruck()
{
	std::cout << "Vip dest" << std::endl;
}//def destructor.

void VipTruck::setCapacity(int TCap)
{
	Capacity = TCap;
};//capacity setter.

void VipTruck::setMaintenanceTime(int MTime)
{
	maintenanceTime = MTime;
};//maintenanceTime setter.

void VipTruck::setSpeed(int speed)
{
	this->speed = speed;
};//speed setter.

int VipTruck::getCapacity()
{
	return Capacity;
};//capacity getter.

int VipTruck::getCurCapacity()
{
	return CurCapacity;
};//Current capacity getter.

int VipTruck::getMaintenanceTime()
{
	return maintenanceTime;
};//maintenanceTime getter.

int VipTruck::getSpeed()
{
	return speed;
};//speed getter.

void VipTruck::display()
{
	std::cout << "printing Normal Truck data" << std::endl;
	std::cout << "Truck current capacity: " << getCurCapacity() << std::endl;
	std::cout << "Truck max capacity: " << getCapacity() << std::endl;
	std::cout << "Truck Maintenance time: " << getMaintenanceTime() << std::endl;
	std::cout << "Truck speed: " << getSpeed() << std::endl;
	std::cout << "Truck Delivery interval: " << getDeliveryInterval() << std::endl;
	std::cout << "Truck Current number of journeys: " << getCurrentJourneyCount() << std::endl;
	std::cout << "Truck max number of journeys before a maintenace: " << GetJ() << std::endl;
	std::cout << "Count of Current assigned cargos : " << getCurrentAssignedCargosCount() << std::endl;
	std::cout << "printing Data of Assigned Cargos" << std::endl;
	for (int i = 0; i < getCurrentAssignedCargosCount(); i++)
	{
		AssignedCargos[i]->display();
	}
};//display data.

void VipTruck::setJ(int j)
{
	J = j;
};//Number of journeys after which the Truck needs maintenance setter (J)

int VipTruck::GetJ()
{
	return J;
};//Number of journeys after which the Truck needs maintenance getter (J)

bool VipTruck::isFull()
{
	return CurCapacity == Capacity;
};//checks if the truck is full(max capacity) 

bool VipTruck::AssignCargo(Cargo* CargoToAssign)
{
	if (isFull())//if full return false
		return false;
	AssignedCargos[CurAssignedCargos] = CargoToAssign;//add the cargo to the array
	CurAssignedCargos++;//incrementing current Assigned Cargos Count by 1
	//update delivery Interval after each assign
	//deliveryInterval=(Delivery distance of the furthest cargo/truck speed)+sum of unload times of all its cargos+time to come back(Delivery distance of the furthest cargo)
	deliveryInterval = (GetfurthestDeliveryTime() / speed) + GetTotalUnLoadingTime() + GetfurthestDeliveryTime();
	return true;//succesfully assigned

};//Assign cargo to Truck

int  VipTruck::getDeliveryInterval()
{
	return deliveryInterval;
};//delivery Interval getter.

int VipTruck::getCurrentJourneyCount()
{
	return currentJourneyCount;
};//Number of Current journeys

int VipTruck::getCurrentAssignedCargosCount()
{
	return CurAssignedCargos;
};//Number of Current Assigned cargos

int VipTruck::GetfurthestDeliveryTime()
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

int VipTruck::GetTotalUnLoadingTime()
{
	int totalUnLoadingTime = 0;//total UnLoading Time of the cargos
	for (int i = 0; i < getCurrentAssignedCargosCount(); i++)
	{
		totalUnLoadingTime = totalUnLoadingTime + AssignedCargos[i]->getLoad_Unload_Time();
	}
	return totalUnLoadingTime;
};//getter for total UnLoading Time of the cargos