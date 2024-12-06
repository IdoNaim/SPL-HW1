#include "../include/Settlement.h"
using std::string;
#include <string>

Settlement::Settlement(const string &name, SettlementType type)
:name(name), type(type) {}

const string& Settlement::getName() const{
    return name;
}

SettlementType Settlement::getType() const{
    return type;
}

const string Settlement::toString() const{
    return "settlement "+ getName()+" " + std::to_string(static_cast<int>(type)-1);
}
Settlement* Settlement::clone() const{
    return new Settlement(this->getName(),this->getType());
}