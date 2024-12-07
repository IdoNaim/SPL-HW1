#include "../include/Simulation.h"
#include "../include/Action.h"
#include "../include/Auxiliary.h" 
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;



Simulation::Simulation(const string &configFilePath)
: isRunning(false), planCounter(0), actionsLog(), plans(), settlements(), facilitiesOptions() {
    ifstream config(configFilePath);
    
    if (!config.is_open()) {
        cerr << "Error: Unable to open the file at " << configFilePath << endl;
    }
    string line;
    while(getline(config,line)){
        vector<string> lineArgs = Auxiliary::parseArguments(line);
        if(lineArgs.at(0) != "#"){
            if(lineArgs.at(0) == "settlement"){
                SettlementType t = static_cast<SettlementType>(stoi(lineArgs.at(2))+1);
                this->settlements.push_back( new Settlement(lineArgs.at(1),t));
            }
            else if(lineArgs.at(0) == "facility"){
                FacilityCategory c = static_cast<FacilityCategory>(stoi(lineArgs.at(2)));
                this->facilitiesOptions.push_back(FacilityType(lineArgs.at(1), c, stoi(lineArgs.at(3)),stoi(lineArgs.at(4)),stoi(lineArgs.at(5)),stoi(lineArgs.at(6))));
            }
            else if(lineArgs.at(0) == "plan"){
                string policy =lineArgs.at(2);
                SelectionPolicy* s;
                if(policy == "nve"){
                    s = new NaiveSelection();
                }
                else if(policy == "bal"){
                    s = new BalancedSelection(0,0,0);
                }
                else if(policy == "eco"){
                    s = new EconomySelection();
                }
                else if(policy == "env"){
                    s = new SustainabilitySelection();
                }
             //   Settlement t = getSettlement(lineArgs.at(1));
               // Plan p(this->planCounter,t,s,this->facilitiesOptions);
                this->plans.push_back(Plan(this->planCounter, getSettlement(lineArgs.at(1)),s,this->facilitiesOptions));
                this->planCounter++;
            }
        }
    }
}

void Simulation::start(){
    cout<<"The simulation has started"<<endl;
    open();
    string input;
    while(isRunning){
        getline(cin,input);
        vector<string> arguments = Auxiliary::parseArguments(input);
        int size = arguments.size();
        string& command = arguments.at(0);
        if (command == "step"){
            if(size==2 && isdigit(arguments.at(1).at(0)));
            BaseAction* a = new SimulateStep(stoi(arguments.at(1)));
            a->act(*this);
            addAction(a);
        }
        else if(command == "planStatus"){
            if(size == 2 && isdigit(arguments.at(1).at(0))){
                BaseAction* a =  new PrintPlanStatus(stoi(arguments.at(1)));
                a->act(*this);
                addAction(a);

            }
        }
        else if(command == "plan"){
            if(size == 3){
                BaseAction* a = new AddPlan(arguments.at(1), arguments.at(2));
                a->act(*this);
                addAction(a);
            }
        }
        else if(command == "settlement" && size == 3 && isdigit(arguments.at(2).at(0))){
            if(stoi(arguments.at(2))>2){
                cout<< "no settlement type of type "+ arguments.at(2)<<endl;
            }
            else{
                BaseAction* a = new AddSettlement(arguments.at(1), static_cast<SettlementType>(stoi(arguments.at(2))+1));
                a->act(*this);
                addAction(a);
            }
        }
        else if(command == "facility" && size == 7){
            if(stoi(arguments.at(2)) > 2){
                cout<< "no facility type of type "+ arguments.at(2)<<endl;
            }
            else{
                BaseAction* a = new AddFacility(arguments.at(1), static_cast<FacilityCategory>(stoi(arguments.at(2))), stoi(arguments.at(3)),stoi(arguments.at(4)),stoi(arguments.at(5)),stoi(arguments.at(6)));
                a->act(*this);
                addAction(a);
            }
        }
        else if(command == "changePolicy" && size == 3){
            BaseAction* a = new ChangePlanPolicy(stoi(arguments.at(1)), arguments.at(2));
            a->act(*this);
            addAction(a);
        }
        else if(command == "log"){
            BaseAction* a = new PrintActionsLog();
            a->act(*this);
            addAction(a);
        }
        else if(command == "close"){
            BaseAction* a = new Close();
            a->act(*this);
            addAction(a);
        }
        else if(command == "backup"){
            BaseAction* a = new BackupSimulation();
            a->act(*this);
            addAction(a);
        }
        else if(command == "restore"){
            BaseAction* a = new RestoreSimulation();
            a->act(*this);
            addAction(a);
        }
    }
}
void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy){
    Plan p(this->planCounter,settlement,selectionPolicy,this->facilitiesOptions);
    this->plans.push_back(p);
    this->planCounter++;
}

void Simulation::addAction(BaseAction *action){
    this->actionsLog.push_back(action);
}

bool Simulation::addSettlement(Settlement *settlement){
    try{
        this->settlements.push_back(settlement);
        return true;
    }
    catch(const exception& e){
        return false;
    }
}

bool Simulation::addFacility(FacilityType facility){
    try{
    this->facilitiesOptions.push_back(facility);
    return true;
    }
    catch(const exception& e){
        return false;
    }
}

bool Simulation::isSettlementExists(const string &settlementName){
    bool ans = false;
    for(int i = 0; (i<static_cast<int>(settlements.size())) && !ans;i++){
        if (settlements.at(i)->getName() == settlementName){
            ans = true;
        }
    }
    return ans;
}

Settlement & Simulation::getSettlement(const string &settlementName){
    //need to implement outside of function what happens if settlement doesnt exist
    for(int i = 0; i < static_cast<int>(settlements.size());i++){
        if (settlements.at(i)->getName() == settlementName){
            return *settlements.at(i);
        }
    }
    throw std::runtime_error("Plan with the given ID does not exist");

}

bool Simulation::isPlanExists(const int planID){
    bool ans = false;
    for(int i = 0; i< static_cast<int>(plans.size()) && !ans;i++){
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
    for(int i=0; i < static_cast<int>(this->plans.size());i++){
        if(this->plans.at(i).getId()==planID){
            return plans.at(i);
        }
    }
    throw std::runtime_error("Plan with the given ID does not exist");
}

void Simulation::step(){
    for(Plan& plan : plans){
        plan.step();
    }
}

void Simulation::close(){
    for(Plan plan : plans){
        cout<<plan.toStringClose()<<endl;
    }
    this->isRunning= false;
}

void Simulation::open(){
    this->isRunning =true;
}
Simulation::~Simulation(){
    clear();
}
Simulation::Simulation(const Simulation& other): isRunning(false), planCounter(0), actionsLog(), plans(), settlements(), facilitiesOptions()
{

    for(Settlement* s: other.settlements){
        this->settlements.push_back(s->clone());
    }
    for(BaseAction* s: other.actionsLog){
        this->actionsLog.push_back(s->clone());
    }
    for(FacilityType s : other.facilitiesOptions){
        this->facilitiesOptions.push_back(s);
    }
    for(Plan s : other.plans){
        this->plans.push_back(Plan(s));
    }

}
Simulation& Simulation::operator=(const Simulation& other){
    if(this != &other){
        this->planCounter = other.planCounter;
        clear();
        
        for(BaseAction* a : other.actionsLog){
            this->actionsLog.push_back(a->clone());
        }

        for(Settlement* s : other.settlements){
            this->settlements.push_back(s->clone());
        }

        for(Plan p: other.plans){
            this->plans.push_back(Plan(p));
        }

        for(FacilityType f : other.facilitiesOptions){
            this->facilitiesOptions.push_back(FacilityType(f));
        }
    }
    return *this;
}
Simulation::Simulation(Simulation&& other):
isRunning(other.isRunning), planCounter(other.planCounter), actionsLog(std::move(other.actionsLog)), plans(std::move(other.plans)), settlements(std::move(other.settlements)), facilitiesOptions(std::move(other.facilitiesOptions)){}

Simulation & Simulation::operator=(Simulation&& other){
    if(this != &other){
        clear();
    
        this->planCounter = other.planCounter;
        this->actionsLog = std::move(other.actionsLog);
        this->facilitiesOptions = std::move(other.facilitiesOptions);
        this->plans = std::move(other.plans);
        this->settlements = std::move(other.settlements);
    }
    return *this;

}
void Simulation::clear(){
    for(BaseAction* a : this->actionsLog){
        if(a != nullptr){
            delete a;
        } 
    }
    actionsLog.clear();
    for(Settlement* s : this->settlements){
        if(s != nullptr){
            delete s;
        }
    }
    settlements.clear();
    plans.clear();
    facilitiesOptions.clear();
}

const vector<Plan>& Simulation::getPlans() const{
    return plans;
}

const vector<FacilityType>& Simulation::getFacilitiesOptions() const{
    return facilitiesOptions;
}

const vector<BaseAction*> Simulation::getActionsLog() const{
    return actionsLog;
}