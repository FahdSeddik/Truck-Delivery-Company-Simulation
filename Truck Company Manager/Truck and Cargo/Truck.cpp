#include "Truck.h"
#include "../DS/LLQ.h"
#include "../DS/PQ.h"

#include <iostream>
using namespace std;

Truck::Truck(int CAP, int SPEED, int JBM, Truck_Type TT,int Id)
{
	CurCapacity = 0;
	deliveryInterval = 0;
	currentJourneyCount = 0;
	CurAssignedCargos = 0;
	furthestDistance = 0;
	activeTime = 0;
	TotalCargosDel = 0;
	Capacity = CAP;
	speed = SPEED;
	J = JBM;
	Ttype = TT;
	ID = Id;
}//constructor.

Truck::~Truck()
{
	
}//def destructor.

//Truck::Truck(Truck& T)
//{
//	Capacity=T.Capacity;
//	maintenanceTime=T.maintenanceTime;
//	speed=T.speed;
//	J=T.J;
//	Ttype=T.Ttype;
//	CurCapacity=T.CurCapacity;
//	deliveryInterval = T.deliveryInterval;
//	currentJourneyCount=T.currentJourneyCount;
//	T.AssignedCargos = new Cargo * [Capacity];//allocating a newarray of max Capacity Size for the copied object
//	CurAssignedCargos=T.CurAssignedCargos;
//	MoveTime=T.MoveTime;
//	activeTime=T.activeTime;
//	TruckUtlization=T.TruckUtlization;		
//	TotalCargosDel=T.TotalCargosDel;
//	TotalDeliveryJour=T.TotalDeliveryJour;
//	TotalSimTime = T.TotalSimTime;
//};//copy constructor

//GETTERS
int Truck::getCapacity()
{
	return Capacity;
};//capacity getter.

int Truck::getCurCapacity()
{
	return CurCapacity;
};//Current capacity getter.


int  Truck::getDeliveryInterval()
{
	return deliveryInterval;
};//delivery Interval getter.

int Truck::getCurrentJourneyCount()
{
	return currentJourneyCount;
};//Number of Current journeys

int Truck::getCurrentAssignedCargosCount()
{
	return CurAssignedCargos;
};//Number of Current Assigned cargos

int Truck::getSpeed()
{
	return speed;
};//Truck Speed Getter.


int Truck::getActiveTime()
{
	return activeTime;
};//getter for active time
//time a truck is loading or in delivering cargos,
 //doesn't include time for a truck to return after delivery

Truck_Type Truck::getTruckType()
{
	return Ttype;
};//type of truck getter.

int Truck::getID()
{
	return ID;
};//getter for ID


//METHODS
bool Truck::isFull()
{
	return CurCapacity == Capacity;
};//checks if the truck is full(max capacity) 

bool Truck::AssignCargo(Cargo * CargoToAssign)
{
	if (isFull())//if full return false
		return false;
	AssignedCargos.enqueue(CargoToAssign, -CargoToAssign->getDeliveryDistance());
	//add the cargo to the array
	CurAssignedCargos = AssignedCargos.getSize();
	return true;//succesfully assigned

};//Assign cargo to Truck

void Truck::CalculateDeliveryTime()
{

	
}//calculates DT and set el data member

bool Truck::NeedsRepairing()
{
	return currentJourneyCount % J == 0;
};//return journeycount % J;

void  Truck::CalculateTruckUtlization(int SimTime)
{
	TruckUtlization=((TotalCargosDel / (Capacity * currentJourneyCount) * (activeTime * SimTime)));
};//Calculated the percentage



//SETTERS
void Truck::setCapacity(int TCap)
{
	Capacity = TCap;
};//capacity setter.

void Truck::setSpeed(int speed)
{
	if (speed > 0)//validation for Time to be Postive
	{
		this->speed = speed;
	}
	else//else throw exception
	{
		//throw Exception
	}
};//speed setter.


void Truck::setJ(int j)
{
	if (j > 0)//validation for Time to be Postive
	{
		J = j;
	}
	else//else throw exception
	{
		//throw Exception
	}
	
};//Number of journeys after which the Truck needs maintenance setter (J)

PQ<Cargo*>* Truck::getAssignedList() {
	return &AssignedCargos;
}



ostream& operator<<(ostream& os, Truck& t) {
	os << t.getID();
	if (t.getTruckType() == NT)
		os << "[";
	else if (t.getTruckType() == VT)
		os << "{";
	else if (t.getTruckType() == ST)
		os << "(";
	PQ<Cargo*>* l = t.getAssignedList();
	Cargo* c;
	LLQ<Cargo*> tempq;
	while (l->dequeue(c)) {
		tempq.enqueue(c);
		if (l->isEmpty()) {
			os << c->getID();
			break;
		}
		os << c->getID() << ",";
	}
	while (tempq.dequeue(c))
		t.AssignCargo(c);

	if (t.getTruckType() == NT)
		os << "]";
	else if (t.getTruckType() == VT)
		os << "}";
	else if (t.getTruckType() == ST)
		os << ")";
	return os;
}