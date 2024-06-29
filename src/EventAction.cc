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
  for(int i = 0; i < NLAYERS; i++){
    fEnergyTot = 0.;
    fTrackLTot = 0.;
    fEnergyFibers[i] = 0.;
    fTrackLFibers[i] = 0.;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  if(fEnergyFibers[0] != 0. && fEnergyFibers[NLAYERS - 1] != 0.){
    G4int i = 0;
    // fill histograms
    analysisManager->FillH1(i, fEnergyTot);
    analysisManager->FillNtupleDColumn(i, fEnergyTot);

    i++;
    analysisManager->FillH1(i, fTrackLTot);
    analysisManager->FillNtupleDColumn(i, fTrackLTot);

    for(int j = 0; j < NLAYERS; j++){
      i++;
      analysisManager->FillH1(i, fEnergyFibers[j]);
      analysisManager->FillNtupleDColumn(i, fEnergyFibers[j]);
      i++;
      analysisManager->FillH1(i, fTrackLFibers[j]);
      analysisManager->FillNtupleDColumn(i, fTrackLFibers[j]);
    }
    
    analysisManager->AddNtupleRow();

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
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

}