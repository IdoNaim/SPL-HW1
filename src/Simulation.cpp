#include "../include/Simulation.h"
using std::string;
#include <string>
using std::vector;

void start();

void addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy);

void addAction(BaseAction *action);

bool addSettlement(Settlement *settlement);
bool addFacility(FacilityType facility);
bool isSettlementExists(const string &settlementName);
Settlement &getSettlement(const string &settlementName);
Plan &getPlan(const int planID);
void step();
void close();
void open();