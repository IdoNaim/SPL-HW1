#include "../include/Simulation.h"
#include "../include/Action.h"
#include <iostream>
#include <sstream>
using namespace std;


Simulation::Simulation(const string &configFilePath)
: isRunning(false), planCounter(0), actionsLog(), plans(), settlements(), facilitiesOptions() {
}

void Simulation::start(){
    cout<<"The simulation has started"<<endl;
    open();
    string input;
    while(isRunning){
        getline(cin,input);
        vector<string>& arguments = split(input);
        int size = arguments.size();
        string& command = arguments.at(0);
        if (command == "step"){
            if(size==2 && isdigit(arguments.at(1).at(0)));
            BaseAction* a = new SimulateStep(stoi(arguments.at(1)));
            a->act(*this);
        }
        else if(command == "planStatus"){
            if(size == 2 && isdigit(arguments.at(1).at(0))){
                BaseAction* a =  new PrintPlanStatus(stoi(arguments.at(1)));
                a->act(*this);
            }
        }
        else if(command == "plan"){
            if(size == 3){
                BaseAction* a = new AddPlan(arguments.at(1), arguments.at(2));
                a->act(*this);
            }
        }
        else if(command == "settlement" && size == 3 && isdigit(arguments.at(2).at(0))){
            if(stoi(arguments.at(2))>2){
                cout<< "no settlement type of type "+ arguments.at(2)<<endl;
            }
            else{
                BaseAction* a = new AddSettlement(arguments.at(1), static_cast<SettlementType>(stoi(arguments.at(2))));
                a->act(*this);
            }
        }
        else if(command == "facility" && size == 7){
            if(stoi(arguments.at(2)) > 2){
                cout<< "no facility type of type "+ arguments.at(2)<<endl;
            }
            else{
                BaseAction* a = new AddFacility(arguments.at(1), static_cast<FacilityCategory>(stoi(arguments.at(2))), stoi(arguments.at(3)),stoi(arguments.at(4)),stoi(arguments.at(5)),stoi(arguments.at(6)));
                a->act(*this);
            }
        }
        else if(command == "changePolicy" && size == 3){
            BaseAction* a = new ChangePlanPolicy(stoi(arguments.at(1)), arguments.at(2));
            a->act(*this);
        }
        else if(command == "log"){
            BaseAction* a = new PrintActionsLog();
            a->act(*this);
        }
        else if(command == "close"){
            BaseAction* a = new Close();
            a->act(*this);
        }
        else if(command == "backup"){
            BaseAction* a = new BackupSimulation();
            a->act(*this);
        }
        else if(command == "restore"){
            BaseAction* a = new RestoreSimulation();
            a->act(*this);
        }
    }
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
    for(Plan plan : plans){
        plan.step();
    }
}

void Simulation::close(){
    for(Plan plan : plans){
        cout<<plan.toString()<<endl;
    }
    this->isRunning= false;
}

void Simulation::open(){
    this->isRunning =true;
}

vector<string>& Simulation::split(const string& input) {
    istringstream iss(input);
    vector<string> tokens;
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}