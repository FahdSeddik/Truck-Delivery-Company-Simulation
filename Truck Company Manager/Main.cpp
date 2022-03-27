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

//instantiate company object 
//call update


//TODO @GASER
/*
*   Method Update() in truck to call UpdateStatus() at end of implementation
    Method in trucks to return cargo list
    Method in trucks to return delivered cargos and clear them when delivered 
    add truck status data member to take enum implemented in INFO.h 
    truck status data member would be updated when method Update is called in truck from company

*/

/*@Ayman
* STEP BY STEP
UI.DisplayTruck(Truck *) to print ID[cid,cid,cid] 3ala 7asab cout<<truck->getID()<<"["<<truck->getCargoID(i)   ]

*/

int main()
{
    cout << "amr ashf 3tya el 3twy" << endl;

    Company TC; //truck company instantiation
    while (TC.UpdateAll());


}

