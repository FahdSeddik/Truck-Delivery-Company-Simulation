#include "CancellationEvent.h"

CancellationEvent::CancellationEvent(int eventtime, int id, char state)
{
	Time = eventtime;
	ID = id;
}

CancellationEvent::~CancellationEvent()
{
}

// TO DO: should cancel the requested normal cargo(IF FOUND!!)
void CancellationEvent::Execute(Company* pComp)
{
	pComp->CancelCargo(ID);
}
