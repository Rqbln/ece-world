#include "Init_Allegro/allegro.h"
#include "Menu/menu.h"
#include "Parc/Parc.h"
#include "joueur/joueur.h"
#include "Sauvegarde/sauvegarde.h"
//#include "Games/Course_Chevaux/chevaux.h"
//#include "Games/Jackpot/jackpot.h"
//#include "Games/Ducky/ducky.h"

int main() {
    initialisation_allegro(); // Initialise Allegro

    BITMAP *buffer = create_bitmap(WIDTH, HEIGHT); // Crée un bitmap pour stocker l'image à afficher
    int playerX = WIDTH/2; //Position horizontale initiale du joueur
    int playerY = HEIGHT/2; // Position verticale initiale du joueur
    int playerSize = 100; // Taille initiale du joueur
    int gameOver = 0; // Indique si le jeu est terminé
    int squareColor = makecol(rand() % 256, rand() % 256, rand() % 256); // Couleur initiale du carré

    //Initialisation des joueurs
    for (int i = 0; i < 2; ++i) {
        joueurs[i].nbTickets=5;
        joueurs[i].persoChoisi=0;
        //Nom choisi dans le Parc.c
    }

    loadHighScore(highscore);
    //tableau_score();
    //ducky();
    //jeu_taupe();
    //shoot();
    //snake();
    //river();
    //pari();
    //anim_horse();
    //jackpot();
    //playguitar();
    //menuguitar();
    menu();
    /*while (!key[KEY_ESC] && !gameOver) { // Boucle principale du jeu
        clear_bitmap(buffer); // Efface le contenu du bitmap

        // Déplace le joueur à gauche ou à droite en fonction des touches de direction
        if (key[KEY_LEFT] && playerX > 0) {
            playerX -= 10;
        }
        if (key[KEY_RIGHT] && playerX + playerSize < 800) {
            playerX += 10;
        }
        if (key[KEY_UP] && playerX > 0) {
            playerY -= 10;
        }
        if (key[KEY_DOWN] && playerX + playerSize < 800) {
            playerY += 10;
        }


        // Dessine le carré et la météorite sur le bitmap
        rectfill(buffer, playerX, playerY, playerX + playerSize, playerY + playerSize, squareColor);

        // Affiche le bitmap à l'écran
        blit(buffer, screen, 0, 0, 0, 0, 800, 600);
        rest(10); // Attend un court instant avant de passer à la boucle suivante
    }*/

    allegro_exit(); // Quitte Allegro
    return 0; // Termine le programme avec un code de réussite
}
END_OF_MAIN(); // Macro qui doit être incluse à la fin de la fonction main() pour certains systèmes d'exploitation
