//
// Created by bapti on 19/04/2023.
//

#include "shoot.h"
#include <time.h>
#include <stdlib.h>
/*
void baloon() {

    srand(time(NULL));
    int gameover;
    int baloon_h=309;
    int baloon_w=192;
    int temps;
    int end=0;
    int randir[2][5];
    int baloonxy[2][5];
    int baloonState[5];
    int vxy=5;
    for (int i = 0; i < 5; ++i) {
        baloonxy[1][i]=rand()%1800;
        baloonxy[2][i]=rand()%900;
        randir[1][i]=0;
        randir[2][i]=0;
    }

    // Chargement des images
    BITMAP* background = load_bitmap("../image/background.bmp", NULL);
    if(!background){
        allegro_message("../Games/Baloon/image/background.bmp");
        exit(EXIT_FAILURE);
    }
    BITMAP* baloon = load_bitmap("../image/baloon.bmp", NULL);
    if(!background){
        allegro_message("../Games/Baloon/image/baloon.bmp");
        exit(EXIT_FAILURE);
    }


    // Création du buffer
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    clear_to_color(buffer, makecol(0, 0, 0));
    // Boucle principale du jeu
    while (!key[KEY_ESC])
    {
        srand(time(NULL));
        // Copie de l'image dans le back buffer
        blit(background, buffer, 0, 0, 0, 0, background->w, background->h);
        for (int i = 0; i < 5; ++i) {
            if (baloonState[i]==0) draw_sprite(buffer,baloon,baloonxy[1][i],baloonxy[2][i]);
            //vérifie si le ballon a été éclaté
            if ((mouse_b & 1)&&(mouse_x>baloonxy[1][i])&&(mouse_x<(baloonxy[1][i]+baloon_w))&&(mouse_y>baloonxy[2][i])&&(mouse_y<(baloonxy[2][i]+baloon_w))) {
                baloonState[i]=1;
                end++;
            }
            baloonxy[1][i]+=randir[1][i];
            baloonxy[2][i]+=randir[2][i];
            randir[1][i]=(rand()%(1-(-1))+1)*vxy;
            randir[2][i]=(rand()%(1-(-1))+1)*vxy;
            //Rebond sur les bords de l'écran
            if ((baloonxy[1][i]<=0 ||(baloonxy[1][i]+baloon_w>=1920)))randir[1][i]-=randir[1][i];

        }
        //Condition de "Victoire"
        if (end==6) {
            textout_centre_ex(buffer, font, "Fini !", SCREEN_W/2, SCREEN_H/2, makecol(255, 0, 0), -1);
        }
        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
        // Affichage du buffer principal
        vsync();

    }


    // Libération des ressources
    destroy_bitmap(background);
    destroy_bitmap(buffer);
}
int main() {
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1920, 1080, 0, 0);
    show_mouse(screen);
    set_display_switch_mode(SWITCH_BACKGROUND);
    baloon();
    return 0;
}
*/