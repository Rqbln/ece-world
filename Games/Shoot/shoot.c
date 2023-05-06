#include <time.h>
#include <stdlib.h>
#include "shoot.h"

void shoot() {
    srand(time(NULL));
    //Données joueurs
    int nbjoueur=2;
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

    // Création du buffer
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    clear_to_color(buffer, makecol(0, 0, 0));
    //écran d'explication
    rest(2000);

    readkey();
    rest(2000);
    // Boucle principale du jeu
    for (int turn = 0; turn < 2; ++turn) {
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
                textprintf_ex(screen, font, 10, 1050, makecol(255, 0, 0), -1, "J%d : %.2f secondes écoulées", turn + 1,elapsed_time);
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
                textprintf_ex(screen, font, background->w/2, background->h/2, makecol(255, 255, 0), -1, "J%d : SCORE : %.2f s", turn+1,joueurscore[turn]);
                if (turn==0) {
                    textprintf_ex(screen, font, (background->w / 2) - 80, (background->h / 2) + 100, makecol(255, 0, 255),-1, "Appuyez sur une touche, au tour du J2 !");
                    rest(1000);
                    readkey();

                }
                else {
                    textprintf_ex(screen, font, (background->w/2)-80, (background->h/2)+100, makecol(255, 0, 255), -1, "Appuyez sur une touche, pour voir les scores !");
                    rest(200);
                    readkey();
                    if (joueurscore[0]<joueurscore[1]) {
                        textprintf_ex(screen, font, (background->w/2)-80, (background->h/2)+200, makecol(255, 255, 0), -1, "Le J1 a remporté 1 ticket ! Quelle vitesse !");
                    }
                    else {
                        textprintf_ex(screen, font, (background->w/2)-200, (background->h/2)+200, makecol(255, 255, 0), -1, "Le J2 a remporté 1 ticket ! Quelle vitesse !");
                    }
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
    while (!key[KEY_ESC]) {
        textprintf_ex(screen, font, (background->w/2)-80, (background->h/2)+250, makecol(rand()%255, rand()%255, rand()%255), -1, "Cliquez sur échap pour retourner au parc !");
        rest(20);
    }
    // Libération des ressources
    destroy_bitmap(background);
    destroy_bitmap(buffer);
}