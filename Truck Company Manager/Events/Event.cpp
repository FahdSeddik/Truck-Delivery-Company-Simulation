#include "Event.h"

void Event::SetID(int i)
{
	ID = i;
}

void Event::SetState(char s)
{
	State = s;
}

void Event::SetTime(int t)
{
	Time = t;
}

char Event::GetEventState()
{
	return State;
}

int Event::GetID()
{
	return ID;
}


int Event::GetTime()
{
	return Time;
}
