#pragma once
#include <iostream>
#include "../INFO.h"
//GENERAL CARGO CLASS
class Cargo
{
private:
	//DATA MEMBERS TO BE TAKEN FROM INPUT FILE
	int load_Unload_Time;//time to load/unload cargo to/from the truck.
	int deliveryDistance;//the distance (in kilometers) from the company to the delivery location of the cargo.
	int Cost;//the cost of delivering the cargo.
	int ID; //unique ID for cargo.
	int TID; // ID of the truck that delived the cargo
	Cargo_Type Ctype;//cargo type.
	


	//DATA MEMBERS NOT TAKEN FROM INPUT FILE
	int prepTime; //time when the cargo is ready to be assigned to truck stored in hours.
	int watingTime;//the Time from the preration of the cargo untill its truck starts to move to deliver it 
	//(MoveTime-PrepTime)
	int deliveryTime;//cargo delivery time from company to the destination 
					 //((MT)+(cargo distance/truck speed)+(cargo unload time))
	int moveTime;
	
	//PRIVATE SETTERS TO GET INPUT IN LEGAL LIMIT(VALIDATION)
	void setload_Unload_Time(int LTime);//load/Unload Time setter.
	void setDeliveryDistance(int DDistance);//Delivery Distance setter.
	
	

public:

	Cargo(int PREPT, int LOADTIME, int DELIVERYDIST, int COST, Cargo_Type CT, int ID);//Non default constructor.
	~Cargo();//destructor.

	//PUBLIC SETTERS

	//SETTERS
	void setMoveTime(int t);
	void setDeliveryTime(int t);
	void setCost(int cost);//cost setter.
	void setType(Cargo_Type type);
	void setTID(int id); //TID setter

	//PUBLIC GETTERS
	
	//GETTERS
	int getLoad_Unload_Time();//load/Unload Time getter.
	int getDeliveryDistance();//DeliveryDistance getter.
	int getcost();//cost getter.
	int getPrepTime();//getter for PrepTime(time when the cargo is ready to be assigned to truck stored in hours).
	int getWatingTime();//the Time from the preparation of the cargo untill its truck starts to move to deliver it 
	//(MoveTime-PrepTime))
	int getDeliveryTime();///getter cargo delivery time from company to the destination 
	//((MT)+(cargo distance/truck speed)+(cargo unload time))
	Cargo_Type getType();//Cargo Type getter.
	int getID();//getter for ID
	int getTID(); // getter for TID

	int getPrio()const;

	bool operator>(Cargo Right) {
		int rPrio = Right.getPrio();
		if (getPrio() > rPrio)return true;
		else return false;
	}
	bool operator<(Cargo Right) {
		int rPrio = Right.getPrio();
		if (getPrio() < rPrio)return true;
		else return false;
	}
	bool operator==(Cargo Right) {
		int rPrio = Right.getPrio();
		if (getPrio() == rPrio)return true;
		else return false;
	}
};