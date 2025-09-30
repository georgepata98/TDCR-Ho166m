#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"
#include "G4VUserPhysicsList.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProductionCutsTable.hh"
#include "G4EmParameters.hh"

// #include "G4EmStandardPhysics_option4.hh"
#include "G4EmPenelopePhysics.hh"
// #include "G4EmLivermorePhysics.hh"

/*#include "FTFP_BERT.hh"
#include "G4OpticalPhysics.hh"
#include "G4PhysListFactory.hh"*/

class MyPhysicsList : public G4VModularPhysicsList
{
public:
    MyPhysicsList();
    ~MyPhysicsList() override;
    
    void SetCuts();
};

#endif
