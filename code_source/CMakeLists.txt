cmake_minimum_required(VERSION 3.16)
project(InfoSysteme VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(InfoSysteme
    main.cpp
    fenetreprincipale.cpp
    fenetreprincipale.h
    fenetreprincipale.ui
)

target_link_libraries(InfoSysteme PRIVATE
    Qt6::Core
    Qt6::Widgets
)
