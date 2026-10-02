#include "run.hh"

#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"


MyRunAction::MyRunAction()
    : G4UserRunAction()
{
    auto analysisManager = G4AnalysisManager::Instance();

    analysisManager->SetVerboseLevel(1);

    // -------------------------------------------------
    // Ntuple for detector hit information
    // -------------------------------------------------

    analysisManager->CreateNtuple("Hits", "Detector Hits");

    analysisManager->CreateNtupleIColumn("fEvent");
    analysisManager->CreateNtupleDColumn("fX");
    analysisManager->CreateNtupleDColumn("fY");
    analysisManager->CreateNtupleDColumn("fZ");

    analysisManager->FinishNtuple();
}

MyRunAction::~MyRunAction()
{
}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    G4cout << "=========================================" << G4endl;
    G4cout << "Run " << run->GetRunID() << " started" << G4endl;
    G4cout << "Number of events: "
           << run->GetNumberOfEventToBeProcessed()
           << G4endl;
    G4cout << "=========================================" << G4endl;

    auto analysisManager = G4AnalysisManager::Instance();

    // Create a different ROOT file for each run
    G4int runID = run->GetRunID();
    G4String fileName = "output" + std::to_string(runID) + ".root";

    analysisManager->SetFileName(fileName);
    analysisManager->OpenFile();
}

void MyRunAction::EndOfRunAction(const G4Run* run)
{
    auto analysisManager = G4AnalysisManager::Instance();

    analysisManager->Write();
    analysisManager->CloseFile();

    if (!IsMaster())
        return;

    G4int numberOfEvents = run->GetNumberOfEvent();

    G4cout << G4endl;
    G4cout << "=========================================" << G4endl;
    G4cout << "Run " << run->GetRunID() << " completed." << G4endl;
    G4cout << "Processed events : "
           << numberOfEvents << G4endl;
    G4cout << "Output file      : "
           << analysisManager->GetFileName()
           << G4endl;
    G4cout << "=========================================" << G4endl;
}