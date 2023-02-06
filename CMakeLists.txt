cmake_minimum_required(VERSION 3.9.0)

project(LACT_MATCH VERSION 1.0)
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/compiled")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_INSTALL_PREFIX}/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1 CACHE BOOL "for clang" FORCE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-O3")

find_package(ROOT  CONFIG REQUIRED COMPONENTS Minuit)
include("${ROOT_USE_FILE}")
root_generate_dictionary(LHEvent ${PROJECT_SOURCE_DIR}/include/LHEvent.h   
		LINKDEF ${PROJECT_SOURCE_DIR}/include/LHEventLinkDef.h)



add_executable(LACT_MATCH)
target_sources(LACT_MATCH PUBLIC ${PROJECT_SOURCE_DIR}/src/LACT_MATCH.cpp  ${PROJECT_SOURCE_DIR}/src/LACTree.cpp ${PROJECT_SOURCE_DIR}/src/LHEvent.cc LHEvent.cxx)
target_include_directories(LACT_MATCH PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(LACT_MATCH PRIVATE  ${ROOT_LIBRARIES})
