#include "Truck.h"
Truck::Truck(int CAP, int MAINT, int SPEED, int JBM, Truck_Type TT)
{
	CurCapacity = 0;
	deliveryInterval = 0;
	currentJourneyCount = 0;
	CurAssignedCargos = 0;
	MoveTime = 0;
	activeTime = 0;
	TotalCargosDel = 0;
	TotalDeliveryJour = 0;
	TotalSimTime=0;
	Capacity = CAP;
	maintenanceTime = MAINT;
	speed = SPEED;
	J = JBM;
	Ttype = TT;
	AssignedCargos = new Cargo*[Capacity];//allocating array of max Capacity Size
}//constructor.

Truck::~Truck()
{
	
}//def destructor.

Truck::Truck(Truck& T)
{
	Capacity=T.Capacity;
	maintenanceTime=T.maintenanceTime;
	speed=T.speed;
	J=T.J;
	Ttype=T.Ttype;
	CurCapacity=T.CurCapacity;
	deliveryInterval = T.deliveryInterval;
	currentJourneyCount=T.currentJourneyCount;
	T.AssignedCargos = new Cargo * [Capacity];//allocating a newarray of max Capacity Size for the copied object
	CurAssignedCargos=T.CurAssignedCargos;
	MoveTime=T.MoveTime;
	activeTime=T.activeTime;
	TruckUtlization=T.TruckUtlization;		
	TotalCargosDel=T.TotalCargosDel;
	TotalDeliveryJour=T.TotalDeliveryJour;
	TotalSimTime = T.TotalSimTime;
};//copy constructor

//GETTERS
int Truck::getCapacity()
{
	return Capacity;
};//capacity getter.

int Truck::getCurCapacity()
{
	return CurCapacity;
};//Current capacity getter.

int Truck::getMaintenanceTime()
{
	return maintenanceTime;
};//maintenanceTime getter.


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

int Truck::getMoveTime()
{
	return MoveTime;

};//getter for the time at which the truck carrying the cargo starts to move deliver the cargo.

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
	AssignedCargos[CurAssignedCargos] = CargoToAssign;//add the cargo to the array
	CurAssignedCargos++;//incrementing current Assigned Cargos Count by 1
	return true;//succesfully assigned

};//Assign cargo to Truck

void Truck::CalculateDeliveryTime()
{
	int furthestDeliveryTime = -9999;//getting the furthest delivery to calculate deliveryInterval
								//setting initialy with a verylow value to get max(futhest delivery time)

	int totalUnLoadingTime = 0;//total UnLoading Time of the cargos
	for (int i = 0; i < getCurrentAssignedCargosCount(); i++)
	{
		if ((AssignedCargos[i]->getDeliveryDistance()) > furthestDeliveryTime)//getting the furthest delivery to calculate deliveryInterval
			furthestDeliveryTime = AssignedCargos[i]->getDeliveryDistance();

		totalUnLoadingTime = totalUnLoadingTime + AssignedCargos[i]->getLoad_Unload_Time();
	}
	//deliveryInterval=(Delivery distance of the furthest cargo/truck speed)+sum of unload times of 
	//all its cargos+time to come back(Delivery distance of the furthest cargo)
	deliveryInterval = ((furthestDeliveryTime / speed) + totalUnLoadingTime + furthestDeliveryTime);
}//calculates DT and set el data member

bool Truck::NeedsRepairing()
{
	return currentJourneyCount % J;
};//return journeycount % J;

void  Truck::CalculateTruckUtlization()
{
	TruckUtlization=((TotalCargosDel / (Capacity * TotalDeliveryJour) * (activeTime * TotalSimTime)));
};//Calculated the percentage

void Truck::update()
{
	//TODO
};//update status of the truck



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

void Truck::setMaintenanceTime(int MTime)
{
	if (MTime > 0)//validation for Time to be Postive
	{
		maintenanceTime = MTime;
	}
	else//else throw exception
	{
		//throw Exception
	}
};//maintenanceTime setter.

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
