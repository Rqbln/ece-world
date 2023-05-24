//-~-~-~-~-~-~-~TURTLE RIVER-~-~-~-~-~-~-~-~-~-
#include "river.h"
#include "../../Init_Allegro/allegro.h"
#include "../../joueur/joueur.h"
#include "../../ScoreTab/scoreTab.h"
void river()
{
    srand(time(NULL));
    int randlimit=10;
    int randmax=100;
    double start,end;
    int gameover;
    char mess[100];
    int temps;
    double joueurscore[2];
    int frogw=195; //Largeur du bmp de la grenouille
    int frogx=500;
    int frogy=730;
    int frogvxy=10; //vitesse grenouille
    //position et vitesse des bûches (1,2,3,4 = bûches normales ; 5,6,7,8= bûches grandes)
    int log[2][8]; //Position de chaque bûche [1][x] = position en abscisse ; [2][x] = position en ordonnée
    int logw[8]; //Largeurs des bûches
    int logx0left=-600; //Position d'apparition des bûches de gauche en x
    int logx0right=2200; //Position d'apparition des bûches de droite en x
    int dlog=5;
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

    //Chargement des sons
    SAMPLE *transition = load_wav("../Games/Shoot/musique/transition.wav");
    SAMPLE *talk = load_wav("../Games/River/musique/talk.wav");
    SAMPLE *clear = load_wav("../Games/Shoot/musique/marioclear.wav");
    SAMPLE *music = load_wav("../Games/River/musique/musicriver.wav");
    SAMPLE *death = load_wav("../Games/River/musique/death.wav");
    // Chargement des images
    BITMAP* player1= load_bitmap("../Games/Ducky/IMAGES/player1.bmp",NULL);
    if(!player1){
        allegro_message("../Games/River/image/player1.bmp");
        exit(EXIT_FAILURE);
    }
    BITMAP* player2= load_bitmap("../Games/Ducky/IMAGES/player2.bmp",NULL);
    if(!player2){
        allegro_message("../Games/River/image/player2.bmp");
        exit(EXIT_FAILURE);
    }
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
    BITMAP* frog_ded= load_bitmap("../Games/River/image/frog_ded.bmp",NULL);
    if(!frog){
        allegro_message("../Games/River/image/frog_ded.bmp");
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
    BITMAP* regles= load_bitmap("../Games/River/image/regles.bmp",NULL);
    if(!frog){
        allegro_message("../Games/River/image/regles.bmp");
        exit(EXIT_FAILURE);
    }
    BITMAP* scores= load_bitmap("../Games/River/image/scores.bmp",NULL);
    if(!frog){
        allegro_message("../Games/River/image/scores.bmp");
        exit(EXIT_FAILURE);
    }
    BITMAP* scroll= load_bitmap("../Games/River/image/scroll.bmp",NULL);
    if(!frog){
        allegro_message("../Games/River/image/scroll.bmp");
        exit(EXIT_FAILURE);
    }

    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    clear_to_color(buffer, makecol(0, 0, 0));
    draw_sprite(buffer, frog, frogx, frogy);
    play_sample(music, 255, 128, 1000, 1);
    for (int turn = 0; turn < 2; ++turn) {
        start=(double) clock();
        //Retirer un ticket pour la participation au mini-jeu
        joueurs[turn].nbTickets--;
        gameover=0;
        while (!key[KEY_ENTER]){
            draw_sprite(buffer,background,0,0);
            if (turn==0) draw_sprite(buffer,regles,WIDTH/2-200,HEIGHT/2-200);

            sprintf(mess, "Appuyez sur entrée pour commencer le tour de %s !",joueurs[turn].nom);
            textout_centre_ex(buffer, font, mess, WIDTH / 2, HEIGHT / 2+100, makecol(255, 255, 255), -1);
            draw_sprite(buffer, frog, frogx, frogy);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        }
        if (turn==0) {
            play_sample(transition, 255, 128, 1000, 0);
            for (int i = 0; i < 300; ++i) {
                draw_sprite(buffer,background,0,0);
                draw_sprite(buffer, regles, WIDTH / 2 - 200, HEIGHT / 2 - 200-2*i);
                sprintf(mess, "Appuyez sur entrée pour commencer le tour de %s !",joueurs[turn].nom);
                textout_centre_ex(buffer, font, mess, WIDTH / 2, HEIGHT / 2+100, makecol(255, 255, 255), -1);
                draw_sprite(buffer, frog, frogx, frogy);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            }
        }
        for (int i = 3; i > 0; --i) {
            clear_bitmap(buffer);
            draw_sprite(buffer,background,0,0);
            sprintf(mess, "%d", i);
            textout_centre_ex(buffer, font, mess, WIDTH / 2, HEIGHT / 2, makecol(255, 255, 255), -1);
            draw_sprite(buffer, frog, frogx, frogy);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(1000);
        }
        if (turn==0){
            clear_bitmap(buffer);
            draw_sprite(buffer,background,0,0);
            draw_sprite(buffer,player1,(WIDTH/2)-400,(HEIGHT/2)-200);
            draw_sprite(buffer, frog, frogx, frogy);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(1000);
        }
        else if (turn==1){
            clear_bitmap(buffer);
            draw_sprite(buffer,background,0,0);
            draw_sprite(buffer,player2,(WIDTH/2)-400,(HEIGHT/2)-200);
            draw_sprite(buffer, frog, frogx, frogy);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(1000);
        }
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
                default:
                    break;
            }
        }
        //attribution aléatoire de bmp bûches (moyenne ou grande)
        for (int i = 0; i < 9; ++i) {
            randbmp[i] = rand() % 2;
        }
        //Génération de nombre pour apparition aléatoire au niveau du temps
        for (int i = 0; i < 9; ++i) {
            randtime[i] = rand() % 10000;
        }
        // Création du buffer

        // Boucle principale du jeu-------------------------------------------------------------------------
        while (gameover==0) {

            couleurPixel = getpixel(background, (frogx+frogw)/2, frogy+frogw);
// Extraire les composantes R, G et B de la valeur de couleur
            pixelR = getr(couleurPixel);
            pixelG = getg(couleurPixel);
            pixelB = getb(couleurPixel);
            // Vérifiez si les composantes de couleur correspondent et que frog se trouve bine sur une buche
            if (frogy+frogw<700 && frogy>100 && !(pixelR == couleurRm && pixelG == couleurGm && pixelB == couleurBm)&& !((frogx + frogw / 2) > log[0][logfrog] && (frogx + frogw / 2) < log[0][logfrog] + logw[logfrog] &&
                                                                                                                         (frogy + frogw) > log[1][logfrog] && (frogy + frogw) < log[1][logfrog] + 124) ){
                play_sample(death, 255, 128, 1000, 0);
                joueurscore[turn]=1000;
                while (!key[KEY_ENTER]){
                    draw_sprite(buffer,background,0,0);
                    textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "Perdu ! à %s de jouer",joueurs[1].nom);

                    for (int i = 0; i < 9; ++i) {

                        if ((i == 1 || i == 4 || i==2 || i==3 || i == 5 || i==6 || i == 7 || i == 8) && randtime[i] < 40) {
                            // Dessinez un rectangle marron superposé à la bûche
                            rectfill(buffer, log[0][i], log[1][i], log[0][i] + logw[i], log[1][i] + logh, makecol(couleurRm, couleurGm, couleurBm));
                            if (randbmp[i]==0)draw_sprite(buffer, log1, log[0][i], log[1][i]);
                            else  draw_sprite(buffer, log0, log[0][i], log[1][i]);
                        }

                        if ((i == 1 || i == 4 || i == 5 || i == 7 || i == 8) && randtime[i] < 40) {

                            if (randbmp[i] == 1) {
                                draw_sprite(buffer, log0, log[0][i], log[1][i]);
                            } else draw_sprite(buffer, log1, log[0][i], log[1][i]);
                        }

                        if ((i == 2 || i == 6) && randtime[i] < 40) {
                            if (randbmp[i] == 1) {
                                draw_sprite(buffer, log0, log[0][i], log[1][i]);
                            } else draw_sprite(buffer, log1, log[0][i], log[1][i]);
                        }
                    }
                    draw_sprite(buffer, frog_ded, frogx, frogy);
                    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

                }
                gameover = 1;
                frogx=500;
                frogy=730;
            }
            draw_sprite(buffer, frog, 100, 100);
            //Réatribution aléatoire pour les bûches non encore apparues
            for (int i = 0; i < 9; ++i) {
                if (randtime[i] > 40) randtime[i] = rand() % 12000;
            }
            // Copie de l'image dans le back buffer
            blit(background, buffer, 0, 0, 0, 0, background->w, background->h);
            // Déplacement du grounouille
            if (key[KEY_UP]) {
                frogy = frogy - frogvxy;
            }
            if ((key[KEY_LEFT] && frogx > -100)) {
                frogx = frogx - frogvxy;
            }
            if (key[KEY_DOWN] && frogy < 780) {
                frogy = frogy + frogvxy;
            }
            if (key[KEY_RIGHT] && frogx < 1800) {
                frogx = frogx + frogvxy;
            }
            //buche générée puis on la fait dériver
            for (int i = 0; i < 9; ++i) {

                if ((i == 1 || i == 4 || i == 5 || i == 7 || i == 8) && randtime[i] < 40) {

                    if (randbmp[i] == 1) {
                        draw_sprite(buffer, log0, log[0][i], log[1][i]);
                    } else draw_sprite(buffer, log1, log[0][i], log[1][i]);
                    log[0][i] += dlog;
                }

                if ((i == 2 || i == 6) && randtime[i] < 40) {
                    if (randbmp[i] == 1) {
                        draw_sprite(buffer, log0, log[0][i], log[1][i]);
                    } else draw_sprite(buffer, log1, log[0][i], log[1][i]);
                    log[0][i] -=dlog;
                }
            }
            //Dérivation de la grenouille si bûche
            for (int i = 1; i < 9; ++i) {
                //attribution de la longueur de la buche en fonction de sa taille effective
                if (randbmp[i] == 1) logw[i] = 577;
                else logw[i] = 390;

                if ((frogx + frogw / 2) > log[0][i] && (frogx + frogw / 2) < log[0][i] + logw[i] &&
                    (frogy + frogw) > log[1][i] && (frogy + frogw) < log[1][i] + 124) {
                    logfrog = i;
                    //bûches allant de gauche à droite
                    if (i == 1 || i == 4 || i == 5 || i == 7 || i == 8) {
                        frogx += dlog;
                    }
                    //bûches allant de droite à gauche
                    if (i == 2 || i == 3 || i == 6) {
                        frogx -= dlog;
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
            for (int i = 1; i < 9; ++i) {
                // Vérifiez si la bûche est en mouvement
                if ((i == 1 || i == 4 || i==2 || i==3 || i == 5 || i==6 || i == 7 || i == 8) && randtime[i] < 40) {
                    // Dessinez un rectangle marron superposé à la bûche
                    rectfill(buffer, log[0][i], log[1][i], log[0][i] + logw[i], log[1][i] + logh, makecol(couleurRm, couleurGm, couleurBm));
                    if (randbmp[i]==0)draw_sprite(buffer, log1, log[0][i], log[1][i]);
                    else  draw_sprite(buffer, log0, log[0][i], log[1][i]);
                }
            }
            //Apparition et réapparition des büches aléatoirement
            for (int i = 1; i < 9; ++i) {
                if ((i == 1 || i == 4 || i == 5 || i == 7 || i == 8) && log[0][i] > SCREEN_W) {
                    randtime[i] =rand()%10000;
                    log[0][i] = logx0left;
                }
                if ((i == 2 ||i==3|| i == 6) && log[0][i] < -577) {
                    log[0][i] = logx0right;
                    randtime[i] =rand()%10000;
                }
            }
            //Condition de défaite (Hors écran puis rivère)

            if (frogx + frogw / 2 < -50 && frogy + frogw > 2200) {

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
            //Condition victoire
            if (frogy + frogw <= 50) {
                end=(double) clock();
                joueurscore[turn]=(double)((end-start)/CLOCKS_PER_SEC)*4;
                while (!key[KEY_ENTER]){
                    draw_sprite(buffer,background,0,0);
                    sprintf(mess, "Traversée réussie pour %s en %.2f s ! Bravo !",joueurs[turn].nom,joueurscore[turn]);
                    textout_centre_ex(buffer, font, mess, WIDTH / 2, HEIGHT / 2, makecol(255, 255, 255), -1);
                    textprintf_ex(screen, font, (background->w/2)+100, (background->h/2)+250, makecol(255, 0, 0), -1, "Appuyez sur entrée pour voir les scores !");
                    draw_sprite(buffer, frog, frogx, frogy);
                    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                    for (int i = 0; i < 9; ++i) {

                        if ((i == 1 || i == 4 || i == 5 || i == 7 || i == 8) && randtime[i] < 40) {

                            if (randbmp[i] == 1) {
                                draw_sprite(buffer, log0, log[0][i], log[1][i]);
                            } else draw_sprite(buffer, log1, log[0][i], log[1][i]);
                        }

                        if ((i == 2 || i == 6) && randtime[i] < 40) {
                            if (randbmp[i] == 1) {
                                draw_sprite(buffer, log0, log[0][i], log[1][i]);
                            } else draw_sprite(buffer, log1, log[0][i], log[1][i]);
                        }
                    }
                    //Rafraichissement du high-score
                   /* for (int i = 0; i < 10; ++i) {
                        if (joueurscore[turn]<statist)
                    }
                }*/
                gameover = 1;
                frogx=500;
                frogy=730;
            }

            }
            draw_sprite(buffer, frog, frogx, frogy);
            blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
            // Affichage du buffer principal
            vsync();
        }
        gameover=0;
        joueurs[turn].score_river[joueurs[turn].nb_essaie_river]=joueurscore[turn];
        joueurs[turn].nb_essaie_river++;

    }
    stop_sample(music);
    play_sample(clear, 255, 128, 1000, 0);

    while (!(key[KEY_ESC])) {
        draw_sprite(buffer,background,0,0);
        draw_sprite(buffer,scores,WIDTH/2-200,HEIGHT/2-200);
        textprintf_ex(buffer, font, (WIDTH/2)-50, (HEIGHT/2)-75, makecol(0, 0, 0), -1, "%s : %.2f s",joueurs[0].nom,joueurscore[0]);
        textprintf_ex(buffer, font, (WIDTH/2)-50, (HEIGHT/2)-50, makecol(0, 0, 0), -1, "%s : %.2f s",joueurs[1].nom,joueurscore[1]);
        draw_sprite(buffer, frog, 500, 730);
        if (joueurscore[0]<joueurscore[1]){
            textprintf_ex(buffer, font, (WIDTH/2)-20, (HEIGHT/2)-25, makecol(0, 0, 0), -1, "%s a gagné le combat Tortuesque !",joueurs[0].nom,joueurscore[0]);
            textprintf_ex(buffer, font, (WIDTH/2)-110, (HEIGHT/2)-15, makecol(0, 0, 0), -1, "Il remporte 2 tickets !");
        }
        else if (joueurscore[0]==joueurscore[1]) {
            textprintf_ex(buffer, font, (WIDTH/2)-110, (HEIGHT/2)-25, makecol(0, 0, 0), -1, "Personne n'a gagné le combat :( <+1 ticket>",joueurs[0].nom,joueurscore[0]);
        }
            else {
            textprintf_ex(buffer, font, (WIDTH/2)-100, (HEIGHT/2)-25, makecol(0, 0, 0), -1, "%s a gagné le combat Tortuesque !",joueurs[0].nom,joueurscore[1]);
            textprintf_ex(buffer, font, (WIDTH/2)-110, (HEIGHT/2)-15, makecol(0, 0, 0), -1, "Il remporte 2 tickets !");
        }
        textprintf_ex(buffer, font, (WIDTH/2)-110, (HEIGHT/2)-8, makecol(rand()%255, rand()%255, rand()%255), -1, "Appuyez sur <échap> pour retourner au parc !");
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


    }
    play_sample(transition, 255, 128, 1000, 0);
    for (int i = 0; i < 300; ++i) {
        draw_sprite(buffer,background,0,0);
        draw_sprite(buffer,scores,WIDTH/2-200,HEIGHT/2-200-2*i);
        textprintf_ex(buffer, font, (WIDTH/2)-50, (HEIGHT/2)-75-2*i, makecol(0, 0, 0), -1, "%s : %.2f s",joueurs[0].nom,joueurscore[0]);
        textprintf_ex(buffer, font, (WIDTH/2)-50, (HEIGHT/2)-50-2*i, makecol(0, 0, 0), -1, "%s : %.2f s",joueurs[1].nom,joueurscore[1]);
        draw_sprite(buffer, frog, 500, 730);
        if (joueurscore[0]<joueurscore[1]){
            textprintf_ex(buffer, font, (WIDTH/2)-20, (HEIGHT/2)-25-2*i, makecol(0, 0, 0), -1, "%s a gagné le combat Tortuesque !",joueurs[0].nom,joueurscore[0]);
            textprintf_ex(buffer, font, (WIDTH/2)-110, (HEIGHT/2)-15-2*i, makecol(0, 0, 0), -1, "Il remporte 2 tickets !");
        }
        else if (joueurscore[0]==joueurscore[1]) {
            textprintf_ex(buffer, font, (WIDTH/2)-30, (HEIGHT/2)-25-2*i, makecol(0, 0, 0), -1, "Personne n'a gagné le combat, les chevaliers reprennent leurs tickets",joueurs[0].nom,joueurscore[0]);
        }
        else {
            textprintf_ex(buffer, font, (WIDTH/2)-100, (HEIGHT/2)-25-2*i, makecol(0, 0, 0), -1, "%s a gagné le combat Tortuesque !",joueurs[0].nom,joueurscore[1]);
            textprintf_ex(buffer, font, (WIDTH/2)-110, (HEIGHT/2)-15-2*i, makecol(0, 0, 0), -1, "Il remporte 2 tickets !");
        }
        textprintf_ex(buffer, font, (WIDTH/2)-110, (HEIGHT/2)-8-2*i, makecol(rand()%255, rand()%255, rand()%255), -1, "Appuyez sur <échap> pour retourner au parc !");
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    }
    if (joueurscore[0]<joueurscore[1]) {
        joueurs[0].nbTickets=joueurs[0].nbTickets+2;
        if ((double)((highscore[6].score)/100) >= joueurscore[0]||highscore[6].score==0) {

            sprintf(mess, "%s vient d'établir un nouveau record ! Enregistrement du meilleur score terminé.",joueurs[0].nom);
            textout_centre_ex(buffer,font, mess, WIDTH/2, HEIGHT / 2 + 20, makecol(255, 255, 255), -1);
            saveMiniGame(joueurs,"6Frogger",joueurscore[0]*100,0);
        }
    }
    else if (joueurscore[0]==joueurscore[1]) {
        joueurs[0].nbTickets++;
        joueurs[1].nbTickets++;
    }
    else {
        textprintf_ex(buffer, font, (WIDTH/2)-100, (HEIGHT/2)-25, makecol(0, 0, 0), -1, "%s a gagné le combat Tortuesque !",joueurs[0].nom,joueurscore[1]);
        joueurs[1].nbTickets=joueurs[1].nbTickets+2;
        textprintf_ex(buffer, font, (WIDTH/2)-110, (HEIGHT/2)-15, makecol(0, 0, 0), -1, "Il remporte 2 tickets !");
       if ((highscore[6].score/100) >= (int)joueurscore[1]||highscore[6].score==0) {

            sprintf(mess, "%s vient d'établir un nouveau record ! Enregistrement du meilleur score terminé.",joueurs[1].nom);
            textout_centre_ex(buffer,font, mess, WIDTH/2, HEIGHT / 2 + 20, makecol(255, 255, 255), -1);
            saveMiniGame(joueurs,"6Frogger",(int)joueurscore[1]*100,1);
        }
    }
    // Libération des ressources
    destroy_bitmap(background);
    destroy_bitmap(buffer);
    destroy_bitmap(frog);
    loadHighScore(highscore);
}