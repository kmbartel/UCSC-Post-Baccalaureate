This project contains all the relevant pieces of my post-baccalaureate work at UC Santa Cruz during my 2024-25 gap year (Summer 2024 and Fall 2024). The goal of the project is to model the possible production and behavior of dark matter particles produced at FermiLab's DarkQuest experiment. To model the detector geometry and produce initial events, I used CERN's Geant4 toolkit and corresponding code written in C++. These initial events were then decayed by hand into potential dark matter particles (i.e. pi+ --> gamma + dark photon) using Python code I've written. Our ultimate goal is to use machine learning to compare my simulated events to actual DarkQuest data. This work would have been impossible without the guidance of Prof. Stefania Gori.

Provided you have a working installation of Geant4 (see https://geant4.web.cern.ch), the .cc, .hh, and .ipynb files below are all you need to run both the DarkQuest detector simulation code to produce events and to subsequently decay them into dark matter using the Python code. For a summary, see below:

1. The files needed for the Geant4 detector simulation are as follows:
   a. simDarkQuest.cc: 
   b. action.cc:
   c. action.hh:
   d. construction.cc:
   e. construction.hh:
   f. generator.cc:
   g. generator.hh:
   h. physics.cc:
   i. physics.hh:
