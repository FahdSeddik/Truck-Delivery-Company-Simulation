# Truck Delivery Company Simulation

This is a simulation of a truck delivery company written in C++. This was made as a University project in the Data Structures and Algorithms course at Faculty of Engineering, Cairo University.
#### Objects Simulated include: 
* **Cargos (3 types):** Normal, Special, VIP (N,S,V)
    1. Unique ID
    2. Delivery Distance
    3. Cost
* **Trucks (3 types):** Normal, Special, VIP (N,S,V)
    1. Unique ID
    2. Speed
    3. Capacity
    4. Repair time and number of journey before repairing
* **Events:**
    1. Ready(**R**): new cargo to deliver with type, money, deliveryDistance, loading/unloading time.
    2. Cancellation(**X**): cancel a cargo from waiting normal cargos.
    3. Promotion(**P**): promote a normal cargo paying extra money.
* **Other:**
    1. A normal cargo that waits AutoP days would get automatically promoted to VIP.
    2. A truck that waits MaxW hours without reaching full capacity would start loading and deliver.

## Input File

![image](https://user-images.githubusercontent.com/62207434/174483550-02b972bd-8262-4db4-9667-56eba157a85c.png)

## Output FIle  

![image](https://user-images.githubusercontent.com/62207434/174484238-55b510d9-3a78-4948-96e9-98d6c605afb6.png)
- **CDT:** Cargo delivery time  
- **PT:** preparation time  
- **WT:** waiting time
- **TID:** truck ID that delivered the cargo
## Interface

![image](https://user-images.githubusercontent.com/62207434/174482334-465ad491-ee5a-4c46-8d1a-9e45cc22461d.png)
  
   
#### After running the program you will have 3 modes to choose from:
* **Interactive Mode:** Would allow you to manually increment hours by pressing Enter
* **Step-by-Step Mode:** Automatically increment hours by 1 each second
* **Silent Mode:** Just produce an output file  
  
  
**You would then be asked to enter the input file's name aswell as the output file's name**  

![image](https://user-images.githubusercontent.com/62207434/174482719-714a058f-c7be-4701-9cd1-adda5155255a.png)
  


## Interactive Mode & Step-By-Step Modes

![image](https://user-images.githubusercontent.com/62207434/174482833-8945ef46-7a7f-4411-a97c-0eda1484f5c6.png)

### Items Displayed:
- Output format of a truck:  
    * TruckID [CargoID,CargoID]
    * Brackets change [] or () or {} depending on truck type (N,S,V)
    
**Current time (Day:Hour): 1:0** This implies day 1 hour 0 of the simulation  
**0 Waiting Cargos: [] () {}** 0 total number of cargos [] for normal () for special {} for VIP  
**Rest of Items are displayed similarily**

## Contributers
- @FahdSeddik
- @AbdulrahmanEl-Bedewy
- @amrashraf2001
- @gaserSami

