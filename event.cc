#include "event.hh"
#include "G4Event.hh"

MyEventAction::MyEventAction()
{}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event* event)
{
    auto eventID = event->GetEventID();
    G4cout << "Event #: " << eventID << G4endl;
}

void MyEventAction::EndOfEventAction(const G4Event* event)
{}