cmake_minimum_required(VERSION 3.24)
project(Projet2 C)

set(CMAKE_C_STANDARD 23)

set(CMAKE_PREFIX_PATH /usr/local/lib/allegro/4.4.3)

find_package(PkgConfig REQUIRED)
pkg_search_module(ALLEGRO REQUIRED allegro)

include_directories(${ALLEGRO_INCLUDE_DIRS})
add_executable(Projet2 main.c)
target_link_libraries(Projet2 ${ALLEGRO_LIBRARIES})

