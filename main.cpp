#include <iostream>
#include <cstdio>
#include "traffic_system.h"
#include <thread>

int main()
{
    TrafficSystem ts("C:\\My Projects\\Traffic_System_CPP_v3\\test.txt");
    while(true)
    {
        ts.addCars();
        ts.showTrafficSystem();
        Sleep(1000);
    }
    return 0;
}
