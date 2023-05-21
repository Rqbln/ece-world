//
// Created by bapti on 17/05/2023.
//
#include "../joueur/joueur.h"
#include "scoreTab.h"
void tableau_score(){
    rest(200); // Pause de 10 ms pour rafraîchir l'écran
    BITMAP *buffer;
    BITMAP *compteur[10];
    BITMAP *lettre[37];//+10 pour les chiffre
    BITMAP *affichage= load_bitmap("../ScoreTab/image/affichage.bmp",NULL);
    BITMAP *fond= load_bitmap("../ScoreTab/image/fond.bmp",NULL);
    BITMAP *enterkey= load_bitmap("../Games/Course_Chevaux/image/enterkey.bmp",NULL);
    SAMPLE *musique= load_sample("../Games/Guitar_hero/musique/kingGT.wav");
    set_trans_blender(0, 0, 0, 128);
    if (!musique) {
        allegro_message("Erreur : impossible de charger la musique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    int score=0;
    int score1=0;
    int score2=0;
    int score3=0;
    int xcompteur=0;
    int ycompteur=0;
    int numlettre=0;
    int nblettre=40;
    int xlettre;
    int ylettre;
    char message[8][nblettre];
    char nomDeFichier[50];
    char messageDebut[200];
    int option=0;

    int xenter=WIDTH-400;
    int yenter=HEIGHT-80;

    if(!affichage){
        allegro_message("../image/affichageguitar0.bmp ");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    buffer=create_bitmap(WIDTH,HEIGHT);
    for(int i=0;i<10;i++){
        sprintf(nomDeFichier,"../Games/Guitar_hero/compteur/%d.bmp",i);
        compteur[i]= load_bitmap(nomDeFichier,NULL);
        if(!compteur[i]){
            allegro_message("../Games/compteur/%d.bmp",i);
            exit(EXIT_FAILURE);
        }
    }
    for(int i=0;i<37;i++){ //+10
        if (i<27){
            sprintf(nomDeFichier,"../police/lettre12/%c.bmp",i+97);
        } else{
            sprintf(nomDeFichier,"../police/lettre12/%d.bmp",i-27);
        }
        lettre[i]= load_bitmap(nomDeFichier,NULL);
        if(!lettre[i]){
            allegro_message("../police/lettre12/%c.bmp",i+97);
            exit(EXIT_FAILURE);
        }   
    }
    while (!key[KEY_ESC]) {
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        draw_sprite(buffer,fond,0,0);
        draw_sprite(buffer, affichage, 0, 0);
        sprintf(messageDebut, "Appuyez sur les flèches HAUT et BAS pour naviguer entre les Highscores et les statistiques des différents jeux de la partie");
        textout_centre_ex(buffer, font, messageDebut, WIDTH / 2, HEIGHT - 200, makecol(0, 0, 0), -1);

        if (key[KEY_UP]) { // Flèche du haut
            option--;
            if (option<0){
                option=8;
            }
            rest(250); // Pause pour éviter les mouvements trop rapides
        }
        if (key[KEY_DOWN]) { // Flèche du bas
            option++;
            if (option>9){
                option=0;
            }
            rest(250); // Pause pour éviter les mouvements trop rapides
        }
        switch (option) {
            case 0:
                sprintf(message[0],"           Tableau des winners");
                nblettre = strlen(message[0]);
                for (int i = 0; i < nblettre; ++i) {

                    numlettre = (message[0][i] - '0') - 49;
                    if (numlettre < 0 || numlettre > 25) {
                        if (numlettre > -33 && numlettre < -6) {
                            numlettre += 32;
                        } else if (numlettre > -50 && numlettre < -39) {
                            numlettre += 49 + 27;//26+49 pour les chiffre on remplace 49 par ca
                        } else {
                            numlettre = 26;
                        }
                    }
                    ylettre = 140;
                    xlettre = i * (lettre[0]->w) +180;
                    draw_sprite(buffer, lettre[numlettre], xlettre, ylettre);
                }

                for (int i = 0; i <=7; ++i) {
                    sprintf(message[i],"%s nom %s score %d", highscore[i].nomjeu,highscore[i].nom,highscore[i].score);
                }
                for (int j = 0; j < 8; ++j) {
                    nblettre = strlen(message[j]);
                    for (int i = 0; i < nblettre; ++i) {

                        numlettre = (message[j][i] - '0')-49;
                        if (numlettre<0 || numlettre>25){
                            if (numlettre>-33 && numlettre<-6){
                                numlettre+=32;
                            }
                            else if(numlettre>-50 && numlettre<-39) {
                                numlettre+=49+27;//26+49 pour les chiffre on remplace 49 par ca
                            }
                            else{
                                numlettre=26;
                            }
                        }
                        ylettre=(j+1)*(lettre[0]->h)+140;
                        xlettre=i*(lettre[0]->w)+180;
                        draw_sprite(buffer,lettre[numlettre],xlettre,ylettre);
                    }

                }
                blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
                break;
            case 1:
                while (!key[KEY_DOWN]&& !key[KEY_UP]&& !key[KEY_ESC]){
                    for (int j = 0; j < 2; ++j) {
                        sprintf(message[0],"               %s", highscore[option + 1].nomjeu);
                        sprintf(message[1],"%s             %s", joueurs[0].nom,joueurs[1].nom);
                        nblettre = strlen(message[j]);
                        for (int i = 0; i < nblettre; ++i) {

                            numlettre = (message[j][i] - '0') - 49;
                            if (numlettre < 0 || numlettre > 25) {
                                if (numlettre > -33 && numlettre < -6) {
                                    numlettre += 32;
                                } else if (numlettre > -50 && numlettre < -39) {
                                    numlettre += 49 + 27;//26+49 pour les chiffre on remplace 49 par ca
                                } else {
                                    numlettre = 26;
                                }
                            }
                            ylettre = j * (lettre[0]->h) + 140;
                            xlettre = i * (lettre[0]->w) + 180;
                            draw_sprite(buffer, lettre[numlettre], xlettre, ylettre);
                        }

                    }
                    for (int tour = 0; tour < 2; ++tour) {
                        for (int i = 0; i < (joueurs[tour].nb_essaie_guitare); ++i) {
                            sprintf(message[i], "score %d", joueurs[tour].score_guitare[i]);
                        }
                        for (int j = 0; j < (joueurs[tour].nb_essaie_guitare); ++j) {
                            nblettre = strlen(message[j]);
                            for (int i = 0; i < nblettre; ++i) {

                                numlettre = (message[j][i] - '0') - 49;
                                if (numlettre < 0 || numlettre > 25) {
                                    if (numlettre > -33 && numlettre < -6) {
                                        numlettre += 32;
                                    } else if (numlettre > -50 && numlettre < -39) {
                                        numlettre += 49 + 27;//26+49 pour les chiffre on remplace 49 par ca
                                    } else {
                                        numlettre = 26;
                                    }
                                }
                                ylettre = (j+2) * (lettre[0]->h) + 140;
                                xlettre = i * (lettre[0]->w) + 180;
                                draw_sprite(buffer, lettre[numlettre], xlettre+tour*1050, ylettre);
                            }

                        }
                        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
                    }
                }
                break;
            case 2:
                while (!key[KEY_DOWN]&& !key[KEY_UP]&& !key[KEY_ESC]){
                    for (int j = 0; j < 2; ++j) {
                        sprintf(message[0],"               %s", highscore[option + 1].nomjeu);
                        sprintf(message[1],"%s             %s", joueurs[0].nom,joueurs[1].nom);
                        nblettre = strlen(message[j]);
                        for (int i = 0; i < nblettre; ++i) {

                            numlettre = (message[j][i] - '0') - 49;
                            if (numlettre < 0 || numlettre > 25) {
                                if (numlettre > -33 && numlettre < -6) {
                                    numlettre += 32;
                                } else if (numlettre > -50 && numlettre < -39) {
                                    numlettre += 49 + 27;//26+49 pour les chiffre on remplace 49 par ca
                                } else {
                                    numlettre = 26;
                                }
                            }
                            ylettre = j * (lettre[0]->h) + 140;
                            xlettre = i * (lettre[0]->w) + 180;
                            draw_sprite(buffer, lettre[numlettre], xlettre, ylettre);
                        }

                    }
                    for (int tour = 0; tour < 2; ++tour) {
                        for (int i = 0; i < (joueurs[tour].nb_essaie_guitare1); ++i) {
                            sprintf(message[i], "score %d", joueurs[tour].score_guitare1[i]);
                        }
                        for (int j = 0; j < (joueurs[tour].nb_essaie_guitare1); ++j) {
                            nblettre = strlen(message[j]);
                            for (int i = 0; i < nblettre; ++i) {

                                numlettre = (message[j][i] - '0') - 49;
                                if (numlettre < 0 || numlettre > 25) {
                                    if (numlettre > -33 && numlettre < -6) {
                                        numlettre += 32;
                                    } else if (numlettre > -50 && numlettre < -39) {
                                        numlettre += 49 + 27;//26+49 pour les chiffre on remplace 49 par ca
                                    } else {
                                        numlettre = 26;
                                    }
                                }
                                ylettre = (j+2) * (lettre[0]->h) + 140;
                                xlettre = i * (lettre[0]->w) + 180;
                                draw_sprite(buffer, lettre[numlettre], xlettre+tour*1050, ylettre);
                            }

                        }
                        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
                    }
                }
                break;
            case 3:
                while (!key[KEY_DOWN]&& !key[KEY_UP]&& !key[KEY_ESC]){
                    for (int j = 0; j < 2; ++j) {
                        sprintf(message[0],"               %s", highscore[option + 1].nomjeu);
                        sprintf(message[1],"%s             %s", joueurs[0].nom,joueurs[1].nom);
                        nblettre = strlen(message[j]);
                        for (int i = 0; i < nblettre; ++i) {

                            numlettre = (message[j][i] - '0') - 49;
                            if (numlettre < 0 || numlettre > 25) {
                                if (numlettre > -33 && numlettre < -6) {
                                    numlettre += 32;
                                } else if (numlettre > -50 && numlettre < -39) {
                                    numlettre += 49 + 27;//26+49 pour les chiffre on remplace 49 par ca
                                } else {
                                    numlettre = 26;
                                }
                            }
                            ylettre = j * (lettre[0]->h) + 140;
                            xlettre = i * (lettre[0]->w) + 180;
                            draw_sprite(buffer, lettre[numlettre], xlettre, ylettre);
                        }

                    }
                    for (int tour = 0; tour < 2; ++tour) {
                        for (int i = 0; i < (joueurs[tour].nb_essaie_river); ++i) {
                            sprintf(message[i], "score %d", joueurs[tour].score_river[i]);
                        }
                        for (int j = 0; j < (joueurs[tour].nb_essaie_river); ++j) {
                            nblettre = strlen(message[j]);
                            for (int i = 0; i < nblettre; ++i) {

                                numlettre = (message[j][i] - '0') - 49;
                                if (numlettre < 0 || numlettre > 25) {
                                    if (numlettre > -33 && numlettre < -6) {
                                        numlettre += 32;
                                    } else if (numlettre > -50 && numlettre < -39) {
                                        numlettre += 49 + 27;//26+49 pour les chiffre on remplace 49 par ca
                                    } else {
                                        numlettre = 26;
                                    }
                                }
                                ylettre = (j+2) * (lettre[0]->h) + 140;
                                xlettre = i * (lettre[0]->w) + 180;
                                draw_sprite(buffer, lettre[numlettre], xlettre+tour*1050, ylettre);
                            }

                        }
                        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
                    }
                }
                break;
            case 4:
                while (!key[KEY_DOWN]&& !key[KEY_UP]&& !key[KEY_ESC]){
                    for (int j = 0; j < 2; ++j) {
                        sprintf(message[0],"               %s", highscore[option + 1].nomjeu);
                        sprintf(message[1],"%s             %s", joueurs[0].nom,joueurs[1].nom);
                        nblettre = strlen(message[j]);
                        for (int i = 0; i < nblettre; ++i) {

                            numlettre = (message[j][i] - '0') - 49;
                            if (numlettre < 0 || numlettre > 25) {
                                if (numlettre > -33 && numlettre < -6) {
                                    numlettre += 32;
                                } else if (numlettre > -50 && numlettre < -39) {
                                    numlettre += 49 + 27;//26+49 pour les chiffre on remplace 49 par ca
                                } else {
                                    numlettre = 26;
                                }
                            }
                            ylettre = j * (lettre[0]->h) + 140;
                            xlettre = i * (lettre[0]->w) + 180;
                            draw_sprite(buffer, lettre[numlettre], xlettre, ylettre);
                        }

                    }
                    for (int tour = 0; tour < 2; ++tour) {
                        for (int i = 0; i < (joueurs[tour].nb_essaie_taupe); ++i) {
                            sprintf(message[i], "score %d", joueurs[tour].score_taupe[i]);
                        }
                        for (int j = 0; j < (joueurs[tour].nb_essaie_taupe); ++j) {
                            nblettre = strlen(message[j]);
                            for (int i = 0; i < nblettre; ++i) {

                                numlettre = (message[j][i] - '0') - 49;
                                if (numlettre < 0 || numlettre > 25) {
                                    if (numlettre > -33 && numlettre < -6) {
                                        numlettre += 32;
                                    } else if (numlettre > -50 && numlettre < -39) {
                                        numlettre += 49 + 27;//26+49 pour les chiffre on remplace 49 par ca
                                    } else {
                                        numlettre = 26;
                                    }
                                }
                                ylettre = (j+2) * (lettre[0]->h) + 140;
                                xlettre = i * (lettre[0]->w) + 180;
                                draw_sprite(buffer, lettre[numlettre], xlettre+tour*1050, ylettre);
                            }

                        }
                        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
                    }
                }
                break;
            case 5:
                while (!key[KEY_DOWN]&& !key[KEY_UP]&& !key[KEY_ESC]){
                    for (int j = 0; j < 2; ++j) {
                        sprintf(message[0],"               %s", highscore[option + 1].nomjeu);
                        sprintf(message[1],"%s             %s", joueurs[0].nom,joueurs[1].nom);
                        nblettre = strlen(message[j]);
                        for (int i = 0; i < nblettre; ++i) {

                            numlettre = (message[j][i] - '0') - 49;
                            if (numlettre < 0 || numlettre > 25) {
                                if (numlettre > -33 && numlettre < -6) {
                                    numlettre += 32;
                                } else if (numlettre > -50 && numlettre < -39) {
                                    numlettre += 49 + 27;//26+49 pour les chiffre on remplace 49 par ca
                                } else {
                                    numlettre = 26;
                                }
                            }
                            ylettre = j * (lettre[0]->h) + 140;
                            xlettre = i * (lettre[0]->w) + 180;
                            draw_sprite(buffer, lettre[numlettre], xlettre, ylettre);
                        }

                    }
                    for (int tour = 0; tour < 2; ++tour) {
                        for (int i = 0; i < (joueurs[tour].nb_essaie_snake); ++i) {
                            sprintf(message[i], "score %d", joueurs[tour].score_snake[i]);
                        }
                        for (int j = 0; j < (joueurs[tour].nb_essaie_snake); ++j) {
                            nblettre = strlen(message[j]);
                            for (int i = 0; i < nblettre; ++i) {

                                numlettre = (message[j][i] - '0') - 49;
                                if (numlettre < 0 || numlettre > 25) {
                                    if (numlettre > -33 && numlettre < -6) {
                                        numlettre += 32;
                                    } else if (numlettre > -50 && numlettre < -39) {
                                        numlettre += 49 + 27;//26+49 pour les chiffre on remplace 49 par ca
                                    } else {
                                        numlettre = 26;
                                    }
                                }
                                ylettre = (j+2) * (lettre[0]->h) + 140;
                                xlettre = i * (lettre[0]->w) + 180;
                                draw_sprite(buffer, lettre[numlettre], xlettre+tour*1050, ylettre);
                            }

                        }
                        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
                    }
                }
                break;
            case 6:
                while (!key[KEY_DOWN]&& !key[KEY_UP]&& !key[KEY_ESC]){
                    for (int j = 0; j < 2; ++j) {
                        sprintf(message[0],"               %s", highscore[option + 1].nomjeu);
                        sprintf(message[1],"%s             %s", joueurs[0].nom,joueurs[1].nom);
                        nblettre = strlen(message[j]);
                        for (int i = 0; i < nblettre; ++i) {

                            numlettre = (message[j][i] - '0') - 49;
                            if (numlettre < 0 || numlettre > 25) {
                                if (numlettre > -33 && numlettre < -6) {
                                    numlettre += 32;
                                } else if (numlettre > -50 && numlettre < -39) {
                                    numlettre += 49 + 27;//26+49 pour les chiffre on remplace 49 par ca
                                } else {
                                    numlettre = 26;
                                }
                            }
                            ylettre = j * (lettre[0]->h) + 140;
                            xlettre = i * (lettre[0]->w) + 180;
                            draw_sprite(buffer, lettre[numlettre], xlettre, ylettre);
                        }

                    }
                    for (int tour = 0; tour < 2; ++tour) {
                        for (int i = 0; i < (joueurs[tour].nb_essaie_canard); ++i) {
                            sprintf(message[i], "score %d", joueurs[tour].score_canard[i]);
                        }
                        for (int j = 0; j < (joueurs[tour].nb_essaie_canard); ++j) {
                            nblettre = strlen(message[j]);
                            for (int i = 0; i < nblettre; ++i) {

                                numlettre = (message[j][i] - '0') - 49;
                                if (numlettre < 0 || numlettre > 25) {
                                    if (numlettre > -33 && numlettre < -6) {
                                        numlettre += 32;
                                    } else if (numlettre > -50 && numlettre < -39) {
                                        numlettre += 49 + 27;//26+49 pour les chiffre on remplace 49 par ca
                                    } else {
                                        numlettre = 26;
                                    }
                                }
                                ylettre = (j+2) * (lettre[0]->h) + 140;
                                xlettre = i * (lettre[0]->w) + 180;
                                draw_sprite(buffer, lettre[numlettre], xlettre+tour*1050, ylettre);
                            }

                        }
                        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
                    }
                }
                break;
            case 7:
                while (!key[KEY_DOWN]&& !key[KEY_UP]&& !key[KEY_ESC]){
                    for (int j = 0; j < 2; ++j) {
                        sprintf(message[0],"               %s", highscore[option + 1].nomjeu);
                        sprintf(message[1],"%s             %s", joueurs[0].nom,joueurs[1].nom);
                        nblettre = strlen(message[j]);
                        for (int i = 0; i < nblettre; ++i) {

                            numlettre = (message[j][i] - '0') - 49;
                            if (numlettre < 0 || numlettre > 25) {
                                if (numlettre > -33 && numlettre < -6) {
                                    numlettre += 32;
                                } else if (numlettre > -50 && numlettre < -39) {
                                    numlettre += 49 + 27;//26+49 pour les chiffre on remplace 49 par ca
                                } else {
                                    numlettre = 26;
                                }
                            }
                            ylettre = j * (lettre[0]->h) + 140;
                            xlettre = i * (lettre[0]->w) + 180;
                            draw_sprite(buffer, lettre[numlettre], xlettre, ylettre);
                        }

                    }
                    for (int tour = 0; tour < 2; ++tour) {
                        for (int i = 0; i < (joueurs[tour].nb_essaie_casino); ++i) {
                            sprintf(message[i], "score %d", joueurs[tour].score_casino[i]);
                        }
                        for (int j = 0; j < (joueurs[tour].nb_essaie_casino); ++j) {
                            nblettre = strlen(message[j]);
                            for (int i = 0; i < nblettre; ++i) {

                                numlettre = (message[j][i] - '0') - 49;
                                if (numlettre < 0 || numlettre > 25) {
                                    if (numlettre > -33 && numlettre < -6) {
                                        numlettre += 32;
                                    } else if (numlettre > -50 && numlettre < -39) {
                                        numlettre += 49 + 27;//26+49 pour les chiffre on remplace 49 par ca
                                    } else {
                                        numlettre = 26;
                                    }
                                }
                                ylettre = (j+2) * (lettre[0]->h) + 140;
                                xlettre = i * (lettre[0]->w) + 180;
                                draw_sprite(buffer, lettre[numlettre], xlettre+tour*1050, ylettre);
                            }

                        }
                        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
                    }
                }
                break;
            case 8:
                while (!key[KEY_DOWN]&& !key[KEY_UP]&& !key[KEY_ESC]){
                    for (int j = 0; j < 2; ++j) {
                        sprintf(message[0],"               %s", highscore[option + 1].nomjeu);
                        sprintf(message[1],"%s             %s", joueurs[0].nom,joueurs[1].nom);
                        nblettre = strlen(message[j]);
                        for (int i = 0; i < nblettre; ++i) {

                            numlettre = (message[j][i] - '0') - 49;
                            if (numlettre < 0 || numlettre > 25) {
                                if (numlettre > -33 && numlettre < -6) {
                                    numlettre += 32;
                                } else if (numlettre > -50 && numlettre < -39) {
                                    numlettre += 49 + 27;//26+49 pour les chiffre on remplace 49 par ca
                                } else {
                                    numlettre = 26;
                                }
                            }
                            ylettre = j * (lettre[0]->h) + 140;
                            xlettre = i * (lettre[0]->w) + 180;
                            draw_sprite(buffer, lettre[numlettre], xlettre, ylettre);
                        }

                    }
                    for (int tour = 0; tour < 2; ++tour) {
                        for (int i = 0; i < (joueurs[tour].nb_essaie_chevaux); ++i) {
                            sprintf(message[i], "score %d", joueurs[tour].score_chevaux[i]);
                        }
                        for (int j = 0; j < (joueurs[tour].nb_essaie_chevaux); ++j) {
                            nblettre = strlen(message[j]);
                            for (int i = 0; i < nblettre; ++i) {

                                numlettre = (message[j][i] - '0') - 49;
                                if (numlettre < 0 || numlettre > 25) {
                                    if (numlettre > -33 && numlettre < -6) {
                                        numlettre += 32;
                                    } else if (numlettre > -50 && numlettre < -39) {
                                        numlettre += 49 + 27;//26+49 pour les chiffre on remplace 49 par ca
                                    } else {
                                        numlettre = 26;
                                    }
                                }
                                ylettre = (j+2) * (lettre[0]->h) + 140;
                                xlettre = i * (lettre[0]->w) + 180;
                                draw_sprite(buffer, lettre[numlettre], xlettre+tour*1050, ylettre);
                            }

                        }
                        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
                    }
                }
                break;
            case 9:
                while (!key[KEY_DOWN]&& !key[KEY_UP]&& !key[KEY_ESC]){
                    for (int j = 0; j < 2; ++j) {
                        sprintf(message[0],"               %s", highscore[option + 1].nomjeu);
                        sprintf(message[1],"%s             %s", joueurs[0].nom,joueurs[1].nom);
                        nblettre = strlen(message[j]);
                        for (int i = 0; i < nblettre; ++i) {

                            numlettre = (message[j][i] - '0') - 49;
                            if (numlettre < 0 || numlettre > 25) {
                                if (numlettre > -33 && numlettre < -6) {
                                    numlettre += 32;
                                } else if (numlettre > -50 && numlettre < -39) {
                                    numlettre += 49 + 27;//26+49 pour les chiffre on remplace 49 par ca
                                } else {
                                    numlettre = 26;
                                }
                            }
                            ylettre = j * (lettre[0]->h) + 140;
                            xlettre = i * (lettre[0]->w) + 180;
                            draw_sprite(buffer, lettre[numlettre], xlettre, ylettre);
                        }

                    }
                    for (int tour = 0; tour < 2; ++tour) {
                        for (int i = 0; i < (joueurs[tour].nb_essaie_ballon); ++i) {
                            sprintf(message[i], "score %d", joueurs[tour].score_ballon[i]);
                        }
                        for (int j = 0; j < (joueurs[tour].nb_essaie_ballon); ++j) {
                            nblettre = strlen(message[j]);
                            for (int i = 0; i < nblettre; ++i) {

                                numlettre = (message[j][i] - '0') - 49;
                                if (numlettre < 0 || numlettre > 25) {
                                    if (numlettre > -33 && numlettre < -6) {
                                        numlettre += 32;
                                    } else if (numlettre > -50 && numlettre < -39) {
                                        numlettre += 49 + 27;//26+49 pour les chiffre on remplace 49 par ca
                                    } else {
                                        numlettre = 26;
                                    }
                                }
                                ylettre = (j+2) * (lettre[0]->h) + 140;
                                xlettre = i * (lettre[0]->w) + 180;
                                draw_sprite(buffer, lettre[numlettre], xlettre+tour*1050, ylettre);
                            }

                        }
                        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
                    }
                }
                break;

        }
    }
    rest(150); // Pause de 10 ms pour rafraîchir l'écran
    clear_bitmap(buffer);
    clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
    rest(150); // Pause de 10 ms pour rafraîchir l'écran
}