#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

namespace Detectors
{

/// Detector construction class to define materials and geometry.
/// The detector is a block of CsI.
/// The detector parameters are:
/// - The width of the block - 15R_m; 
/// - The heigth of the block - 15R_m; 
/// - The lenght of the block - 40X0.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction() = default;
    ~DetectorConstruction() override = default;

  public:
    G4VPhysicalVolume* Construct() override;

    // get methods
    //
    const G4VPhysicalVolume* GetDetectorPV() const;

  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();

    //
    // data members
    //

    G4VPhysicalVolume* fDetectorPV = nullptr; // the detector physical volume

    G4bool fCheckOverlaps = true; // option to activate checking of volumes overlaps
};

// inline functions

inline const G4VPhysicalVolume* DetectorConstruction::GetDetectorPV() const {
  return fDetectorPV;
}

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

