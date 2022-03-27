#pragma once
#include <iostream>
#include <string>
using namespace std;
class UI_Class
{
private:
	int mode; // Decides the mode of the program interface
public:
	UI_Class();
	string ReadFileName();
	void Print();
};

