/// \file DetectorMessenger.cc
/// \brief Implementation of the DetectorMessenger class

#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(DetectorConstruction* det)
 : fDetectorConstruction(det)
{
  fDirectory = new G4UIdirectory("/brem/");
  fDirectory->SetGuidance("UI commands specific to this example.");

  fDetDirectory = new G4UIdirectory("/brem/det/");
  fDetDirectory->SetGuidance("Detector construction control");
/*
  fTargMatCmd = new G4UIcmdWithAString("//det/setTargetMaterial",this);
  fTargMatCmd->SetGuidance("Select Material of the Target.");
  fTargMatCmd->SetParameterName("choice",false);
  fTargMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fChamMatCmd = new G4UIcmdWithAString("//det/setChamberMaterial",this);
  fChamMatCmd->SetGuidance("Select Material of the Chamber.");
  fChamMatCmd->SetParameterName("choice",false);
  fChamMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
*/
  fCvtThickCmd = new G4UIcmdWithADoubleAndUnit("/brem/det/CvtThick",this);
  fCvtThickCmd->SetGuidance("Define converter thickness");
  fCvtThickCmd->SetParameterName("CvtThick",false);
  fCvtThickCmd->SetUnitCategory("Length");
  fCvtThickCmd->SetDefaultUnit("mm");
  fCvtThickCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
/*  delete fTargMatCmd;
  delete fChamMatCmd;*/
  delete fCvtThickCmd;
  delete fDirectory;
  delete fDetDirectory;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
/*if( command == fTargMatCmd )
   { fDetectorConstruction->SetTargetMaterial(newValue);}

  if( command == fChamMatCmd )
   { fDetectorConstruction->SetChamberMaterial(newValue);}
*/  
  if( command == fCvtThickCmd ) {
    fDetectorConstruction
      ->SetConverterThickness(fCvtThickCmd->GetNewDoubleValue(newValue));
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

