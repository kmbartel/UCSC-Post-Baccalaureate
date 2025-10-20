#include "generator.hh"
#include "G4Geantino.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName="proton";
    G4ParticleDefinition *particle = particleTable->FindParticle("proton");

    //for debugging:
    //G4String particleName="geantino";
    //G4ParticleDefinition *particle = particleTable->FindParticle("geantino");
    
    //position particle gun at start, momentum direction => particle created in z direction
    G4ThreeVector pos(0., 0., -13.*m);
    G4ThreeVector mom(0., 0., 1.);
    
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    //standard unit of energy/momentum is MeV
    fParticleGun->SetParticleEnergy(120.*GeV);
    fParticleGun->SetParticleDefinition(particle);
    
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
