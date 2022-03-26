#include "VIPCargo.h"
VIPCargo::VIPCargo()
{
	std::cout << " vip const" << std::endl;

};//def constructor.

VIPCargo::~VIPCargo()
{
	std::cout << "vip dest" << std::endl;
};//def constructor.

void VIPCargo::setPreperationTime(int dy, int hr)
{
	prepTime.setDay(dy);
	prepTime.setHour(hr);
};//PreperationTime setter.

void VIPCargo::setload_Unload_Time(int LTime)
{
	load_Unload_Time = LTime;
};//load/Unload Time setter.

void VIPCargo::setDeliveryDistance(int DDistance)
{
	deliveryDistance = DDistance;
};//DeliveryDistance setter.

void VIPCargo::setCost(int cost)
{
	Cost = cost;
};//cost setter.

preperationTime VIPCargo::getPreperationTime()
{
	return prepTime;
};//PreperationTime getter.

int VIPCargo::getLoad_Unload_Time()
{
	return load_Unload_Time;
};//load/Unload Time getter.

int VIPCargo::getDeliveryDistance()
{
	return deliveryDistance;
};//DeliveryDistance getter.

int VIPCargo::getcost()
{
	return Cost;
};//cost getter.

void VIPCargo::display()
{
	std::cout << "printing VIP Cargo data" << std::endl;
	std::cout << "Cargo Preperation Time:";
	prepTime.display();
	std::cout << "Cargo loading/unloading Time: " << getLoad_Unload_Time() << std::endl;
	std::cout << "Cargo delivery distance: " << getDeliveryDistance() << std::endl;
	std::cout << "Cargo Cost: " << getcost() << std::endl;
};//display data.