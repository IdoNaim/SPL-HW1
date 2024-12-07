#include "../include/SelectionPolicy.h"
using std::string;
#include <string>
using std::vector;

//NAIVE SELECTION

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
    return "nve";
}

NaiveSelection* NaiveSelection::clone() const{
    return new NaiveSelection(*this);
}

// BALANCED SELECTION

BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore): LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore){

}

const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    int minIndex =-1;
    int minDistance = -1;
    for (int i =0; i < facilitiesOptions.size() & minDistance != 0; i++) {
        FacilityType option = facilitiesOptions.at(i);
        int lifeQuality =this->getLifeQualityScore() + option.getLifeQualityScore();
        int economy = this->getEconomyScore() + option.getEconomyScore();
        int environment = this->getEnvironmentScore() + option.getEnvironmentScore();
        int maximum = std::max(lifeQuality,std::max(economy,environment));
        int minimum = std::min(lifeQuality,std::min(economy,environment));
        int distance = maximum - minimum;
        if(distance < minDistance | minDistance==-1){
            minDistance = distance ;
            minIndex = i;
        }
    }
    this->LifeQualityScore = LifeQualityScore +facilitiesOptions[minIndex].getLifeQualityScore();
    this->EconomyScore = EconomyScore + facilitiesOptions[minIndex].getEconomyScore();
    this->EnvironmentScore = EnvironmentScore + facilitiesOptions[minIndex].getEnvironmentScore();
    return facilitiesOptions.at(minIndex);
}


const string BalancedSelection::toString()const{
    return "bal";
}

BalancedSelection* BalancedSelection::clone()const{
    return new BalancedSelection(*this);
}

int BalancedSelection::getLifeQualityScore() const{
    return this->LifeQualityScore;
}

int BalancedSelection::getEconomyScore() const{
    return this->EconomyScore;
}

int BalancedSelection::getEnvironmentScore() const{
    return this->EnvironmentScore;
}

// ECONOMY SELECTION

EconomySelection::EconomySelection(): lastSelectedIndex(-1) {}

const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
    bool found = false;
    int index =0;
    for(int i = lastSelectedIndex+1 ; i != lastSelectedIndex & !found ; i=(i+1)%facilitiesOptions.size()){
        const FacilityType& option = facilitiesOptions.at(i);
        if (option.getCategory() == FacilityCategory::ECONOMY){
            found = true;
            index = i;
        }
    }
    setIndex(index);
    return facilitiesOptions.at(index);
}


const string EconomySelection::toString() const{
    return "eco";
}

EconomySelection* EconomySelection::clone() const{
    return new EconomySelection(*this);
}
void EconomySelection::setIndex(int index){
    this->lastSelectedIndex = index;
}

//SUSTAINABILITY SELECTION

SustainabilitySelection::SustainabilitySelection(): lastSelectedIndex(-1) {}

const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
    bool found = false;
    int index =0;
    for(int i =lastSelectedIndex+1; i !=lastSelectedIndex & !found ; i=(i+1)%facilitiesOptions.size()){
        const FacilityType& option = facilitiesOptions.at(i);
        if (option.getCategory() == FacilityCategory::ENVIRONMENT){
            found = true;
            index = i;
        }
    }
    setIndex(index);
    return facilitiesOptions.at(index);
}

const string SustainabilitySelection::toString() const{
    return "env";
}

SustainabilitySelection* SustainabilitySelection::clone() const{
    return new SustainabilitySelection(*this);
}
void SustainabilitySelection::setIndex(int index){
    this->lastSelectedIndex = index;
}
