#include "TrackingAction.hh"
#include "G4TrackingManager.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Gamma.hh"

namespace Detectors{

TrackingAction::TrackingAction(EventAction* eventAction) {
    fEventAction = eventAction;
}


void TrackingAction::PostUserTrackingAction(const G4Track*) {

  G4TrackVector* secTracks = fpTrackingManager -> GimmeSecondaries();

  // You can use the secTracks vector to retrieve the number of secondary 
  // electrons
  if(secTracks) { 
     size_t nmbSecTracks = secTracks->size();       

     for(size_t i = 0; i < nmbSecTracks; i++) { 
        if((*secTracks)[i] -> GetDefinition() == G4Electron::Definition()){
            fEventAction->AddElectron();
        } else if((*secTracks)[i] -> GetDefinition() == G4Positron::Definition()){
            fEventAction->AddPositron();
        } else if((*secTracks)[i] -> GetDefinition() == G4Gamma::Definition()){
            fEventAction->AddPhoton();
        }
     }
  }
}

}
