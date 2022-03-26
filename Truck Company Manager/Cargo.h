#include <iostream>
#include "preperationTime.h"
#pragma once
//general abstract Cargo class
class Cargo
{
protected:
	preperationTime prepTime; //time when the cargo is ready to be assigned to truck day:hour
	int load_Unload_Time;//time to load/unload cargo to/from the truck.
	int deliveryDistance;//the distance (in kilometers) from the company to the delivery location of the cargo.
	int Cost;//the cost of delivering the cargo
public:
	Cargo() {};//def constructor.
	virtual~Cargo() {};//def constructor.
	virtual void setPreperationTime(int day,int hour) = 0;//PreperationTime setter.
	virtual void setload_Unload_Time(int LTime) = 0;//load/Unload Time setter.
	virtual void setDeliveryDistance(int DDistance) = 0;//DeliveryDistance setter.
	virtual void setCost(int cost) = 0;//cost setter.
	virtual preperationTime getPreperationTime() = 0;//PreperationTime getter.
	virtual	int getLoad_Unload_Time() = 0;//load/Unload Time getter.
	virtual int getDeliveryDistance() = 0;//DeliveryDistance getter.
	virtual int getcost() = 0;//cost getter.
	virtual void display() = 0;//display data.
};