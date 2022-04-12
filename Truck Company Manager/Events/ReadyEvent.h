#pragma once
#include "Event.h"
class ReadyEvent :
    public Event
{
protected:
    char TYP; //the cargo type
    int Dist; //the cargo distance in km
    int LT; //time to load or to unload
    int Cost; //the cost of the cargo
public:
    ReadyEvent(int eventtime, int id, char cargotype, int dist, int loadtime, int cost, char state = 'R'); //constructor 
    ~ReadyEvent();//destructor
    //setters
    virtual void SetTYP(char t);
    virtual void SetDist(int d);
    virtual void SetLT(int t);
    virtual void SetCost(int c);
    //getters
    virtual char GetTYP();
    virtual int GetDist();
    virtual int GetLT();
    virtual int GetCost();

    //execute function
    virtual void Execute(Company* C);
};

