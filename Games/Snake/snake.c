#include "snake.h"
#include "../../Init_Allegro/allegro.h"
#include "../../joueur/joueur.h"
#include "../../Sauvegarde/sauvegarde.h"

void snake() {
    //Iniitialiser bitmaps
    BITMAP *snake1[4];
    BITMAP *snake2[4];
    BITMAP *pomme= load_bitmap("../Games/Snake/images/pomme.bmp",NULL);
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *fond = load_bitmap("../Games/Snake/images/fond.bmp",NULL);
    BITMAP* regles = load_bitmap("../Games/Snake/images/regles.bmp", NULL);

    SAMPLE *ambiance = load_sample("../Games/Snake/sons/ambiance.wav");
    SAMPLE *mange_pomme = load_sample("../Games/Snake/sons/mange_pomme.wav");
    SAMPLE *victoire = load_sample("../Games/Snake/sons/victoire.wav");

    char filename[80];
    int memotickets[NB_JOUEURS];
    int OldHighScore=highscore[1].score;


    for (int i = 0; i < NB_JOUEURS; ++i) {
        joueurs[i].nbTickets-=1;
        memotickets[i]=joueurs[i].nbTickets;
    }

    //Snake 1
    for (int i = 0; i < 4; i++) {
        sprintf(filename, "../Games/Snake/images/snake1_%d.bmp",i);
        snake1[i] = load_bitmap(filename, NULL);
        sprintf(filename, "../Games/Snake/images/snake2_%d.bmp",i);
        snake2[i] = load_bitmap(filename, NULL);
        if (!snake1[i] && !snake2[i]) { //blindage
            allegro_message("Erreur icone");
            exit(EXIT_FAILURE);
        }
    }
    if (!fond && !pomme) { //blindage
        allegro_message("Erreur images fond, pomme");
        exit(EXIT_FAILURE);
    }

    if (!ambiance && !mange_pomme && !victoire) {
        allegro_message("Erreur : impossible de charger la musique");
        allegro_exit();
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

    play_sample(ambiance, 255, 128, 1000, 1);

    while (!key[KEY_ENTER]){
        draw_sprite(buffer,fond,0,0);
        //Affichage règles
        draw_sprite(buffer,regles,WIDTH/2-230,HEIGHT/2-200);

        sprintf(messageDebut, "Appuyez sur entrée pour commencer la partie !");
        textout_centre_ex(buffer, font, messageDebut, WIDTH / 2, HEIGHT / 2+120, makecol(255, 255, 255), -1);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    }
        for (int i = 0; i < 300; ++i) {
            draw_sprite(buffer,fond,0,0);
            draw_sprite(buffer, regles, WIDTH / 2 - 230, HEIGHT / 2 - 200-2*i);
            sprintf(messageDebut, "Appuyez sur entrée pour commencer la partie !");
            textout_centre_ex(buffer, font, messageDebut, WIDTH / 2, HEIGHT / 2+120, makecol(255, 255, 255), -1);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
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
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        draw_sprite(buffer,fond,0,0);
        for (int i = 0; i < snake1_length; i++) {
            rectfill(buffer, snake1_x[i], snake1_y[i], snake1_x[i] + TAILLE_JEU, snake1_y[i] + TAILLE_JEU, makecol(136, 170, 0));
        }
        // Dessiner le serpent 2
        for (int i = 0; i < snake2_length; i++) {
            rectfill(buffer, snake2_x[i], snake2_y[i], snake2_x[i] + TAILLE_JEU, snake2_y[i] + TAILLE_JEU, makecol(255, 0,  0));
        }
        // Dessiner la nourriture
        draw_sprite(buffer,pomme,food_x,food_y);

        // Mettre à jour le serpent 1
        int old_x1 = snake1_x[0];
        int old_y1 = snake1_y[0];
        switch (direction1) {
            case 0: // droite
                snake1_x[0] += TAILLE_JEU;
                draw_sprite(buffer,snake1[0],snake1_x[0],snake1_y[0]);
                break;
            case 1: // bas
                snake1_y[0] += TAILLE_JEU;
                draw_sprite(buffer,snake1[1],snake1_x[0],snake1_y[0]);
                break;
            case 2: // gauche
                snake1_x[0] -= TAILLE_JEU;
                draw_sprite(buffer,snake1[2],snake1_x[0],snake1_y[0]);
                break;
            case 3: // haut
                snake1_y[0] -= TAILLE_JEU;
                draw_sprite(buffer,snake1[3],snake1_x[0],snake1_y[0]);
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
                draw_sprite(buffer,snake2[0],snake2_x[0],snake2_y[0]);
                break;
            case 1: // bas
                snake2_y[0] += TAILLE_JEU;
                draw_sprite(buffer,snake2[1],snake2_x[0],snake2_y[0]);
                break;
            case 2: // gauche
                snake2_x[0] -= TAILLE_JEU;
                draw_sprite(buffer,snake2[2],snake2_x[0],snake2_y[0]);
                break;
            case 3: // haut
                snake2_y[0] -= TAILLE_JEU;
                draw_sprite(buffer,snake2[3],snake2_x[0],snake2_y[0]);
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
            play_sample(mange_pomme, 255, 128, 1000, 0);
            food_x = rand() % WIDTH;
            food_y = rand() % HEIGHT;
            snake1_length++;
            score1++;
        }

        if (snake2_x[0] < food_x + TAILLE_JEU && snake2_x[0] + TAILLE_JEU > food_x && snake2_y[0] < food_y + TAILLE_JEU && snake2_y[0] + TAILLE_JEU > food_y) {
            play_sample(mange_pomme, 255, 128, 1000, 0);
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
        textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "%s : %d", joueurs[0].nom,score1);

        // Afficher le score2
        textprintf_ex(buffer, font, 10, 30, makecol(255, 255, 255), -1, "%s : %d", joueurs[1].nom,score2);


        // Mettre à jour l'écran
        vsync();
        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);

        // Attendre un peu pour éviter que les serpents ne se déplace trop rapidement
        rest(50);

        // Lire les entrées du clavier pour le serpent 1
        if (key[KEY_G] && direction1 != 2) {
            direction1 = 0;
        } else if (key[KEY_F] && direction1 != 3) {
            direction1 = 1;
        } else if (key[KEY_D] && direction1 != 0) {
            direction1 = 2;
        } else if (key[KEY_R] && direction1 != 1) {
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
    stop_sample(ambiance);
    play_sample(victoire, 255, 128, 1000, 0);
    while (!key[KEY_ENTER]){
        if (gagnant == 1){
            sprintf(messageFin, "%s a gagné par collision ! +1 ticket",joueurs[0].nom);
            textout_centre_ex(buffer,font, messageFin, WIDTH/2, HEIGHT / 2, makecol(255, 255, 255), -1);
            joueurs[0].nbTickets=memotickets[0]+2;
            if (highscore[0].score <= score1) {
                saveMiniGame(joueurs,"Snake",score1,0);
                sprintf(messageFin, "%s vient d'établir un nouveau record en battant %d ! Enregistrement du meilleur score terminé.",joueurs[0].nom,OldHighScore);
                textout_centre_ex(buffer,font, messageFin, WIDTH/2, HEIGHT / 2 + 20, makecol(255, 255, 255), -1);
            }
        }

        else if (gagnant == 2) {
            sprintf(messageFin, "%s a gagné par collision ! +1 ticket",joueurs[1].nom);
            textout_centre_ex(buffer,font, messageFin, WIDTH/2, HEIGHT / 2, makecol(255, 255, 255), -1);
            joueurs[1].nbTickets=memotickets[1]+2;
            if (highscore[0].score <= score2) {
                saveMiniGame(joueurs,"Snake",score2,1);
                sprintf(messageFin, "%s vient d'établir un nouveau record en battant %d ! Enregistrement du meilleur score terminé.",joueurs[1].nom,OldHighScore);
                textout_centre_ex(buffer,font, messageFin, WIDTH/2, HEIGHT / 2 + 20, makecol(255, 255, 255), -1);

            }
        }

        else {
            if (score1 == 5) {
                sprintf(messageFin, "%s a gagné en atteignant 5 points ! +1 ticket",joueurs[0].nom);
                textout_centre_ex(buffer,font, messageFin, WIDTH/2, HEIGHT / 2, makecol(255, 255, 255), -1);
                joueurs[0].nbTickets=memotickets[0]+2;

                if (highscore[0].score <= score1) {
                    saveMiniGame(joueurs,"Snake",score1,0);
                    sprintf(messageFin, "%s vient d'établir un nouveau record en battant %d ! Enregistrement du meilleur score terminé.",joueurs[0].nom, OldHighScore);
                    textout_centre_ex(buffer,font, messageFin, WIDTH/2, HEIGHT / 2 + 20, makecol(255, 255, 255), -1);
                }
            }
            else if (score2 == 5){
                sprintf(messageFin, "%s a gagné en atteignant 5 points ! +1 ticket",joueurs[1].nom);
                textout_centre_ex(buffer,font, messageFin, WIDTH/2, HEIGHT / 2, makecol(255, 255, 255), -1);
                joueurs[1].nbTickets=memotickets[1]+2;

                if (highscore[0].score <= score2) {

                    sprintf(messageFin, "%s vient d'établir un nouveau record en battant %d ! Enregistrement du meilleur score terminé.",joueurs[1].nom, OldHighScore);
                    textout_centre_ex(buffer,font, messageFin, WIDTH/2, HEIGHT / 2 + 20, makecol(255, 255, 255), -1);
                    saveMiniGame(joueurs,"Snake",score2,1);
                }
            }
            joueurs[0].score_snake[joueurs[0].nb_essaie_snake]=score1;
            joueurs[1].score_snake[joueurs[1].nb_essaie_snake]=score2;
            joueurs[0].nb_essaie_snake+=1;
            joueurs[1].nb_essaie_snake+=1;

            loadHighScore(highscore);
        }


        blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
        rest(10); // Pause de 10 ms pour rafraîchir l'écran
    }
}
