#pragma once
#include <vector>
#include <iostream>
#include "../include/Plan.h"
#include "../include/Facility.h"
#include "../include/Settlement.h"
#include "../include/SelectionPolicy.h"
using namespace std;
using std::vector;

        Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions)
        : plan_id(planId), settlement(settlement), selectionPolicy(selectionPolicy), facilities(),
         facilityOptions(facilityOptions), status(PlanStatus::AVALIABLE), underConstruction(),
          life_quality_score(0), economy_score(0), environment_score(0){}

        const int Plan::getlifeQualityScore() const{
            return life_quality_score;
        }
        const int Plan::getEconomyScore() const{
            return economy_score;
        }
        const int Plan::getEnvironmentScore() const{
            return environment_score;
        }
        void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy){
            this->selectionPolicy = selectionPolicy;
        }
        void Plan::step() {
            if(status == PlanStatus::AVALIABLE){
                while (underConstruction.size() < static_cast<int>(settlement.getType())) {
                    Facility* f = new Facility(selectionPolicy->selectFacility(facilityOptions), settlement.getName());
                    underConstruction.push_back(f);
                }
            }
            status = PlanStatus::BUSY;


            for (int i = 0; i < underConstruction.size(); i++ ) {
                Facility* f = underConstruction[i];
                f->step();
        
                if (f->getTimeLeft() == 0) {
                    underConstruction.erase(underConstruction.begin() + i);
                    facilities.push_back(f);
                    i--;
                }
            }

            if(underConstruction.size() != static_cast<int>(settlement.getType()))
                status = PlanStatus::AVALIABLE;

        }

        void Plan::printStatus(){
            cout << planStatusToString();
        }

        const vector<Facility*>& Plan::getFacilities() const{
            return facilities;
        }
        void Plan::addFacility(Facility* facility){
            underConstruction.push_back(facility);
        }

        const string Plan::toString() const{
            string s = "PlanID: " + to_string(plan_id) + "\n" + "SettlementName: " + settlement.getName() + "\n" +
            string("PlanStatus: ") + planStatusToString() + "Selection Policy: " + selectionPolicy->toString() + "\n" +
            "LifeQualityScore: " + to_string(life_quality_score) + "\n" + "EconomyScore: " + to_string(economy_score) + "\n" + 
            "EnvironmentScore: " + to_string(environment_score) + "\n";
            for(Facility* f : underConstruction)
                s = s + f->toString();
            for(Facility* f : facilities)
                s = s + f->toString();
            return s;
        }

        const string Plan::planStatusToString() const{
            switch (status) {
                case PlanStatus::AVALIABLE:
                    return "AVALIABLE";
                case PlanStatus::BUSY:
                    return "BUSY";
                default:
                    return "Not Possible";
            }
}
const int Plan::getId() const{
    return this->plan_id;
}