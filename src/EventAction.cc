#include "EventAction.hh"
#include "RunAction.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

namespace Detectors
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{
  // initialisation per event
  fEnergyDetector = 0.;
  fEnergy5X0Detector = 0.;
  fLateralEnergy = 0.;
  fEnergyElectron = 0.;
  fEnergyPositron = 0.;
  fEnergyPhoton = 0.;
  fElectronCounter = 0;
  fPositronCounter = 0;
  fPhotonCounter = 0; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{ 
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( printModulo > 0 && eventID % printModulo == 0 ) {
    G4cout << "----------> Total Energy Deposit = " << fEnergyDetector << G4endl;
    G4cout << "----------> Fraction of Energy Deposit in 5X0 = " << fEnergy5X0Detector << G4endl;
    G4cout << "----------> Fraction of Energy Deposit within 4*MolRad^2 = " << fLateralEnergy << G4endl;
    G4cout << "----------> Electron Energy Deposit = " << fEnergyElectron << G4endl;
    G4cout << "----------> Positron Energy Deposit = " << fEnergyPositron << G4endl;
    G4cout << "----------> Photon Energy Deposit = " << fEnergyPhoton << G4endl;
    G4cout << "----------> Number of secondary Electrons = " << fElectronCounter << G4endl;
    G4cout << "----------> Number of secondary Positrons = " << fPositronCounter << G4endl;
    G4cout << "----------> Number of secondary Photon = " << fPhotonCounter << G4endl;
  }

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  
  analysisManager->FillNtupleDColumn(0, fEnergyDetector);
  analysisManager->FillNtupleDColumn(1, fEnergy5X0Detector);
  analysisManager->FillNtupleDColumn(2, fLateralEnergy);
  analysisManager->FillNtupleDColumn(3, fEnergyElectron);
  analysisManager->FillNtupleDColumn(4, fEnergyPositron);
  analysisManager->FillNtupleDColumn(5, fEnergyPhoton);
  analysisManager->FillNtupleDColumn(6, fElectronCounter);
  analysisManager->FillNtupleDColumn(7, fPositronCounter);
  analysisManager->FillNtupleDColumn(8, fPhotonCounter);
  
  analysisManager->AddNtupleRow();

  for(int i = 0; i < nnumberOfBins; i++){
    for(int j = 0; j < (int)fLongEnergyDeposit[i]; j++){
      analysisManager->FillH1(0, i/2. + 0.25);
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

}