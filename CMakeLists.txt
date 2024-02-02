cmake_minimum_required(VERSION 3.12)
project(ProtoChess6)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Find and include SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

# Add all source files with relative path
add_executable(ProtoChess6
    Arrow.hpp
    Arrow.cpp
    Utilities.hpp
    Utilities.cpp
    Board.hpp
    Board.cpp
    MoveFinder.cpp
    CheckDetection.cpp
    VisualBoard.hpp
    VisualBoard.cpp
    Player.hpp
    Player.cpp
    Game.hpp
    Game.cpp
    main.cpp
)

# Link SFML libraries
target_link_libraries(ProtoChess6 PRIVATE sfml-graphics sfml-window sfml-system)