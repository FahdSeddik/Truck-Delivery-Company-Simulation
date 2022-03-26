#include <iostream>
#pragma once
class preperationTime //class for time day:hour
{
	int hour;
	int day;
public:
	preperationTime();//def constructor.
	~preperationTime();//def constructor.
	void setHour(int h);//hour setter
	void setDay(int d);//Day setter
	int getHour();//hour getter
	int getDay();//day getter
	void display();//display data
};

