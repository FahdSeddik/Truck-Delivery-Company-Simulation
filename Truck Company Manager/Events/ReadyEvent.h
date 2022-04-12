#pragma once
#include "Event.h"
class ReadyEvent :
    public Event
{
protected:
    Cargo_Type TYP; //the cargo type
    int Dist; //the cargo distance in km
    int LT; //time to load or to unload
    int Cost; //the cost of the cargo
public:
    ReadyEvent(int eventtime, int id, Cargo_Type cargotype, int dist, int loadtime, int cost); //constructor 
    ~ReadyEvent();//destructor
    //setters
    virtual void SetTYP(Cargo_Type t);
    virtual void SetDist(int d);
    virtual void SetLT(int t);
    virtual void SetCost(int c);
    //getters
    virtual char GetTYP();
    virtual int GetDist();
    virtual int GetLT();
    virtual int GetCost();

    //execute function
    virtual void Execute(Company* pComp);
};

