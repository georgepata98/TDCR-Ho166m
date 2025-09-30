#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
    return DefineVolumes();
}

G4VPhysicalVolume* MyDetectorConstruction::DefineVolumes()
{
    G4NistManager *nist = G4NistManager::Instance();

    G4Material *air = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *C = nist->FindOrBuildMaterial("G4_C");
    G4Material *H = nist->FindOrBuildMaterial("G4_H");
    G4Material *N = nist->FindOrBuildMaterial("G4_N");
    G4Material *O = nist->FindOrBuildMaterial("G4_O");
    G4Material *F = nist->FindOrBuildMaterial("G4_F");
    G4Material *P = nist->FindOrBuildMaterial("G4_P");
    G4Material *B = nist->FindOrBuildMaterial("G4_B");
    G4Material *Si = nist->FindOrBuildMaterial("G4_Si");
    G4Material *Na = nist->FindOrBuildMaterial("G4_Na");
    G4Material *Al = nist->FindOrBuildMaterial("G4_Al");

    G4Material *vid = new G4Material("vid", 1, 1.008*g/mole, 1e-25*g/cm3, kStateGas, 2.73*kelvin, 3e-18*pascal);

    G4Material *UGAB = new G4Material("UltimaGold AB", 0.98*g/cm3, 5);
    UGAB->AddMaterial(C, 76.3*perCent);
    UGAB->AddMaterial(H, 9.7*perCent);
    UGAB->AddMaterial(N, 0.1*perCent);
    UGAB->AddMaterial(O, 13.8*perCent);
    UGAB->AddMaterial(P, 0.1*perCent);
    
    G4Material *glass = nist->FindOrBuildMaterial("G4_Pyrex_Glass");

    G4Material *teflon = new G4Material("Teflon", 2.2*g/cm3, 2);
    teflon->AddMaterial(C, 24.02*perCent);
    teflon->AddMaterial(F, 75.98*perCent);
    
    G4Element* Cs = new G4Element("Cesium", "Cs", 55., 132.9*g/mole);
    G4Element* Sb = new G4Element("Antimony", "Sb", 51., 121.8*g/mole);
    G4Element* K  = new G4Element("Potassium", "K", 19., 39.1*g/mole);
    
    G4Material *catodMat = new G4Material("catodMat", 3.5*g/cm3, 3);
    catodMat->AddElement(Cs, 2);
    catodMat->AddElement(Sb, 1);
    catodMat->AddElement(K, 1);
    
    G4Material *borosilicat = new G4Material("borosilicat", 2.23*g/cm3, 5);
    borosilicat->AddMaterial(Si, 37.675*perCent);
    borosilicat->AddMaterial(B, 4.06849*perCent);
    borosilicat->AddMaterial(Na, 3.871*perCent);
    borosilicat->AddMaterial(Al, 1.2173*perCent);
    borosilicat->AddMaterial(O, 53.16821*perCent);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Dimensiuni fiola                                           |
    G4double hFiola = 50*mm; // inaltime fiola                    |
    G4double dFiola = 28*mm; // diametru fiola                    |
    G4double tFiola = 1.8*mm; // grosime fiola                    |
    G4double hLS = 22*mm; // inaltime LS                          |
    //                                                            |
    // Dimensiuni tija manevrat fiola                             |
    G4double hTija = 145*mm; // DE VERIFICAT                      |
    G4double dTija = 40*mm ; // DE VERIFICAT                      |
    //                                                            |
    // Dimensiuni Detectori                                       |
    G4double hDetector = 151.4*mm; //                             |
    G4double dDetector = 60*mm; //                                |
    //                                                            |
    G4double hPMT = 121*mm; //                                    |
    G4double dPMT = 51.5*mm; //                                   |
    //                                                            |
    G4double dCatod = 44*mm; //                                   |
    G4double hCatod = 300*nm; //                                  |
    //                                                            |
    G4double hFereastra = 0.5*mm; //                              |
    G4double dFereastra = 51.5*mm; //                             |
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    // INALTIME CAMERA OPTICA = 138 mm
    // CAPAC CAMERA OPTICA = 20 mm


    G4Box *solidWorld = new G4Box("solidWorld", 40*cm, 40*cm, 40*cm);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, air, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicWorld, "physWorld", 0, false, 0);

    // Fiola - pereti
    G4Tubs *sPereteFiola = new G4Tubs("sPereteFiola", dFiola/2 - tFiola, dFiola/2, hFiola/2, 0.*deg, 360.*deg);
    G4LogicalVolume *lPereteFiola = new G4LogicalVolume(sPereteFiola, glass, "lPereteFiola");
    G4VPhysicalVolume *pPereteFiola = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), lPereteFiola, "pPereteFiola", logicWorld, false, 0);

    G4Tubs *sPereteJosFiola = new G4Tubs("sPereteJosFiola", 0*mm, dFiola/2 - tFiola, tFiola/2, 0*deg, 360*deg);
    G4LogicalVolume *lPereteJosFiola = new G4LogicalVolume(sPereteJosFiola, glass, "lPereteJosFiola");
    G4VPhysicalVolume *pPereteJosFiola = new G4PVPlacement(0, G4ThreeVector(0, 0, -(hFiola/2 - tFiola/2)), lPereteJosFiola, "pPereteJosFiola", logicWorld, false, 0);

    G4Tubs *sPereteSusFiola = new G4Tubs("sPereteSusFiola", 0*mm, dFiola/2 - tFiola, tFiola/2, 0*deg, 360*deg);
    G4LogicalVolume *lPereteSusFiola = new G4LogicalVolume(sPereteSusFiola, glass, "lPereteSusFiola");
    G4VPhysicalVolume *pPereteSusFiola = new G4PVPlacement(0, G4ThreeVector(0, 0, hFiola/2 - tFiola/2), lPereteSusFiola, "pPereteSusFiola", logicWorld, false, 0);

    // LS (UltimaGold AB) in fiola
    G4Tubs *sLS = new G4Tubs("sLS", 0*mm, dFiola/2 - tFiola, hLS/2, 0*deg, 360*deg);
    G4LogicalVolume *lLS = new G4LogicalVolume(sLS, UGAB, "lLS");
    G4VPhysicalVolume *pLS = new G4PVPlacement(0, G4ThreeVector(0, 0, -(hFiola/2 - hLS/2 - tFiola)), lLS, "pLS", logicWorld, false, 0);

    // Aer in fiola (deasupra LS)
    G4double hAer = hFiola - hLS - 2*tFiola;
    G4Tubs *sAer = new G4Tubs("sAer", 0*mm, dFiola/2 - tFiola, hAer/2, 0*deg, 360*deg);
    G4LogicalVolume *lAer = new G4LogicalVolume(sAer, air, "lAer");
    G4VPhysicalVolume *pAer = new G4PVPlacement(0, G4ThreeVector(0, 0, (hFiola/2 - hAer/2 - tFiola)), lAer, "pAer", logicWorld, false, 0);

    // Tija
    G4Tubs *sTija = new G4Tubs("sTija", 0*mm, dTija/2, hTija/2, 0*deg, 360*deg);
    G4LogicalVolume *lTija = new G4LogicalVolume(sTija, teflon, "lTija");
    G4VPhysicalVolume *pTija = new G4PVPlacement(0, G4ThreeVector(0, 0, hFiola/2 + hTija/2), lTija, "pTija", logicWorld, false, 0);

    // Continutul celor 3 detectori
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    G4Tubs *sPMT = new G4Tubs("sPMT", 0*mm, dPMT/2, hPMT/2, 0*deg, 360*deg);
    G4LogicalVolume *lPMT = new G4LogicalVolume(sPMT, vid, "lPMT");

    G4Tubs *sPereteDetector = new G4Tubs("sPereteDetector", dPMT/2, dDetector/2, hDetector/2, 0*deg, 360*deg);
    G4LogicalVolume *lPereteDetector = new G4LogicalVolume(sPereteDetector, teflon, "lPereteDetector");

    G4Tubs *sPereteJosDetector = new G4Tubs("sPereteJosDetector", 0*mm, dPMT/2, (hDetector - hPMT)/2, 0*deg, 360*deg);
    G4LogicalVolume *lPereteJosDetector = new G4LogicalVolume(sPereteJosDetector, teflon, "lPereteJosDetector");
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Intregul detector 1 ca mother volume pt. piesele din el
    G4Tubs *sDetector1 = new G4Tubs("sDetector1", 0*mm, dDetector/2, hDetector/2, 0*deg, 360*deg);
    G4LogicalVolume *lDetector1 = new G4LogicalVolume(sDetector1, vid, "lDetector1");

    // Intregul detector 2 ca mother volume pt. piesele din el
    G4Tubs *sDetector2 = new G4Tubs("sDetector2", 0*mm, dDetector/2, hDetector/2, 0*deg, 360*deg);
    G4LogicalVolume *lDetector2 = new G4LogicalVolume(sDetector2, vid, "lDetector2");

    // Intregul detector 3 ca mother volume pt. piesele din el
    G4Tubs *sDetector3 = new G4Tubs("sDetector3", 0*mm, dDetector/2, hDetector/2, 0*deg, 360*deg);
    G4LogicalVolume *lDetector3 = new G4LogicalVolume(sDetector3, vid, "lDetector3");
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Punerea pieselor (PMT, pereti si fund) in Detectorul 1
    G4VPhysicalVolume *pPMT1 = new G4PVPlacement(0, G4ThreeVector(0, 0, hDetector/2 - hPMT/2), lPMT, "pPMT1", lDetector1, false, 0);
    G4VPhysicalVolume *pPereteDetector1 = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), lPereteDetector, "pPereteDetector1", lDetector1, false, 0);
    G4VPhysicalVolume *pPereteJosDetector1 = new G4PVPlacement(0, G4ThreeVector(0, 0, -hDetector/2 + (hDetector - hPMT)/2), lPereteJosDetector, "pPereteJosDetector1", lDetector1, false, 0);
    
    // Punerea pieselor (PMT, pereti si fund) in Detectorul 2
    G4VPhysicalVolume *pPMT2 = new G4PVPlacement(0, G4ThreeVector(0, 0, hDetector/2 - hPMT/2), lPMT, "pPMT2", lDetector2, false, 1);
    G4VPhysicalVolume *pPereteDetector2 = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), lPereteDetector, "pPereteDetector2", lDetector2, false, 1);
    G4VPhysicalVolume *pPereteJosDetector2 = new G4PVPlacement(0, G4ThreeVector(0, 0, -hDetector/2 + (hDetector - hPMT)/2), lPereteJosDetector, "pPereteJosDetector2", lDetector2, false, 1);
    
    // Punerea pieselor (PMT, pereti si fund) in Detectorul 3
    G4VPhysicalVolume *pPMT3 = new G4PVPlacement(0, G4ThreeVector(0, 0, hDetector/2 - hPMT/2), lPMT, "pPMT3", lDetector3, false, 2);
    G4VPhysicalVolume *pPereteDetector3 = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), lPereteDetector, "pPereteDetector3", lDetector3, false, 2);
    G4VPhysicalVolume *pPereteJosDetector3 = new G4PVPlacement(0, G4ThreeVector(0, 0, -hDetector/2 + (hDetector - hPMT)/2), lPereteJosDetector, "pPereteJosDetector3", lDetector3, false, 2);
    
    
    // Matricile de rotatie
    G4RotationMatrix *rot1 = new G4RotationMatrix();
    rot1->rotateY(-90*deg); // rotire in jurul lui Y
    
    G4RotationMatrix *rotation = new G4RotationMatrix();
    rotation->rotateY(90*deg);
    
    G4RotationMatrix *rot2 = new G4RotationMatrix();
    rot2->rotateZ(-60*deg); // rotire in jurul lui Z
    
    G4RotationMatrix *combRotation2 = new G4RotationMatrix(*rotation * *rot2);
    
    G4RotationMatrix *rot3 = new G4RotationMatrix();
    rot3->rotateZ(60*deg); // rotire in jurul lui Z
    
    G4RotationMatrix *combRotation3 = new G4RotationMatrix(*rotation * *rot3);
    
    
    // Pozitionarea celor 3 detectori
    G4VPhysicalVolume *pDetector1 = new G4PVPlacement(rot1, G4ThreeVector(-25*mm - hDetector/2, 0, 0), lDetector1, "pDetector1", logicWorld, false, 0);
    
    G4VPhysicalVolume *pDetector2 = new G4PVPlacement(combRotation2, G4ThreeVector(0.5*(25*mm + hDetector/2), cos(30*deg)*(25*mm + hDetector/2), 0), lDetector2, "pDetector2", logicWorld, false, 1);
    
    G4VPhysicalVolume *pDetector3 = new G4PVPlacement(combRotation3, G4ThreeVector(0.5*(25*mm + hDetector/2), -cos(30*deg)*(25*mm + hDetector/2), 0), lDetector3, "pDetector3", logicWorld, false, 2);
    
    
    // Fotocatozii
    G4Tubs *sCatod = new G4Tubs("sCatod", 0*mm, dCatod/2, hCatod/2, 0*deg, 360*deg);
    G4LogicalVolume *lCatod = new G4LogicalVolume(sCatod, catodMat, "lCatod");
    
    G4VPhysicalVolume *pCatod1 = new G4PVPlacement(rot1, G4ThreeVector(-25*mm + hCatod/2, 0, 0), lCatod, "pCatod1", logicWorld, false, 0);
    
    G4VPhysicalVolume *pCatod2 = new G4PVPlacement(combRotation2, G4ThreeVector(0.5*(25*mm - hCatod/2), cos(30*deg)*(25*mm - hCatod/2), 0), lCatod, "pCatod2", logicWorld, false, 1);
    
    G4VPhysicalVolume *pCatod3 = new G4PVPlacement(combRotation3, G4ThreeVector(0.5*(25*mm - hCatod/2), -cos(30*deg)*(25*mm - hCatod/2), 0), lCatod, "pCatod3", logicWorld, false, 2);
    
    
    // Ferestrele de intrare in PMT, in fata fotocatozilor
    G4Tubs *sFereastra = new G4Tubs("sFereastra", 0*mm, dFereastra/2, hFereastra/2, 0*deg, 360*deg);
    G4LogicalVolume *lFereastra = new G4LogicalVolume(sFereastra, borosilicat, "lFereastra");
    
    G4VPhysicalVolume *pFereastra1 = new G4PVPlacement(rot1, G4ThreeVector(-25*mm + hCatod + hFereastra/2, 0, 0), lFereastra, "pFereastra", logicWorld, false, 0);
    G4VPhysicalVolume *pFereastra2 = new G4PVPlacement(combRotation2, G4ThreeVector(0.5*(25*mm - hCatod - hFereastra/2), cos(30*deg)*(25*mm - hCatod - hFereastra/2), 0), lFereastra, "pFereastra1", logicWorld, false, 1);
    G4VPhysicalVolume *pFereastra3 = new G4PVPlacement(combRotation3, G4ThreeVector(0.5*(25*mm - hCatod - hFereastra/2), -cos(30*deg)*(25*mm - hCatod - hFereastra/2), 0), lFereastra, "pFereastra3", logicWorld, false, 2);

    
    
    // Vizualizare
    // ***************************************************************
    G4VisAttributes *red = new G4VisAttributes(G4Colour::Red());
    G4VisAttributes *brown = new G4VisAttributes(G4Colour::Brown());
    G4VisAttributes *blue = new G4VisAttributes(G4Colour::Blue());
    G4VisAttributes *white = new G4VisAttributes(G4Colour::White());
    G4VisAttributes *green = new G4VisAttributes(G4Colour::Green());
    
    red->SetVisibility(true);
    red->SetForceSolid(false);
    brown->SetVisibility(true);
    brown->SetForceSolid(false);
    blue->SetVisibility(true);
    blue->SetForceSolid(true);
    white->SetVisibility(true);
    white->SetForceSolid(true);
    green->SetVisibility(true);
    green->SetForceSolid(true);
    lPMT->SetVisAttributes(red);
    lPereteDetector->SetVisAttributes(brown);
    lPereteJosDetector->SetVisAttributes(brown);
    lPereteFiola->SetVisAttributes(G4Colour::Yellow());
    lPereteJosFiola->SetVisAttributes(G4Colour::Yellow());
    lPereteSusFiola->SetVisAttributes(G4Colour::Yellow());
    lLS->SetVisAttributes(blue);
    lAer->SetVisAttributes(G4Colour::White());
    lTija->SetVisAttributes(white);
    lCatod->SetVisAttributes(green);
    lFereastra->SetVisAttributes(blue);
    // ***************************************************************


    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
    G4MultiFunctionalDetector *LS;
    G4VPrimitiveScorer *primitive;

    LS = new G4MultiFunctionalDetector("LS");
    primitive = new G4PSEnergyDeposit("Edep");

    LS->RegisterPrimitive(primitive);

    SetSensitiveDetector("lLS", LS); // numele volumului logic care sa fie detector, nume MultiFunctionalDetector
    
    G4SDManager::GetSDMpointer()->AddNewDetector(LS);
}
