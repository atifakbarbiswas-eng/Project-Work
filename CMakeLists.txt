cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(ScatPolSim)

option(WITH_GEANT4_UIVIS "Build with Geant4 UI and Vis drivers" ON)

if(WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
else()
    find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${Geant4_INCLUDE_DIR}
)

file(GLOB sources "${PROJECT_SOURCE_DIR}/*.cc")
file(GLOB headers "${PROJECT_SOURCE_DIR}/*.hh")

file(GLOB MACRO_FILES "*.Mac")
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_SOURCE_DIR})

add_executable(sim ${sources} ${headers})

target_link_libraries(sim ${Geant4_LIBRARIES})

add_custom_target(Simulation DEPENDS sim)