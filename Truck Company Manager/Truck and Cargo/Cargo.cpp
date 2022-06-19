#include "Cargo.h"
#include <iostream>
using namespace std;

Cargo::Cargo(int PREPT,int LOADTIME, int DELIVERYDIST, int COST, Cargo_Type CT, int Id)
{
	prepTime = PREPT;
	load_Unload_Time = LOADTIME;
	deliveryDistance = DELIVERYDIST;
	Cost = COST;
	Ctype = CT;
	deliveryTime = -1;
	ID = Id;
	moveTime = -1;
};//constructor.


Cargo::~Cargo()
{
	
};//destructor.



//SETTERS
void Cargo::setType(Cargo_Type CT) 
{
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
 }//cost setter.

void Cargo::setTID(int id)
{
	TID = id;
};//Cargo ID setter

void Cargo::setDeliveryTime(int t) {
	deliveryTime = t;
}//delivery time setter.

void Cargo::setMoveTime(int t) {
	moveTime = t;
}//move time setter.

//GETTERS
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
};//getter for Cargo ID

//getter for PrepTIme(time when the cargo is ready to be assigned to truck stored in hours).
int Cargo::getPrepTime() {
	return prepTime;
}

//the Time from the preparation of the cargo untill its truck starts to move to deliver it 
//(MoveTime-PrepTime)).
int Cargo::getWatingTime() {
	return moveTime-prepTime;
}

///getter cargo delivery time from company to the destination 
//((MT)+(cargo distance/truck speed)+(cargo unload time)).
int Cargo::getDeliveryTime() {
	return deliveryTime;
}

int Cargo::getTID()
{
	return TID;
}
//Truck ID getter.
int Cargo::getPrio() const
{
	return 5 * Cost - 3 * deliveryDistance - 2 * prepTime;
}

Cargo_Type Cargo::getType() {
	return Ctype;
}//Cargo Type getter.



ostream& operator << (ostream& os, Cargo& c) {
	os << c.getID();
	return os;
}//operator overloading.

