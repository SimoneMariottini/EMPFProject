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
/// \file B4/B4a/src/EventAction.cc
/// \brief Implementation of the B4a::EventAction class

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
  fEnergyElectron = 0.;
  fEnergyPositron = 0.;
  fEnergyPhoton = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{ 
  G4cout << "----------> Total Energy Deposit = " << fEnergyDetector << G4endl;
  G4cout << "----------> Fraction of Energy Deposit in 5X0 = " << fEnergy5X0Detector << G4endl;
  G4cout << "----------> Electron Energy Deposit = " << fEnergyElectron << G4endl;
  G4cout << "----------> Positron Energy Deposit = " << fEnergyPositron << G4endl;
  G4cout << "----------> Photon Energy Deposit = " << fEnergyPhoton << G4endl;
  
  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  
  analysisManager->FillNtupleDColumn(0, fEnergyDetector);
  analysisManager->FillNtupleDColumn(1, fEnergy5X0Detector);
  analysisManager->FillNtupleDColumn(2, fEnergyElectron);
  analysisManager->FillNtupleDColumn(3, fEnergyPositron);
  analysisManager->FillNtupleDColumn(4, fEnergyPhoton);
  analysisManager->FillNtupleDColumn(5, fElectronN);
  analysisManager->FillNtupleDColumn(6, fPositronN);
  analysisManager->FillNtupleDColumn(7, fPhotonN);
  
  analysisManager->AddNtupleRow();

  for(int i = 0; i < nnumberOfBins; i++){
    for(int j = 0; j < (int)fLongEnergyDeposit[i]; j++){
      analysisManager->FillH1(0, i/2. + 0.25);
    }
  }
  /*
  // Print per event (modulo n)
  //
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
    G4cout
      << "   Fiber: total energy: " << std::setw(7)
                                        << G4BestUnit(fEnergyTot,"Energy")
      << "       total track length: " << std::setw(7)
                                        << G4BestUnit(fTrackLTot,"Length")
      << G4endl;
    G4cout << "--> End of event " << eventID << "\n" << G4endl;       
  }*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

}