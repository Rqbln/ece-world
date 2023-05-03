//
// Created by bapti on 19/04/2023.
//

#include "shoot.h"
#include <time.h>
#include <stdlib.h>

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
        baloonxy[0][i]=rand()%1800;
        baloonxy[1][i]=rand()%900;
        randir[0][i]=0;
        randir[1][i]=0;
    }

    // Chargement des images
    BITMAP* background = load_bitmap("../Games/Shoot/image/background.bmp", NULL);
    if(!background){
        allegro_message("../Games/Shoot/image/background.bmp");
        exit(EXIT_FAILURE);
    }
    BITMAP* baloon = load_bitmap("../Games/Shoot/image/baloon.bmp", NULL);



    // Création du buffer
    BITMAP* buffer = create_bitmap(WIDTH, HEIGHT);
    clear_to_color(buffer, makecol(0, 0, 0));
    // Boucle principale du jeu
    while (!key[KEY_ESC])
    {
        srand(time(NULL));
        // Copie de l'image dans le back buffer
        blit(background, buffer, 0, 0, 0, 0, background->w, background->h);
        for (int i = 0; i < 5; ++i) {
            if (baloonState[i]==0) draw_sprite(buffer,baloon,baloonxy[0][i],baloonxy[1][i]);
            //vérifie si le ballon a été éclaté
            if ((mouse_b & 1)&&(mouse_x>baloonxy[0][i])&&(mouse_x<(baloonxy[0][i]+baloon_w))&&(mouse_y>baloonxy[1][i])&&(mouse_y<(baloonxy[1][i]+baloon_w))) {
                baloonState[i]=1;
                end++;
            }
            baloonxy[0][i]+=randir[0][i];
            baloonxy[1][i]+=randir[1][i];
            randir[0][i]=(rand()%(1-(-1))+1)*vxy;
            randir[1][i]=(rand()%(1-(-1))+1)*vxy;
            //Rebond sur les bords de l'écran
            if ((baloonxy[0][i]<=0 ||(baloonxy[0][i]+baloon_w>=1920)))randir[0][i]-=randir[0][i];

        }
        //Condition de "Victoire"
        if (end==6) {
            textout_centre_ex(buffer, font, "Fini !", WIDTH/2, HEIGHT/2, makecol(255, 0, 0), -1);
        }
        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
        // Affichage du buffer principal
        vsync();
    }
    rest(200);
    // Libération des ressources
    //destroy_bitmap(background);
    //destroy_bitmap(buffer);
}

