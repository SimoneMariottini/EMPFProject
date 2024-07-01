
/////////////////////////////////////////////////////////////////////////
// G4Tutorial:
//
// UserTrackingAction.hh
// 
// Defining actions performed at the start/end point of processing a
// track
//
/////////////////////////////////////////////////////////////////////////


#include "UserTrackingAction.hh"
#include "G4TrackingManager.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Gamma.hh"


UserTrackingAction::UserTrackingAction() :
    electron_counter(0), positron_counter(0), photon_counter(0) {

}


void UserTrackingAction::PostUserTrackingAction(const G4Track*) {

  // The user tracking action class holds the pointer to the tracking manager:
  // fpTrackingManager

  // From the tracking manager we can retrieve the secondary track vector,
  // which is a container class for tracks:
  G4TrackVector* secTracks = fpTrackingManager -> GimmeSecondaries();

  // You can use the secTracks vector to retrieve the number of secondary 
  // electrons
  if(secTracks) { 
     size_t nmbSecTracks = (*secTracks).size();       

     for(size_t i = 0; i < nmbSecTracks; i++) { 
        if((*secTracks)[i] -> GetDefinition() == G4Electron::Definition()){
              electron_counter++;
        } else if((*secTracks)[i] -> GetDefinition() == G4Positron::Definition()){
            positron_counter++;
        } else if((*secTracks)[i] -> GetDefinition() == G4Gamma::Definition()){
            photon_counter++;
        }
     }
  }
}
