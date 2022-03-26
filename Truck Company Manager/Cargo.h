#pragma once
#include <iostream>
#include "INFO.h"
//GENERAL CARGO CLASS
class Cargo
{
private:
	//DATA MEMBERS TO BE TAKEN FROM INPUT FILE
	int load_Unload_Time;//time to load/unload cargo to/from the truck.
	int deliveryDistance;//the distance (in kilometers) from the company to the delivery location of the cargo.
	int Cost;//the cost of delivering the cargo.
	Cargo_Type Ctype;//cargo type.
	int MaxWait;//max wait Time
	int autoP;//maximum wating days in hours


	//DATA MEMBERS NOT TAKEN FROM INPUT FILE
	int prepTime; //time when the cargo is ready to be assigned to truck stored in hours.
	bool IsAssigned;//check if Cargo is assigned
	int CurrWait;//Current wating time
	int watingTime;//the Time from the preration of the cargo untill its truck starts to move to deliver it 
	//(MoveTime-PrepTime)
	int deliveryTime;//cargo delivery time from company to the destination 
					 //((MT)+(cargo distance/truck speed)+(cargo unload time))

	
	//PRIVATE SETTERS TO GET INPUT IN LEGAL LIMIT(VALIDATION)
	void setload_Unload_Time(int LTime);//load/Unload Time setter.
	void setDeliveryDistance(int DDistance);//Delivery Distance setter.
	void setCost(int cost);//cost setter.
	void setCargoType(Cargo_Type CT);//Cargo Type Setter
	void setMaxWait(int MW);//Max wait setter
	void setAutoP(int AP);//setter for AUTOP
	//(the Time from the preration of the cargo untill its truck starts to move to deliver it (MoveTime-PrepTime))

public:

	Cargo(int MAXWAIT, int LOADTIME, int DELIVERYDIST, int COST, Cargo_Type CT, int AUTOP);//Non default destructor.
	~Cargo();//destructor.
	Cargo(Cargo& c);//copy constructor

	//METHODS
	void AssignToTruck(bool stat);//mark cargo as assigned (isAssigned=true)


	//PUBLIC GETTERS
	int getLoad_Unload_Time();//load/Unload Time getter.
	int getDeliveryDistance();//DeliveryDistance getter.
	int getcost();//cost getter.
	int getPrepTime();//getter for PrepTIme(time when the cargo is ready to be assigned to truck stored in hours).
	bool isAssigned();//getter for status of cargo (is assigned or not)
	int getMaxWait();//getter for Max waiting time
	int getCurrWait();//getter for Current waiting time
	int getAutoP();//getter for AUTOP
	//(the Time from the preration of the cargo untill its truck starts to move to deliver it (MoveTime-PrepTime))
	int getWatingTime();//getter for cargo delivery time from company to the destination 
	//((MT)+(cargo distance/truck speed)+(cargo unload time))
	int getDeliveryTime();///getter cargo delivery time from company to the destination 
	//((MT)+(cargo distance/truck speed)+(cargo unload time))
	Cargo_Type getType();//Cargo Type getter.

};