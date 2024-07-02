
/////////////////////////////////////////////////////////////////////////
// G4Tutorial:
//
// UserTrackingAction.hh
// 
// Defining actions performed at the start/end point of processing a
// track
//
/////////////////////////////////////////////////////////////////////////


#ifndef TRACKINGACTION_HH
#define TRACKINGACTION_HH

#include "G4UserTrackingAction.hh"
#include "globals.hh"
#include "EventAction.hh"


// G4UserTrackingAction is the base class for defining user actions performed 
// at the beginning and in the end of processing one track:

namespace Detectors{

class TrackingAction : public G4UserTrackingAction {

 public:
   TrackingAction(EventAction* eventAction);
   virtual ~TrackingAction() { }

   // G4UserTrackingAction has two method, UserPreTrackingAction and
   // UserPostTrackingAction, which can be overloaded by the user to define 
   // specific actions performed at the beginning and the end of processing 
   // one track.
   // Information about the track can be retrieved from the G4Track object 
   // passed to this function, or from the tracking manager pointer.
   void PreUserTrackingAction(const G4Track*) { };
   virtual void PostUserTrackingAction(const G4Track*);

  private:
    EventAction* fEventAction = nullptr;
};

}

#endif // USERTRACKINGACTION_HH
