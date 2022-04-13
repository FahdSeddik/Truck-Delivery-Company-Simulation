#pragma once
#include <iostream>
#include <string>
#include "../DS/LLQ.h"
#include "../DS/PQ.h"

class Cargo;
class Truck;

using namespace std;
class UI_Class
{
private:
	int mode; // Decides the mode of the program interface
	bool pSilent; //to know if in silent mode and already printed info
public:
	UI_Class();
	string ReadFileName();


	//TODO: takes copies of all lists
	//calls other print methods
	void Print(int time,LLQ<Cargo*> wn,LLQ<Cargo*> ws,PQ<Cargo*>wv,LLQ<Cargo*> dc,LLQ<Truck*> an, LLQ<Truck*> av, LLQ<Truck*> as
	, PQ<Truck*> ln, PQ<Truck*> lv, PQ<Truck*> ls,PQ<Truck*> uc,PQ<Truck*> m);

	//TODO: takes a truck list copy and its name
	//prints it with appropriate format
	void PrintTruckList(LLQ<Truck*>& tl);
	void PrintTruckListP(PQ<Truck*>& tl);
	//TODO: take a cargo list copy and its name
	//prints it with appropriate format
	void PrintCargoList(LLQ<Cargo*>& cl);
	void PrintCargoListP(PQ<Cargo*>& cl);
};

