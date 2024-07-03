#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

namespace Detectors
{

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


