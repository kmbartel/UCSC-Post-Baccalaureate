#include "run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    analysisManager->OpenFile("output.csv");
    analysisManager->CreateNtuple("step", "step");
    analysisManager->CreateNtupleSColumn("Detector Name");
    analysisManager->CreateNtupleSColumn("Particle Name");
    analysisManager->CreateNtupleDColumn("Particle Energy");
    analysisManager->CreateNtupleDColumn("Particle p_x"); 
    analysisManager->CreateNtupleDColumn("Particle p_y");
    analysisManager->CreateNtupleDColumn("Particle p_z");
    analysisManager->FinishNtuple();


}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    analysisManager->Write();
    analysisManager->CloseFile();
}