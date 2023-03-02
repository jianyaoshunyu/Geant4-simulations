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
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ }

void DetectorConstruction::SetConverterThickness(G4double thickness)
{
  // Get the original solid shape of the logical volume
  if (fLogicConverter) G4VSolid* originalSolid = fLogicConverter->GetSolid();
  // Create a new solid shape with the desired geometry
  G4double shape3_rin =  0.*cm;
  G4double shape3_rout =  2.*cm;
  G4double shape3_phimin = 0.*deg, shape3_phimax = 360.*deg;
  G4Tubs*  newSolid =    
    new G4Tubs("newShape3", 
    shape3_rin, shape3_rout,0.5*thickness, shape3_phimin, shape3_phimax);

// Update the solid shape of the logical volume
  if (thickness <= 5*cm ){
    fLogicConverter->SetSolid(newSolid);
    G4cout
          << G4endl
          << "----> The converter thickness is " << thickness << G4endl;
  }
  else{
    G4cout
          << G4endl
          << "volume exist " << thickness << G4endl;
  }
  // flash geometry
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  

   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 6.*cm;
  G4double world_sizeZ  = 6.*cm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     

  // Set Shape3 as scoring volume
  //
  fScoringVolume = fLogicConverter ;
  //shape 3 means a converter

  fConverterMaterial = nist->FindOrBuildMaterial("G4_Ta");
  G4ThreeVector pos3 = G4ThreeVector(0, 0, 0*cm);

  G4double shape3_rin =  0.*cm;
  G4double shape3_rout =  2.*cm;
  G4double shape3_hz = 1 *cm;
  G4double shape3_phimin = 0.*deg, shape3_phimax = 360.*deg;
  G4Tubs* solidShape3 =    
    new G4Tubs("Shape3", 
    shape3_rin, shape3_rout,0.5*shape3_hz, shape3_phimin, shape3_phimax);
                      
    fLogicConverter  =                         
    new G4LogicalVolume(solidShape3,         //its solid
                        fConverterMaterial,          //its material
                        "Shape3");           //its name

  G4VPhysicalVolume* physShape3 =             
  new G4PVPlacement(0,                       //no rotation
                    pos3,                    //at position
                    fLogicConverter ,             //its logical volume
                    "Shape3",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  G4VisAttributes* Shape3_logVisAtt
		= new G4VisAttributes(G4Colour(0.5,0.50,0.50));//gray
  fLogicConverter ->SetVisAttributes(Shape3_logVisAtt);

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
