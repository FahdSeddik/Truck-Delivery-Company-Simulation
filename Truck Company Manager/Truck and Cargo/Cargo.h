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
	
	
	//PRIVATE SETTERS TO GET INPUT IN LEGAL LIMIT(VALIDATION)
	void setload_Unload_Time(int LTime);//load/Unload Time setter.
	void setDeliveryDistance(int DDistance);//Delivery Distance setter.
	
	void setCargoType(Cargo_Type CT);//Cargo Type Setter
	//(the Time from the preration of the cargo untill its truck starts to move to deliver it (MoveTime-PrepTime))

public:

	Cargo(int PREPT, int LOADTIME, int DELIVERYDIST, int COST, Cargo_Type CT, int ID);//Non default destructor.
	~Cargo();//destructor.

	


	//PUBLIC GETTERS
	
	//GETTERS
	int getLoad_Unload_Time();//load/Unload Time getter.
	int getDeliveryDistance();//DeliveryDistance getter.
	int getcost();//cost getter.
	int getPrepTime();//getter for PrepTIme(time when the cargo is ready to be assigned to truck stored in hours).
	int getCurrWait();//getter for Current waiting time
	//(the Time from the preration of the cargo untill its truck starts to move to deliver it (MoveTime-PrepTime))
	int getWatingTime();//getter for cargo delivery time from company to the destination 
	//((MT)+(cargo distance/truck speed)+(cargo unload time))
	int getDeliveryTime();///getter cargo delivery time from company to the destination 
	//((MT)+(cargo distance/truck speed)+(cargo unload time))

	
	Cargo_Type getType();//Cargo Type getter.
	
	int getID();//getter for ID
	void setDeliveryTime(int t);
	void setCost(int cost);//cost setter.
	void setType(Cargo_Type type);
	int getTID(); // getter for TID

	
	void setTID(int id); //TID setter

	//Methods

	//TODO: to be used when a cargo is assigned to a truck to have cargo sorted in prio queue in truck
	// gets movetime passed from truck
	// assigns data member: deliveryTime with appriopriate value
	//void CalculateDeliveryTime(int MoveTime);

};