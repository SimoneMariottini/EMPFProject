//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B4/B4a/src/RunAction.cc
/// \brief Implementation of the B4::RunAction class

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
    // Note: merging ntuples is available only with Root output

  // Book histograms, ntuple
  //

  // Creating histograms
  analysisManager->CreateH1("ShowerLongProfile" ,"Shower Longitudinal Profile", nnumberOfBins, 0., 50.);
  
  // Creating ntuple
  analysisManager->CreateNtuple("Detector", "Simulation results");
  analysisManager->CreateNtupleDColumn("TotEnergyDeposit");
  analysisManager->CreateNtupleDColumn("EnergyDeposit5X0");
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
  /*
  if ( analysisManager->GetH1(1) ) {
    G4cout << G4endl << " ----> print histograms statistic ";
    if(isMaster) {
      G4cout << "for the entire run " << G4endl << G4endl;
    }
    else {
      G4cout << "for the local thread " << G4endl << G4endl;
    }

    G4int i = 0;

    G4cout << " Etot : mean = "
       << G4BestUnit(analysisManager->GetH1(i)->mean(), "Energy")
       << " rms = "
       << G4BestUnit(analysisManager->GetH1(i)->rms(),  "Energy") << G4endl;

    i++;
    G4cout << " Ltot : mean = "
      << G4BestUnit(analysisManager->GetH1(i)->mean(), "Length")
      << " rms = "
      << G4BestUnit(analysisManager->GetH1(i)->rms(),  "Length") << G4endl; 

      for(int j = 0; j < NLAYERS; j++){
        i++;
        G4cout << " E " + to_string(j) + " : mean = "
          << G4BestUnit(analysisManager->GetH1(i)->mean(), "Energy")
          << " rms = "
          << G4BestUnit(analysisManager->GetH1(i)->rms(),  "Energy") << G4endl;

        i++;
        G4cout << " L " + to_string(j) + " : mean = "
          << G4BestUnit(analysisManager->GetH1(i)->mean(), "Length")
          << " rms = "
          << G4BestUnit(analysisManager->GetH1(i)->rms(),  "Length") << G4endl; 
      }    
  }
  */
  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}