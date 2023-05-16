#include "sauvegarde.h"

t_highscore highscore [MAX_HIGH_SCORES];

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

char* serializeMiniGames(const t_joueurs* players, int score, int gagnant) { // sérialiser la structure de joueurs en une représentation de chaîne de caractères
    char* serializedData = (char*)malloc(MAX_SERIALIZE_LENGTH * sizeof(char));
    if (serializedData == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour la sérialisation.\n");
        return NULL;
    }

    // Utilisez sprintf pour formater les données de la structure de joueurs dans la chaîne de caractères de sérialisation
    snprintf(serializedData, MAX_SERIALIZE_LENGTH, "%s,%d", players[gagnant].nom, score);

    return serializedData;
}

void saveMiniGame (const t_joueurs* players, const char* saveFileName, int score, int gagnant) {
    // Modifiez le chemin du fichier de sauvegarde pour inclure le dossier "saves" à la racine du projet
    char saveFilePath[100]; // Modifier la taille selon vos besoins
    snprintf(saveFilePath, sizeof(saveFilePath), "../saves/games/%s.sav", saveFileName);

    FILE* file = fopen(saveFilePath, "wb");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return;
    }

    char* serializedData = serializeMiniGames(players,score,gagnant);
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

void loadHighScore(t_highscore* highscores) {
    // Chemin du dossier contenant les fichiers de sauvegarde
    const char* savesFolderPath = "../saves/games/";

    // Tableau pour stocker les chemins de fichiers de sauvegarde
    char saveFilePaths[MAX_HIGH_SCORES][100]; // Modifier la taille selon vos besoins

    // Tableau pour stocker les scores chargés
    int scores[MAX_HIGH_SCORES];

    // Ouvrir le dossier des sauvegardes
    DIR* savesDir = opendir(savesFolderPath);
    if (savesDir == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du dossier des sauvegardes.\n");
        return;
    }

    // Lire les fichiers de sauvegarde dans le dossier
    struct dirent* saveFile;
    int fileCount = 0;
    while ((saveFile = readdir(savesDir)) != NULL && fileCount < MAX_HIGH_SCORES) {
        if (saveFile->d_type == DT_REG && strcmp(saveFile->d_name, ".") != 0 && strcmp(saveFile->d_name, "..") != 0) {
            snprintf(saveFilePaths[fileCount], sizeof(saveFilePaths[fileCount]), "%s%s", savesFolderPath, saveFile->d_name);
            fileCount++;
        }
    }
    closedir(savesDir);

    // Charger les scores à partir des fichiers de sauvegarde
    for (int i = 0; i < fileCount; i++) {
        FILE* file = fopen(saveFilePaths[i], "rb");
        if (file == NULL) {
            fprintf(stderr, "Erreur lors de l'ouverture du fichier de sauvegarde '%s'.\n", saveFilePaths[i]);
            continue;
        }

        // Allouer suffisamment de mémoire pour contenir la chaîne de caractères de sérialisation
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        char* serializedData = (char*)malloc(fileSize + 1);
        if (serializedData == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour la désérialisation.\n");
            fclose(file);
            continue;
        }

        // Lire la chaîne de caractères de sérialisation à partir du fichier
        fread(serializedData, sizeof(char), fileSize, file);
        serializedData[fileSize] = '\0'; // Ajouter le caractère de fin de chaîne

        // Extraire le nom du joueur et le score à partir de la chaîne de caractères sérialisée
        sscanf(serializedData, "%[^,],%d", highscores[i].nom, &highscores[i].score);

        free(serializedData); // Libérer la mémoire allouée
        fclose(file); // Fermer le fichier
    }


// Afficher les meilleurs scores
    printf("Scores des mini-jeux :\n");
    for (int i = 0; i < fileCount; i++) {
        printf("%d. %s - %d\n", i + 1, highscores[i].nom, scores[i]);
    }
}
