#pragma once
#include <iostream>
#include <string>
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
	void Print();

	//TODO: takes a truck list copy and its name
	//prints it with appropriate format
	void PrintTruckList();

	//TODO: take a cargo list copy and its name
	//prints it with appropriate format
	void PrintCargoList();
};

