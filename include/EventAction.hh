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
/// \file B4/B4a/include/EventAction.hh
/// \brief Definition of the B4a::EventAction class

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

namespace Detectors
{
  #define NLAYERS 16

/// Event action class
///
/// It defines data members to hold the energy deposit and track lengths
/// of charged particles in Absober and Gap layers:
/// - fEnergyAbs, fEnergyGap, fTrackLAbs, fTrackLGap
/// which are collected step by step via the functions
/// - AddAbs(), AddGap()

class EventAction : public G4UserEventAction
{
  public:
    EventAction() = default;
    ~EventAction() override = default;

    void   BeginOfEventAction(const G4Event* event) override;
    void   EndOfEventAction(const G4Event* event) override;

    void AddEnergy(G4double de);
    void Add5X0Energy(G4double de);
    void AddLateralEnergy(G4double de);
    void AddElectronEnergy(G4double de);
    void AddPositronEnergy(G4double de);
    void AddPhotonEnergy(G4double de);
    void AddLongEnergy(G4int i, G4double de);
    void AddElectron() {fElectronCounter++;};
    void AddPositron() {fPositronCounter++;};
    void AddPhoton() {fPhotonCounter++;};

  private:
    G4double fEnergyDetector = 0.;
    G4double fEnergy5X0Detector = 0.;
    G4double fLateralEnergy = 0.;
    G4double fEnergyElectron = 0.;
    G4double fEnergyPositron = 0.;
    G4double fEnergyPhoton = 0.;
    G4double fLongEnergyDeposit[100] = {0.};
    G4int fElectronCounter = 0;
    G4int fPositronCounter = 0;
    G4int fPhotonCounter = 0; 
};

// inline functions

inline void EventAction::AddEnergy(G4double de) {
  fEnergyDetector += de;
}

inline void EventAction::Add5X0Energy(G4double de) {
  fEnergy5X0Detector += de;
}

inline void EventAction::AddLateralEnergy(G4double de) {
  fLateralEnergy += de;
}

inline void EventAction::AddElectronEnergy(G4double de) {
  fEnergyElectron += de;
}

inline void EventAction::AddPositronEnergy(G4double de) {
  fEnergyPositron += de;
}

inline void EventAction::AddPhotonEnergy(G4double de) {
  fEnergyPhoton += de;
}

inline void EventAction::AddLongEnergy(G4int i, G4double de) {
  fLongEnergyDeposit[i] += de;
}



}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif


