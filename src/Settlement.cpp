#include "../include/Settlement.h"
using std::string;
#include <string>
const string& Settlement::getName() const{
    return this->name;
}
SettlementType Settlement::getType() const{
    return this->type;
}
const string Settlement::toString() const{
    return "settlement "+ getName()+" " + getTypeNum();
}
const string Settlement::getTypeNum() const{
    switch(type){
        case SettlementType::VILLAGE:
            return "0";
        case SettlementType::CITY:
            return "1";
        case SettlementType::METROPOLIS:
            return "2";
    }
}