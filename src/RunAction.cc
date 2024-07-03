#include "RunAction.hh"

#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

namespace Detectors
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
{
  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);

  // Create analysis manager
  // The choice of the output format is done via the specified
  // file extension.
  auto analysisManager = G4AnalysisManager::Instance();

  // Create directories
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);

  // Book histograms, ntuple
  //

  // Creating histograms
  analysisManager->CreateH1("ShowerLongProfile" ,"Shower Longitudinal Profile", nnumberOfBins, 0., 50.);
  
  // Creating ntuple
  analysisManager->CreateNtuple("Detector", "Simulation results");
  analysisManager->CreateNtupleDColumn("TotEnergyDeposit");
  analysisManager->CreateNtupleDColumn("EnergyDeposit5X0");
  analysisManager->CreateNtupleDColumn("EnergyDeposit4MolRad^2");
  analysisManager->CreateNtupleDColumn("ElectronEnergy");
  analysisManager->CreateNtupleDColumn("PositronEnergy");
  analysisManager->CreateNtupleDColumn("PhotonEnergy");
  analysisManager->CreateNtupleDColumn("NElectron");
  analysisManager->CreateNtupleDColumn("NPositron");
  analysisManager->CreateNtupleDColumn("NPhoton");

  analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  G4String fileName = "detectors.root";

  analysisManager->OpenFile(fileName);
  G4cout << "Using " << analysisManager->GetType() << G4endl;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{ 
  // print histogram statistics
  //
  auto analysisManager = G4AnalysisManager::Instance();
  
  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}