#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"

class MySteppingAction : public G4UserSteppingAction
{

public:
    MySteppingAction();
    ~MySteppingAction();

    void UserSteppingAction(const G4Step* step);

};

#endif