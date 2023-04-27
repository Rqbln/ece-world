//-~-~-~-~-~-~-~TURTLE RIVER-~-~-~-~-~-~-~-~-~-
#include "river.h"
#include<time.h>
int main()
{
    srand(time(NULL));
    int gameover;
    int temps;
    int restx =10;
    char winmessage [64];

    int frogw=195;
    int frogx=0;
    int frogy=730;
    int vitesse_grounouille=1;
    //position et vitesse des bûches (1,2,3,4 = bûches normales ; 5,6,7,8= bûches grandes)
    int log[8][2];
    int dlog=1;
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


    // Création du buffer
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    clear_to_color(buffer, makecol(0, 0, 0));
    draw_sprite(buffer,frog,frogx,frogy);
    // Boucle principale du jeu
    while (!key[KEY_ESC])
    {
        // Copie de l'image dans le back buffer
        blit(background, buffer, 0, 0, 0, 0, background->w, background->h);
        // Déplacement du grounouille
        if (key[KEY_Z]) {
            frogy=frogy-vitesse_grounouille;
        }
        if (key[KEY_Q]) {
            frogx=frogx-vitesse_grounouille;
        }
        if (key[KEY_S]) {
            frogy=frogy+vitesse_grounouille;
        }
        if (key[KEY_D]) {
            frogx=frogx+vitesse_grounouille;
        }
        //Condition de défaite
        if (frogx==0){
            gameover=1;
        }
        //Condition victoire
        if (frogy+frogw/2<=90){
            textout_centre_ex(buffer, font, "valider !", SCREEN_W/2, SCREEN_H/2, makecol(255, 0, 0), -1);
        }
        //Apparition et réapparition des büches aléatoirement

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