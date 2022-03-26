#include "VipTruck.h"
VipTruck::VipTruck()
{
	std::cout << "vip const" << std::endl;
}//def constructor.

VipTruck::~VipTruck()
{
	std::cout << "Vip dest" << std::endl;
}//def destructor.

void VipTruck::setCapacity(int TCap)
{
	capacity = TCap;
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
	return capacity;
};//capacity getter.

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
	std::cout << "printing Vip Truck data" << std::endl;
	std::cout << "Truck capacity: " << getCapacity() << std::endl;
	std::cout << "Truck Maintenance time: " << getMaintenanceTime() << std::endl;
	std::cout << "Truck speed: " << getSpeed() << std::endl;
};//display data.