#pragma once
#include "Event.h"
class PromotionEvent :
    public Event
{
protected:
    int ExtraMoney; // money needed to promote
public:
    PromotionEvent(int eventtime, int id, int extramoney, char c = 'P'); //constructor
    ~PromotionEvent(); //destructor
    virtual void SetExtraMoney(int money); //setter
    virtual int GetValueOfExtraMoney();//getter
     //execute function
    virtual void Execute();
};

