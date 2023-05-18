#include "taupe.h"
#include "../../Init_Allegro/allegro.h"
#include "../../joueur/joueur.h"

int score[2];
int gagnant = 0;
int gameOver = 0;
char messageDebut[90];
char messageFin[180];
int isClicked = 0;



// Les coordonnées des 6 trous de la pyramide
int pyramid_x[6] = {686, 1700, 1300, 1406, 400, 266 };
int pyramid_y[6] = {516, 660, 700, 334, 676, 390};
int pyramid_index = 0;
int maxTargets = 1;
int memotickets[NB_JOUEURS];


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

void jeu_taupe() {

    BITMAP *Tireur[17];
    char filename[80];

    //Tireur
    for (int i = 0; i < 17; i++) {
        sprintf(filename, "../Games/Taupe/images/sprites/Tireur_%d.bmp", i);

        Tireur[i] = load_bitmap(filename, NULL);


        if (!Tireur[i]) { //blindage
            allegro_message("Erreur icone");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NB_JOUEURS; ++i) {
        memotickets[i] = joueurs[i].nbTickets;
    }

    BITMAP *fond = load_bitmap("../Games/Taupe/images/fond.bmp", NULL);
    BITMAP *fond2 = load_bitmap("../Games/Taupe/images/fond2.bmp", NULL);
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);

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


    while (!key[KEY_SPACE]) {
        draw_sprite(buffer, fond, 0, 0);
        sprintf(messageDebut, "Appuyez sur espace pour commencer la partie !");
        textout_centre_ex(buffer, font, messageDebut, WIDTH / 2, HEIGHT / 2, makecol(255, 255, 255), -1);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(10);
    }


    for (int i = 0; i < 2; ++i) {

        gameOver = 0;
        targets[0].size = TAILLE_INITIALE;
        targets[1].size = TAILLE_INITIALE;

        while (!key[KEY_ENTER]) {
            draw_sprite(buffer, fond, 0, 0);
            sprintf(messageDebut, "%s, A toi de jouer. Appuie sur entrée pour commencer.", joueurs[i].nom);
            textout_centre_ex(buffer, font, messageDebut, WIDTH / 2, HEIGHT / 2, makecol(255, 255, 255), -1);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(10);
        }

        for (int i = 3; i > 0; --i) {
            clear_bitmap(buffer);
            draw_sprite(buffer, fond, 0, 0);
            sprintf(messageDebut, "%d", i);
            textout_centre_ex(buffer, font, messageDebut, WIDTH / 2, HEIGHT / 2, makecol(255, 255, 255), -1);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(1000);
        }


        while (!gameOver && !key[KEY_ESC]) {
            clear_bitmap(buffer);
            clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
            draw_sprite(buffer, fond, 0, 0);

            for (int j = 0; j < maxTargets; ++j) {
                targets[j].size -= 2;

                for (int i = 0; i < 17; i++) {
                    if (targets[j].size < (i + 1) * TAILLE_INITIALE / 17) {
                        circle(buffer, targets[j].x, targets[j].y, TAILLE_INITIALE, makecol(0, 0, 0));
                        draw_sprite(buffer, Tireur[i], targets[j].x - 60, targets[j].y - 70);
                        break;
                    }
                }
            }


            if (mouse_b & 1 && !isClicked) {
                int mx = mouse_x;
                int my = mouse_y;

                for (int j = 0; j < maxTargets; ++j) {
                    if (mx >= targets[j].x - TAILLE_INITIALE && mx <= targets[j].x + TAILLE_INITIALE &&
                        my >= targets[j].y - TAILLE_INITIALE && my <= targets[j].y + TAILLE_INITIALE) {
                        score[i]++;
                        targets[j].isBusy = 0;  // Marquez la position comme libre
                        targets[j].size = TAILLE_INITIALE;
                        int newIndex;
                        do {
                            newIndex = rand() % 6;
                        } while (is_target_occupied(newIndex, targets, maxTargets));
                        targets[j].pyramid_index = newIndex;
                        targets[j].x = pyramid_x[targets[j].pyramid_index];
                        targets[j].y = pyramid_y[targets[j].pyramid_index];
                        targets[j].isBusy = 1;  // Marquez la nouvelle position comme occupée

                        if (score[i] % 7 == 0 && maxTargets < 6) {
                            maxTargets++;
                            do {
                                newIndex = rand() % 6;
                            } while (is_target_occupied(newIndex, targets, maxTargets));
                            targets[maxTargets - 1].x = pyramid_x[newIndex];
                            targets[maxTargets - 1].y = pyramid_y[newIndex];
                            targets[maxTargets - 1].size = TAILLE_INITIALE;
                            targets[maxTargets - 1].pyramid_index = newIndex;
                            targets[maxTargets - 1].isBusy = 1;  // Marquez la nouvelle position comme occupée
                        }
                    }
                }
                isClicked = 1;
            } else if (!(mouse_b & 1) && isClicked) {
                isClicked = 0;
            }


            for (int j = 0; j < maxTargets; ++j) {
                if (targets[j].size < 1) {
                    gameOver = 1;
                    if (pyramid_index < 6) {
                        targets[j].x = pyramid_x[pyramid_index];
                        targets[j].y = pyramid_y[pyramid_index];
                        pyramid_index++;
                    }
                }
            }

            textprintf_centre_ex(buffer, font, WIDTH / 2, 10, makecol(255, 255, 255), -1, "Score: %d", score[i]);

            // Mettre à jour l'écran
            vsync();
            blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);

            // Attendre un peu pour éviter que les cercles n'apparaissent trop rapidement
            rest(50);

            if (score[i] >= 30) {

                gameOver = 1;
                while (!key[KEY_ENTER]) {
                    clear_bitmap(buffer);
                    draw_sprite(buffer, fond, 0, 0);
                    sprintf(messageFin, "Points maximum ! %d points récoltés.", score[i]);
                    textout_centre_ex(buffer, font, messageFin, WIDTH / 2, HEIGHT / 2, makecol(255, 255, 255), -1);
                    sprintf(messageFin, "%s, A toi de jouer. Appuie sur entrée pour commencer.", joueurs[1].nom,
                            score[1]);
                    textout_centre_ex(buffer, font, messageFin, WIDTH / 2, (HEIGHT / 2) + 50,
                                      makecol(255, 255, 255), -1);

                    blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);

                }

            }
        }
    }

    while (!key[KEY_ESC]) {
        clear_bitmap(buffer);
        draw_sprite(buffer, fond, 0, 0);
        sprintf(messageFin, "Points de %s : %d", joueurs[0].nom, score[0]);
        textout_centre_ex(buffer, font, messageFin, WIDTH / 2, HEIGHT / 2, makecol(255, 255, 255), -1);
        sprintf(messageFin, "Points de %s : %d", joueurs[1].nom, score[1]);
        textout_centre_ex(buffer, font, messageFin, WIDTH / 2, (HEIGHT / 2) + 100, makecol(255, 255, 255), -1);

        if (score[0] > score[1]) {
            sprintf(messageFin, "%s a gagné ! +1 ticket", joueurs[0].nom);
            textout_centre_ex(buffer, font, messageFin, WIDTH / 2, (HEIGHT / 2) + 200, makecol(255, 255, 255), -1);
            joueurs[0].nbTickets = memotickets[0] + 1;
        } else if (score[1] > score[0]) {
            sprintf(messageFin, "%s a gagné ! +1 ticket", joueurs[1].nom);
            textout_centre_ex(buffer, font, messageFin, WIDTH / 2, (HEIGHT / 2) + 200, makecol(255, 255, 255), -1);
            joueurs[1].nbTickets = memotickets[1] + 1;
        } else {
            sprintf(messageFin, "Égalité ! +1 ticket pour %s et %s ", joueurs[0].nom, joueurs[1].nom);
            textout_centre_ex(buffer, font, messageFin, WIDTH / 2, (HEIGHT / 2) + 200, makecol(255, 255, 255), -1);
            joueurs[0].nbTickets = memotickets[0] + 1;
            joueurs[1].nbTickets = memotickets[1] + 1;
        }

        // Mettre à jour l'écran
        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
        rest(10); // Pause de 10 ms pour rafraîchir l'écran
        vsync();
    }

}
