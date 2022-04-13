#include "Truck.h"
Truck::Truck(int CAP, int SPEED, int JBM, Truck_Type TT,int Id)
{
	CurCapacity = 0;
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
}
int Truck::getMoveTime()
{
	return MoveTime;
}
int Truck::getNextDT()
{
	return 0;
}
int Truck::getFinishCheck()
{
	return 0;
}
int Truck::getLastReturnTime()
{
	return 0;
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
}
void Truck::setMoveTime(int time)
{
}
//METHODS
bool Truck::isFull()
{
	return CurCapacity == Capacity;
};//checks if the truck is full(max capacity) 

bool Truck::AssignCargo(Cargo * CargoToAssign)
{
	if (isFull())//if full return false
		return false;
	if (NeedsRepairing())
		return false;
	AssignedCargos.enqueue(CargoToAssign, -CargoToAssign->getDeliveryDistance());
	//add the cargo to the array
	CurAssignedCargos++;//incrementing current Assigned Cargos Count by 1
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

void  Truck::CalculateTruckUtlization(int SimTime)
{
	TruckUtlization=((TotalCargosDel / (Capacity * currentJourneyCount) * (activeTime * SimTime)));
}
int Truck::CalcNextDT()
{

	return 0;
}
bool Truck::Update(Company* C, int Global_Time)
{
	return false;
}
;//Calculated the percentage



//SETTERS
void Truck::setCapacity(int TCap)
{
	if (TCap > 0)//validation for Capacity to be Postive
	{
		Capacity = TCap;
	}
	else//else throw exception
	{
		//throw Exception
	}
	
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
