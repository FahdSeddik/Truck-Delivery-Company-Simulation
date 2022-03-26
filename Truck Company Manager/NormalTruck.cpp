#include "NormalTruck.h"
NormalTruck::NormalTruck()
{
	std::cout << "normal const" << std::endl;
}//def constructor.

NormalTruck::~NormalTruck()
{
	std::cout << "normal dest" << std::endl;
}//def destructor.

void NormalTruck::setCapacity(int TCap)
	{
	capacity = TCap;
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
	return capacity;
	};//capacity getter.

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
	std::cout <<"Truck capacity: "<<getCapacity()<<std::endl;
	std::cout << "Truck Maintenance time: " << getMaintenanceTime() << std::endl;
	std::cout << "Truck speed: " << getSpeed() << std::endl;
};//display data.