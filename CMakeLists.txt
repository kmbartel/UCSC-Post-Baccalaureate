cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(DarkQuest)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

add_executable(simDarkQuest simDarkQuest.cc ${sources} ${headers})
target_link_libraries(simDarkQuest ${Geant4_LIBRARIES})

add_custom_target(DarkQuest DEPENDS simDarkQuest)
