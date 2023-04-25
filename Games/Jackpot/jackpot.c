
#include "jackpot.h"

#include <allegro.h>
#include <stdlib.h>
#include <time.h>
#include "stdio.h"

#define NUM_ICONS 4
// MACHINE A SOUS LOLA LE GALL
BITMAP *icons[NUM_ICONS];
char filename[20];

void load_icon() { // sous programme pour charger les icones
    for (int i = 0; i < NUM_ICONS; i++) {
        sprintf(filename, "../Games/Jackpot/IMAGES/icon%d.bmp",i);
        icons[i] = load_bitmap(filename, NULL);
        if (!icons[i]) { //blindage
            allegro_message("Erreur icone");
            exit(EXIT_FAILURE);
        }
    }
}

void load_slotmachine(char *path) { // charger la machine a sous en transparence
    BITMAP *slotmachine = NULL;
    slotmachine = load_bitmap(path, NULL);
    if (!slotmachine) { //blindage
        allegro_message("Erreur image slot machine");
        exit(EXIT_FAILURE);
    }
    set_trans_blender(255, 0, 255, 255);
    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    draw_trans_sprite(screen, slotmachine, (SCREEN_W - slotmachine->w) / 2, (SCREEN_H - slotmachine->h) / 2);
    destroy_bitmap(slotmachine);
}

int tourner_roues() {// tourner les roues de manière aleatoire
    srand(time(NULL));
    int last_rand = -1; // valeure d'icone impossible
    int win = 1;
    for (int i = 0; i < 3; i++) { // 3 car 3 roues
        int rand_icon= rand() % NUM_ICONS; // choix d'une icone aléatoire
        draw_sprite(screen, icons[rand_icon],  748+ i * (75 + 41+i*i), 430);// le calcule de la position NE PAS HESITER A CHANGER CAR JE L'AI TROUVER AU HASARD
        if (last_rand != -1 && last_rand != rand_icon) { // detecter la victoire
            win = 0;
        }
        last_rand=rand_icon;
    }
    return win;
}

void jackpot(){

    // ici on charge toutes les images
    BITMAP *fond;
    fond= load_bitmap("../Games/Jackpot/IMAGES/fond2.bmp",NULL);
    if (!fond) { //blindage
        allegro_message("Erreur image fond");
        exit(EXIT_FAILURE);
    }
    draw_sprite(screen,fond,23,50);
    load_slotmachine("../Games/Jackpot/IMAGES/SLOTREELS.bmp");
    load_icon();

    // boucle principale
    while (!key[KEY_ESC]) {
        if (key[KEY_ENTER]) {
            int win = tourner_roues();
            if (win==1) {
                textout_ex(screen, font, "+1 ticket", 300, 700, makecol(0, 255, 255), -1);
            }
            rest(100);
        }

        rest(10);
    }
    // on libère la memoire
    destroy_bitmap(fond);
    for (int i = 0; i < NUM_ICONS; i++) {
        destroy_bitmap(icons[i]);
    }

}
