#pragma once
#include "Event.h"


class Event; //forward declaration

class PromotionEvent :
    public Event
{
protected:
    int ExtraMoney; // money needed to promote
public:
    PromotionEvent(int eventtime, int id, int extramoney); //constructor
    ~PromotionEvent(); //destructor
    virtual void SetExtraMoney(int money); //setter
    virtual int GetValueOfExtraMoney();//getter
     //execute function
    virtual void Execute(Company* pComp);
};

