#include "SpecialTruck.h"
SpecialTruck::SpecialTruck()
{
	std::cout << "special const" << std::endl;
}//def constructor.

SpecialTruck::~SpecialTruck()
{
	std::cout << "special dest" << std::endl;
}//def destructor.

void SpecialTruck::setCapacity(int TCap)
{
	capacity = TCap;
};//capacity setter.

void SpecialTruck::setMaintenanceTime(int MTime)
{
	maintenanceTime = MTime;
};//maintenanceTime setter.

void SpecialTruck::setSpeed(int speed)
{
	this->speed = speed;
};//speed setter.

int SpecialTruck::getCapacity()
{
	return capacity;
};//capacity getter.

int SpecialTruck::getMaintenanceTime()
{
	return maintenanceTime;
};//maintenanceTime getter.

int SpecialTruck::getSpeed()
{
	return speed;
};//speed getter.

void SpecialTruck::display()
{
	std::cout << "printing special Truck data" << std::endl;
	std::cout << "Truck capacity: " << getCapacity() << std::endl;
	std::cout << "Truck Maintenance time: " << getMaintenanceTime() << std::endl;
	std::cout << "Truck speed: " << getSpeed() << std::endl;
};//display data.