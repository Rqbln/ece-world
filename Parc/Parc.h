#include "stdio.h"
#include <allegro.h>
#include "../joueur/joueur.h"
#include "../Sauvegarde/sauvegarde.h"
#include "../Games/Course_Chevaux/chevaux.h"
#include "../Games/Jackpot/jackpot.h"
#include "../Games/Snake/snake.h"
#include "../Games/Taupe/taupe.h"
#include "../Games/Shoot/shoot.h"
#include "../Games/Guitar_hero/guitar_hero.h"
#include "../Games/Ducky/ducky.h"
#include "../Games/River/river.h"
#include "../ScoreTab/scoreTab.h"

#ifndef PROJET_ALGO2_PARC_H
#define PROJET_ALGO2_PARC_H
#endif //PROJET_ALGO2_PARC_H

#define HEIGHT 1080
#define WIDTH 1920
#define nbMusique 1//6
#define nbcheval 6
#define nbdragon 1

#define grille 5
#define action 16
#define posirang 4

#define NB_JOUEURS 2



void parc();
void parc2();

