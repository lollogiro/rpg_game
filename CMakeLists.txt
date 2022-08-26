cmake_minimum_required(VERSION 3.18)
project(progetto_programmazione)

set(CMAKE_CXX_STANDARD 14)

add_executable(progetto_programmazione
        main.cpp Artifact.cpp Bullet.cpp Enemy.cpp Entity.cpp Level.cpp LivingEntity.cpp Power.cpp Wall.cpp constants.cpp GameState.hpp Player.cpp Player.hpp)

target_link_libraries(progetto_programmazione ncurses)