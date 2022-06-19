#include <iostream>
using namespace std;
#include "Company.h"

/*
Classes:
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
    int mode = UI.getMode();
    while (TC.UpdateAll(Global_Time)) { //calls updateAll
        TC.PrintStatus(); //print
        Global_Time++;//increment global time +1 hour
    }
    if (mode == 3)
        UI.PrintSilent();
    TC.PrintStatus();//print last status after UpdateAll returned false (i.e. finish state)
    TC.WriteOutput();
       
}

