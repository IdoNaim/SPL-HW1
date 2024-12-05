#pragma once
#include <vector>
#include <iostream>
#include "../include/Plan.h"
#include "../include/Facility.h"
#include "../include/Settlement.h"
#include "../include/SelectionPolicy.h"
#include "../include/Action.h"
#include "../include/Simulation.h"
using namespace std;
using std::vector;
extern Simulation* backup;

        BaseAction::BaseAction()
        : errorMsg(""), status(ActionStatus:: ERROR){}

        ActionStatus BaseAction::getStatus() const{
            return status;
        }
        void BaseAction::complete(){
            status = ActionStatus::COMPLETED;
        }
        void BaseAction::error(string errorMsg){
            status = ActionStatus::ERROR;
            this->errorMsg = ("Error: " + errorMsg);
        }
        const string& BaseAction::getErrorMsg() const{
            return errorMsg;
        }

        SimulateStep::SimulateStep(const int numOfSteps): BaseAction(), numOfSteps(numOfSteps){}

        void SimulateStep::act(Simulation &simulation){
            for(int i=0;i<numOfSteps;i++)
                simulation.step();
            complete();
        }

        const string SimulateStep::toString() const{
            return "step " + to_string(numOfSteps);
        }

        SimulateStep* SimulateStep::clone() const{
            SimulateStep* s = new SimulateStep(numOfSteps);
            return s;
        }

        AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy): BaseAction(),
        settlementName(settlementName),selectionPolicy(selectionPolicy){}

        void AddPlan::act(Simulation &simulation){
            if(simulation.isSettlementExists(settlementName)){
                Settlement& s = simulation.getSettlement(settlementName);
                if(selectionPolicy == "nve"){
                    NaiveSelection* nve = new NaiveSelection();
                    simulation.addPlan(s,nve);
                    complete();
                }
                else if(selectionPolicy == "bal"){
                    BalancedSelection* bal = new BalancedSelection(0,0,0);
                    simulation.addPlan(s,bal);
                    complete();
                    }
                    else if(selectionPolicy == "eco"){
                        EconomySelection* eco = new EconomySelection();
                        simulation.addPlan(s,eco);
                        complete();
                        }
                        else if(selectionPolicy == "env"){
                            SustainabilitySelection* env = new SustainabilitySelection();
                            simulation.addPlan(s,env);
                            complete();
                            }
                            else
                            error("Cannot create this plan");

            }
            else
            error("Cannot create this plan");
        }
        const string AddPlan::toString() const{
            return "plan " + settlementName + " " + selectionPolicy;
        }
        AddPlan* AddPlan::clone() const{
            string newName = settlementName;
            AddPlan* cloneAddPlan = new AddPlan(newName, selectionPolicy);
            return cloneAddPlan;
        }

        AddSettlement::AddSettlement(const string &settlementName,SettlementType settlementType)
        : BaseAction(), settlementName(settlementName), settlementType(settlementType) {}

        void AddSettlement::act(Simulation &simulation){
            if(!simulation.isSettlementExists(settlementName)){
                Settlement* s = new Settlement(settlementName, settlementType);
                simulation.addSettlement(s);
                complete();
            }
            else
                error("Settlement already exists");
        }
        AddSettlement* AddSettlement::clone() const{
            string newName = settlementName;
            AddSettlement* as = new AddSettlement(newName, settlementType);
            return as;
        }
        const string AddSettlement::toString() const{
            return "settlement " + settlementName + " " + to_string(static_cast<int>(settlementType));
        }

        AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore)
        : BaseAction(), facilityName(facilityName), facilityCategory(facilityCategory), price(price),
        lifeQualityScore(lifeQualityScore), economyScore(economyScore), environmentScore(environmentScore) {}

        void AddFacility::act(Simulation &simulation){
            for(FacilityType f : simulation.getFacilitiesOptions()){
                if(f.getName() == facilityName)
                    error("Facility already exists");
            }
            FacilityType f(facilityName,facilityCategory,price,lifeQualityScore,economyScore,environmentScore);
            simulation.addFacility(f);
            complete();
        }
        AddFacility* AddFacility::clone() const{
            string newName = facilityName;
            AddFacility* af = new AddFacility(newName,facilityCategory,price,lifeQualityScore,economyScore,environmentScore);
            return af;
        }
        const string AddFacility::toString() const{
            return "facility " + facilityName + " " + to_string(static_cast<int>(facilityCategory)) + " " + to_string(price)
            + " " + to_string(lifeQualityScore) + " " + to_string(economyScore) + " " + to_string(environmentScore);
        }

        PrintPlanStatus::PrintPlanStatus(int planId): BaseAction(), planId(planId) {}

        void PrintPlanStatus::act(Simulation &simulation){
            if(simulation.isPlanExists(planId)){
                simulation.getPlan(planId).toString();
                complete();
            }
            else
                error("Plan doesn't exist");
        }
        PrintPlanStatus* PrintPlanStatus::clone() const{
            PrintPlanStatus* pps = new PrintPlanStatus(planId);
            return pps;
        }
        const string PrintPlanStatus::toString() const{
            return "planStatus " + to_string(planId);
        }

        ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy): BaseAction(), planId(planId), newPolicy(newPolicy) {}

        void ChangePlanPolicy::act(Simulation &simulation){
            if(!simulation.isPlanExists(planId))
                error("Cannot change selection policy");
            else if(simulation.getPlan(planId).getSelectionPolicy()->toString() == newPolicy)
                    error("Cannot change selection policy");
                    else{
                        if(newPolicy == "nve"){
                            SelectionPolicy* s = new NaiveSelection();
                            simulation.getPlan(planId).setSelectionPolicy(s);
                        }
                        else if(newPolicy == "bal"){
                            SelectionPolicy* s = new BalancedSelection(simulation.getPlan(planId).getlifeQualityScore(),simulation.getPlan(planId).getEconomyScore(),simulation.getPlan(planId).getEnvironmentScore());
                            simulation.getPlan(planId).setSelectionPolicy(s);
                            }
                                else if(newPolicy == "eco"){
                                        SelectionPolicy* s = new EconomySelection();
                                        simulation.getPlan(planId).setSelectionPolicy(s);
                                        }
                                        else if(newPolicy == "env"){
                                            SelectionPolicy* s = new SustainabilitySelection();
                                            simulation.getPlan(planId).setSelectionPolicy(s);
                                            }
                        complete();
                        }
        }
        ChangePlanPolicy* ChangePlanPolicy::clone() const{
            string newName = newPolicy;
            ChangePlanPolicy* cpp = new ChangePlanPolicy(planId, newName);
            return cpp;
        }
        const string ChangePlanPolicy::toString() const{
            return "changePolicy " + to_string(planId) + newPolicy;
        }




        PrintActionsLog::PrintActionsLog(): BaseAction(){}

        const string PrintActionsLog::statusToString(ActionStatus status) {
            switch (status) {
                case ActionStatus::ERROR: return "ERROR";
                case ActionStatus::COMPLETED: return "COMPLETED";
                default: return "Not Possible";
                }
        }

        void PrintActionsLog::act(Simulation &simulation){
            for(BaseAction* a : simulation.getActionsLog()){
                if (!dynamic_cast<PrintActionsLog*>(a))
                    cout << a->toString() << " " << statusToString(a->getStatus()) << endl;
            }
            complete();
        }
        PrintActionsLog* PrintActionsLog::clone() const{
            PrintActionsLog* pal = new PrintActionsLog();
            return pal;
        }
        const string PrintActionsLog::toString() const{
            return "log";
        }

        Close::Close(): BaseAction() {}

        void Close::act(Simulation &simulation){
            simulation.close();
            complete();
        }

        Close* Close::clone() const{
            Close* c = new Close();
            return c;
        }
        const string Close::toString() const{
            return "close";
        }

        BackupSimulation::BackupSimulation(): BaseAction() {}
        void BackupSimulation::act(Simulation &simulation){
            backup = new Simulation(simulation);
            complete();
        }
        BackupSimulation* BackupSimulation::clone() const{
            BackupSimulation* bs = new BackupSimulation();
            return bs;
        }
        const string BackupSimulation::toString() const{
            return "backup";
        }


        RestoreSimulation::RestoreSimulation(): BaseAction() {}

        void RestoreSimulation::act(Simulation &simulation){
            if(!(backup == nullptr)){
                simulation = *backup;
            }
            else
                error("No backup available");
        }
        RestoreSimulation* RestoreSimulation::clone() const{
            RestoreSimulation* rs = new RestoreSimulation();
            return rs;
        }
        const string RestoreSimulation::toString() const{
            return "restore";
        }