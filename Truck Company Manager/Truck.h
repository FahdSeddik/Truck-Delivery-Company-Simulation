#include <iostream>
#pragma once
 //general abstract Truck class
class Truck
{
protected:
	int capacity;//Number of cargos Truck can carry to be fully loaded.
	int maintenanceTime;//checkup time needed after j number of journeys.
	int speed;//speed of the Truck (KM/hour).
	int deliveryInterval;//time needed to deliver all cargos.
public:
	Truck(){};//def constructor.
	virtual~Truck(){};//def constructor.
	virtual void setCapacity(int TCap)=0;//capacity setter.
	virtual void setMaintenanceTime(int MTime)=0;//maintenanceTime setter.
	virtual void setSpeed(int speed)=0;//speed setter.
	virtual int getCapacity()=0;//capacity getter.
	virtual	int getMaintenanceTime()=0;//maintenanceTime getter.
	virtual int getSpeed()=0;//speed getter.
	virtual void display()=0;//display data.
};