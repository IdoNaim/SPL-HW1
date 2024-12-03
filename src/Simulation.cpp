#include "../include/Simulation.h"
#include "../include/Action.h"
#include <iostream>
using namespace std;


Simulation::Simulation(const string &configFilePath){
    //TODO: finish method
}

void Simulation::start(){
    cout<<"The simulation has started"<<endl;
    isRunning = true;
//TODO: finish method
}

void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy){
    Plan p(this->planCounter,settlement,selectionPolicy,this->facilitiesOptions);
    this->plans.push_back(p);

    AddPlan* a = new AddPlan(settlement.getName(), selectionPolicy->toString());
    addAction(a);
  //  delete a; 
  //dont know if needed

}

void Simulation::addAction(BaseAction *action){
    this->actionsLog.push_back(action);
}

bool Simulation::addSettlement(Settlement *settlement);

bool Simulation::addFacility(FacilityType facility);

bool Simulation::isSettlementExists(const string &settlementName);

Settlement & Simulation::getSettlement(const string &settlementName);

Plan & Simulation::getPlan(const int planID);

void Simulation::step();

void Simulation::close();

void Simulation::open();