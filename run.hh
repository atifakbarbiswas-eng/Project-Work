#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4run.hh"

class G4Run;

class MyRunAction : public G4UserRunAction
{
public:
    MyRunAction();
    virtual ~MyRunAction();

    virtual void BeginOfRunAction(const G4Run*) override;
    virtual void EndOfRunAction(const G4Run*) override;
};

#endif