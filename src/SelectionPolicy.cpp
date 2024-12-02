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
    return "Naive Selection, last index: "+ std::to_string(this->lastSelectedIndex);
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
        int environment = this->getEnvironmentScore() + option.getEconomyScore();
        int maximum = std::max(lifeQuality,economy,environment);
        int minimum = std::min(lifeQuality,economy,environment);
        int distance = maximum - minimum;
        if(distance < minDistance | minDistance==-1){
            minDistance = distance ;
            minIndex = i;
        }
    }
    return facilitiesOptions.at(minIndex);
}

const string BalancedSelection::toString()const{
    return "Balanced Selection, life Quality Score:  "+ std::to_string(getLifeQualityScore()) + " Economy Score: "+ std::to_string(getEconomyScore())+ " Environment Score: "+ std::to_string(getEnvironmentScore());
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

EconomySelection::EconomySelection(): lastSelectedIndex(0) {}

const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
    bool found = false;
    int index =0;
    for(int i =0; i < facilitiesOptions.size() & !found ; i++){
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
    return "Economy Selection, last index: "+ std::to_string(this->lastSelectedIndex);
}

EconomySelection* EconomySelection::clone() const{
    return new EconomySelection(*this);
}
void EconomySelection::setIndex(int index){
    this->lastSelectedIndex = index;
}

//SUSTAINABILITY SELECTION

SustainabilitySelection::SustainabilitySelection(): lastSelectedIndex(0) {}

const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
    bool found = false;
    int index =0;
    for(int i =0; i < facilitiesOptions.size() & !found ; i++){
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
    return "Sustainability Selection, last index: "+ std::to_string(this->lastSelectedIndex);
}

SustainabilitySelection* SustainabilitySelection::clone() const{
    return new SustainabilitySelection(*this);
}
void SustainabilitySelection::setIndex(int index){
    this->lastSelectedIndex = index;
}
