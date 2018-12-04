cmake_minimum_required(VERSION 3.12)
project(jnp_star_wars)

set(CMAKE_CXX_STANDARD 17)

add_executable(starwars_example battle.h rebelfleet.h imperialfleet.h tests.cpp)