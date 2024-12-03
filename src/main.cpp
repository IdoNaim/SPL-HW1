//#include "Simulation.h"
#include "../include/Facility.h"
#include <iostream>

using namespace std;

//Simulation* backup = nullptr;

int main(int argc, char** argv){
    FacilityType g("hello", FacilityCategory::ECONOMY, 1,1,1,1);
    FacilityCategory a = g.getCategory();
    cout<<"sigma"<<endl;
    /*if(argc!=2){
        cout << "usage: simulation <config_path>" << endl;
        return 0;
    }
    string configurationFile = argv[1];
    Simulation simulation(configurationFile);
    simulation.start();
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }*/
    return 0;
}