#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    
    //volumes are always half-volumes (i.e. divide the actual volume by two)
    //old world volume:
    G4Box *solidWorld = new G4Box("solidWorld", 2.5*m, 3.5*m, 13.*m);

    //G4Box *solidWorld = new G4Box("solidWorld", 2.5*m, 3.5*m, 6.*m);
    
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
    
    //we need 7 shapes for the most basic detector sketch:
    
    //SHAPE 1: FMag and Beam Dump (iron)
    G4Material *beamdumpMat = nist->FindOrBuildMaterial("G4_Fe");
    //old position:
    G4ThreeVector pos1 = G4ThreeVector(0, 0, -9.5*m);

    //G4ThreeVector pos1 = G4ThreeVector(0, 0, -2.5*m);
    
    //new dimensions (1 meter depth):
    //G4Box *solidShape1 = new G4Box("BeamDump", 2.3*m, 2.5*m, 0.25*m);
    G4Box *solidShape1 = new G4Box("BeamDump", 2.3*m, 2.5*m, 0.5*m);

    //original dimensions:
    //G4Box *solidShape1 = new G4Box("BeamDump", 2.3*m, 2.5*m, 2.5*m);
    
    //G4LogicalVolume *logicShape1 = new G4LogicalVolume(solidShape1, beamdumpMat, "BeamDump");
    logicShape1 = new G4LogicalVolume(solidShape1, beamdumpMat, "BeamDump");
    
    new G4PVPlacement(nullptr,  // no rotation
      pos1,                     // at position
      logicShape1,              // its logical volume
      "BeamDump",               // its name
      logicWorld,               // its mother  volume
      false,                    // no boolean operation
      0,                        // copy number
      true);                    // overlaps checking
    
    //set the color and style
    G4VisAttributes *beamdumpVisAtt = new G4VisAttributes(G4Colour(1., 1., 0.));
    beamdumpVisAtt->SetForceSolid(true);
    logicShape1->SetVisAttributes(beamdumpVisAtt);
    
    //DETECTOR
    G4Material *detectorMat = nist->FindOrBuildMaterial("G4_AIR");
    //old detector placement
    G4ThreeVector posDetect = G4ThreeVector(0, 0, -6.625*m);

    //G4ThreeVector posDetect = G4ThreeVector(0, 0, -12.5*m);

    //G4ThreeVector posDetect = G4ThreeVector(0, 0, -9.625*m);
    
    G4Box *solidDetector = new G4Box("Detector", 2.5*m, 3.5*m, 0.125*m);
    
    //if you don't want a segfault, make sure to not use the * operator here
    G4LogicalVolume *logicDetector = new G4LogicalVolume(solidDetector, detectorMat, "Detector");
    //logicDetector = new G4LogicalVolume(solidDetector, detectorMat, "Detector");
    
    new G4PVPlacement(nullptr,  // no rotation
      posDetect,                // at position
      logicDetector,            // its logical volume
      "Detector",               // its name
      logicWorld,               // its mother  volume
      false,                    // no boolean operation
      0,                        // copy number
      true);                    // overlaps checking
    
    //SHAPE 2: Station 1 (silicon)
    G4Material *stat1Mat = nist->FindOrBuildMaterial("G4_Si");
    G4ThreeVector pos2 = G4ThreeVector(0, 0, -6.*m);
    
    G4Box *solidShape2 = new G4Box("Station1", 1.*m, 1.*m, 0.5*m);
    
    G4LogicalVolume *logicShape2 = new G4LogicalVolume(solidShape2, stat1Mat, "Station1");
    
    new G4PVPlacement(nullptr,  // no rotation
      pos2,                     // at position
      logicShape2,              // its logical volume
      "Station1",               // its name
      logicWorld,               // its mother  volume
      false,                    // no boolean operation
      0,                        // copy number
      true);                    // overlaps checking
    
    //set the color and style
    G4VisAttributes *stat1VisAtt = new G4VisAttributes(G4Colour(1., 0., 1.));
    stat1VisAtt->SetForceSolid(true);
    logicShape2->SetVisAttributes(stat1VisAtt);
    
    //SHAPE 3: KMag (iron)
    G4Material *kmagMat = nist->FindOrBuildMaterial("G4_Fe");
    G4ThreeVector pos3 = G4ThreeVector(0, 0, -2.5*m);
    
    G4Box *solidShape3 = new G4Box("initKMag", 2.*m, 2.*m, 1.5*m);
    
    G4Box *holeBox = new G4Box("Hole", 1.*m, 1.*m, 1.5*m);
    
    G4SubtractionSolid *finalsolidShape3 = new G4SubtractionSolid("solidKMag", solidShape3, holeBox);
    
    G4LogicalVolume *logicShape3 = new G4LogicalVolume(finalsolidShape3, kmagMat, "KMag");
    
    new G4PVPlacement(nullptr,  // no rotation
      pos3,                     // at position
      logicShape3,              // its logical volume
      "KMag",                   // its name
      logicWorld,               // its mother  volume
      false,                    // no boolean operation
      0,                        // copy number
      true);                    // overlaps checking
    
    //set the color and style
    G4VisAttributes *kmagVisAtt = new G4VisAttributes(G4Colour(0., 1., 1.));
    kmagVisAtt->SetForceSolid(true);
    logicShape3->SetVisAttributes(kmagVisAtt);
    
    //SHAPE 4: Station 2 (silicon)
    G4Material *stat2Mat = nist->FindOrBuildMaterial("G4_Si");
    G4ThreeVector pos4 = G4ThreeVector(0, 0, 0.5*m);
    
    G4Box *solidShape4 = new G4Box("solidStation2", 1.5*m, 1.5*m, 0.5*m);
    
    G4LogicalVolume *logicShape4 = new G4LogicalVolume(solidShape4, stat2Mat, "Station2");
    
    new G4PVPlacement(nullptr,  // no rotation
      pos4,                     // at position
      logicShape4,              // its logical volume
      "Station2",               // its name
      logicWorld,               // its mother  volume
      false,                    // no boolean operation
      0,                        // copy number
      true);                    // overlaps checking
    
    //set the color and style
    G4VisAttributes *stat2VisAtt = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5));
    stat2VisAtt->SetForceSolid(true);
    logicShape4->SetVisAttributes(stat2VisAtt);
    
    //SHAPE 5: Station 3 (silicon)
    G4Material *stat3Mat = nist->FindOrBuildMaterial("G4_Si");
    G4ThreeVector pos5 = G4ThreeVector(0, 0, 4.5*m);
    
    G4Box *solidShape5 = new G4Box("solidStation3", 1.5*m, 1.5*m, 0.5*m);
    
    G4LogicalVolume *logicShape5 = new G4LogicalVolume(solidShape5, stat3Mat, "Station3");
    
    new G4PVPlacement(nullptr,  // no rotation
      pos5,                     // at position
      logicShape5,              // its logical volume
      "Station3",               // its name
      logicWorld,               // its mother  volume
      false,                    // no boolean operation
      0,                        // copy number
      true);                    // overlaps checking
    
    //set the color and style
    G4VisAttributes *stat3VisAtt = new G4VisAttributes(G4Colour(1., 0., 0.));
    stat3VisAtt->SetForceSolid(true);
    logicShape5->SetVisAttributes(stat3VisAtt);

    //DETECTOR 2
    G4Material *detectorTwoMat = nist->FindOrBuildMaterial("G4_AIR");
    
    G4ThreeVector posDetectTwo = G4ThreeVector(0, 0, 5.625*m);
    
    G4Box *solidDetectorTwo = new G4Box("DetectorTwo", 2.5*m, 3.5*m, 0.125*m);
    
    //if you don't want a segfault, make sure to not use the * operator here
    G4LogicalVolume *logicDetectorTwo = new G4LogicalVolume(solidDetectorTwo, detectorMat, "DetectorTwo");
    //logicDetectorTwo = new G4LogicalVolume(solidDetectorTwo, detectorTwoMat, "DetectorTwo");
    
    new G4PVPlacement(nullptr,  // no rotation
      posDetectTwo,             // at position
      logicDetectorTwo,         // its logical volume
      "DetectorTwo",            // its name
      logicWorld,               // its mother  volume
      false,                    // no boolean operation
      0,                        // copy number
      true);                    // overlaps checking
    
    //SHAPE 6: Absorber Wall (lead)
    G4Material *absorberMat = nist->FindOrBuildMaterial("G4_Pb");
    G4ThreeVector pos6 = G4ThreeVector(0, 0, 7.25*m);
    
    G4Box *solidShape6 = new G4Box("solidAbsorber", 2.*m, 2.*m, 0.5*m);
    
    G4LogicalVolume *logicShape6 = new G4LogicalVolume(solidShape6, absorberMat, "Absorber");
    
    new G4PVPlacement(nullptr,  // no rotation
      pos6,                     // at position
      logicShape6,              // its logical volume
      "Absorber",               // its name
      logicWorld,               // its mother  volume
      false,                    // no boolean operation
      0,                        // copy number
      true);                    // overlaps checking
    
    //set the color and style
    G4VisAttributes *absorbVisAtt = new G4VisAttributes(G4Colour(0., 0., 1.));
    absorbVisAtt->SetForceSolid(true);
    logicShape6->SetVisAttributes(absorbVisAtt);
    
    //SHAPE 7: Station 4 (silicon)
    G4Material *stat4Mat = nist->FindOrBuildMaterial("G4_Si");
    G4ThreeVector pos7 = G4ThreeVector(0, 0, 9.5*m);
    
    G4Box *solidShape7 = new G4Box("solidStation4", 2.*m, 2.*m, 1.5*m);
    
    G4LogicalVolume *logicShape7 = new G4LogicalVolume(solidShape7, stat4Mat, "Station4");
    
    new G4PVPlacement(nullptr,  // no rotation
      pos7,                     // at position
      logicShape7,              // its logical volume
      "Station4",               // its name
      logicWorld,               // its mother  volume
      false,                    // no boolean operation
      0,                        // copy number
      true);                    // overlaps checking
    
    //set the color and style
    G4VisAttributes *stat4VisAtt = new G4VisAttributes(G4Colour(0., 1., 0.));
    stat4VisAtt->SetForceSolid(true);
    logicShape7->SetVisAttributes(stat4VisAtt);
    
    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    //MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
    
    //logicDetector->SetSensitiveDetector(sensDet);

    //MySecondSensitiveDetector *sensDetTwo = new MySecondSensitiveDetector("SecondSensitiveDetector");
    
    //logicDetectorTwo->SetSensitiveDetector(sensDetTwo);
    
    G4MagneticField *magField = new G4UniformMagField(G4ThreeVector(1.8*tesla, 0., 0.));
    G4FieldManager* fieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
    fieldMgr->SetDetectorField(magField);
    fieldMgr->CreateChordFinder(magField);

    G4bool allLocal = true;
    logicShape1->SetFieldManager(fieldMgr, allLocal); //here insert the name of the logical vol. with the B-field
}
