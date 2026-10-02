#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4GenericMessenger.hh"
#include "G4Material.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

private:
    void DefineMaterial();

    G4Box *solidWorld, *solidRadiator, *solidDetector;
    G4LogicalVolume *logicWorld, *logicRadiator, *logicDetector;
    G4VPhysicalVolume *physWorld, *physRadiator, *physDetector;

    G4GenericMessenger *fMessenger;

    G4Material *SiO2, *H2O, *Aerogel, *worldMat;

    G4int nCols;
    G4int nRows;
};

#endif