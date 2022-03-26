#pragma once
#include "Truck.h"
//Normal Truck class
class NormalTruck :public Truck
{
	public:
	NormalTruck();//def constructor.
	virtual~NormalTruck();//def destructor.
	virtual void setCapacity(int TCap);//capacity setter.
	virtual void setMaintenanceTime(int MTime);//maintenanceTime setter.
	virtual void setSpeed(int speed);//speed setter.
	virtual int getCapacity();//capacity getter.
	virtual	int getMaintenanceTime();//maintenanceTime getter.
	virtual int getSpeed();//speed getter.
	virtual void display();//display data.
};