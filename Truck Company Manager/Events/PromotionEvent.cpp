#include "PromotionEvent.h"


PromotionEvent::PromotionEvent(int eventtime, int id, int extramoney):Event()
{
	Time = eventtime;
	ID = id;
	ExtraMoney = extramoney;
}

PromotionEvent::~PromotionEvent()
{
}

void PromotionEvent::SetExtraMoney(int money)
{
	ExtraMoney = money;
}

int PromotionEvent::GetValueOfExtraMoney()
{
	return ExtraMoney;
}

// TO DO: should move a normal cargo to the VIP list and update the cargo's data(IF FOUND!!)
void PromotionEvent::Execute(Company* pComp)
{
	pComp->PromoteCargo(ID,ExtraMoney);
}
