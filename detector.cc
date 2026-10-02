#include "detector.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"

MySensitiveDetector::MySensitiveDetector(G4String name)
    : G4VSensitiveDetector(name)
{
}

MySensitiveDetector::~MySensitiveDetector()
{
}

G4bool MySensitiveDetector::ProcessHits(
    G4Step* aStep,
    G4TouchableHistory*)
{

    G4Track* track = aStep->GetTrack();


    track->SetTrackStatus(fStopAndKill);


    G4StepPoint* preStepPoint = aStep->GetPreStepPoint();

    G4ThreeVector posPhoton = preStepPoint->GetPosition();
    const G4VTouchable* touchable =preStepPoint->GetTouchable();

    G4int copyNo = touchable->GetCopyNumber();
    G4int eventID =
        G4RunManager::GetRunManager()
            ->GetCurrentEvent()
            ->GetEventID();

    G4cout << "Photon position: "<< posPhoton<< G4endl;

    G4cout << "Detector copy number: "<< copyNo<< G4endl;
    auto analysisManager =
        G4AnalysisManager::Instance();
        analysisManager->FillNtupleIColumn( 0, eventID);

    analysisManager->FillNtupleDColumn(1, posPhoton.x());

    analysisManager->FillNtupleDColumn(2, posPhoton.y());

    analysisManager->FillNtupleDColumn(3, posPhoton.z());

    analysisManager->AddNtupleRow();

    return true;
}