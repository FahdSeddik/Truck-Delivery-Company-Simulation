#include "SpecialCargo.h"
SpecialCargo::SpecialCargo()
{
	std::cout << "Special const" << std::endl;

};//def constructor.

SpecialCargo::~SpecialCargo()
{
	std::cout << "Special dest" << std::endl;
};//def constructor.

void SpecialCargo::setPreperationTime(int dy, int hr)
{
	prepTime.setDay(dy);
	prepTime.setHour(hr);
};//PreperationTime setter.

void SpecialCargo::setload_Unload_Time(int LTime)
{
	load_Unload_Time = LTime;
};//load/Unload Time setter.

void SpecialCargo::setDeliveryDistance(int DDistance)
{
	deliveryDistance = DDistance;
};//DeliveryDistance setter.

void SpecialCargo::setCost(int cost)
{
	Cost = cost;
};//cost setter.

preperationTime SpecialCargo::getPreperationTime()
{
	return prepTime;
};//PreperationTime getter.

int SpecialCargo::getLoad_Unload_Time()
{
	return load_Unload_Time;
};//load/Unload Time getter.

int SpecialCargo::getDeliveryDistance()
{
	return deliveryDistance;
};//DeliveryDistance getter.

int SpecialCargo::getcost()
{
	return Cost;
};//cost getter.

void SpecialCargo::display()
{
	std::cout << "printing Special Cargo data" << std::endl;
	std::cout << "Cargo Preperation Time:";
	prepTime.display();
	std::cout << "Cargo loading/unloading Time: " << getLoad_Unload_Time() << std::endl;
	std::cout << "Cargo delivery distance: " << getDeliveryDistance() << std::endl;
	std::cout << "Cargo Cost: " << getcost() << std::endl;
};//display data.