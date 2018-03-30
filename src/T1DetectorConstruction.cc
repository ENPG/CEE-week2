#include "T1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"  //yuanzhu guanzi
#include "G4Cons.hh"
#include "G4Orb.hh"  //shixinqiu
#include "G4Torus.hh"  //quan
#include "G4Sphere.hh" //qiu  (duocanshu)
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T1DetectorConstruction::T1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T1DetectorConstruction::~T1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* T1DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* default_mat = nist->FindOrBuildMaterial("G4_Galactic");
  G4VisAttributes* default_Vis = new G4VisAttributes(G4Colour(0,0,0,0));

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = false;

  //////////////////////CEE-1

  G4double CEE_world_sx = 5*m;  //gao
  G4double CEE_world_sy = 10*m;  //kuan
  G4double CEE_world_sz = 10*m;  //chang  zhouxiang
  G4ThreeVector CEE_world_p = G4ThreeVector(0*cm, 0*cm, 0*cm);
  G4Material* CEE_world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4VisAttributes* CEE_world_Vis = new G4VisAttributes(G4Colour(0.0,0.0,0.0,0.0));


  G4double CEE_Pix_sx = 3*cm;
  G4double CEE_Pix_sy = 3*cm;
  G4double CEE_Pix_sz = 3*cm;
  G4double CEE_Pix_px = 0*cm;
  G4double CEE_Pix_py = 0*cm;
  G4double CEE_Pix_pz = -8*cm;
  G4ThreeVector CEE_Pix_p = G4ThreeVector(CEE_Pix_px, CEE_Pix_py, CEE_Pix_pz);
  G4Material* CEE_Pix_mat = nist->FindOrBuildMaterial("G4_Galactic");//Ar:CO2 7:3
  G4VisAttributes* CEE_Pix_Vis = new G4VisAttributes(G4Colour(0.0,0.0,1.0,1));

  G4double CEE_T0_sr1 = 0*cm;
  G4double CEE_T0_sr2 = 2*cm;
  G4double CEE_T0_sz = 8*cm;
  G4double CEE_T0_px = 0*cm;
  G4double CEE_T0_py = 0*cm;
  G4double CEE_T0_pz = 0*cm;
  G4ThreeVector CEE_T0_p = G4ThreeVector(CEE_T0_px, CEE_T0_py, CEE_T0_pz);
  G4Material* CEE_T0_mat = nist->FindOrBuildMaterial("G4_Galactic");//SiO2
  G4VisAttributes* CEE_T0_Vis = new G4VisAttributes(G4Colour(0.1,0.4,1.5,1));

  G4double CEE_TPC_sx = 80*cm;
  G4double CEE_TPC_sy = 100*cm;
  G4double CEE_TPC_sz = 80*cm;
  G4double CEE_TPC_px = 0*cm;
  G4double CEE_TPC_py = 0*cm;
  G4double CEE_TPC_pz = 60*cm;
  G4ThreeVector CEE_TPC_p = G4ThreeVector(CEE_TPC_px, CEE_TPC_py, CEE_TPC_pz);
  G4Material* CEE_TPC_mat = nist->FindOrBuildMaterial("G4_Galactic");//Ar:CH4 9:1
  G4VisAttributes* CEE_TPC_Vis = new G4VisAttributes(G4Colour(0.0,0.0,1.0,0.5));

  G4double CEE_iTOF0_sx = 80*cm+5*cm;  //
  G4double CEE_iTOF0_sy = 1*cm;
  G4double CEE_iTOF0_sz = 80*cm;
  G4double CEE_iTOF0_px = 0*cm;
  G4double CEE_iTOF0_py = 0.5*(CEE_TPC_sy+CEE_iTOF0_sy);
  G4double CEE_iTOF0_pz = 60*cm;
  G4ThreeVector CEE_iTOF01_p = G4ThreeVector(CEE_iTOF0_px, CEE_iTOF0_py, CEE_iTOF0_pz);
  G4ThreeVector CEE_iTOF02_p = G4ThreeVector(CEE_iTOF0_px, -CEE_iTOF0_py, CEE_iTOF0_pz);
  G4Material* CEE_iTOF0_mat = default_mat;//nist->FindOrBuildMaterial("G4_Galactic");//SiO2
  G4VisAttributes* CEE_iTOF0_Vis = new G4VisAttributes(G4Colour(0.35,0.35,0.3,0.5));
  G4Material* CEE_MRPC_mat1 = nist->FindOrBuildMaterial("G4_Galactic");//SiO2
  G4Material* CEE_MRPC_mat2 = nist->FindOrBuildMaterial("G4_Galactic");//SiO2

  G4double CEE_iTOF1_sx = 1*cm;  //
  G4double CEE_iTOF1_sy = 100*cm;
  G4double CEE_iTOF1_sz = 80*cm;
  G4double CEE_iTOF1_px = -0.5*(CEE_TPC_sx+CEE_iTOF1_sx);
  G4double CEE_iTOF1_py = 0*cm;
  G4double CEE_iTOF1_pz = 60*cm;
  G4ThreeVector CEE_iTOF1_p = G4ThreeVector(CEE_iTOF1_px, CEE_iTOF1_py, CEE_iTOF1_pz);
  G4Material* CEE_iTOF1_mat = nist->FindOrBuildMaterial("G4_Galactic");//SiO2
  G4VisAttributes* CEE_iTOF1_Vis = new G4VisAttributes(G4Colour(0.35,0.35,0.3,0.5));

  G4double CEE_MWDC1_sx = 100*cm;
  G4double CEE_MWDC1_sy = 100*cm;
  G4double CEE_MWDC1_sz = 4*cm;
  G4double CEE_MWDC1_px = 0*cm;
  G4double CEE_MWDC1_py = (75+50)*cm;
  G4double CEE_MWDC1_pz = (80+1+60)*cm;
  G4ThreeVector CEE_MWDC11_p = G4ThreeVector(CEE_MWDC1_px, CEE_MWDC1_py, CEE_MWDC1_pz);
  G4ThreeVector CEE_MWDC12_p = G4ThreeVector(CEE_MWDC1_px, -CEE_MWDC1_py, CEE_MWDC1_pz);
  G4Material* CEE_MWDC1_mat = nist->FindOrBuildMaterial("G4_Ar");//Ar?
  G4VisAttributes* CEE_MWDC1_Vis = new G4VisAttributes(G4Colour(0.4,0.4,0.2,0.5));

  G4double CEE_MWDC2_sx = 100*cm;
  G4double CEE_MWDC2_sy = 110*cm;
  G4double CEE_MWDC2_sz = 4*cm;
  G4double CEE_MWDC2_px = 0*cm;
  G4double CEE_MWDC2_py = (75+50+5)*cm;
  G4double CEE_MWDC2_pz = (80+1+10+60)*cm;
  G4ThreeVector CEE_MWDC21_p = G4ThreeVector(CEE_MWDC2_px, CEE_MWDC2_py, CEE_MWDC2_pz);
  G4ThreeVector CEE_MWDC22_p = G4ThreeVector(CEE_MWDC2_px, -CEE_MWDC2_py, CEE_MWDC2_pz);
  G4Material* CEE_MWDC2_mat = nist->FindOrBuildMaterial("G4_Ar");//Ar?
  G4VisAttributes* CEE_MWDC2_Vis = new G4VisAttributes(G4Colour(0.4,0.4,0.2,0.5));

  G4double CEE_MWDC3_sx = 100*cm;
  G4double CEE_MWDC3_sy = 120*cm;
  G4double CEE_MWDC3_sz = 4*cm;
  G4double CEE_MWDC3_px = 0*cm;
  G4double CEE_MWDC3_py = (75+50+10)*cm;
  G4double CEE_MWDC3_pz = (80+1+20+60)*cm;
  G4ThreeVector CEE_MWDC31_p = G4ThreeVector(CEE_MWDC3_px, CEE_MWDC3_py, CEE_MWDC3_pz);
  G4ThreeVector CEE_MWDC32_p = G4ThreeVector(CEE_MWDC3_px, -CEE_MWDC3_py, CEE_MWDC3_pz);
  G4Material* CEE_MWDC3_mat = nist->FindOrBuildMaterial("G4_Ar");//Ar?
  G4VisAttributes* CEE_MWDC3_Vis = new G4VisAttributes(G4Colour(0.4,0.4,0.2,0.5));

  G4double CEE_eTOF_sx = 200*cm;
  G4double CEE_eTOF_sy = 300*cm;
  G4double CEE_eTOF_sz = 1*cm;
  G4double CEE_eTOF_px = 0*cm;
  G4double CEE_eTOF_py = (75+150)*cm;
  G4double CEE_eTOF_pz = (180+60)*cm;
  G4ThreeVector CEE_eTOF1_p = G4ThreeVector(CEE_eTOF_px, CEE_eTOF_py, CEE_eTOF_pz);
  G4ThreeVector CEE_eTOF2_p = G4ThreeVector(CEE_eTOF_px, -CEE_eTOF_py, CEE_eTOF_pz);
  G4Material* CEE_eTOF_mat = nist->FindOrBuildMaterial("G4_Ar");//SiO2
  G4VisAttributes* CEE_eTOF_Vis = new G4VisAttributes(G4Colour(0.35,0.35,0.3,0.5));





  //////////////////////CEE-1






  //
  // CEE_World
  //

  G4Box* CEE_world_solid =
    new G4Box("CEE_world_solid",                       //its name
       0.5*CEE_world_sx, 0.5*CEE_world_sy, 0.5*CEE_world_sz);     //its size

  G4LogicalVolume* CEE_world_logic =
    new G4LogicalVolume(CEE_world_solid,          //its solid
                        CEE_world_mat,           //its material
                        "CEE_world_logic");            //its name

  G4VPhysicalVolume* CEE_world_phys =
    new G4PVPlacement(0,                     //no rotation
                      CEE_world_p,       //at (,,)
                      CEE_world_logic,            //its logical volume
                      "CEE_world_phys",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
  CEE_world_logic -> SetVisAttributes(CEE_world_Vis);
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
///ZDC
  G4double CEE_ZDC_px = 0*cm;
  G4double CEE_ZDC_py = 0*cm;
  G4double CEE_ZDC_pz = CEE_eTOF_pz+5*cm+40*cm;
  G4ThreeVector CEE_ZDC_p = G4ThreeVector(CEE_ZDC_px, CEE_ZDC_py, CEE_ZDC_pz);
  G4double CEE_ZDC_sx = 2*m;
  G4double CEE_ZDC_sy = 2*m;
  //G4double CEE_ZDC_sz = 80*cm+5*cm;

  G4double CEE_ZDC_Pb_0_sx = CEE_ZDC_sx/20;
  G4double CEE_ZDC_Pb_0_sy = CEE_ZDC_sy/20;
  G4double CEE_ZDC_Pb_0_sz = 10*mm;
  G4Material* CEE_ZDC_Pb_mat = nist->FindOrBuildMaterial("G4_Pb");
  G4VisAttributes* CEE_ZDC_Pb_Vis = new G4VisAttributes(G4Colour(0.35,0.35,0.3,0.5));
  G4double CEE_ZDC_Sc_0_sx = CEE_ZDC_sx/20;
  G4double CEE_ZDC_Sc_0_sy = CEE_ZDC_sy/20;
  G4double CEE_ZDC_Sc_0_sz = 2.5*mm;
  G4Material* CEE_ZDC_Sc_mat = nist->FindOrBuildMaterial("G4_Sc");
  G4VisAttributes* CEE_ZDC_Sc_Vis = new G4VisAttributes(G4Colour(0.5,0.25,0.25,0.5));

  G4Box* CEE_ZDC_Pb_0_solid =
    new G4Box("CEE_ZDC_Pb_0_solid",                       //its name
       0.5*CEE_ZDC_Pb_0_sx, 0.5*CEE_ZDC_Pb_0_sy, 0.5*CEE_ZDC_Pb_0_sz);     //its size
  G4Box* CEE_ZDC_Sc_0_solid =
    new G4Box("CEE_ZDC_Sc_0_solid",                       //its name
       0.5*CEE_ZDC_Sc_0_sx, 0.5*CEE_ZDC_Sc_0_sy, 0.5*CEE_ZDC_Sc_0_sz);     //its size
  G4LogicalVolume* CEE_ZDC_Pb_0_logic= new G4LogicalVolume(CEE_ZDC_Pb_0_solid,          //its solid
                      CEE_ZDC_Pb_mat,           //its material
                      "CEE_ZDC_Pb_0_logic");            //its name
  G4LogicalVolume* CEE_ZDC_Sc_0_logic= new G4LogicalVolume(CEE_ZDC_Sc_0_solid,          //its solid
                      CEE_ZDC_Sc_mat,           //its material
                      "CEE_ZDC_Sc_0_logic");            //its name

  G4Box* CEE_ZDC_Pb_Sc_solid =
    new G4Box("CEE_ZDC_Pb_Sc_solid",                       //its name
       0.5*CEE_ZDC_Pb_0_sx, 0.5*CEE_ZDC_Pb_0_sy, 0.5*(CEE_ZDC_Pb_0_sz+CEE_ZDC_Sc_0_sz)*65);     //its size
  G4LogicalVolume* CEE_ZDC_Pb_Sc_logic= new G4LogicalVolume(CEE_ZDC_Pb_Sc_solid,          //its solid
                     default_mat,           //its material
                     "CEE_ZDC_Pb_Sc_logic");            //its name



  for(int id1=0;id1<65;id1++){

    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(0,0,id1*12.5*mm),       //at (,,)
                      CEE_ZDC_Pb_0_logic,            //its logical volume
                      "CEE_ZDC_Pb_0_phys",               //its name
                      CEE_ZDC_Pb_Sc_logic,                     //its mother  volume
                      false,                 //no boolean operation
                      id1,                     //copy number
                      checkOverlaps);        //overlaps checking

    /////

    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(0,0,id1*12.5*mm+0.5*12.5*mm),       //at (,,)
                      CEE_ZDC_Sc_0_logic,            //its logical volume
                      "CEE_ZDC_Sc_0_phys",               //its name
                      CEE_ZDC_Pb_Sc_logic,                     //its mother  volume
                      false,                 //no boolean operation
                      id1,                     //copy number
                      checkOverlaps);        //overlaps checking

  }
  CEE_ZDC_Sc_0_logic -> SetVisAttributes(CEE_ZDC_Sc_Vis);
  CEE_ZDC_Pb_0_logic -> SetVisAttributes(CEE_ZDC_Pb_Vis);
  CEE_ZDC_Pb_Sc_logic -> SetVisAttributes(default_Vis);
  ///
  G4Box* CEE_ZDC_solid =
    new G4Box("CEE_ZDC_solid",                       //its name
       0.5*CEE_ZDC_sx, 0.5*CEE_ZDC_sy, 0.5*(CEE_ZDC_Pb_0_sz+CEE_ZDC_Sc_0_sz)*65);     //its size

  G4LogicalVolume* CEE_ZDC_logic= new G4LogicalVolume(CEE_ZDC_solid,          //its solid
                      default_mat,           //its material
                      "CEE_ZDC_logic");            //its name

  for(int id1=0;id1<20;id1++){
    for(int jd2=0;jd2<20;jd2++){

      new G4PVPlacement(0,                     //no rotation
                        G4ThreeVector(0.5*CEE_ZDC_sx-0.5*CEE_ZDC_Pb_0_sx-jd2*CEE_ZDC_Pb_0_sx,-0.5*CEE_ZDC_sy+0.5*CEE_ZDC_Pb_0_sy+id1*CEE_ZDC_Pb_0_sy,0),       //at (,,)
                        CEE_ZDC_Pb_Sc_logic,            //its logical volume
                        "CEE_ZDC_Pb_Sc_phys",               //its name
                        CEE_ZDC_logic,                     //its mother  volume
                        false,                 //no boolean operation
                        20*id1+jd2,                     //copy number
                        checkOverlaps);        //overlaps checking
    }
  }
  ///
  new G4PVPlacement(0,                     //no rotation
                    G4ThreeVector(0,0,CEE_ZDC_pz),       //at (,,)
                    CEE_ZDC_logic,            //its logical volume
                    "CEE_ZDC_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking

///ZDC//////////////////
//
// CEE_Pix
//

G4Box* CEE_Pix_solid =
  new G4Box("CEE_Pix_solid",                       //its name
     0.5*CEE_Pix_sx, 0.5*CEE_Pix_sy, 0.5*CEE_Pix_sz);     //its size

G4LogicalVolume* CEE_Pix_logic =
  new G4LogicalVolume(CEE_Pix_solid,          //its solid
                      CEE_Pix_mat,           //its material
                      "CEE_Pix_logic");            //its name


  new G4PVPlacement(0,                     //no rotation
                    CEE_Pix_p,       //at (,,)
                    CEE_Pix_logic,            //its logical volume
                    "CEE_Pix_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking
CEE_Pix_logic -> SetVisAttributes(CEE_Pix_Vis);
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// CEE_T0
//

G4Tubs* CEE_T0_solid =
  new G4Tubs("CEE_TPC_solid",CEE_T0_sr1,CEE_T0_sr2,0.5*CEE_T0_sz,0,2*pi);

G4LogicalVolume* CEE_T0_logic =
  new G4LogicalVolume(CEE_T0_solid,          //its solid
                      CEE_T0_mat,           //its material
                      "CEE_T0_logic");            //its name


  new G4PVPlacement(0,                     //no rotation
                    CEE_T0_p,       //at (,,)
                    CEE_T0_logic,            //its logical volume
                    "CEE_T0_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking
CEE_T0_logic -> SetVisAttributes(CEE_T0_Vis);
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// CEE_TPC
//

G4Box* CEE_TPC_solid =
  new G4Box("CEE_TPC_solid",                       //its name
     0.5*CEE_TPC_sx, 0.5*CEE_TPC_sy, 0.5*CEE_TPC_sz);     //its size

G4LogicalVolume* CEE_TPC_logic =
  new G4LogicalVolume(CEE_TPC_solid,          //its solid
                      CEE_TPC_mat,           //its material
                      "CEE_TPC_logic");            //its name


  new G4PVPlacement(0,                     //no rotation
                    CEE_TPC_p,       //at (,,)
                    CEE_TPC_logic,            //its logical volume
                    "CEE_TPC_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking
CEE_TPC_logic -> SetVisAttributes(CEE_TPC_Vis);
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// CEE_iTOF
//
///// iTOF01

G4Box* CEE_iTOF01_solid =
  new G4Box("CEE_iTOF01_solid",                       //its name
     0.5*CEE_iTOF0_sx, 0.5*CEE_iTOF0_sy, 0.5*CEE_iTOF0_sz);     //its size

G4LogicalVolume* CEE_iTOF01_logic =
  new G4LogicalVolume(CEE_iTOF01_solid,          //its solid
                      CEE_iTOF0_mat,           //its material
                      "CEE_iTOF01_logic");            //its name

for(int id1=0;id1<58;id1++){
  G4Box* CEE_iTOF01_MRPC_solid =
    new G4Box("CEE_iTOF01_MRPC_solid",                       //its name
       0.5*25*mm, 0.5*5*mm, 0.5*80*cm);     //its size

  G4LogicalVolume* CEE_iTOF01_MRPC_logic =
    new G4LogicalVolume(CEE_iTOF01_MRPC_solid,          //its solid
                        default_mat,           //its material
                        "CEE_iTOF01_MRPC_logic");            //its name

  G4Box* CEE_iTOF01_MRPC_solid1 =
    new G4Box("CEE_iTOF01_MRPC_solid1",                       //its name
       0.5*25*mm, 0.5*0.25*mm, 0.5*80*cm);     //its size

  G4LogicalVolume* CEE_iTOF01_MRPC_logic1 =
    new G4LogicalVolume(CEE_iTOF01_MRPC_solid1,          //its solid
                        CEE_MRPC_mat1,           //its material
                        "CEE_iTOF01_MRPC_logic1");            //its name
  CEE_iTOF01_MRPC_logic1 -> SetVisAttributes(CEE_iTOF0_Vis);
  for(int jd2=0;jd2<19;jd2++){
      new G4PVPlacement(0,                     //no rotation
                        G4ThreeVector(0,-2.5*mm+0.5*0.25*mm+jd2*0.25*mm,0),       //at (,,)
                        CEE_iTOF01_MRPC_logic1,            //its logical volume
                        "CEE_iTOF01_MRPC_phys1",               //its name
                        CEE_iTOF01_logic,                     //its mother  volume
                        false,                 //no boolean operation
                        jd2,                     //copy number
                        checkOverlaps);        //overlaps checking
    }

  if(id1<29){
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(400*mm-id1*28*mm,-2.5*mm,0),       //at (,,)
                      CEE_iTOF01_MRPC_logic,            //its logical volume
                      "CEE_iTOF01_MRPC_phys",               //its name
                      CEE_iTOF01_logic,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
    CEE_iTOF01_MRPC_logic -> SetVisAttributes(CEE_iTOF0_Vis);
  }
  else{
    int jd3=id1-29;
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(400*mm-14*mm-jd3*28*mm,2.5*mm,0),       //at (,,)
                      CEE_iTOF01_MRPC_logic,            //its logical volume
                      "CEE_iTOF01_MRPC_phys",               //its name
                      CEE_iTOF01_logic,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
    CEE_iTOF01_MRPC_logic -> SetVisAttributes(CEE_iTOF0_Vis);

  }
}




  new G4PVPlacement(0,                     //no rotation
                    CEE_iTOF01_p,       //at (,,)
                    CEE_iTOF01_logic,            //its logical volume
                    "CEE_iTOF01_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking
CEE_iTOF01_logic -> SetVisAttributes(default_Vis);
/////iTOF02
G4Box* CEE_iTOF02_solid =
  new G4Box("CEE_iTOF02_solid",                       //its name
     0.5*CEE_iTOF0_sx, 0.5*CEE_iTOF0_sy, 0.5*CEE_iTOF0_sz);     //its size

G4LogicalVolume* CEE_iTOF02_logic =
  new G4LogicalVolume(CEE_iTOF02_solid,          //its solid
                      CEE_iTOF0_mat,           //its material
                      "CEE_iTOF01_logic");            //its name

for(int id1=0;id1<58;id1++){
  G4Box* CEE_iTOF02_MRPC_solid =
    new G4Box("CEE_iTOF02_MRPC_solid",                       //its name
       0.5*25*mm, 0.5*5*mm, 0.5*80*cm);     //its size

  G4LogicalVolume* CEE_iTOF02_MRPC_logic =
    new G4LogicalVolume(CEE_iTOF02_MRPC_solid,          //its solid
                        default_mat,           //its material
                        "CEE_iTOF02_MRPC_logic");            //its name

  G4Box* CEE_iTOF02_MRPC_solid1 =
    new G4Box("CEE_iTOF02_MRPC_solid1",                       //its name
       0.5*25*mm, 0.5*0.25*mm, 0.5*80*cm);     //its size

  G4LogicalVolume* CEE_iTOF02_MRPC_logic1 =
    new G4LogicalVolume(CEE_iTOF02_MRPC_solid1,          //its solid
                        CEE_MRPC_mat1,           //its material
                        "CEE_iTOF02_MRPC_logic1");            //its name
  CEE_iTOF02_MRPC_logic1 -> SetVisAttributes(CEE_iTOF0_Vis);
  for(int jd2=0;jd2<19;jd2++){
      new G4PVPlacement(0,                     //no rotation
                        G4ThreeVector(0,-2.5*mm+0.5*0.25*mm+jd2*0.25*mm,0),       //at (,,)
                        CEE_iTOF02_MRPC_logic1,            //its logical volume
                        "CEE_iTOF02_MRPC_phys1",               //its name
                        CEE_iTOF02_logic,                     //its mother  volume
                        false,                 //no boolean operation
                        jd2,                     //copy number
                        checkOverlaps);        //overlaps checking
    }

  if(id1<29){
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(400*mm-id1*28*mm,-2.5*mm,0),       //at (,,)
                      CEE_iTOF02_MRPC_logic,            //its logical volume
                      "CEE_iTOF02_MRPC_phys",               //its name
                      CEE_iTOF02_logic,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
    CEE_iTOF02_MRPC_logic -> SetVisAttributes(CEE_iTOF0_Vis);
  }
  else{
    int jd3=id1-29;
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(400*mm-14*mm-jd3*28*mm,2.5*mm,0),       //at (,,)
                      CEE_iTOF02_MRPC_logic,            //its logical volume
                      "CEE_iTOF02_MRPC_phys",               //its name
                      CEE_iTOF02_logic,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
    CEE_iTOF02_MRPC_logic -> SetVisAttributes(CEE_iTOF0_Vis);

  }
}




  new G4PVPlacement(0,                     //no rotation
                    CEE_iTOF02_p,       //at (,,)
                    CEE_iTOF02_logic,            //its logical volume
                    "CEE_iTOF02_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking
CEE_iTOF02_logic -> SetVisAttributes(default_Vis);
///// iTOF1
G4Box* CEE_iTOF1_solid =
  new G4Box("CEE_iTOF1_solid",                       //its name
     0.5*CEE_iTOF1_sx, 0.5*CEE_iTOF1_sy, 0.5*CEE_iTOF1_sz);     //its size

G4LogicalVolume* CEE_iTOF1_logic =
  new G4LogicalVolume(CEE_iTOF1_solid,          //its solid
                      CEE_iTOF1_mat,           //its material
                      "CEE_iTOF1_logic");            //its name


  new G4PVPlacement(0,                     //no rotation
                    CEE_iTOF1_p,       //at (,,)
                    CEE_iTOF1_logic,            //its logical volume
                    "CEE_iTOF1_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking
CEE_iTOF1_logic -> SetVisAttributes(CEE_iTOF1_Vis);
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// CEE_MWDC
//
/////MWDC11
G4Box* CEE_MWDC1_solid =
  new G4Box("CEE_MWDC1_solid",                       //its name
     0.5*CEE_MWDC1_sx, 0.5*CEE_MWDC1_sy, 0.5*CEE_MWDC1_sz);     //its size

G4LogicalVolume* CEE_MWDC11_logic =
  new G4LogicalVolume(CEE_MWDC1_solid,          //its solid
                      CEE_MWDC1_mat,           //its material
                      "CEE_MWDC11_logic");            //its name


  new G4PVPlacement(0,                     //no rotation
                    CEE_MWDC11_p,       //at (,,)
                    CEE_MWDC11_logic,            //its logical volume
                    "CEE_MWDC11_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking
CEE_MWDC11_logic -> SetVisAttributes(CEE_MWDC1_Vis);
/////MWDC12
G4LogicalVolume* CEE_MWDC12_logic =
  new G4LogicalVolume(CEE_MWDC1_solid,          //its solid
                      CEE_MWDC1_mat,           //its material
                      "CEE_MWDC12_logic");            //its name


  new G4PVPlacement(0,                     //no rotation
                    CEE_MWDC12_p,       //at (,,)
                    CEE_MWDC12_logic,            //its logical volume
                    "CEE_MWDC12_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking
CEE_MWDC12_logic -> SetVisAttributes(CEE_MWDC1_Vis);
/////MWDC21
G4Box* CEE_MWDC2_solid =
  new G4Box("CEE_MWDC2_solid",                       //its name
     0.5*CEE_MWDC2_sx, 0.5*CEE_MWDC2_sy, 0.5*CEE_MWDC2_sz);     //its size

G4LogicalVolume* CEE_MWDC21_logic =
  new G4LogicalVolume(CEE_MWDC2_solid,          //its solid
                      CEE_MWDC2_mat,           //its material
                      "CEE_MWDC21_logic");            //its name


  new G4PVPlacement(0,                     //no rotation
                    CEE_MWDC21_p,       //at (,,)
                    CEE_MWDC21_logic,            //its logical volume
                    "CEE_MWDC21_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking
CEE_MWDC21_logic -> SetVisAttributes(CEE_MWDC2_Vis);
/////MWDC22
G4LogicalVolume* CEE_MWDC22_logic =
  new G4LogicalVolume(CEE_MWDC2_solid,          //its solid
                      CEE_MWDC2_mat,           //its material
                      "CEE_MWDC22_logic");            //its name


  new G4PVPlacement(0,                     //no rotation
                    CEE_MWDC22_p,       //at (,,)
                    CEE_MWDC22_logic,            //its logical volume
                    "CEE_MWDC22_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking
CEE_MWDC22_logic -> SetVisAttributes(CEE_MWDC2_Vis);
/////MWDC31
G4Box* CEE_MWDC3_solid =
  new G4Box("CEE_MWDC3_solid",                       //its name
     0.5*CEE_MWDC3_sx, 0.5*CEE_MWDC3_sy, 0.5*CEE_MWDC3_sz);     //its size

G4LogicalVolume* CEE_MWDC31_logic =
  new G4LogicalVolume(CEE_MWDC3_solid,          //its solid
                      CEE_MWDC3_mat,           //its material
                      "CEE_MWDC31_logic");            //its name


  new G4PVPlacement(0,                     //no rotation
                    CEE_MWDC31_p,       //at (,,)
                    CEE_MWDC31_logic,            //its logical volume
                    "CEE_MWDC31_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking
CEE_MWDC31_logic -> SetVisAttributes(CEE_MWDC3_Vis);
/////MWDC32
G4LogicalVolume* CEE_MWDC32_logic =
  new G4LogicalVolume(CEE_MWDC3_solid,          //its solid
                      CEE_MWDC3_mat,           //its material
                      "CEE_MWDC32_logic");            //its name


  new G4PVPlacement(0,                     //no rotation
                    CEE_MWDC32_p,       //at (,,)
                    CEE_MWDC32_logic,            //its logical volume
                    "CEE_MWDC32_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking
CEE_MWDC32_logic -> SetVisAttributes(CEE_MWDC3_Vis);
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// CEE_eTOF
//

/////eTOF1
G4Box* CEE_eTOF_solid =
  new G4Box("CEE_eTOF_solid",                       //its name
     0.5*CEE_eTOF_sx, 0.5*CEE_eTOF_sy, 0.5*CEE_eTOF_sz);     //its size

G4LogicalVolume* CEE_eTOF1_logic =
  new G4LogicalVolume(CEE_eTOF_solid,          //its solid
                      CEE_eTOF_mat,           //its material
                      "CEE_eTOF1_logic");            //its name


  new G4PVPlacement(0,                     //no rotation
                    CEE_eTOF1_p,       //at (,,)
                    CEE_eTOF1_logic,            //its logical volume
                    "CEE_eTOF1_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking
CEE_eTOF1_logic -> SetVisAttributes(CEE_eTOF_Vis);
/////eTOF2
G4LogicalVolume* CEE_eTOF2_logic =
  new G4LogicalVolume(CEE_eTOF_solid,          //its solid
                      CEE_eTOF_mat,           //its material
                      "CEE_eTOF2_logic");            //its name


  new G4PVPlacement(0,                     //no rotation
                    CEE_eTOF2_p,       //at (,,)
                    CEE_eTOF2_logic,            //its logical volume
                    "CEE_eTOF2_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking
CEE_eTOF2_logic -> SetVisAttributes(CEE_eTOF_Vis);
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////




  /*
  //
  // Set Shape1 as scoring volume
  //
  fScoringVolume = logicShape1;

  //
  //always return the physical World
  //
  */
  return CEE_world_phys;
}
