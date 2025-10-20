#include "stepping.hh"
#include "G4ParticleDefinition.hh"
#include "G4AnalysisManager.hh"
#include "G4Step.hh"

MySteppingAction::MySteppingAction()
{}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step* step)
{
    //new KE, mom. stuff from G4 forums
    //check to make sure track isn't leaving the worl vol. first (returns physical vol. as null ptr)
    G4bool worldboundary = step->GetPostStepPoint()->GetStepStatus()==fWorldBoundary;
    if (!worldboundary){

        G4LogicalVolume* post_volume = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
        G4String vol_name = post_volume->GetName();
        G4bool boundary = step->GetPreStepPoint()->GetStepStatus()==fGeomBoundary;

        if (((vol_name == "Detector") || (vol_name == "DetectorTwo")) && (boundary)){
            //get kinetic energy, momenta, particle name
            G4double KE = step->GetPostStepPoint()->GetKineticEnergy();
            G4double p_x = step->GetPostStepPoint()->GetMomentum().x(); 
            G4double p_y = step->GetPostStepPoint()->GetMomentum().y();
            G4double p_z = step->GetPostStepPoint()->GetMomentum().z();
        
            G4String particleName = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();

            //print out the 4-mom.
            G4cout << "Particle Name, 4-mom.: " << vol_name << ", " << particleName << ", " << "(" << KE << ", " << p_x << ", " << p_y << ", " << p_z << ")" << G4endl;

            //record the 4-mom.
            G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
            analysisManager->FillNtupleSColumn(0, 0, vol_name);
            analysisManager->FillNtupleSColumn(0, 1, particleName);
            analysisManager->FillNtupleDColumn(0, 2, KE);
            analysisManager->FillNtupleDColumn(0, 3, p_x);
            analysisManager->FillNtupleDColumn(0, 4, p_y);
            analysisManager->FillNtupleDColumn(0, 5, p_z);
            analysisManager->AddNtupleRow(0);
        }
        
    }

}
