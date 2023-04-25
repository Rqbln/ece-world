#ifndef ECE_WORLD_JACKPOT_H
#define ECE_WORLD_JACKPOT_H
#endif //ECE_WORLD_JACKPOT_H
#include <allegro.h>
#include <stdlib.h>
#include <time.h>
#include "stdio.h"

#define NUM_ICONS 4
void load_icon();
void load_slotmachine(char *path);
int tourner_roues();
void jackpot();

//il faut que tu utilise les :
// #define HEIGHT 1080
//#define WIDTH 1920
// avec des multiplications et des divisions et pas des addition
// pour definir les coordonné des images comme ca l emplacement de tes image et de tes sprites
// ne dependerons plus de la resolution
//l image de fond n est pas definit a la bonne taille

//et sinon le probleme que tu avais c etais juste un truc tout con:
//char filename[20];  => 20 caracteres
//sprintf(filename, "../Games/Jackpot/IMAGES/icon%d.bmp",i); =>33 caracteres