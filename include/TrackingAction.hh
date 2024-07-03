#ifndef TRACKINGACTION_HH
#define TRACKINGACTION_HH

#include "G4UserTrackingAction.hh"
#include "globals.hh"
#include "EventAction.hh"

namespace Detectors{

class TrackingAction : public G4UserTrackingAction {

 public:
   TrackingAction(EventAction* eventAction);
   virtual ~TrackingAction() { }

   void PreUserTrackingAction(const G4Track*) { };
   virtual void PostUserTrackingAction(const G4Track*);

  private:
    EventAction* fEventAction = nullptr;
};

}

#endif
