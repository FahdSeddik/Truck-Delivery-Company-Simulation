#pragma once
#include "../Company.h"
#include "../Truck and Cargo/Cargo.h"

class Company;

class Event
{
protected:
	//char State; //the state of the event P or R or X
	int Time; //the time of the event in hr
	int ID; //the ID of the cargo
public:

	//setters
	//virtual void SetState(char s);
	virtual void SetTime(int t);
	virtual void SetID(int i);
	//getters
	//virtual char GetEventState();
	virtual int GetTime();
	virtual int GetID();

	//execute function
	virtual void Execute(Company* pComp) = 0;
};

