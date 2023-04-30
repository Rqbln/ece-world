#include "menu.h"
#include <allegro.h>
#include "stdio.h"

void menu() {

    BITMAP *buffer = create_bitmap(WIDTH, HEIGHT);
    clear_to_color(buffer, makecol(255, 255, 255)); // Fond blanc
    BITMAP *fond = load_bitmap("../Menu/image/menu.bmp",NULL);
    BITMAP *selectstart[2];
    BITMAP *selectrules[2];
    BITMAP *selectexit[2];

    //declaration variable
    int selection = 0; // Index de l'option sélectionnée
    int num_options = 3; // Nombre total d'options
    char *options[] = {"Jouer", "Lire les règles", "Quitter"}; // Texte des options
    char nomDeFichier[50];
    int xselect=WIDTH/2-50;
    int yselectstart=WIDTH/2-200;
    int yselectrules=WIDTH/2-100;
    int yselectexit=WIDTH/2;
    int option=0;

    //creation des touche de selection
    for(int i=0;i<2;i++)
    {
        sprintf(nomDeFichier,"../Menu/image/selectstart%d.bmp",i);
        selectstart[i]= load_bitmap(nomDeFichier,NULL);
        if(!selectstart[i])
        {
            allegro_message("../Menu/image/selectstart%d.bmp",i);
            exit(EXIT_FAILURE);
        }

        sprintf(nomDeFichier,"../Menu/image/selectrules%d.bmp",i);
        selectrules[i]= load_bitmap(nomDeFichier,NULL);
        if(!selectrules[i])
        {
            allegro_message("../image/selectrules%d.bmp",i);
            exit(EXIT_FAILURE);
        }
        sprintf(nomDeFichier,"../Menu/image/selectexit%d.bmp",i);
        selectexit[i]= load_bitmap(nomDeFichier,NULL);
        if(!selectexit[i])
        {
            allegro_message("../Menu/image/selectexit%d.bmp",i);
            exit(EXIT_FAILURE);
        }
    }

    // Boucle principale
    while (!key[KEY_ESC]) {
        // Affichage de l'image de fond
        // Affichage du buffer à l'écran avec l'image de fond
        stretch_blit(fond, buffer, 0, 0, fond->w, fond->h, 0, 0, WIDTH, HEIGHT);


        // Affichage du menu en texte
        /*for (int i = 0; i < num_options; i++) {
            if (i == selection) { // Option sélectionnée
                textout_centre_ex(buffer, font, options[i], WIDTH/2, HEIGHT/2 + i*20, makecol(255, 0, 0), -1);
            } else { // Option non sélectionnée
                textout_centre_ex(buffer, font, options[i], WIDTH/2, HEIGHT/2 + i*20, makecol(0, 0, 0), -1);
            }
        }*/
        switch (option) {
            case 0:
                draw_sprite(buffer,selectstart[1],xselect,yselectstart);
                draw_sprite(buffer,selectrules[0],xselect,yselectrules);
                draw_sprite(buffer,selectexit[0],xselect,yselectexit);
                break;
            case 1:
                draw_sprite(buffer,selectstart[0],xselect,yselectstart);
                draw_sprite(buffer,selectrules[1],xselect,yselectrules);
                draw_sprite(buffer,selectexit[0],xselect,yselectexit);
                break;
            case 2:
                draw_sprite(buffer,selectstart[0],xselect,yselectstart);
                draw_sprite(buffer,selectrules[0],xselect,yselectrules);
                draw_sprite(buffer,selectexit[1],xselect,yselectexit);
                break;
        }

        // Affichage du buffer à l'écran
        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);

        // Gestion de l'entrée utilisateur
        if (key[KEY_UP]) { // Flèche du haut
            option--;
            if (option<0){
                option=2;
            }
            rest(250); // Pause pour éviter les mouvements trop rapides
        }
        if (key[KEY_DOWN]) { // Flèche du bas
            option++;
            if (option>2){
                option=0;
            }
            rest(250); // Pause pour éviter les mouvements trop rapides
        }
        if (key[KEY_ENTER]) { // Touche Entrée

            if (option == 0) { // Option Jouer
                // TODO: Ajouter le code pour lancer le jeu
                parc2();
            } else if (option == 1) { // Option Lire les règles
                // TODO: Ajouter le code pour afficher les règles
            } else if (option == 2) { // Option Quitter
                rest(250); // Pause pour éviter les mouvements trop rapides
                break; // Sortie de la boucle principale
            }
        }
        rest(10); // Pause pour libérer un peu le processeur
    }
}

