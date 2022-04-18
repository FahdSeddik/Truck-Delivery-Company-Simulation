#pragma once
#include "Event.h"
#include "../Company.h"


class Company; //forward declaration
class Event; //forward declaration

class CancellationEvent :
    public Event
{
public:
    CancellationEvent(int eventtime, int id); //constructor
    ~CancellationEvent(); //destructor

    //execute function
    virtual void Execute(Company* pComp);
};

