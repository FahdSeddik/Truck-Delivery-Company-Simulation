#pragma once
#include <iostream>
#include <string>
#include "../DS/LLQ.h"
#include "../DS/PQ.h"
#include "../DS/MaxHeap.h"
class Company;
class Cargo;
class Truck;

using namespace std;
class UI_Class
{
private:
	int mode; // Decides the mode of the program interface
	
	void PrintWaiting(Company* pComp)const;
	void PrintLoading(Company* pComp)const;
	void PrintEmpty(Company* pComp)const;
	void PrintMoving(Company* pComp,int n)const;
	void PrintInCheckUp(Company* pComp)const;
	void PrintDelivered(string dn,string dv,string ds,int del)const;
public:
	UI_Class();
	string ReadFileName(string io);
	void PrintSilent()const;
	//TODO: takes copies of all lists
	//calls other print methods
	void Print(Company* pComp, string& dn, string& dv, string& ds,int del,int n)const;
	int getMode()const;
};

