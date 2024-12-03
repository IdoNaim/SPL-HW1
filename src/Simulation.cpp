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
    this->planCounter++;
  //  delete a; 
  //dont know if needed

}

void Simulation::addAction(BaseAction *action){
    this->actionsLog.push_back(action);
}

bool Simulation::addSettlement(Settlement *settlement){
    this->settlements.push_back(settlement);
}

bool Simulation::addFacility(FacilityType facility){
    this->facilitiesOptions.push_back(facility);
}

bool Simulation::isSettlementExists(const string &settlementName){
    bool ans = false;
    for(int i = 0; i<settlements.size() & !ans;i++){
        if (settlements.at(i)->getName() == settlementName){
            ans = true;
        }
    }
    return ans;
}

Settlement & Simulation::getSettlement(const string &settlementName){
    //need to implement outside of function what happens if settlement doesnt exist
    for(int i = 0; i<settlements.size();i++){
        if (settlements.at(i)->getName() == settlementName){
            return *settlements.at(i);
        }
    }
    
}

bool Simulation::isPlanExists(const int planID){
    bool ans = false;
    for(int i = 0; i<plans.size() & !ans;i++){
        if (plans.at(i).getId() == planID){
            ans = true;
        }
    }
    return ans;
}
Plan & Simulation::getPlan(const int planID){
    //if(!isPlanExists(planID)){
    //    throw std::runtime_error("Plan doesn't exist");
    //} need to be implemented outside of function
    for(int i=0; i<this->plans.size();i++){
        if(this->plans.at(i).getId()==planID){
            return plans.at(i);
        }
    }
}

void Simulation::step(){
    
}

void Simulation::close();

void Simulation::open();