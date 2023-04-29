//-~-~-~-~-~-~-~TURTLE RIVER-~-~-~-~-~-~-~-~-~-
#include "river.h"
#include<time.h>
#include <stdlib.h>
int main()
{
    srand(time(NULL));
    int gameover;
    int temps;
    int restx =10;
    char winmessage [64];

    int frogw=195;
    int frogx=500;
    int frogy=730;
    int frogvxy=2;
    //position et vitesse des bûches (1,2,3,4 = bûches normales ; 5,6,7,8= bûches grandes)
    int log[2][8];
    int logw[8];
    int logx0left=-600;
    int logx0right=2200;
    int dlog=1;
    int collision;
    int direction;
    int randbmp[8];
    int randtime[8];
    // Initialisation d'Allegro
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1920, 1080, 0, 0);


    // Chargement des images
    BITMAP* background = load_bitmap("../image/background.bmp", NULL);
    if(!background){
        allegro_message("../Games/River/image/background.bmp");
        exit(EXIT_FAILURE);
    }
    BITMAP* frog= load_bitmap("../image/frog.bmp",NULL);
    if(!frog){
        allegro_message("../Games/River/image/frog.bmp");
        exit(EXIT_FAILURE);
    }
    BITMAP* log0= load_bitmap("../image/log0.bmp",NULL);
    if(!log0){
        allegro_message("../Games/River/image/log0.bmp");
        exit(EXIT_FAILURE);
    }
    BITMAP* log1= load_bitmap("../image/log1.bmp",NULL);
    if(!log1){
        allegro_message("../Games/River/image/log1.bmp");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 9; ++i) {
        switch (i) {
            case 1:
                log[1][i]=logx0left;
                log[2][i]=1080-370-120;
                break;
            case 2:
                log[1][i]=logx0right;
                log[2][i]=1080-494-120;
                break;
            case 3:
                log[1][i]=logx0right;
                log[2][i]=1080-494-120;
                break;
            case 4:
                log[1][i]=logx0left;
                log[2][i]=1080-628-120;
                break;
            case 5:
                log[1][i]=logx0left;
                log[2][i]=1080-628-120;
                break;
            case 6:
                log[1][i]=logx0right;
                log[2][i]=1080-754-120;
                break;
            case 7:
                log[1][i]=logx0left;
                log[2][i]=1080-878-120;
                break;
            case 8:
                log[1][i]=logx0left;
                log[2][i]=1080-878-120;
                break;
        }
    }
    //attribution aléatoire de bmp bûches (moyenne ou grande)
    for (int i = 0; i < 9; ++i) {
        randbmp[i]=rand()%2;
    }
    //Génération de nombre pour apparition aléatoire au niveau du temps
    for (int i = 0; i < 9; ++i) {
        randtime[i]=rand()%20000;
    }
    // Création du buffer
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    clear_to_color(buffer, makecol(0, 0, 0));
    draw_sprite(buffer,frog,frogx,frogy);
    // Boucle principale du jeu
    while (!key[KEY_ESC])
    {
        draw_sprite(buffer,frog,100,100);
        //Réatribution aléatoire pour les bûches non encore apparues
        for (int i = 0; i < 9; ++i) {
            if (randtime[i]>40) randtime[i]=rand()%20000;
        }
        // Copie de l'image dans le back buffer
        blit(background, buffer, 0, 0, 0, 0, background->w, background->h);
        // Déplacement du grounouille
        if (key[KEY_Z]) {
            frogy= frogy - frogvxy;
        }
        if ((key[KEY_Q]&&frogx>-50)) {
            frogx= frogx - frogvxy;
        }
        if (key[KEY_S]&& frogy<780) {
            frogy= frogy + frogvxy;
        }
        if (key[KEY_D]) {
            frogx= frogx + frogvxy;
        }
        rest(100);
        //buche générée puis on la fait dériver
        for (int i = 0; i < 9; ++i) {

            if ((i==1 || i==4 || i==5 || i==7 ||i==8)&&randtime[i]<40) {

                if (randbmp[i]==1){
                    draw_sprite(buffer,log0,log[1][i],log[2][i]);
                } else draw_sprite(buffer,log1,log[1][i],log[2][i]);
                log[1][i]+=1;
                rest(100+(rand()%100));
            }

            if ((i==2 || i==6) && randtime[i]<40) {
                if (randbmp[i]==1){
                    draw_sprite(buffer,log0,log[1][i],log[2][i]);
                } else draw_sprite(buffer,log1,log[1][i],log[2][i]);
                log[1][i]-=1;
                rest(100+(rand()%100));
            }
        }
        rest(100);
        //Dérivation de la grenouille si bûche
        for (int i = 0; i < 9; ++i) {
            if (randbmp[i]==1) logw[i]=577;
            else logw[i]=390;
            if ((frogx+frogw/2)>log[1][i]&&(frogx+frogw/2)<log[1][i]+logw[i]&&(frogy+frogw)>log[2][i]&&(frogy+frogw)<log[2][i]+124) {

                if (i == 1 || i == 4 || i == 5 || i == 7 || i == 8) {
                    frogx += 1;
                    rest(100);
                }

                if (i == 2 || i == 3) {
                    frogx-=1;
                    rest(100);
                }

            }
        }

        //Condition de défaite (Hors écran puis rivère)
        if (frogx<0 && frogy<600){
            gameover=1;
            textout_centre_ex(buffer, font, "Hors écran!", SCREEN_W/2, SCREEN_H/2, makecol(255, 0, 0), -1);
            gameover=1;
        }
        for (int i = 0; i < 9; ++i) {
            if (randbmp[i]==1) logw[i]=577;
            else logw[i]=390;
            if ((frogy<370) && (frogx+frogw/2)<log[1][i] || (frogx+frogw/2)>log[1][i]+logw) {
                textout_centre_ex(buffer, font, "Tombé!", SCREEN_W/2, SCREEN_H/2, makecol(255, 0, 0), -1);
            }
        }
        //Condition victoire
        if (frogy+frogw/2<=90){
            textout_centre_ex(buffer, font, "Traversée réussie !", SCREEN_W/2, SCREEN_H/2, makecol(255, 0, 0), -1);
        }
        //Apparition et réapparition des büches aléatoirement
        for (int i = 0; i < 9; ++i) {
            if ((i==1 || i==4 || i==5 || i==7 ||i==8)&&log[1][i]>SCREEN_W) {
                randtime[i]=rand()%20000;
                log[1][i]=logx0left;
            }
            if ((i==2 || i==6)&& log[1][i]<-577) {
                log[1][i]=logx0right;
                randtime[i]=rand()%20000;
            }
        }
        draw_sprite(buffer,frog,frogx,frogy);
        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
        // Affichage du buffer principal
        vsync();
        rest(250);
    }

    // Libération des ressources
    destroy_bitmap(background);
    destroy_bitmap(buffer);

    return 0;
}