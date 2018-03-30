#ifndef T1T0_h
#define T1T0_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "T1MRPC.hh"

class T1T0
{
  public:
    T1T0();
    ~T1T0();
    G4LogicalVolume* logicT0;
};

T1T0::T1T0()
{
  logicT0 = new G4AssemblyVolume();

  for(int i=1;i<=36;i++)
  {
    G4double ax,ay,az,angz1,angy,angz2,d1,d2;
    G4int n;

    ///// queding shangmian shuju de zhi
    G4ThreeVector uz = G4ThreeVector(std::cos(phi),  std::sin(phi),0.);
    G4ThreeVector posv = (ring_R1+0.5*cryst_dZ)*uz;
    /////

    T1MRPC aMRPC=T1MRPC(n,d1,d2);
    G4ThreeVector posv=G4ThreeVector(ax,ay,az);
    G4RotationMatrix rotm= G4RotationMatrix();
    rotm.rotateZ(angz1);
    rotm.rotateY(angy);
    rotm.rotateZ(angZ2);

    G4Transform3D transform = G4Transform3D(rotm,posv);
    logicT0->AddPlacedVolume( aMRPC.logicMRPC, transform );
  }

  //G4RotationMatrix Rm;
  //G4ThreeVector Tm( 0,0,i*(caloZ + caloCaloOffset) - firstCaloPos );
  //Tr = G4Transform3D(Rm,Tm);
  //assemblyDetector->MakeImprint( worldLV, Tr );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
