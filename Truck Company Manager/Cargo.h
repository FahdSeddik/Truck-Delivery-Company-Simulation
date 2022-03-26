#pragma once
#include <iostream>
#include "INFO.h"
//general abstract Cargo class
class Cargo
{
private:

	//time when the cargo is ready to be assigned to truck stored in hours
	int prepTime; 
	//time to load/unload cargo to/from the truck.
	int load_Unload_Time;
	//the distance (in kilometers) from the company to the delivery location of the cargo.
	int deliveryDistance;
	//the cost of delivering the cargo
	int Cost;
	//cargo type
	Cargo_Type Ctype;


	
	//SETTERS
	void setload_Unload_Time(int LTime);//load/Unload Time setter.
	void setDeliveryDistance(int DDistance);//DeliveryDistance setter.
	void setCost(int cost);//cost setter.

public:

	Cargo(int PREPT, int LOADTIME,int DELIVERYDIST, int COST, Cargo_Type CT);//def constructor.
	~Cargo();//def destructor.


	//GETTERS
	int getLoad_Unload_Time();//load/Unload Time getter.
	int getDeliveryDistance();//DeliveryDistance getter.
	int getcost();//cost getter.


};