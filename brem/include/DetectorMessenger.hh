/// \file DetectorMessenger.hh
/// \brief Definition of the DetectorMessenger class

#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;

class DetectorConstruction;

/// Messenger class that defines commands for DetectorConstruction.
///
/// It implements commands:
/// - //det/setTargetMaterial name
/// - //det/setChamberMaterial name
/// - //det/stepMax value unit

class DetectorMessenger: public G4UImessenger
{
  public:
    DetectorMessenger(DetectorConstruction* );
    ~DetectorMessenger() override;

    void SetNewValue(G4UIcommand*, G4String) override;

  private:
    DetectorConstruction*  fDetectorConstruction = nullptr;

    G4UIdirectory*         fDirectory = nullptr;
    G4UIdirectory*         fDetDirectory = nullptr;

 //   G4UIcmdWithAString*    fTargMatCmd = nullptr;
 //   G4UIcmdWithAString*    fChamMatCmd = nullptr;

    G4UIcmdWithADoubleAndUnit* fCvtThickCmd = nullptr;
};



#endif
