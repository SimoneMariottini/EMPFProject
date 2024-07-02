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
/// \file B4/B4a/include/SteppingAction.hh
/// \brief Definition of the B4a::SteppingAction class

#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "G4SystemOfUnits.hh"

namespace Detectors
{

/// Stepping action class.
///
/// In UserSteppingAction() we collecte the energy deposit
/// charged particles in Detector layer and
/// updated in EventAction.

class SteppingAction : public G4UserSteppingAction
{
public:
  SteppingAction(const DetectorConstruction* detConstruction,
                 EventAction* eventAction);
  ~SteppingAction() override = default;

  void UserSteppingAction(const G4Step* step) override;

private:
  const DetectorConstruction* fDetConstruction = nullptr;
  EventAction* fEventAction = nullptr;

  G4double radLenght = 1.86*cm;
  G4double molierRad = 3.531*cm;
  G4double latContainment = 49.871844*cm*cm;
};

}
#endif
