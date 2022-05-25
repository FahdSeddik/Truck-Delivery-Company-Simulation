#include "ReadyEvent.h"

ReadyEvent::ReadyEvent(int eventtime, int id, Cargo_Type cargotype, int dist, int loadtime, int cost) :Event()
{
	Time = eventtime;
	ID = id;
	TYP = cargotype;
	Dist = dist;
	LT = loadtime;
	Cost = cost;
}

ReadyEvent::~ReadyEvent()
{
}

void ReadyEvent::SetTYP(Cargo_Type t)
{
	TYP = t;
}

void ReadyEvent::SetDist(int d)
{
	Dist = d;
}

void ReadyEvent::SetLT(int t)
{
	LT = t;
}

void ReadyEvent::SetCost(int c)
{
	Cost = c;
}


char ReadyEvent::GetTYP()
{
	return TYP;
}

int ReadyEvent::GetDist()
{
	return Dist;
}

int ReadyEvent::GetLT()
{
	return LT;
}

int ReadyEvent::GetCost()
{
	return Cost;
}

//TO DO :should create a new cargo and call appendwaitingcargo in company
void ReadyEvent::Execute(Company* pComp)
{
	Cargo* pC = new Cargo(Time, LT, Dist, Cost, TYP, ID);
	pComp->AppendWaitingCargo(pC);
}

