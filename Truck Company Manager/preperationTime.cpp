#include "preperationTime.h"
preperationTime::preperationTime()
{

}//def constructor.
preperationTime::~preperationTime()
{

}//def constructor.
void preperationTime::setHour(int h)
{
	hour = h;
}//hour setter
void  preperationTime::setDay(int d)
{
	day = d;
}//Day setter
int  preperationTime::getHour()
{
	return hour;
}//hour getter
int  preperationTime::getDay()
{
	return day;
}//day getter
void preperationTime::display()
{
	std::cout << getDay();
	std::cout << ":";
	std::cout << getHour() << std::endl;
}//display data