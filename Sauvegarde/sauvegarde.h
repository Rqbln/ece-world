#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../joueur/joueur.h" // Inclure le fichier d'en-tête contenant la structure de joueurs


#ifndef ECE_WORLD_SAUVEGARDE_H
#define ECE_WORLD_SAUVEGARDE_H



#define MAX_SERIALIZE_LENGTH 1000 // Taille maximale de la chaîne de caractères de sérialisation
#define MAX_HIGH_SCORES 10 // Proportionnel au nombre de mini jeux
#define MAX_NOM_LENGTH 50

typedef struct highscore {
    char nomjeu[20];
    char nom[MAX_NOM_LENGTH];
    int score;
} t_highscore;



char* serializePlayers(const t_joueurs* players);
void deserializePlayers(const char* serializedData, t_joueurs* players);
void saveGame(const t_joueurs* players, const char* saveFileName);
void loadGame(t_joueurs* players, const char* loadFileName) ;
char* serializeMiniGames(const t_joueurs* players, int score, int gagnant);
void saveMiniGame (const t_joueurs* players, const char* saveFileName, int score, int gagnant);
void loadHighScore(t_highscore* highscores);
void nom_jeu();

extern t_highscore highscore [MAX_HIGH_SCORES];

#endif //ECE_WORLD_SAUVEGARDE_H