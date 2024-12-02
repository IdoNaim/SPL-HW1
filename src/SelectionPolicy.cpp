#include "../include/SelectionPolicy.h"

NaiveSelection::NaiveSelection(): lastSelectedIndex(0){}

const FacilityType& NaiveSelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
    int t1 = this->lastSelectedIndex;
    if(this->lastSelectedIndex+1 > facilitiesOptions.size()-1){
        this->lastSelectedIndex = 0;
    }
    else{
        this->lastSelectedIndex ++;
    }
    return facilitiesOptions[t1];
}

const string NaiveSelection::toString() const{
    return "Naive Selection, last index: "+ std::to_string(this->lastSelectedIndex);
}

NaiveSelection* NaiveSelection::clone() const{
    return new NaiveSelection(*this);
}

BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore){
    
}