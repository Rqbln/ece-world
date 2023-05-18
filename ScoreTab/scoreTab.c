//
// Created by bapti on 17/05/2023.
//

#include "scoreTab.h"
void tableau_score(){
    rest(200); // Pause de 10 ms pour rafraîchir l'écran
    BITMAP *buffer;
    BITMAP *compteur[10];
    BITMAP *lettre[27];//+10 pour les chiffre
    BITMAP *fond= load_bitmap("../Games/Guitar_hero/image/tetedragon1.bmp",NULL);
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
    int nblettre=30;
    int xlettre=0;
    int ylettre=0;
    char message[8][nblettre];
    char nomDeFichier[50];

    int xenter=WIDTH-400;
    int yenter=HEIGHT-80;

    if(!fond){
        allegro_message("../image/fondguitar0.bmp ");
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
    for(int i=0;i<27;i++){ //+10
        if (i<27){
            sprintf(nomDeFichier,"../ScoreTab/lettre/%c.bmp",i+97);
        } else{
            sprintf(nomDeFichier,"../ScoreTab/lettre/%d.bmp",i-27);
        }
        lettre[i]= load_bitmap(nomDeFichier,NULL);
        if(!lettre[i]){
            allegro_message("../Games/lettre/%c.bmp",i+97);
            exit(EXIT_FAILURE);
        }
    }
    while (!key[KEY_ESC]) {
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        draw_sprite(buffer,enterkey,xenter,yenter);
        stretch_blit(fond,buffer,0,0,fond->w,fond->h,0,0,WIDTH,HEIGHT);
        score1=score%10;
        score2=((score-score1)/10)%10;
        score3=((score-(score1+ 10*score2))/100)%10;
        draw_sprite(buffer,compteur[score3],xcompteur,ycompteur);
        draw_sprite(buffer,compteur[score2],xcompteur+(compteur[0]->w),ycompteur);
        draw_sprite(buffer,compteur[score1],xcompteur+2*(compteur[0]->w),ycompteur);
        textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "score: %d", score);
        sprintf(message[0], "ERIKA");
        sprintf(message[1], "JeanMarie");
        sprintf(message[2], "Lenazy");
        sprintf(message[3], "Z");
        sprintf(message[4], "la mere de lulu");
        sprintf(message[5], "vit dans");
        sprintf(message[6], "un ananas dans la mer");
        sprintf(message[7], "Zaptiste ce bg01234");

        for (int j = 0; j < 8; ++j) {
            nblettre = strlen(message[j]);
            for (int i = 0; i < nblettre; ++i) {

                numlettre = (message[j][i] - '0')-49;
                if (numlettre<0 || numlettre>25){
                    if (numlettre>-33 && numlettre<-6){
                        numlettre+=32;
                    }
                    else if(numlettre>-50 && numlettre<-39) {
                        numlettre+=49;//26+49 pour les chiffre on remplace 49 par ca
                    }
                    else{
                        numlettre=26;
                    }
                }
                printf("Caractere : %c, Entier : %d\n", message[j][i], (message[j][i] - '0'));
                ylettre=j*(lettre[0]->h);
                xlettre=i*(lettre[0]->w);
                draw_sprite(buffer,lettre[numlettre],xlettre,ylettre);
            }

        }
        blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);


    }
    rest(150); // Pause de 10 ms pour rafraîchir l'écran
    clear_bitmap(buffer);
    clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
    rest(150); // Pause de 10 ms pour rafraîchir l'écran
}