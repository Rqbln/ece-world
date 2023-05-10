#include "taupe.h"
#include "../../Init_Allegro/allegro.h"

int score = 0;
int gagnant = 0;
int gameOver = 0;
char messageDebut[90];
char messageFin[90];
int isClicked = 0;

// Les coordonnées des 6 trous de la pyramide
int pyramid_x[6] = {WIDTH/2-200, WIDTH/2 -400, WIDTH/2, WIDTH/2 + 400, WIDTH/2 +200, WIDTH/2 };
int pyramid_y[6] = {3*HEIGHT/7, 2*HEIGHT/3, 2*HEIGHT/3, 2*HEIGHT/3, 3*HEIGHT/7, HEIGHT/5};
int pyramid_index = 0;
int maxTargets = 1;

typedef struct Target {
    int x, y, size, pyramid_index, isBusy;
} Target;


Target targets[6];



int is_target_occupied(int index, Target targets[], int num_targets) {
    for (int i = 0; i < num_targets; ++i) {
        if (targets[i].pyramid_index == index) {
            return 1;
        }
    }
    return 0;
}

void jeu_taupe(){

    BITMAP *taupe[5];
    char filename[80];

    //Taupe
    for (int i = 0; i < 5; i++) {
        sprintf(filename, "../Games/Taupe/images/taupe_%d.bmp",i);

        taupe[i] = load_bitmap(filename, NULL);



        if (!taupe[i]) { //blindage
            allegro_message("Erreur icone");
            exit(EXIT_FAILURE);
        }
    }

    BITMAP *fond = load_bitmap("../Games/Taupe/images/fond.bmp",NULL);
    BITMAP *buffer = create_bitmap(SCREEN_W,SCREEN_H);

    srand(time(NULL));
    for (int i = 0; i < maxTargets; ++i) {
        targets[i].x = pyramid_x[pyramid_index];
        targets[i].y = pyramid_y[pyramid_index];
        targets[i].size = TAILLE_INITIALE;
        targets[i].pyramid_index = pyramid_index;
        targets[i].isBusy = 0;
        pyramid_index++;
    }

    show_mouse(screen);


    while (!key[KEY_ENTER]){
        draw_sprite(buffer,fond,0,0);
        sprintf(messageDebut, "Appuyez sur entrée pour commencer la partie !");
        textout_centre_ex(buffer,font, messageDebut, WIDTH/2, HEIGHT / 2, makecol(255, 255, 255), -1);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(10);
    }

    for (int i = 3; i > 0; --i) {
        clear_bitmap(buffer);
        draw_sprite(buffer,fond,0,0);
        sprintf(messageDebut, "%d",i);
        textout_centre_ex(buffer,font, messageDebut, WIDTH/2, HEIGHT / 2, makecol(255, 255, 255), -1);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(1000);
    }


    while (!gameOver && !key[KEY_ESC]) {
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        draw_sprite(buffer,fond,0,0);
        for (int i = 0; i < 6; ++i) {
            circle(buffer, pyramid_x[i], pyramid_y[i], TAILLE_INITIALE, makecol(255, 255, 255));
        }

        for (int i = 0; i < maxTargets; ++i) {
            circlefill(buffer, targets[i].x, targets[i].y, targets[i].size, makecol(255, 0, 0));
            targets[i].size -= 2;

            if (targets[i].size < TAILLE_INITIALE/8) {
                draw_sprite(buffer,taupe[0],targets[i].x-119,targets[i].y-91);
            } else if (targets[i].size < 2 * TAILLE_INITIALE/8) {
                draw_sprite(buffer,taupe[1],targets[i].x-119,targets[i].y-91);
            } else if (targets[i].size < 3 * TAILLE_INITIALE/8) {
                draw_sprite(buffer,taupe[2],targets[i].x-119,targets[i].y-91);
            } else if (targets[i].size < 4 * TAILLE_INITIALE/8) {
                draw_sprite(buffer,taupe[3],targets[i].x-119,targets[i].y-91);
            } else if (targets[i].size < 5 * TAILLE_INITIALE/8) {
                draw_sprite(buffer,taupe[2],targets[i].x-119,targets[i].y-91);
            } else if (targets[i].size < 6 * TAILLE_INITIALE/8) {
                draw_sprite(buffer,taupe[1],targets[i].x-119,targets[i].y-91);
            } else if (targets[i].size < 7 * TAILLE_INITIALE / 8){
                draw_sprite(buffer,taupe[0],targets[i].x-119,targets[i].y-91);
            } else if (targets[i].size < TAILLE_INITIALE){
                draw_sprite(buffer,taupe[4],targets[i].x-119,targets[i].y-91);
            }
        }


        if (mouse_b & 1 && !isClicked) {
            int mx = mouse_x;
            int my = mouse_y;

            for (int i = 0; i < maxTargets; ++i) {
                if (mx >= targets[i].x - TAILLE_INITIALE && mx <= targets[i].x + TAILLE_INITIALE&& my >= targets[i].y - TAILLE_INITIALE && my <= targets[i].y + TAILLE_INITIALE) {
                    score++;
                    targets[i].isBusy = 0;  // Marquez la position comme libre
                    targets[i].size = TAILLE_INITIALE;
                    int newIndex;
                    do {
                        newIndex = rand()%6;
                    } while (is_target_occupied(newIndex, targets, maxTargets));
                    targets[i].pyramid_index = newIndex;
                    targets[i].x = pyramid_x[targets[i].pyramid_index];
                    targets[i].y = pyramid_y[targets[i].pyramid_index];
                    targets[i].isBusy = 1;  // Marquez la nouvelle position comme occupée

                    if (score % 5 == 0 && maxTargets < 6) {
                        maxTargets++;
                        do {
                            newIndex = rand()%6;
                        } while (is_target_occupied(newIndex, targets, maxTargets));
                        targets[maxTargets-1].x = pyramid_x[newIndex];
                        targets[maxTargets-1].y = pyramid_y[newIndex];
                        targets[maxTargets-1].size = TAILLE_INITIALE;
                        targets[maxTargets-1].pyramid_index = newIndex;
                        targets[maxTargets-1].isBusy = 1;  // Marquez la nouvelle position comme occupée
                    }
                }
            }
            isClicked = 1;
        }
        else if (!(mouse_b & 1) && isClicked) {
            isClicked = 0;
        }






        for (int i = 0; i < maxTargets; ++i) {
            if (targets[i].size < 1) {
                gameOver = 1;
                if (pyramid_index < 6) {
                    targets[i].x = pyramid_x[pyramid_index];
                    targets[i].y = pyramid_y[pyramid_index];
                    pyramid_index++;
                }
            }
        }

        textprintf_centre_ex(buffer, font, WIDTH / 2, 10, makecol(255, 255, 255), -1, "Score: %d", score);

        // Mettre à jour l'écran
        vsync();
        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);

        // Attendre un peu pour éviter que les cercles n'apparaissent trop rapidement
        rest(50);

        if (score == 20){
            gameOver = 1;
            gagnant = 1;
            clear_bitmap(buffer);
        }
    }

    while (!key[KEY_ESC]){
        clear_bitmap(buffer);
        draw_sprite(buffer,fond,0,0);
        if (gagnant){
            sprintf(messageFin, "Le joueur 1 a atteint 30 points, Vous avez gagné ! Fin de la partie.");
            textout_centre_ex(buffer,font, messageFin, WIDTH/2, HEIGHT / 2, makecol(255, 255, 255), -1);
        } else {
            sprintf(messageFin, "Vous avez laissé partir une Taupe après %d points. Fin de la partie",score);
            textout_centre_ex(buffer,font, messageFin, WIDTH/2, HEIGHT / 2, makecol(255, 255, 255), -1);
        }
        // Mettre à jour l'écran
        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
        rest(10); // Pause de 10 ms pour rafraîchir l'écran
        vsync();
    }
}