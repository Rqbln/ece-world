
#ifndef ECE_WORLD_DUCKY_H
#define ECE_WORLD_DUCKY_H

#endif //ECE_WORLD_DUCKY_H


#include <allegro.h>
#include <time.h>
#include <stdio.h>

#define NCANARD 40 // Nombre de canards
#define TX 60 // Largeur canards
#define TY 70 // Hauteur canards

typedef struct{ // structure canard avec la position et son déplacement
    int posX, posY;
    int depX, depY;
}t_canard;


void aleaDepCanard(t_canard* canard);
t_canard* creerCanard();
void actualiserCanard(t_canard* canard);
void dessinerCanard(BITMAP* buffer, t_canard* canard);
void remplirTab(t_canard* colonies[NCANARD]);
int collision(t_canard *c1, t_canard *c2);
void actualiserTab(t_canard* colonies[NCANARD]);
void dessinerTab(BITMAP* buffer, t_canard* colonies[NCANARD]);
int canardClicked(t_canard* canard, int mouseX, int mouseY);
void player1(int *score1);
void player2(int *score2);
void ducky();