#include "NormalCargo.h"
NormalCargo::NormalCargo()
{
	std::cout << "normal const" << std::endl;

};//def constructor.

NormalCargo::~NormalCargo()
{
	std::cout << "normal dest" << std::endl;
};//def constructor.

void NormalCargo::setPreperationTime(int dy, int hr)
{
	prepTime.setDay(dy);
	prepTime.setHour(hr);
 };//PreperationTime setter.

void NormalCargo::setload_Unload_Time(int LTime)
{
	load_Unload_Time = LTime;
 };//load/Unload Time setter.

void NormalCargo::setDeliveryDistance(int DDistance)
{
	deliveryDistance = DDistance;
 };//DeliveryDistance setter.

void NormalCargo::setCost(int cost)
{
	Cost = cost;
 };//cost setter.

preperationTime NormalCargo::getPreperationTime()
{
	return prepTime;
 };//PreperationTime getter.

int NormalCargo::getLoad_Unload_Time()
{
	return load_Unload_Time;
};//load/Unload Time getter.

int NormalCargo::getDeliveryDistance()
{
	return deliveryDistance;
 };//DeliveryDistance getter.

int NormalCargo::getcost()
{
	return Cost;
 };//cost getter.

void NormalCargo::display()
{
	std::cout << "printing Normal Cargo data" << std::endl;
	std::cout << "Cargo Preperation Time:";
	prepTime.display();
	std::cout << "Cargo loading/unloading Time: " << getLoad_Unload_Time() << std::endl;
	std::cout << "Cargo delivery distance: " << getDeliveryDistance() << std::endl;
	std::cout << "Cargo Cost: " << getcost() << std::endl;
 };//display data.