cmake_minimum_required(VERSION 3.24)
project(lab5_II)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab5_II main.cpp UI/UI.cpp Tests/tests.cpp Domain/Scooter.cpp Controller/Controller.cpp Repository/Repo.h Repository/MemoryRepo.h Repository/ScooterFileRepo.h Repository/ScooterFileRepo.cpp Domain/Customer.cpp Domain/Customer.h Repository/CustomerFileRepo.h Repository/CustomerFileRepo.cpp)
