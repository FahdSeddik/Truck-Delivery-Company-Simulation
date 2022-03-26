#include "Cargo.h"

Cargo::Cargo(int PREPT, int LOADTIME, int DELIVERYDIST, int COST,Cargo_Type CT)
{
	prepTime = PREPT;
	load_Unload_Time = LOADTIME;
	deliveryDistance = DELIVERYDIST;
	Cost = COST;
	Ctype = CT;
};//constructor.


Cargo::~Cargo()
{
	
};//destructor.



//SETTERS
void Cargo::setload_Unload_Time(int LTime)
{
	load_Unload_Time = LTime;
 };//load/Unload Time setter.

void Cargo::setDeliveryDistance(int DDistance)
{
	deliveryDistance = DDistance;
 };//DeliveryDistance setter.

void Cargo::setCost(int cost)
{
	Cost = cost;
 };//cost setter.



int Cargo::getLoad_Unload_Time()
{
	return load_Unload_Time;
};//load/Unload Time getter.

int Cargo::getDeliveryDistance()
{
	return deliveryDistance;
 };//DeliveryDistance getter.

int Cargo::getcost()
{
	return Cost;
 };//cost getter.
