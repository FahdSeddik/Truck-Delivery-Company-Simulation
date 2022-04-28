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
	string ReadFileName(string io);


	//TODO: takes copies of all lists
	//calls other print methods
	void Print(int time,LLQ<Cargo*>& wn,LLQ<Cargo*>& ws,PQ<Cargo*>&wv, string& dn, string& dv, string& ds,LLQ<Truck*>& an, LLQ<Truck*>& av, LLQ<Truck*>& as
	, PQ<Truck*>& l,PQ<Truck*>& uc,PQ<Truck*>& m,int del,int n);
};

