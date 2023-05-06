cmake_minimum_required(VERSION 3.25)
project(MP1)

set(CMAKE_CXX_STANDARD 20)

add_executable(MP1 main.cpp Vehicle.h Vehicle.cpp Car.h Car.cpp  utils/Extension_owning.h utils/Extension_owning.h)

find_package(Boost 1.81 REQUIRED COMPONENTS
        serialization)

target_link_libraries(MP1 Boost::serialization)