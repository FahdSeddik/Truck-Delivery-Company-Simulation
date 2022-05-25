#include "CancellationEvent.h"

CancellationEvent::CancellationEvent(int eventtime, int id):Event()
{
	Time = eventtime;
	ID = id;
}

CancellationEvent::~CancellationEvent()
{
}

// TO DO: calls cancel cargo in company with ID
void CancellationEvent::Execute(Company* pComp)
{
	pComp->CancelCargo(ID);
}
