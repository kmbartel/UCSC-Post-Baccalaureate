This project contains all the relevant pieces of my post-baccalaureate work at UC Santa Cruz during my 2024-25 gap year (Summer 2024 and Fall 2024). The goal of the project is to model the possible production and behavior of dark matter particles produced at FermiLab's DarkQuest experiment. To model the detector geometry and produce initial events, I used CERN's Geant4 toolkit and corresponding code written in C++. These initial events were then decayed by hand into potential dark matter particles (i.e. pi+ --> gamma + dark photon) using Python code I've written. Our ultimate goal is to use machine learning to compare my simulated events to actual DarkQuest data. This work would have been impossible without the guidance of Prof. Stefania Gori.

Provided you have a working installation of Geant4 (see https://geant4.web.cern.ch), the .txt, .cc, .hh, and .ipynb files below are all you need to run both the DarkQuest detector simulation code to produce events and to subsequently decay them into dark matter using the Python code. For a summary, see below:

1. The files needed for the Geant4 detector simulation are as follows:
   a. CMakeLists.txt: 
   b. simDarkQuest.cc: The main program, containing the run manager, the physics list specifications (currently FTFP_BERT), and all visualization/UI commands.          Particle trajectories are set to be distinguished by particle ID, with colors set to default.
   c. action.cc: The program that initializes the generation of particles.
   d. action.hh: Contains header files for action.cc.
   e. construction.cc: The program that defines the detector geometry of DarkQuest. The 7 components of the detector are set in a "world volume", a 5m x 7m x 26m       box of air, and are: the FMag and beam dump (4.6m x 5m x 5m iron box), station 1 (2m x 2m x 1m silicon box), KMag (4m x 4m x 3m iron box with a 2m x 2m x         3m hole), station 2 (3m x 3m x 1m silicon box), station 3 (3m x 3m x 1m silicon box), the absorber wall (4m x 4m x 1m lead box), and station 4 (4m x 4m x         3m silicon box). Additionally, there is a "detector" made of air placed between the FMag/beam dump and station 1, though this has yet to be coded to detect       anything. The FMag/beam dump has a local magnetic field set to 1.8 tesla, defined at the bottom of the code.
   f. construction.hh: Contains header files for construction.cc.
   g. generator.cc: The program that defines the particle beam, set to generate 120 GeV protons at the beginning of the world volume.
   h. generator.hh: Contains header files for generator.cc.
   i. physics.cc: The initialy used program that defined the physics lists to be used, now super-ceded by the alternative definition in simDarkQuest.cc.
   j. physics.hh: Contains header files for physics.cc.
