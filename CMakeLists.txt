

cmake_minimum_required(VERSION 3.23)
project(ECE-WORLD C)

set(CMAKE_C_STANDARD 23)

add_executable(
        ECE-WORLD main.c
        Init_Allegro/allegro.c
        Init_Allegro/allegro.h
        Parc/Parc.c
        Parc/Parc.h
        Games/Course_Chevaux/chevaux.c
        Games/Course_Chevaux/chevaux.h
        Games/Snake/snake.c
        Games/Snake/snake.h
        Games/Ducky/ducky.c
        Games/Ducky/ducky.h
        Games/Guitar_hero/guitar_hero.c
        Games/Guitar_hero/guitar_hero.h
        Games/Ice_palace/ice_palace.c
        Games/Ice_palace/ice_palace.h
        Games/Jackpot/jackpot.c
        Games/Jackpot/jackpot.h
        Games/River/river.c
        Games/River/river.h
        Games/Shoot/shoot.c
        Games/Shoot/shoot.h
        Games/Taupe/taupe.c
        Games/Taupe/taupe.h
        Menu/menu.c
        Menu/menu.h)

target_link_libraries(ECE-WORLD -lmingw32 -lalleg44)

