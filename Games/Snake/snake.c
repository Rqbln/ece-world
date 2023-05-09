#include "snake.h"
#include "../../Init_Allegro/allegro.h"

void snake() {

    //Iniitialiser bitmaps


    BITMAP *snake1[4];
    BITMAP *snake2[4];
    char filename[80];

    //Snake 1
        for (int i = 0; i < 4; i++) {
            sprintf(filename, "../Games/Snake/images/snake1_%d.bmp",i);
            sprintf(filename, "../Games/Snake/images/snake2_%d.bmp",i);
            snake1[i] = load_bitmap(filename, NULL);
            snake2[i] = load_bitmap(filename, NULL);

            if (!snake1[i] && !snake2[i]) { //blindage
                allegro_message("Erreur icone");
                exit(EXIT_FAILURE);
            }
        }


    // Buffer et fond

    BITMAP *pomme= load_bitmap("../Games/Snake/images/pomme.bmp",NULL);
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *fond = load_bitmap("../Games/Snake/images/fond.bmp",NULL);

    if (!fond) { //blindage
        allegro_message("Erreur image fond");
        exit(EXIT_FAILURE);
    }




    // Initialiser les serpents
    int snake1_length = 3;
    int snake1_x[100] = { WIDTH/2, WIDTH/2, WIDTH/2 };
    int snake1_y[100] = { HEIGHT/2, HEIGHT/2 + TAILLE_JEU, HEIGHT/2 + 2*TAILLE_JEU };

    int snake2_length = 3;
    int snake2_x[100] = { WIDTH/3, WIDTH/3, WIDTH/3 };
    int snake2_y[100] = { HEIGHT/3, HEIGHT/3 + TAILLE_JEU, HEIGHT/3 + 2*TAILLE_JEU };

    // Variables pour la nourriture
    int food_x = rand() % WIDTH;
    int food_y = rand() % HEIGHT;

    // Variables pour le jeu
    int game_over = 0;
    int gagnant = 0;
    int direction1 = 0; // 0 = droite, 1 = bas, 2 = gauche, 3 = haut
    int direction2 = 0;
    int score1 = 0;
    int score2 = 0;
    char messageDebut[60];
    char messageFin[60];

    srand(time(NULL));

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
    while (!game_over && !key[KEY_ESC]) {

        // Dessiner le serpent 1
        clear_bitmap(screen);
        draw_sprite(screen,fond,0,0);
        for (int i = 0; i < snake1_length; i++) {
            rectfill(screen, snake1_x[i], snake1_y[i], snake1_x[i] + TAILLE_JEU, snake1_y[i] + TAILLE_JEU, makecol(255, 255, 255));
        }

        // Dessiner le serpent 2
        for (int i = 0; i < snake2_length; i++) {
            rectfill(screen, snake2_x[i], snake2_y[i], snake2_x[i] + TAILLE_JEU, snake2_y[i] + TAILLE_JEU, makecol(255, 0,  0));
        }




        // Dessiner la nourriture
        draw_sprite(screen,pomme,food_x,food_y);

        // Mettre à jour le serpent 1
        int old_x1 = snake1_x[0];
        int old_y1 = snake1_y[0];
        switch (direction1) {
            case 0: // droite
                snake1_x[0] += TAILLE_JEU;
                break;
            case 1: // bas
                snake1_y[0] += TAILLE_JEU;
                break;
            case 2: // gauche
                snake1_x[0] -= TAILLE_JEU;
                break;
            case 3: // haut
                snake1_y[0] -= TAILLE_JEU;
                break;
        }
        for (int i = 1; i < snake1_length; i++) {
            int temp_x1 = snake1_x[i];
            int temp_y1 = snake1_y[i];
            snake1_x[i] = old_x1;
            snake1_y[i] = old_y1;
            old_x1 = temp_x1;
            old_y1 = temp_y1;
        }


        // Mettre à jour le serpent 2
        int old_x2 = snake2_x[0];
        int old_y2 = snake2_y[0];
        switch (direction2) {
            case 0: // droite
                snake2_x[0] += TAILLE_JEU;
                break;
            case 1: // bas
                snake2_y[0] += TAILLE_JEU;
                break;
            case 2: // gauche
                snake2_x[0] -= TAILLE_JEU;
                break;
            case 3: // haut
                snake2_y[0] -= TAILLE_JEU;
                break;
        }
        for (int i = 1; i < snake2_length; i++) {
            int temp_x2 = snake2_x[i];
            int temp_y2 = snake2_y[i];
            snake2_x[i] = old_x2;
            snake2_y[i] = old_y2;
            old_x2 = temp_x2;
            old_y2 = temp_y2;
        }


        // Vérifier les collisions avec la nourriture
        if (snake1_x[0] < food_x + TAILLE_JEU && snake1_x[0] + TAILLE_JEU > food_x && snake1_y[0] < food_y + TAILLE_JEU && snake1_y[0] + TAILLE_JEU > food_y) {
            food_x = rand() % WIDTH;
            food_y = rand() % HEIGHT;
            snake1_length++;
            score1++;
        }

        if (snake2_x[0] < food_x + TAILLE_JEU && snake2_x[0] + TAILLE_JEU > food_x && snake2_y[0] < food_y + TAILLE_JEU && snake2_y[0] + TAILLE_JEU > food_y) {
            food_x = rand() % WIDTH;
            food_y = rand() % HEIGHT;
            snake2_length++;
            score2++;
        }

        // Vérifier les collisions avec les bords de l'écran du serpent 1
        if (snake1_x[0] < 0 || snake1_x[0] + TAILLE_JEU > WIDTH || snake1_y[0] < 0 || snake1_y[0] + TAILLE_JEU > HEIGHT) {
            gagnant = 2;
            game_over = 1;
        }

        // Vérifier les collisions avec les bords de l'écran du serpent 2
        if (snake2_x[0] < 0 || snake2_x[0] + TAILLE_JEU > WIDTH || snake2_y[0] < 0 || snake2_y[0] + TAILLE_JEU > HEIGHT) {
            gagnant = 1;
            game_over = 1;
        }




        // Vérifier les collisions du serpent 1 avec lui-même
        for (int i = 1; i < snake1_length; i++) {
            if (snake1_x[0] == snake1_x[i] && snake1_y[0] == snake1_y[i]) {
                gagnant = 2;
                game_over = 1;
            }
        }


        // Vérifier les collisions du serpent 2 avec lui-même
        for (int i = 1; i < snake2_length; i++) {
            if (snake2_x[i] == snake2_x[0] && snake2_y[i] == snake2_y[0]) {
                gagnant = 1;
                game_over = 1;
            }
        }


        // Vérifier les collisions du serpent 1 avec le corps du serpent 2
        for (int i = 0; i < snake2_length; i++) {
            if (snake1_x[0] < snake2_x[i] + TAILLE_JEU && snake1_x[0] + TAILLE_JEU > snake2_x[i] && snake1_y[0] < snake2_y[i] + TAILLE_JEU && snake1_y[0] + TAILLE_JEU > snake2_y[i]) {
                gagnant = 2;

                game_over = 1;
            }
        }

        // Vérifier les collisions du serpent 2 avec le corps du serpent 1
        for (int i = 0; i < snake1_length; i++) {
            if (snake2_x[0] < snake1_x[i] + TAILLE_JEU && snake2_x[0] + TAILLE_JEU > snake1_x[i] && snake2_y[0] < snake1_y[i] + TAILLE_JEU && snake2_y[0] + TAILLE_JEU > snake1_y[i]) {
                gagnant = 1;
                game_over = 1;
            }
        }

        // Vérifier si les têtes des deux serpents se sont heurtées
        if (snake2_x[0] < snake1_x[0] + TAILLE_JEU && snake2_x[0] + TAILLE_JEU > snake1_x[0] && snake2_y[0] < snake1_y[0] + TAILLE_JEU && snake2_y[0] + TAILLE_JEU > snake1_y[0]) {
            // Générer un nombre aléatoire entre 1 et 2
            gagnant = rand() % 2 + 1;
            game_over = 1;
        }

        if (score1 == 5 || score2 == 5){
            game_over = 1;
        }



        // Afficher le score1
        textprintf_ex(screen, font, 10, 10, makecol(255, 255, 255), -1, "score1: %d", score1);

        // Afficher le score2
        textprintf_ex(screen, font, 10, 30, makecol(255, 255, 255), -1, "score2: %d", score2);


        // Mettre à jour l'écran
        vsync();
        blit(screen, screen, 0, 0, 0, 0, WIDTH, HEIGHT);

        // Attendre un peu pour éviter que les serpents ne se déplace trop rapidement
        rest(50);

        // Lire les entrées du clavier pour le serpent 1
        if (key[KEY_D] && direction1 != 2) {
            direction1 = 0;
        } else if (key[KEY_S] && direction1 != 3) {
            direction1 = 1;
        } else if (key[KEY_Q] && direction1 != 0) {
            direction1 = 2;
        } else if (key[KEY_Z] && direction1 != 1) {
            direction1 = 3;
        }


        // Lire les entrées du clavier pour le serpent 2
        if (key[KEY_L] && direction2 != 2) {
            direction2 = 0;
        } else if (key[KEY_K] && direction2 != 3) {
            direction2 = 1;
        } else if (key[KEY_J] && direction2 != 0) {
            direction2 = 2;
        } else if (key[KEY_I] && direction2 != 1) {
            direction2 = 3;
        }
    }


    while (!key[KEY_ESC]){
        if (gagnant == 1){
            sprintf(messageFin, "Le joueur 1 a gagné par collision, fin de la partie !");
            textout_centre_ex(screen,font, messageFin, WIDTH/2, HEIGHT / 2, makecol(255, 255, 255), -1);
        }

        else if (gagnant == 2) {
            sprintf(messageFin, "Le joueur 2 a gagné par collision, fin de la partie !");
            textout_centre_ex(screen,font, messageFin, WIDTH/2, HEIGHT / 2, makecol(255, 255, 255), -1);
        }
        else {
            if (score1 == 5) {
                sprintf(messageFin, "Le joueur 1 a atteint 5 points, fin de la partie !");
                textout_centre_ex(screen,font, messageFin, WIDTH/2, HEIGHT / 2, makecol(255, 255, 255), -1);
            }
            else if (score2 == 5){
                sprintf(messageFin, "Le joueur 2 a atteint 5 points, fin de la partie !");
                textout_centre_ex(screen,font, messageFin, WIDTH/2, HEIGHT / 2, makecol(255, 255, 255), -1);
            }
        }

        rest(10); // Pause de 10 ms pour rafraîchir l'écran
    }
}