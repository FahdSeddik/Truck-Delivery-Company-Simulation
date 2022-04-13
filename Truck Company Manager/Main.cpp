#include <iostream>
using namespace std;
#include "Company.h"

/*
Classes to be developed:
1- Event Classes (Event Abstract)
        - Preparation
        - Cancel
        - Promote
2- Cargo and Truck Classes

3- Company Class

4- UI Class

*/


int main()
{
    
    UI_Class UI;
    Company TC(&UI); //truck company instantiation
    int Global_Time = 0; //global time in hours

    while (TC.UpdateAll(Global_Time)) {
        TC.PrintStatus();
        Global_Time++;
    }

    TC.WriteOutput();
       
}

