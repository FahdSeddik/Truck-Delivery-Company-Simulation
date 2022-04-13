#include "Cargo.h"

Cargo::Cargo(int PREPT,int LOADTIME, int DELIVERYDIST, int COST, Cargo_Type CT, int Id)
{
	prepTime = PREPT;
	load_Unload_Time = LOADTIME;
	deliveryDistance = DELIVERYDIST;
	Cost = COST;
	Ctype = CT;
	deliveryTime = -1;
	ID = Id;
};//constructor.


Cargo::~Cargo()
{
	
};//destructor.



//SETTERS
void Cargo::setCargoType(Cargo_Type CT) {
	Ctype = CT;
}//Cargo Type Setter
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
 }

;//cost setter.

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
 }
;//cost getter.

int Cargo::getID()
{
	return ID;
};//getter for ID


//getter for PrepTIme(time when the cargo is ready to be assigned to truck stored in hours).
int Cargo::getPrepTime() {
	return 0;
}

//getter for Current waiting time
//(the Time from the preration of the cargo untill its truck starts to move to deliver it (MoveTime-PrepTime))
int Cargo::getCurrWait() {
	return 0;
}

//getter for cargo delivery time from company to the destination 
//((MT)+(cargo distance/truck speed)+(cargo unload time))
int Cargo::getWatingTime() {
	return 0;
}


///getter cargo delivery time from company to the destination 
//((MT)+(cargo distance/truck speed)+(cargo unload time))
int Cargo::getDeliveryTime() {
	return 0;
}


//Cargo Type getter.
Cargo_Type Cargo::getType() {
	return Ctype;
}