#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "G4SystemOfUnits.hh"

namespace Detectors
{

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
