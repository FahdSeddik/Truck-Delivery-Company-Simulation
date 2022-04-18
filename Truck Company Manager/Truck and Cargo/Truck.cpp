#include "Truck.h"
Truck::Truck(int CAP, int SPEED, int JBM, Truck_Type TT,int Id)
{
	deliveryInterval = 0;
	currentJourneyCount = 0;
	CurAssignedCargos = 0;
	activeTime = 0;
	TotalCargosDel = 0;
	Capacity = CAP;
	speed = SPEED;
	J = JBM;
	Ttype = TT;
	ID = Id;
	MoveTime = -1;
	nextDT = -1;
	LastReturnTime = -1;
}//constructor.

Truck::~Truck()
{
	
}//def destructor.


//GETTERS
int Truck::getCapacity()
{
	return Capacity;
};//capacity getter.



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
}
int Truck::getMoveTime() //doesnt calculate
{
	return MoveTime;
}
int Truck::getNextDT()
{
	return nextDT;
}
int Truck::getFinishCheck()
{
	return 0;
}
int Truck::getLastReturnTime()
{
	return LastReturnTime;
}
;//getter for ID

int* Truck::getCargoIDs() {
	LLQ<Cargo*> tempq;
	Cargo* c;
	int* ids = new int[CurAssignedCargos];
	int i = 0;
	while (AssignedCargos.dequeue(c)) {
		ids[i] = c->getID();
		i++;
		tempq.enqueue(c);
	}

	while (tempq.dequeue(c))
		AssignCargo(c);

	return ids;
}
void Truck::UpdateLastReturnTime(int LastReturn)
{
	LastReturnTime = LastReturn;
}
void Truck::setMoveTime(int time)
{
	MoveTime = time;
}
void Truck::incrementActiveTime(int time)
{
	activeTime += time;
}
//METHODS
bool Truck::isFull()
{
	return AssignedCargos.getSize()==Capacity;
};//checks if the truck is full(max capacity) 

bool Truck::AssignCargo(Cargo * CargoToAssign)
{
	if (!CargoToAssign)
		return false;
	if (isFull())//if full return false
		return false;
	if (CargoToAssign->getDeliveryDistance() >= furthestDistance)
		furthestDistance = CargoToAssign->getDeliveryDistance();
	AssignedCargos.enqueue(CargoToAssign, -CargoToAssign->getDeliveryDistance());
	//add the cargo to the array
	CurAssignedCargos = AssignedCargos.getSize();
	
	return true;//succesfully assigned

};//Assign cargo to Truck

//int Truck::CalculateDeliveryTime()
//{
//	return 0;
//	
//}//calculates DT and set el data member

bool Truck::NeedsRepairing()
{
	return currentJourneyCount % J == 0;
};//return journeycount % J;

int Truck::CalculateTruckUtlization(int SimTime)
{
	TruckUtlization=((TotalCargosDel / (Capacity * currentJourneyCount) * (activeTime * SimTime)));
	return TruckUtlization;
}
int Truck::CalcLoadTime() //calculates the load interval (not absolute)
{
	LLQ<Cargo*> temq;
	Cargo* c;
	int lt=0;
	while (AssignedCargos.dequeue(c)) {
		lt += c->getLoad_Unload_Time();
		temq.enqueue(c);
	}
	while (temq.dequeue(c)) {
		AssignCargo(c);
	}
	
	return lt;
}
int Truck::CalcNextDT(int GT) //calculates absolute next delivery time
{
	Cargo* c;
	if (AssignedCargos.peekFront(c))
		nextDT = GT + c->getDeliveryDistance() / speed + c->getLoad_Unload_Time();
	else if(LastReturnTime<GT){
		nextDT = furthestDistance / speed + GT;
		UpdateLastReturnTime(nextDT);
	}
	return nextDT;
}
bool Truck::Update(Company* C, int Global_Time)
{
	//if function is called then this means nextDT has come no need to check
	Cargo* c;
	if (AssignedCargos.dequeue(c)) {
		C->AppendDeliveredCargo(c);
		return true;
	}
	//if no cargos to deliver and reach nextDT then this means truck has returned to company
	return false;
}
;//Calculated the percentage



//SETTERS
void Truck::setCapacity(int TCap)
{
	Capacity = TCap;
};//capacity setter.

void Truck::setSpeed(int speed)
{
	this->speed = speed;
};//speed setter.


void Truck::setJ(int j)
{
	J = j;
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