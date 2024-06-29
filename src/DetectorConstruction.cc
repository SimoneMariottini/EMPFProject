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
/// \file B4/B4a/src/DetectorConstruction.cc
/// \brief Implementation of the B4::DetectorConstruction class

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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//G4ThreadLocal
//G4GlobalMagFieldMessenger* DetectorConstruction::fMagFieldMessenger = nullptr;

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
  nistManager->FindOrBuildMaterial("G4_POLYETHYLENE");

  //Mylar
  nistManager->FindOrBuildMaterial("G4_MYLAR");

  //Both BCf-12  SCSF-78 fibers, mostly polystyrene
  nistManager->FindOrBuildMaterial("G4_POLYSTYRENE");
  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  // Geometry parameters
  G4int nofLayers = 16;
  G4double fiberThickness[NLAYERS] = {1.*mm, 1.*mm, 0.5*mm, 0.5*mm, 0.25*mm, 0.25*mm, 0.2*mm, 0.2*mm,
                                      0.2*mm, 0.25*mm, 0.25*mm, 0.25*mm, 0.5*mm, 0.5*mm, 1.*mm, 1.*mm};
  G4double gapThickness[NLAYERS - 1] =  {0.*mm, 0.*mm, 0.5*mm, 0.6*mm, 0.7*mm, 0.7*mm, 0.5*mm, 0.7*mm,
                                         0.2*mm, 0.7*mm, 0.7*mm, 0.6*mm, 0.25*mm, 0.25*mm, 0.*mm};
  G4double mylarThickness = 0.05*mm;
  G4String S = "S", C = "C";
  G4String fiberShape[NLAYERS] = {S, S, C, C, S, S, S, S, S, S, S, S, C, C, S, S}; //C = circular, S = square
  G4double hodoWidth = 16.*mm;
  G4double hodoLength = 20.*cm;
  G4double hodoHeight = 0.*mm;

  //Calculate hodoHeigth:
  hodoHeight += fiberThickness[0];
  hodoHeight += 2*mylarThickness;
  for (int i = 0; i < NLAYERS - 1; i++){
    hodoHeight += 2*mylarThickness;
    hodoHeight += gapThickness[i];
    hodoHeight += fiberThickness[i + 1];
  }

  auto worldSizeX = 1.2 * hodoWidth;
  auto worldSizeY = 1.2 * hodoLength;
  auto worldSizeZ  = 1.2 * hodoHeight;

  // Get materials
  auto defaultMaterial = G4Material::GetMaterial("G4_AIR");
  auto fiberMaterial = G4Material::GetMaterial("G4_POLYSTYRENE");
  auto gapMaterial = G4Material::GetMaterial("G4_POLYETHYLENE");
  auto mylarMaterial = G4Material::GetMaterial("G4_MYLAR");

  if ( ! defaultMaterial || ! fiberMaterial || ! gapMaterial || ! mylarMaterial) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined.";
    G4Exception("DetectorConstruction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  }

  //
  // World
  //
  
  auto worldS = new G4Sphere("World", 0.*mm, worldSizeY/2., 0., 2*CLHEP::pi, 0., CLHEP::pi);

  //auto worldS = new G4Box("World",          // its name
  //               worldSizeX/2., worldSizeY/2., worldSizeZ/2.); // its size

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
  auto hodoscopeS
    = new G4Box("Hodoscope",     // its name
                 hodoWidth/2., hodoHeight/2., hodoLength/2.); // its size

  auto hodoscopeLV
    = new G4LogicalVolume(
                 hodoscopeS,     // its solid
                 defaultMaterial,  // its material
                 "Hodoscope");   // its name

  G4RotationMatrix* rotationMatrix = new G4RotationMatrix();
  rotationMatrix->rotateX(90.*deg);

  new G4PVPlacement(rotationMatrix,  // no rotation
    G4ThreeVector(),          // at (0,0,0)
    hodoscopeLV,                  // its logical volume
    "Hodoscope",            // its name
    worldLV,                  // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    fCheckOverlaps);          // checking overlaps

  //
  // Fiber Layers
  //
  
  G4VSolid* fiberLayerS[NLAYERS];

  G4VSolid* gapLayerS[NLAYERS - 1];

  G4VSolid* singleFiberS[NLAYERS];

  G4VSolid* mylarLayerS;

  G4LogicalVolume* fiberLayerLV[NLAYERS];

  G4LogicalVolume* gapLayerLV[NLAYERS - 1];

  G4LogicalVolume* singleFiberLV[NLAYERS];

  G4LogicalVolume* mylarLayerLV;

  G4double layerPos = - hodoHeight/2;

  for(int i = 0; i < NLAYERS; i++){
    fiberLayerS[i] = (G4VSolid*) new G4Box("Fiber layer " + std::to_string(i),           // its name
                    hodoWidth/2., fiberThickness[i]/2., hodoLength/2.); // its size

    fiberLayerLV[i] = new G4LogicalVolume(
                      fiberLayerS[i],           // its solid
                      defaultMaterial,  // its material
                      "Fiber layer " + std::to_string(i)); // its name

    new G4PVPlacement(nullptr,  // no rotation
                      G4ThreeVector(0.*mm, layerPos + fiberThickness[i]/2 + mylarThickness, 0.*mm),          // at (0,0,0)
                      fiberLayerLV[i],               // its logical volume
                      "Fiber layer " + std::to_string(i),              // its name
                      hodoscopeLV,                  // its mother  volume
                      false,                    // no boolean operation
                      0,                        // copy number
                      fCheckOverlaps);          // checking overlaps

    for (int j = 0; j < 2; j++){
      mylarLayerS = new G4Box("Mylar layer", 
                    hodoWidth/2., mylarThickness/2., hodoLength/2.);
      
      mylarLayerLV = new G4LogicalVolume(
                    mylarLayerS,           // its solid
                    mylarMaterial,  // its material
                    "Mylar layer"); // its name  
      
      new G4PVPlacement(nullptr,  // no rotation
                G4ThreeVector(0.*mm, layerPos + mylarThickness*(j + 0.5) + fiberThickness[i]*j, 0.*mm),          // at (0,0,0)
                mylarLayerLV,               // its logical volume
                "Mylar layer",              // its name
                hodoscopeLV,                  // its mother  volume
                false,                    // no boolean operation
                0,                        // copy number
                fCheckOverlaps);          // checking overlaps
      
      mylarLayerLV->SetVisAttributes(G4VisAttributes::GetInvisible());
    }

    layerPos += fiberThickness[i] + 2*mylarThickness;
    
    if(i < NLAYERS - 1){
      if(gapThickness[i] != 0.*mm){
        gapLayerS[i] = (G4VSolid*) new G4Box("Gap layer " + std::to_string(i),           // its name
                        hodoWidth/2., gapThickness[i]/2., hodoLength/2.); // its size

        gapLayerLV[i] = new G4LogicalVolume(
                          gapLayerS[i],           // its solid
                          gapMaterial,  // its material
                          "Gap layer " + std::to_string(i)); // its name
        
        new G4PVPlacement(nullptr,  // no rotation
                      G4ThreeVector(0.*mm, layerPos + gapThickness[i]/2, 0.*mm),          // at (0,0,0)
                      gapLayerLV[i],               // its logical volume
                      "Gap layer " + std::to_string(i),              // its name
                      hodoscopeLV,                  // its mother  volume
                      false,                    // no boolean operation
                      0,                        // copy number
                      fCheckOverlaps);          // checking overlaps

        layerPos += gapThickness[i];
      }
    }

    if(fiberShape[i] == S)
      singleFiberS[i] = (G4VSolid*) new G4Box("Single fiber", 
                        fiberThickness[i]/2., fiberThickness[i]/2., hodoLength/2.);
    else if(fiberShape[i] == C)
      singleFiberS[i] = (G4VSolid*) new G4Tubs("Single fiber", 
                        0., fiberThickness[i]/2., hodoLength/2., 0., 2*CLHEP::pi);

    singleFiberLV[i] = new G4LogicalVolume(
                      singleFiberS[i],           // its solid
                      fiberMaterial,  // its material
                      "Single fiber"); // its name  

    G4int nofFibers = hodoWidth/fiberThickness[i];
    
    fFiberPV[i] = new G4PVReplica(
                "Single fiber",          // its name
                singleFiberLV[i],          // its logical volume
                fiberLayerLV[i],          // its mother
                kXAxis,           // axis of replication
                nofFibers,        // number of replica
                fiberThickness[i]);  // witdth of replica
  }

  //
  // print parameters
  //
  G4cout
    << G4endl
    << "------------------------------------------------------------" << G4endl
    << "---> The hodoscope is " << NLAYERS << " layers of "
    << fiberMaterial->GetName()
    << "." << G4endl
    << "---> The hodoscope's total height is "
    << hodoHeight
    << "------------------------------------------------------------" << G4endl;

  //
  // Visualization attributes
  //

  worldLV->SetVisAttributes(G4VisAttributes::GetInvisible());

  #if FILLCOLOR

  for(int i = 0; i < NLAYERS; i++){
    if(fiberThickness[i] == 1.*mm){
      fiberLayerLV[i]->SetVisAttributes(G4VisAttributes::GetInvisible());
      singleFiberLV[i]->SetVisAttributes(G4VisAttributes(G4Colour::White()));
    }

    if(fiberThickness[i] == 0.5*mm){
      fiberLayerLV[i]->SetVisAttributes(G4VisAttributes(G4Colour::Green()));
      singleFiberLV[i]->SetVisAttributes(G4VisAttributes(G4Colour::Green()));
    }

    if(fiberThickness[i] == 0.25*mm){
      fiberLayerLV[i]->SetVisAttributes(G4VisAttributes::GetInvisible());
      singleFiberLV[i]->SetVisAttributes(G4VisAttributes(G4Colour::Red()));
    }
    if(fiberThickness[i] == 0.20*mm){
      fiberLayerLV[i]->SetVisAttributes(G4VisAttributes::GetInvisible());
      singleFiberLV[i]->SetVisAttributes(G4VisAttributes(G4Colour::Yellow()));
    }
  }

  #else
  
  for(int i = 0; i < NLAYERS; i++){
    if(fiberThickness[i] == 1.*mm){
      fiberLayerLV[i]->SetVisAttributes(G4VisAttributes(G4Colour::White()));
      singleFiberLV[i]->SetVisAttributes(G4VisAttributes::GetInvisible());
    }

    if(fiberThickness[i] == 0.5*mm){
      fiberLayerLV[i]->SetVisAttributes(G4VisAttributes(G4Colour::Green()));
      singleFiberLV[i]->SetVisAttributes(G4VisAttributes(G4Colour::Green()));
    }

    if(fiberThickness[i] == 0.25*mm){
      fiberLayerLV[i]->SetVisAttributes(G4VisAttributes(G4Colour::Red()));
      singleFiberLV[i]->SetVisAttributes(G4VisAttributes::GetInvisible());
    }
    if(fiberThickness[i] == 0.20*mm){
      fiberLayerLV[i]->SetVisAttributes(G4VisAttributes(G4Colour::Yellow()));
      singleFiberLV[i]->SetVisAttributes(G4VisAttributes::GetInvisible());
    }
  }

  #endif

  for(int i = 0; i < NLAYERS - 1; i++){
    if(gapThickness[i] != 0.*mm)
      gapLayerLV[i]->SetVisAttributes(G4VisAttributes(G4Colour::Grey()));
  }

  hodoscopeLV->SetVisAttributes(G4VisAttributes::GetInvisible());

  //
  // Always return the physical World
  //
  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*void DetectorConstruction::ConstructSDandField()
{
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue;
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);

  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}

