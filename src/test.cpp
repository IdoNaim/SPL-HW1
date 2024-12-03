#include "../include/Facility.h"
#include "../include/SelectionPolicy.h"
#include <iostream>

using namespace std;
//FacilityType::FacilityType(const string &name, const FacilityCategory category,
// const int price, const int lifeQuality_score, const int economy_score, const int environment_score){}

int main(int argc, char** argv){
    vector<FacilityType> v;
    v.push_back(FacilityType("first", FacilityCategory::LIFE_QUALITY, 1, 1,0,1));
    v.push_back(FacilityType("second", FacilityCategory::ECONOMY, 1, 0,1,0));
    v.push_back(FacilityType("third", FacilityCategory::ENVIRONMENT, 1, 0,1,0));
    v.push_back(FacilityType("fourth", FacilityCategory::LIFE_QUALITY, 50, 1,1,1));
    NaiveSelection n;
    EconomySelection e;
    BalancedSelection b(1,1,1);
    SustainabilitySelection s;
    cout<<n.selectFacility(v).getName()<<endl;
    cout<<e.selectFacility(v).getName()<<endl;
    cout<<s.selectFacility(v).getName()<<endl;
    cout<<b.selectFacility(v).getName()<<endl;
    NaiveSelection* n2 = n.clone();
    cout <<"Cloned: "+ n.toString() +", Clone: "+ n2->toString()<<endl;
    delete n2;
    cout<< n.toString() + " is still alive!"<<endl;
    return 0;
}