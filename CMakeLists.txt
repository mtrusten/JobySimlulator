cmake_minimum_required(VERSION 3.10)

project(Simulator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Simulator main.cpp
                         SimStats.cpp
                         SimTimer.cpp
                         StatsGatherer.cpp
                         Transport.cpp
                         TransportAlpha.cpp
                         TransportBeta.cpp
                         TransportCharlie.cpp
                         TransportDelta.cpp
                         TransportEcho.cpp
                         TransportFactory.cpp)