#include "Cargo.h"
#pragma once
class NormalCargo:public Cargo
{
public:
	NormalCargo();//def constructor.
	virtual~NormalCargo();//def destructor.
	virtual void setPreperationTime(int day, int hour);//PreperationTime setter.
	virtual void setload_Unload_Time(int LTime);//load/Unload Time setter.
	virtual void setDeliveryDistance(int DDistance);//DeliveryDistance setter.
	virtual void setCost(int cost);//cost setter.
	virtual preperationTime getPreperationTime();//PreperationTime getter.
	virtual	int getLoad_Unload_Time();//load/Unload Time getter.
	virtual int getDeliveryDistance();//DeliveryDistance getter.
	virtual int getcost();//cost getter.
	virtual void display();//display data.
};

