#pragma once
#include "Event.h"
class CancellationEvent :
    public Event
{
public:
    CancellationEvent(int eventtime, int id, char state = 'X'); //constructor
    ~CancellationEvent(); //destructor

    //execute function
    virtual void Execute(Company* pComp);
};

