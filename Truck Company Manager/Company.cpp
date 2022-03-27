#include "Company.h"
#include <iostream>
using namespace std;



//TODO: READ FROM INPUT FILE CALLED ONLY IN CONSTRUCTOR
void ReadFile();


//TODO: ASSIGNS CARGOS TO TRUCKs OF ITS TYPE OR BASED ON DOCUMENT RULES
// moves cargos from waiting to moving
// returns false if there are no available cargos to assign (ie. empty cargo list)
bool AssignCargos();


//TODO: calls Update of each truck and event
// Calls AssignCargos()
// moves cargos/trucks across lists
// Calls ExecuteEvent()
void UpdateAll();

//TODO: to be used in update in case an event is to be done 
// simply can be Ready::Execute for example
void ExecuteEvent();