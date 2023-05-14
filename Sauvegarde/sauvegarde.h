#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../joueur/joueur.h" // Inclure le fichier d'en-tête contenant la structure de joueurs


#ifndef ECE_WORLD_SAUVEGARDE_H
#define ECE_WORLD_SAUVEGARDE_H

#endif //ECE_WORLD_SAUVEGARDE_H

#define MAX_SERIALIZE_LENGTH 1000 // Taille maximale de la chaîne de caractères de sérialisation

char* serializePlayers(const t_joueurs* players);
void deserializePlayers(const char* serializedData, t_joueurs* players);
void saveGame(const t_joueurs* players, const char* saveFileName);
void loadGame(t_joueurs* players, const char* saveFileName) ;
