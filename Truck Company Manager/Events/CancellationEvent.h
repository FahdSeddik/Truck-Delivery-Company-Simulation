#pragma once
#include "Event.h"
class CancellationEvent :
    public Event
{
public:
    CancellationEvent(int eventtime, int id); //constructor
    ~CancellationEvent(); //destructor

    //execute function
    virtual void Execute(Company* pComp);
};

