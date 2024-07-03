#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"

#include "CLHEP/Units/SystemOfUnits.h"

namespace Detectors
{

  #define RedBox true

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Define materials
  DefineMaterials();

  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
  // Some materials defined using NIST Manager
  auto nistManager = G4NistManager::Instance();

  //Air material
  nistManager->FindOrBuildMaterial("G4_AIR");

  //Polyhethylene - Assumed 3d printing material
  nistManager->FindOrBuildMaterial("G4_CESIUM_IODIDE");

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  // Geometry parameters

  G4double radLenght = 1.86*cm;
  G4double molierRad = 3.531*cm;

  G4double detX = molierRad*15;
  G4double detY = molierRad*15;
  G4double detZ = radLenght*40;

  auto worldSizeX = 1.2 * detX;
  auto worldSizeY = 1.2 * detY;
  auto worldSizeZ  = 1.2 * detZ;

  // Get materials
  auto defaultMaterial = G4Material::GetMaterial("G4_AIR");
  auto detectorMaterial = G4Material::GetMaterial("G4_CESIUM_IODIDE");


  if ( ! defaultMaterial || ! detectorMaterial) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined.";
    G4Exception("DetectorConstruction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  }

  //
  // World
  //
  
  auto worldS = new G4Box("World",worldSizeX/2., worldSizeY/2., worldSizeZ/2.);

  auto worldLV
    = new G4LogicalVolume(
                 worldS,           // its solid
                 defaultMaterial,  // its material
                 "World");         // its name

  auto worldPV = new G4PVPlacement(nullptr,  // no rotation
    G4ThreeVector(),                         // at (0,0,0)
    worldLV,                                 // its logical volume
    "World",                                 // its name
    nullptr,                                 // its mother  volume
    false,                                   // no boolean operation
    0,                                       // copy number
    fCheckOverlaps);                         // checking overlaps

  //
  // Hodoscope
  //
  auto detectorS
    = new G4Box("Detector",     // its name
                 detX/2., detY/2., detZ/2.); // its size

  auto detectorLV
    = new G4LogicalVolume(
                 detectorS,     // its solid
                 detectorMaterial,  // its material
                 "Detector");   // its name

  fDetectorPV = new G4PVPlacement(nullptr,  // no rotation
    G4ThreeVector(),          // at (0,0,0)
    detectorLV,                  // its logical volume
    "Detector",            // its name
    worldLV,                  // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    fCheckOverlaps);          // checking overlaps

  #if RedBox
  auto detector5X0S
    = new G4Box("Detector5X0",     // its name
                 detX/2., detY/2., radLenght*2.5); // its size

  auto detector5X0LV
    = new G4LogicalVolume(
                 detector5X0S,     // its solid
                 detectorMaterial,  // its material
                 "Detector5X0");   // its name

  new G4PVPlacement(nullptr,  // no rotation
    G4ThreeVector(0, 0, -detZ/2. + radLenght*2.5),          // at (0,0,0)
    detector5X0LV,                  // its logical volume
    "Detector5X0",            // its name
    detectorLV,                  // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    fCheckOverlaps);          // checking overlaps*/

  #endif

  //
  // print parameters
  //
  G4cout
    << G4endl
    << "------------------------------------------------------------" << G4endl
    << "---> The detector is made of "
    << detectorMaterial->GetName()
    << "." << G4endl
    << "------------------------------------------------------------" << G4endl;

  //
  // Visualization attributes
  //

  worldLV->SetVisAttributes(G4VisAttributes::GetInvisible());
  detectorLV->SetVisAttributes(G4VisAttributes(G4Colour::Grey()));
  #if RedBox
  auto vis5X0 = G4VisAttributes(G4Colour::Red());
  vis5X0.SetLineWidth(2.);
  detector5X0LV->SetVisAttributes(vis5X0);
  #endif
  //
  // Always return the physical World
  //
  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}

