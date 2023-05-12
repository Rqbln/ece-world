#ifndef ECE_WORLD_JOUEUR_H
#define ECE_WORLD_JOUEUR_H

#define NB_JOUEURS 2

typedef struct joueurs{
    char nom[60];
    int nbTickets;
    int persoChoisi;
} t_joueurs;

extern t_joueurs joueurs[NB_JOUEURS];

#endif //ECE_WORLD_JOUEUR_H
