#include "sauvegarde.h"

char* serializePlayers(const t_joueurs* players) { // sérialiser la structure de joueurs en une représentation de chaîne de caractères
    char* serializedData = (char*)malloc(MAX_SERIALIZE_LENGTH * sizeof(char));
    if (serializedData == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour la sérialisation.\n");
        return NULL;
    }

    // Utilisez sprintf pour formater les données de la structure de joueurs dans la chaîne de caractères de sérialisation
    snprintf(serializedData, MAX_SERIALIZE_LENGTH, "%s,%d,%d;%s,%d,%d;", players[0].nom, players[0].nbTickets, players[0].persoChoisi,
             players[1].nom, players[1].nbTickets, players[1].persoChoisi);

    return serializedData;
}

void deserializePlayers(const char* serializedData, t_joueurs* players) { //désérialiser une chaîne de caractères et restaurer la structure de joueurs à partir de celle-ci
    char* dataCopy = strdup(serializedData); // Dupliquez la chaîne de caractères pour la sécurité

    // Utilisez strtok pour extraire les données de la chaîne de caractères de sérialisation et les attribuer à la structure de joueurs
    char* token = strtok(dataCopy, ";");
    int i = 0;
    while (token != NULL) {
        sscanf(token, "%[^,],%d,%d", players[i].nom, &(players[i].nbTickets), &(players[i].persoChoisi));
        token = strtok(NULL, ";");
        i++;
    }

    free(dataCopy); // Libérez la mémoire allouée pour la copie de la chaîne de caractères
}

void saveGame(const t_joueurs* players, const char* saveFileName) {
    // Modifiez le chemin du fichier de sauvegarde pour inclure le dossier "saves" à la racine du projet
    char saveFilePath[100]; // Modifier la taille selon vos besoins
    snprintf(saveFilePath, sizeof(saveFilePath), "../saves/%s.sav", saveFileName);

    FILE* file = fopen(saveFilePath, "wb");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return;
    }

    char* serializedData = serializePlayers(players);
    if (serializedData != NULL) {
        size_t dataSize = strlen(serializedData);
        fwrite(serializedData, sizeof(char), dataSize, file);
        free(serializedData); // Libérez la mémoire allouée

        printf("Le jeu a été sauvegardé avec succès dans '%s'.\n", saveFilePath);
    } else {
        fprintf(stderr, "Erreur lors de la sérialisation des données.\n");
    }

    fclose(file); // Fermez le fichier
}



void loadGame(t_joueurs* players, const char* loadFileName) {
    // Modifiez le chemin du fichier de sauvegarde pour inclure le dossier "saves" à la racine du projet
    char saveFilePath[100]; // Modifier la taille selon vos besoins
    snprintf(saveFilePath, sizeof(saveFilePath), "../saves/%s.sav", loadFileName);

    FILE* file = fopen(saveFilePath, "rb");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return;
    }

    // Obtenez la taille du fichier en octets
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allouez suffisamment de mémoire pour contenir la chaîne de caractères de sérialisation
    char* serializedData = (char*)malloc(fileSize + 1);
    if (serializedData == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour la désérialisation.\n");
        fclose(file);
        return;
    }

    // Lisez la chaîne de caractères de sérialisation à partir du fichier
    fread(serializedData, sizeof(char), fileSize, file);
    serializedData[fileSize] = '\0'; // Ajoutez le caractère de fin de chaîne

    deserializePlayers(serializedData, players);

    free(serializedData); // Libérez la mémoire allouée
    fclose(file); // Fermez le fichier
}
