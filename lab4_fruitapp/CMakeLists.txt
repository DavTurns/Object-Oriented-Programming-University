cmake_minimum_required(VERSION 3.24)
project(lab4new)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab4new FruitApp.cpp UI/FruitUI.cpp Repository/FruitRepo.cpp Domain/Fruit.cpp Controller/FruitController.cpp Tests/tests.h Tests/tests.cpp)
