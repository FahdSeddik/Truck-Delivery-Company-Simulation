#include "Truck.h"
Truck::Truck(int CAP, int SPEED, int JBM, Truck_Type TT,int Id)
{
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
	loadtime = 0;
	LastReturnTime = -1;
	furthestDistance = -1;
	LastDist = 0;
}//constructor.

Truck::~Truck()
{
	
}//def destructor.


//GETTERS

int Truck::getCurrentJourneyCount()
{
	return currentJourneyCount;
};//Number of Current journeys


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
}//ID getter.

int Truck::getMoveTime()
{
	return MoveTime;
}//move time getter.

int Truck::getNextDT()
{
	return nextDT;
}//next distance getter.

int Truck::getLastReturnTime()
{
	return LastReturnTime;
};//last return time getter.


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
}//assigned cargos getter.

void Truck::UpdateLastReturnTime(int LastReturn)
{
	LastReturnTime = LastReturn;
}//update last return time.

void Truck::setMoveTime(int time)
{
	MoveTime = time;
	Cargo* c;
	LLQ<Cargo*> temq;
	while (AssignedCargos.dequeue(c)) //update all movetimes of cargos
	{
		c->setMoveTime(time);
		temq.enqueue(c);//temq
	}
	while (temq.dequeue(c))//reassign cargos
		AssignCargo(c);
}//move time setter.

void Truck::incrementActiveTime(int time)
{
	activeTime += time;
}//increment active time.

//METHODS
bool Truck::isFull()
{
	return AssignedCargos.getSize() == Capacity;
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


bool Truck::NeedsRepairing()
{
	return ((currentJourneyCount % J) == 0);
};//return journeycount % J;

float Truck::CalculateTruckUtlization(int SimTime)
{
	if (currentJourneyCount == 0)
		return 0;
	return (((float)TotalCargosDel / (Capacity * currentJourneyCount) * ((float)activeTime / SimTime)));
}//calculartes utlization.

int Truck::CalcLoadTime() //calculates the load interval (not absolute)
{
	LLQ<Cargo*> temq;
	Cargo* c;
	int lt=0;
	while (AssignedCargos.dequeue(c))
	{
		lt += c->getLoad_Unload_Time();
		temq.enqueue(c);
	}
	while (temq.dequeue(c))
	{
		AssignCargo(c);
	}
	loadtime = lt;
	return lt;
}
int Truck::CalcNextDT(int GT) //calculates absolute next delivery time
{
	Cargo* c;
	if (AssignedCargos.peekFront(c))
		nextDT = GT + (c->getDeliveryDistance() - LastDist) / speed + c->getLoad_Unload_Time();
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
		LastDist = c->getDeliveryDistance();
		C->AppendDeliveredCargo(c);
		TotalCargosDel++;
		if(AssignedCargos.isEmpty())
			activeTime += Global_Time - MoveTime + loadtime; //increment active time
		return true;
	}
	//if no cargos to deliver and reach nextDT then this means truck has returned to company
	currentJourneyCount++;
	furthestDistance = -1;
	LastDist = 0;
	return false;
}
;//Calculated the percentage

bool Truck::isEmpty() 
{
	return AssignedCargos.getSize() == 0;
}//to return true if no assigned cargos

//operator overloading.
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

