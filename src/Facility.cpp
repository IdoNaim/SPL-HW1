#include "../include/Facility.h"
#include <string>
#include <vector>
using std::string;
using std::vector;
int FacilityType::getCost() const{
    return this->price;
}
int FacilityType::getEconomyScore() const{
    return this->economy_score;
}
int FacilityType::getEnvironmentScore() const{
    return this->environment_score;
}
int FacilityType::getLifeQualityScore() const{
    return this->lifeQuality_score;
}
FacilityCategory FacilityType::getCategory() const{
    return this->category;
}
const string & FacilityType::getName() const{
    return this->name;
}
FacilityType::FacilityType(const string &name, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score):name(name), category(category),price(price),lifeQuality_score(lifeQuality_score), economy_score(economy_score), environment_score(environment_score) {}

const string& Facility::getSettlementName() const{
    return this->settlementName;
}
const int Facility::getTimeLeft() const{
    return this->timeLeft;
}
const FacilityStatus& Facility::getStatus() const{
    return this->status;
}
Facility::Facility(const string &name, const string &settlementName, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score)
:FacilityType(name, category, price, lifeQuality_score, economy_score, environment_score), settlementName(settlementName) ,timeLeft(price), status(FacilityStatus::UNDER_CONSTRUCTIONS)
{}
Facility::Facility(const FacilityType &type, const string &settlementName)
:Facility(type.getName(),settlementName, type.getCategory(), type.getCost(), type.getLifeQualityScore(), type.getEconomyScore(), type.getEnvironmentScore())
{}
void Facility::setStatus(FacilityStatus status){
    this->status = status;
}
FacilityStatus Facility::step(){
    this->timeLeft --;
}
const string Facility::toString() const{
    return "FacilityName: "+ this->getName() +"\n"+ "FacilityStatus: "+ getStatusString();
}
const string Facility::getStatusString() const{
    switch(status){
        case FacilityStatus::OPERATIONAL:
            return "OPERATIONAL";
    
        case FacilityStatus::UNDER_CONSTRUCTIONS:
            return "UNDER_CONSTRUCTIONS";
        }
    }

