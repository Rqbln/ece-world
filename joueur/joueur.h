#ifndef ECE_WORLD_JOUEUR_H
#define ECE_WORLD_JOUEUR_H

#define NB_JOUEURS 2

typedef struct joueurs{
    char nom[60];
    int nbTickets;
    int persoChoisi;
    int score_guitare[10];
    int nb_essaie_guitare;
    int score_guitare1[10];
    int nb_essaie_guitare1;
    int score_river[10];
    int nb_essaie_river;
    int score_snake[10];
    int nb_essaie_snake;
    int score_taupe[10];
    int nb_essaie_taupe;
    int score_casino[10];
    int nb_essaie_casino;
    int score_ballon[10];
    int nb_essaie_ballon;
    int score_canard[10];
    int nb_essaie_canard;
    int score_chevaux[10];
    int nb_essaie_chevaux;
} t_joueurs;

typedef struct statistiques{
    char nom[60];
    int best_score_guitare[10];
    int best_score_snake[10];
    int best_score_canard[10];
    int best_score_ballon[10];
    int score_taupe[10];
} statistiques;

extern t_joueurs joueurs[NB_JOUEURS];

#endif //ECE_WORLD_JOUEUR_H
