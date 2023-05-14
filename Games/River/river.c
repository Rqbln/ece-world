//-~-~-~-~-~-~-~TURTLE RIVER-~-~-~-~-~-~-~-~-~-
#include "river.h"
#include "../../Init_Allegro/allegro.h"
#include "../../joueur/joueur.h"
void river()
{
    srand(time(NULL));
    int gameover;
    int temps;
    int restx =10;
    char winmessage [64];
    double joueurscore[2];
    int frogw=195; //Largeur du bmp de la grenouille
    int frogx=500;
    int frogy=730;
    int frogvxy=2; //vitesse grenouille
    //position et vitesse des bûches (1,2,3,4 = bûches normales ; 5,6,7,8= bûches grandes)
    int log[2][8]; //Position de chaque bûche [1][x] = position en abscisse ; [2][x] = position en ordonnée
    int logw[8]; //Largeurs des bûches
    int logx0left=-600; //Position d'apparition des bûches de gauche en x
    int logx0right=2200; //Position d'apparition des bûches de droite en x
    int dlog=1;
    int logh=124;
    int randbmp[8];//Aléatoire taille
    int randtime[8]; //Aléatoire temps apparition
    int logfrog=0; //bûche sur laquelle se trouve la grenouille

    //Couleurs pour les colisions avec la rivière
    //Couleurs références rivère et bûche
    int couleurR = 84;
    int couleurG = 130;
    int couleurB = 246;
    int couleurRm = 139;
    int couleurGm = 69;
    int couleurBm = 19;
    //Couleur prélevée sur la bitmap
    int couleurPixel;
    int pixelR=0;
    int pixelG=0;
    int pixelB=0;
    int tolerance =10;

    // Chargement des images
    BITMAP* background = load_bitmap("../Games/River/image/background.bmp", NULL);
    if(!background){
        allegro_message("../Games/River/image/background.bmp");
        exit(EXIT_FAILURE);
    }
    BITMAP* frog= load_bitmap("../Games/River/image/frog.bmp",NULL);
    if(!frog){
        allegro_message("../Games/River/image/frog.bmp");
        exit(EXIT_FAILURE);
    }
    BITMAP* log0= load_bitmap("../Games/River/image/log0.bmp",NULL);
    if(!log0){
        allegro_message("../Games/River/image/log0.bmp");
        exit(EXIT_FAILURE);
    }
    BITMAP* log1= load_bitmap("../Games/River/image/log1.bmp",NULL);
    if(!log1){
        allegro_message("../Games/River/image/log1.bmp");
        exit(EXIT_FAILURE);
    }

    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    clear_to_color(buffer, makecol(0, 0, 0));
    draw_sprite(buffer, frog, frogx, frogy);
    for (int turn = 0; turn < 2; ++turn) {

        for (int i = 0; i < 9; ++i) {
            switch (i) {
                case 1:
                    log[0][i]=logx0left;
                    log[1][i]=95+logh*4;
                    break;
                case 2:
                    log[0][i]=logx0right;
                    log[1][i]=95+logh*3;
                    break;
                case 3:
                    log[0][i]=logx0right;
                    log[1][i]=95+logh*3;
                    break;
                case 4:
                    log[0][i]=logx0left;
                    log[1][i]=95+logh*2;
                    break;
                case 5:
                    log[0][i]=logx0left;
                    log[1][i]=95+logh*2;
                    break;
                case 6:
                    log[0][i]=logx0right;
                    log[1][i]=95+logh;
                    break;
                case 7:
                    log[0][i]=logx0left;
                    log[1][i]=95;
                    break;
                case 8:
                    log[0][i]=logx0left;
                    log[1][i]=95;
                    break;
            }
        }
        //attribution aléatoire de bmp bûches (moyenne ou grande)
        for (int i = 0; i < 9; ++i) {
            randbmp[i] = rand() % 2;
        }
        //Génération de nombre pour apparition aléatoire au niveau du temps
        for (int i = 0; i < 9; ++i) {
            randtime[i] = rand() % 20000;
        }
        gameover=0;
        // Création du buffer
        // Boucle principale du jeu-------------------------------------------------------------------------
        while (!key[KEY_ESC] &&gameover==0) {

            couleurPixel = getpixel(background, (frogx+frogw)/2, frogy+frogw);
// Extraire les composantes R, G et B de la valeur de couleur
            pixelR = getr(couleurPixel);
            pixelG = getg(couleurPixel);
            pixelB = getb(couleurPixel);
            // Vérifiez si les composantes de couleur correspondent avec une tolérance
            if (frogy<700 && frogy>100 && pixelR == couleurRm && pixelG == couleurGm && pixelB == couleurBm ){

                while (!key[KEY_ENTER]){
                    textout_centre_ex(buffer, font, "Hors écran!", SCREEN_W / 2, SCREEN_H / 2, makecol(255, 0, 0), -1);
                    rest(10);
                }
                gameover = 1;
                frogx=500;
                frogy=730;
            }
            draw_sprite(buffer, frog, 100, 100);
            //Réatribution aléatoire pour les bûches non encore apparues
            for (int i = 0; i < 9; ++i) {
                if (randtime[i] > 40) randtime[i] = rand() % 16000;
            }
            // Copie de l'image dans le back buffer
            blit(background, buffer, 0, 0, 0, 0, background->w, background->h);
            // Déplacement du grounouille
            if (key[KEY_Z]) {
                frogy = frogy - frogvxy;
            }
            if ((key[KEY_Q] && frogx > -100)) {
                frogx = frogx - frogvxy;
            }
            if (key[KEY_S] && frogy < 780) {
                frogy = frogy + frogvxy;
            }
            if (key[KEY_D] && frogx < 1800) {
                frogx = frogx + frogvxy;
            }
            rest(10);
            //buche générée puis on la fait dériver
            for (int i = 0; i < 9; ++i) {

                if ((i == 1 || i == 4 || i == 5 || i == 7 || i == 8) && randtime[i] < 40) {

                    if (randbmp[i] == 1) {
                        draw_sprite(buffer, log0, log[0][i], log[1][i]);
                    } else draw_sprite(buffer, log1, log[1][i], log[0][i]);
                    log[0][i] += 1;
                    rest(10);
                }

                if ((i == 2 || i == 6) && randtime[i] < 40) {
                    if (randbmp[i] == 1) {
                        draw_sprite(buffer, log0, log[0][i], log[1][i]);
                    } else draw_sprite(buffer, log1, log[0][i], log[1][i]);
                    log[0][i] -= 1;
                    rest(10);
                }
            }
            //Dérivation de la grenouille si bûche
            for (int i = 0; i < 9; ++i) {
                //attribution de la longueur de la buche en fonction de sa taille effective
                if (randbmp[i] == 1) logw[i] = 577;
                else logw[i] = 390;

                if ((frogx + frogw / 2) > log[0][i] && (frogx + frogw / 2) < log[0][i] + logw[i] &&
                    (frogy + frogw) > log[1][i] && (frogy + frogw) < log[1][i] + 124) {
                    logfrog = i;
                    //bûches allant de gauche à droite
                    if (i == 1 || i == 4 || i == 5 || i == 7 || i == 8) {
                        frogx += 1;
                    }
                    //bûches allant de droite à gauche
                    if (i == 2 || i == 3 || i == 6) {
                        frogx -= 1;
                    }

                }
            }
            for (int i = 0; i < 9; ++i) {
                if ((frogx + frogw / 2) > log[0][i] && (frogx + frogw / 2) < log[0][i] + logw[i] &&
                    (frogy + frogw) > log[1][i] && (frogy + frogw) < log[1][i] + 124) {
                    logfrog = i;
                }

            }
            //Rectangle marron en dessous des bûches
            for (int i = 0; i < 9; ++i) {
                // Vérifiez si la bûche est en mouvement
                if ((i == 1 || i == 4 || i==2 || i==3 || i == 5 || i==6 || i == 7 || i == 8) && randtime[i] < 40) {
                    // Dessinez un rectangle marron superposé à la bûche
                    rectfill(buffer, log[0][i], log[1][i], log[0][i] + logw[i], log[1][i] + logh, makecol(couleurRm, couleurGm, couleurBm));
                }
            }
            //Condition de défaite (Hors écran puis rivère)

            if (frogx + frogw / 2 < 0 && frogy + frogw < 600) {

                while (!key[KEY_ENTER]){

                    blit(background, buffer, 0, 0, 0, 0, background->w, background->h);
                    // Dessinez les autres éléments du jeu sur le buffer

                    // Affichage du "panneau"
                    textout_centre_ex(buffer, font, "Hors écran!", SCREEN_W / 2, SCREEN_H / 2, makecol(255, 0, 0), -1);
                    // Blit du buffer sur l'écran
                    blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
                }
                gameover = 1;
                frogx=500;
                frogy=730;
            }
            if ((frogx < -40 || frogx > 1750) && (frogy + frogw < 700 && frogy + frogw > 50) && ((logfrog > 0))) {
                textout_centre_ex(buffer, font, "Hors écran!", SCREEN_W / 2, SCREEN_H / 2, makecol(255, 0, 0), -1);
            }

            //Condition victoire
            if (frogy + frogw <= 50) {
                do {
                    textprintf_ex(screen, font, (background->w/2)+100, (background->h/2)+200, makecol(255, 255, 0), -1, "Traversée réussi pour le J%d en %.2f s",turn+1);
                    textprintf_ex(screen, font, (background->w/2)+100, (background->h/2)+250, makecol(255, 0, 0), -1, "Appuyez sur une échap pour continuer !");
                    rest(10);
                } while (!key[KEY_ENTER]);
                gameover = 1;
                frogx=500;
                frogy=730;
            }
            //Apparition et réapparition des büches aléatoirement
            for (int i = 0; i < 9; ++i) {
                if ((i == 1 || i == 4 || i == 5 || i == 7 || i == 8) && log[1][i] > SCREEN_W) {
                    randtime[i] = rand() % 16000;
                    log[0][i] = logx0left;
                }
                if ((i == 2 || i == 6) && log[1][i] < -577) {
                    log[0][i] = logx0right;
                    randtime[i] = rand() % 16000;
                }
            }
            draw_sprite(buffer, frog, frogx, frogy);
            textprintf_ex(screen, font, (frogx/2), (frogy/2), makecol(255, 255, 0), -1, "J%d",turn+1);
            blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
            // Affichage du buffer principal
            vsync();
            rest(250);
        }
        textprintf_ex(screen, font, (background->w/2), (background->h/2), makecol(255, 255, 0), -1, "Le J%d a remporté 1 ticket ! Quelle vitesse !");
        gameover=0;
    }
    // Libération des ressources
    destroy_bitmap(background);
    destroy_bitmap(buffer);
    destroy_bitmap(frog);

}