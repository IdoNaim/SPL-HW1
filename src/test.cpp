
#include "../include/Settlement.h"

#include <iostream>

using namespace std;


int main(int argc, char** argv){
    SettlementType t(SettlementType::VILLAGE);
    cout<< "made type"<< endl;
    Settlement s("shlomi",t);
    string k =s.toString();
    cout<< k<< endl;
    return 0;
}