#include <time.h>
#include <stdlib.h>
#include "shoot.h"
#include "../../Init_Allegro/allegro.h"
#include "../../joueur/joueur.h"
#include "../../ScoreTab/scoreTab.h"
void shoot() {
    srand(time(NULL));
    //Données joueurs
    int nbjoueur=2;
    char mess[80];
    double joueurscore[nbjoueur];
    //Autres
    int turn[2];
    char timemess[20];
    double start_time, end_time;
    double elapsed_time;
    int gameover=0;
    int baloon_h=309;
    int baloon_w=192;
    int temps;
    int end=0;
    //Positions et états ballons
    int baloonxy[2][5];
    int baloonState[5];
    //Vitesse base ballons
    int vx[5];
    int vy[5];
    //Coordonnées souris pour viseur
    int x;
    int y;
    SAMPLE *transition = load_wav("../Games/Shoot/musique/transition.wav");
    SAMPLE *pop = load_wav("../Games/Shoot/musique/baloonpop.wav");
    SAMPLE *clear = load_wav("../Games/Shoot/musique/marioclear.wav");
    SAMPLE *music = load_wav("../Games/Shoot/musique/mariomusic.wav");
    FONT *police = load_font("arial.pcx", NULL, NULL);
    // Chargement des images
    BITMAP* background = load_bitmap("../Games/Shoot/image/background.bmp", NULL);
    if(!background){
        allegro_message("../Games/Shoot/image/background.bmp");
        exit(EXIT_FAILURE);
    }
    BITMAP* baloon = load_bitmap("../Games/Shoot/image/baloon.bmp", NULL);
    if(!baloon){
        allegro_message("../Games/Shoot/image/baloon.bmp");
        exit(EXIT_FAILURE);
    }
    BITMAP* viseur = load_bitmap("../Games/Shoot/image/viseur.bmp", NULL);
    if(!viseur){
        allegro_message("../Games/Shoot/image/viseur.bmp");
        exit(EXIT_FAILURE);
    }
    BITMAP* scroll = load_bitmap("../Games/Shoot/image/scroll.bmp", NULL);
    if(!viseur){
        allegro_message("../Games/Shoot/image/scroll.bmp");
        exit(EXIT_FAILURE);
    }
    BITMAP* scores = load_bitmap("../Games/Shoot/image/scores.bmp", NULL);
    if(!viseur){
        allegro_message("../Games/Shoot/image/scores.bmp");
        exit(EXIT_FAILURE);
    }
    BITMAP* regles = load_bitmap("../Games/Shoot/image/regles.bmp", NULL);
    if(!viseur){
        allegro_message("../Games/Shoot/image/regles.bmp");
        exit(EXIT_FAILURE);
    }

    // Création du buffer
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    clear_to_color(buffer, makecol(0, 0, 0));
    //écran d'explication

    // Boucle principale du jeu
    play_sample(music, 255, 128, 1000, 0);
    for (int turn = 0; turn < 2; ++turn) {
//Coût de la participation=1 bitcoin
        joueurs[turn].nbTickets--;

        while (!key[KEY_ENTER]){
            draw_sprite(buffer,background,0,0);
            //Affichage règles
            if (turn==0) draw_sprite(buffer,regles,WIDTH/2-200,HEIGHT/2-200);

            sprintf(mess, "Appuyez sur entrée pour commencer le tour de %s !",joueurs[turn].nom);
            textout_centre_ex(buffer, font, mess, WIDTH / 2, HEIGHT / 2+120, makecol(255, 255, 255), -1);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        }
        if (turn==0) {
            play_sample(transition, 255, 128, 1000, 0);
            for (int i = 0; i < 300; ++i) {
                draw_sprite(buffer,background,0,0);
                draw_sprite(buffer, regles, WIDTH / 2 - 200, HEIGHT / 2 - 200-2*i);
                sprintf(mess, "Appuyez sur entrée pour commencer le tour de %s !",joueurs[turn].nom);
                textout_centre_ex(buffer, font, mess, WIDTH / 2, HEIGHT / 2+120, makecol(255, 255, 255), -1);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            }
        }
        for (int i = 3; i > 0; --i) {
            clear_bitmap(buffer);
            draw_sprite(buffer,background,0,0);
            sprintf(mess, "%d", i);
            textout_centre_ex(buffer, font, mess, WIDTH / 2, HEIGHT / 2, makecol(255, 255, 255), -1);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(1000);
        }
        int random_num = rand() % 2 == 0 ? 1 : -1;
        for (int i = 0; i < 5; ++i) {
            baloonxy[0][i]=1920/2;
            baloonxy[1][i]=1080/2;
            vx[i]=8*random_num+(rand()%(5-2)+2);
            vy[i]=10*random_num+(rand()%(5-2)+2);
            baloonState[i]=0;
        }
        start_time =clock();
        end=0;
        while (!key[KEY_ESC]||gameover==0) {
            //Affichage du temps réel écoulé

            x = mouse_x;
            y = mouse_y;
            srand(time(NULL));
            //Timer
            if(gameover==0) {
                end_time =clock();
                elapsed_time = ((end_time-start_time)/CLOCKS_PER_SEC)*5.33;
                textprintf_ex(screen, font, 10, 1050, makecol(255, 0, 0), -1, "%s : %.2f secondes écoulées", joueurs[turn].nom,elapsed_time);
            }
            rest(5);
            // Copie de l'image dans le back buffer
            blit(background, buffer, 0, 0, 0, 0, background->w, background->h);
            for (int i = 0; i < 5; ++i) {
                if (baloonState[i] == 0) {
                    draw_sprite(buffer, baloon, baloonxy[0][i], baloonxy[1][i]);
                    baloonxy[0][i] += vx[i];
                    baloonxy[1][i] += vy[i];
                }
                //vérifie si le ballon a été éclaté
                if ((mouse_b & 1) && (mouse_x > baloonxy[0][i]) && (mouse_x < (baloonxy[0][i] + baloon_w)) &&
                    (mouse_y > baloonxy[1][i]) && (mouse_y < (baloonxy[1][i] + baloon_w))) {
                    baloonState[i] = 1;
                    baloonxy[0][i] = -1000;
                    baloonxy[1][i] = -1000;
                    end++;
                    play_sample(pop, 255, 128, 1000, 0);
                }
                baloonxy[0][i] += vx[i];
                baloonxy[1][i] += vy[i];
                if ((baloonxy[0][i] < 0 && vx[i] < 0) || (baloonxy[0][i] + baloon_w > SCREEN_W && vx[i] > 0)) {
                    vx[i] = -vx[i];
                }
                if ((baloonxy[1][i] < 0 && vy[i] < 0) || (baloonxy[1][i] + baloon_h > SCREEN_H && vy[i] > 0)) {
                    vy[i] = -vy[i];
                }

                //Rebond sur les bords de l'écran

            }
            draw_sprite(buffer, viseur, (x - viseur->w / 2), (y - viseur->h / 2));
            //Condition de "Victoire"
            end_time =clock();
            if (end >= 5) {

                joueurscore[turn]=((end_time-start_time)/CLOCKS_PER_SEC)*5.33;
                textprintf_ex(screen, font, background->w/2, background->h/2, makecol(255, 255, 255), -1, "%s : SCORE : %.2f s", joueurs[turn].nom,joueurscore[turn]);
                if (turn==0) {
                    textprintf_ex(screen, font, (background->w / 2) - 80, (background->h / 2) + 100, makecol(255, 255, 255),-1, "Appuyez sur une touche, au tour de %s !",joueurs[1].nom);
                    rest(1000);
                    readkey();

                }


                readkey();
                gameover=1;
                break;
            }
            blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
            // Affichage du buffer principal
            vsync();
        }
        start_time = time(NULL);
    }
    stop_sample(music);
    play_sample(clear, 255, 128, 1000, 0);

    while (!(key[KEY_ESC])) {
        draw_sprite(buffer,background,0,0);
        draw_sprite(buffer,scores,WIDTH/2-200,HEIGHT/2-200);
        textprintf_ex(buffer, font, (WIDTH/2)-50, (HEIGHT/2)-75, makecol(0, 0, 0), -1, "%s : %.2f s",joueurs[0].nom,joueurscore[0]);
        textprintf_ex(buffer, font, (WIDTH/2)-50, (HEIGHT/2)-50, makecol(0, 0, 0), -1, "%s : %.2f s",joueurs[1].nom,joueurscore[1]);
        draw_sprite(buffer, viseur, viseur->w, viseur->h);
        if (joueurscore[0]<joueurscore[1]){
            textprintf_ex(buffer, font, (WIDTH/2)-20, (HEIGHT/2)-25, makecol(0, 0, 0), -1, "%s a été le plus rapide !",joueurs[0].nom,joueurscore[0]);
            textprintf_ex(buffer, font, (WIDTH/2)-110, (HEIGHT/2)-15, makecol(0, 0, 0), -1, "Il remporte 2 tickets !");
        }
        else if (joueurscore[0]==joueurscore[1]) {
            textprintf_ex(buffer, font, (WIDTH/2)-30, (HEIGHT/2)-25, makecol(0, 0, 0), -1, "Personne n'a gagné le combat :(",joueurs[0].nom,joueurscore[0]);
            textprintf_ex(buffer, font, (WIDTH/2)-30, (HEIGHT/2)-15, makecol(0, 0, 0), -1, "Le roi babouin se suicide de tristesse",joueurs[0].nom,joueurscore[0]);
        }
        else {
            textprintf_ex(buffer, font, (WIDTH/2)-100, (HEIGHT/2)-25, makecol(0, 0, 0), -1, "%s a été le plus vif !",joueurs[0].nom,joueurscore[1]);
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
        draw_sprite(buffer, viseur, viseur->w, viseur->h);
        if (joueurscore[0]<joueurscore[1]){
            textprintf_ex(buffer, font, (WIDTH/2)-20, (HEIGHT/2)-25-2*i, makecol(0, 0, 0), -1, "%s a été le plus vif !",joueurs[0].nom,joueurscore[0]);
            textprintf_ex(buffer, font, (WIDTH/2)-110, (HEIGHT/2)-15-2*i, makecol(0, 0, 0), -1, "Il remporte 2 tickets !");
        }
        else if (joueurscore[0]==joueurscore[1]) {
            textprintf_ex(buffer, font, (WIDTH/2)-30, (HEIGHT/2)-25-2*i, makecol(0, 0, 0), -1, "Personne n'a gagné le combat, les chevaliers reprennent leurs tickets",joueurs[0].nom,joueurscore[0]);
        }
        else {
            textprintf_ex(buffer, font, (WIDTH/2)-100, (HEIGHT/2)-25-2*i, makecol(0, 0, 0), -1, "%s a été le plus vif !",joueurs[0].nom,joueurscore[1]);
            textprintf_ex(buffer, font, (WIDTH/2)-110, (HEIGHT/2)-15-2*i, makecol(0, 0, 0), -1, "Il remporte 2 tickets !");
        }
        textprintf_ex(buffer, font, (WIDTH/2)-110, (HEIGHT/2)-8-2*i, makecol(rand()%255, rand()%255, rand()%255), -1, "Appuyez sur <échap> pour retourner au parc !");
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    }


    if (joueurscore[0]<joueurscore[1]){
        joueurs[0].nbTickets=joueurs[0].nbTickets+2;
        if ((double)((highscore[7].score)/100) >= joueurscore[0]||highscore[7].score==0) {

            sprintf(mess, "%s vient d'établir un nouveau record ! Enregistrement du meilleur score terminé.",joueurs[0].nom);
            textout_centre_ex(buffer,font, mess, WIDTH/2, HEIGHT / 2 + 20, makecol(255, 255, 255), -1);
            saveMiniGame(joueurs,"Shoot",joueurscore[0]*100,0);
        }
    }
    else if (joueurscore[0]==joueurscore[1]) {
        joueurs[0].nbTickets++;
        joueurs[1].nbTickets++;
    }
    else {
        joueurs[1].nbTickets=joueurs[1].nbTickets+2;
        if ((double)((highscore[7].score)/100) >= joueurscore[1]||highscore[7].score==0) {

            sprintf(mess, "%s vient d'établir un nouveau record ! Enregistrement du meilleur score terminé.",joueurs[1].nom);
            textout_centre_ex(buffer,font, mess, WIDTH/2, HEIGHT / 2 + 20, makecol(255, 255, 255), -1);
            saveMiniGame(joueurs,"Shoot",joueurscore[1]*100,1);
        }
    }
    // Libération des ressources
    destroy_bitmap(background);
    destroy_bitmap(buffer);
    loadHighScore(highscore);
}