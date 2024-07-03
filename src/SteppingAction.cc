#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Gamma.hh"
#include "G4ParticleDefinition.hh"

namespace Detectors
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(const DetectorConstruction* detConstruction,
                               EventAction* eventAction)
  : fDetConstruction(detConstruction),
    fEventAction(eventAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  // get volume of the current step
  auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  auto position = step->GetPreStepPoint()->GetPosition();
  auto particle = step->GetTrack()->GetParticleDefinition();
  // energy deposit
  auto edep = step->GetTotalEnergyDeposit();

  if ( volume == fDetConstruction->GetDetectorPV()) {

      fEventAction->AddEnergy(edep);

      if (position.getZ() <= -15*radLenght){
        fEventAction->Add5X0Energy(edep);
      }

      if(position.getX()*position.getX() + position.getY()*position.getY() <= latContainment){
        fEventAction->AddLateralEnergy(edep);
      }
      
      if(particle == G4Electron::Definition()){
        fEventAction->AddElectronEnergy(edep);
      }
      else if(particle == G4Positron::Definition()){
        fEventAction->AddPositronEnergy(edep);
      }
      else if(particle == G4Gamma::Definition()){
        fEventAction->AddPhotonEnergy(edep);
      }
      
      fEventAction->AddLongEnergy((int)(position.getZ()/(radLenght*0.5) + 40), edep);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}