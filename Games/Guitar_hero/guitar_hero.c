//by Baptiste Chesnot
#include "guitar_hero.h"
#include "../../joueur/joueur.h"
void menuguitar(){
    //innitialisation des BITMAP
    BITMAP *buffer = create_bitmap(WIDTH, HEIGHT);
    BITMAP *fond = load_bitmap("../Games/Guitar_hero/image/fondguitar3.bmp",NULL);
    BITMAP *selectstart[2];
    BITMAP *selectstart1[2];
    BITMAP *selectrules[2];
    BITMAP *selectexit[2];
    BITMAP *regle = load_bitmap("../Games/Guitar_hero/image/parcheminGH.bmp",NULL);
    BITMAP *enterkey= load_bitmap("../Games/Course_Chevaux/image/enterkey.bmp",NULL);
    SAMPLE *sound = load_wav("../Musics/Wav/Menu.wav");
    if (!sound) {
        allegro_message("Erreur lors du chargement du fichier WAV\n");
        exit(EXIT_FAILURE);
    }
    play_sample(sound, 255, 128, 1000, 1);

    //declaration variable
    char nomDeFichier[50];
    int ecart=200;
    int xselect=WIDTH/2-200;
    int yselectstart=HEIGHT/2-2*ecart;
    int yselectstart1=HEIGHT/2-ecart;
    int yselectrules=HEIGHT/2;
    int yselectexit=HEIGHT/2+ecart;
    int option=0;
    int xenter=WIDTH-400;
    int yenter=HEIGHT-80;

    //creation des touche de selection
    for(int i=0;i<2;i++){
        sprintf(nomDeFichier,"../Games/Guitar_hero/image/selectmode1%d.bmp",i);
        selectstart[i]= load_bitmap(nomDeFichier,NULL);
        if(!selectstart[i]){
            allegro_message("../../Menu/image/selectstart1%d (Personnalisé).bmp",i);
            exit(EXIT_FAILURE);
        }
        sprintf(nomDeFichier,"../Games/Guitar_hero/image/selectmode2%d.bmp",i);
        selectstart1[i]= load_bitmap(nomDeFichier,NULL);
        if(!selectstart1[i]){
            allegro_message("../../Menu/image/selectstart2%d (Personnalisé).bmp",i);
            exit(EXIT_FAILURE);
        }

        sprintf(nomDeFichier,"../Games/Guitar_hero/image/selectregle%d.bmp",i);
        selectrules[i]= load_bitmap(nomDeFichier,NULL);
        if(!selectrules[i]){
            allegro_message("../../image/selectrules%d.bmp",i);
            exit(EXIT_FAILURE);
        }
        sprintf(nomDeFichier,"../Games/Guitar_hero/image/selectexit%d.bmp",i);
        selectexit[i]= load_bitmap(nomDeFichier,NULL);
        if(!selectexit[i]){
            allegro_message("../Menu/image/selectexit%d (Personnalisé).bmp",i);
            exit(EXIT_FAILURE);
        }
    }

    // Boucle principale
    while (!key[KEY_ESC]) {
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
        stretch_blit(fond, buffer, 0, 0, fond->w, fond->h, 0, 0, WIDTH, HEIGHT);
        switch (option) {
            case 0:
                draw_sprite(buffer,selectstart[1],xselect,yselectstart);
                draw_sprite(buffer,selectstart1[0],xselect,yselectstart1);
                draw_sprite(buffer,selectrules[0],xselect,yselectrules);
                draw_sprite(buffer,selectexit[0],xselect,yselectexit);
                draw_sprite(buffer,enterkey,xenter,yenter);
                break;
            case 1:
                draw_sprite(buffer,selectstart[0],xselect,yselectstart);
                draw_sprite(buffer,selectstart1[1],xselect,yselectstart1);
                draw_sprite(buffer,selectrules[0],xselect,yselectrules);
                draw_sprite(buffer,selectexit[0],xselect,yselectexit);
                draw_sprite(buffer,enterkey,xenter,yenter);
                break;
            case 2:
                draw_sprite(buffer,selectstart[0],xselect,yselectstart);
                draw_sprite(buffer,selectstart1[0],xselect,yselectstart1);
                draw_sprite(buffer,selectrules[1],xselect,yselectrules);
                draw_sprite(buffer,selectexit[0],xselect,yselectexit);
                draw_sprite(buffer,enterkey,xenter,yenter);
                break;
            case 3:
                draw_sprite(buffer,selectstart[0],xselect,yselectstart);
                draw_sprite(buffer,selectstart1[0],xselect,yselectstart1);
                draw_sprite(buffer,selectrules[0],xselect,yselectrules);
                draw_sprite(buffer,selectexit[1],xselect,yselectexit);
                draw_sprite(buffer,enterkey,xenter,yenter);
                break;
        }

        // Affichage du buffer à l'écran
        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);

        // Gestion de l'entrée utilisateur
        if (key[KEY_UP]) { // Flèche du haut
            option--;
            if (option<0){
                option=3;
            }
            rest(250); // Pause pour éviter les mouvements trop rapides
        }
        if (key[KEY_DOWN]) { // Flèche du bas
            option++;
            if (option>3){
                option=0;
            }
            rest(250); // Pause pour éviter les mouvements trop rapides
        }
        if (key[KEY_ENTER]) { // Touche Entrée

            if (option == 0) { // Option Jouer
                stop_sample(sound);
                playguitar1();
            } else if (option == 1) { // Option Lire les règles
                stop_sample(sound);
                playguitar();
            } else if (option == 2) { // Option Quitter
                //stop_sample(sound);
                rest(250); // Pause pour éviter les mouvements trop rapides
                while(!key[KEY_ENTER]){
                    draw_sprite(buffer,regle,((WIDTH/2)-(regle->w)/2),-50);
                    blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
                }
                rest(250); // Pause pour éviter les mouvements trop rapides

            } else{
                stop_sample(sound);
                rest(250); // Pause pour éviter les mouvements trop rapides
                //allegro_exit(); // Quitte Allegro
                break; // Sortie de la boucle principale
            }
        }
        rest(10); // Pause pour libérer un peu le processeur
    }
    destroy_sample(sound);
}
void playguitar1(){
    rest(200); // Pause de 10 ms pour rafraîchir l'écran
    BITMAP *buffer;
    BITMAP *note= load_bitmap("../Games/Guitar_hero/image/bille0.bmp",NULL);;
    BITMAP *arriver= load_bitmap("../Games/Guitar_hero/image/gratte.bmp",NULL);
    BITMAP *fond= load_bitmap("../Games/Guitar_hero/image/fondguitar3.bmp",NULL);
    SAMPLE *musique= load_sample("../Games/Guitar_hero/musique/musique0.wav");
    BITMAP *enterkey= load_bitmap("../Games/Course_Chevaux/image/enterkey.bmp",NULL);
    set_trans_blender(0, 0, 0, 128);
    if (!musique) {
        allegro_message("Erreur : impossible de charger la musique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    int nbnote = 4*bat;
    int xnote[nbnote];
    int ynote[nbnote];
    int nombreAleatoire=20;
    int memo;
    char message[50];
    int score;
    int vitesse;
    int nbjoueur=2;
    int joueurscore[nbjoueur];
    int ticket=0;
    int xenter=WIDTH-400;
    int yenter=HEIGHT-80;
// Joue la musique en boucle
//play_sample(musique, 255, 128, 100, 1);
    // Initialisation de la fonction rand() avec la fonction srand()
    srand(time(NULL));
    if(!arriver){
        allegro_message("../image/arriver.bmp");
        exit(EXIT_FAILURE);
    }
    if(!note){
        allegro_message("../image/note.bmp");
        exit(EXIT_FAILURE);
    }
    if(!fond){
        allegro_message("../image/fondguitar0.bmp ");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    buffer=create_bitmap(WIDTH,HEIGHT);

    for (int tour = 0; tour < nbjoueur; ++tour) {
        joueurs[tour].nbTickets-=1;
        play_sample(musique, 255, 128, 1000, 1);
        memo=0;
        for (int j = 0; j < bat; ++j) {
            for(int i=0;i<nbnote/bat;i++){
                xnote[i+j*(nbnote/bat)]=i*155+WIDTH*0.34;
                ynote[i+j*(nbnote/bat)]=j*(-200*(i+1));
            }
        }
        vitesse=70;
        score=0;
        rest(150); // Pause de 10 ms pour rafraîchir l'écran
        while (!key[KEY_ESC] && memo ==0) {
            clear_bitmap(buffer);
            clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
            // Obtenir les coordonnées de la souris
            stretch_blit(fond,buffer,0,0,fond->w,fond->h,0,0,WIDTH,HEIGHT);
            int x=mouse_x;
            int y=mouse_y;
            draw_sprite(buffer,arriver,(x - ((arriver->w)/2)),(y - ((arriver->h)/2)));
            for (int i=0; i<nbnote; i++){
                // Génération d'un nombre aléatoire compris entre 8 et 20
                //nombreAleatoire = 8+rand() % 20;
                ynote[i]+=nombreAleatoire;
                if (xnote[i] <= (x) && (x) <= (xnote[i] + note->w) && ynote[i] <= (y) && (y) <= (ynote[i] + note->h)){
                    ynote[i]=-200;
                    score+=1;
                    vitesse-=1;
                    // Collision détectée !
                }
                //textprintf_ex(buffer, font, 50, 50, makecol(255, 255, 255), -1, "score: %d", score);

                draw_sprite(buffer,note,xnote[i],ynote[i]);
                if (ynote[i] >= HEIGHT ){
                    memo=1;
                    // Collision détectée !
                }
            }
            textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "score: %d", score);
            blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
            rest(vitesse); // Pause de 10 ms pour rafraîchir l'écran
        }
        while (!key[KEY_ENTER]) {
            draw_sprite(buffer,enterkey,xenter,yenter);
            stop_sample(musique);
            sprintf(message,"Perdu enculé");
            joueurs[tour].score_guitare[joueurs[tour].nb_essaie_guitare]=score;
            textout_centre_ex(buffer, font, message, WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
            blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
            rest(100); // Pause de 10 ms pour rafraîchir l'écran
        }
        joueurs[tour].nb_essaie_guitare+=1;
    }
    rest(150); // Pause de 10 ms pour rafraîchir l'écran
    clear_bitmap(buffer);
    clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
    while (!key[KEY_ESC]) {
        if (joueurs[0].score_guitare[joueurs[0].nb_essaie_guitare-1]<joueurs[1].score_guitare[joueurs[1].nb_essaie_guitare-1]){
            sprintf(message,"%s a gagné 1 ticket",joueurs[1].nom);
            if(ticket==0){
                joueurs[1].nbTickets+=2;
                ticket=1;
            }
        }
        else if(joueurs[0].score_guitare[joueurs[0].nb_essaie_guitare-1]>joueurs[1].score_guitare[joueurs[1].nb_essaie_guitare-1]){
            sprintf(message,"%s a gagné 1 ticket",joueurs[0].nom);
            if(ticket==0){
                joueurs[0].nbTickets+=2;
                ticket=1;
            }
        }
        else {
            sprintf(message,"egalite");
            if(ticket==0){
                joueurs[0].nbTickets+=1;
                joueurs[1].nbTickets+=1;
                ticket=1;
            }
        }
        textout_centre_ex(buffer, font, message, WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
        rest(100); // Pause de 10 ms pour rafraîchir l'écran
    }
    rest(150); // Pause de 10 ms pour rafraîchir l'écran
}
void playguitar(){
    rest(200); // Pause de 10 ms pour rafraîchir l'écran
    BITMAP *buffer;
    BITMAP *note= load_bitmap("../Games/Guitar_hero/image/bille0.bmp",NULL);;
    BITMAP *arriver= load_bitmap("../Games/Guitar_hero/image/gratte.bmp",NULL);
    BITMAP *fond= load_bitmap("../Games/Guitar_hero/image/fondguitar3.bmp",NULL);
    BITMAP *enterkey= load_bitmap("../Games/Course_Chevaux/image/enterkey.bmp",NULL);
    SAMPLE *musique= load_sample("../Games/Guitar_hero/musique/musique0.wav");
    FONT *police = load_font("arial.pcx", NULL, NULL);
    set_trans_blender(0, 0, 0, 128);
    if (!musique) {
        allegro_message("Erreur : impossible de charger la musique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }


    int nbnote = 4*batt;
    int xnote[nbnote];
    int ynote[nbnote];
    int nombreAleatoire=20;
    int memo;
    char message[50];
    int score;
    int vitesse;
    int nbjoueur=2;
    int note1=0*155+WIDTH*0.34;
    int note2=1*155+WIDTH*0.34;
    int note3=2*155+WIDTH*0.34;
    int note4=3*155+WIDTH*0.34;
    int notey=HEIGHT/1.5;
    int ticket=0;
    int xenter=WIDTH-400;
    int yenter=HEIGHT-80;

    int ok[4];
    ok[0]=0;
    ok[1]=0;
    ok[2]=0;
    ok[3]=0;

    // Initialisation de la fonction rand() avec la fonction srand()
    //srand(time(NULL));
    if(!arriver){
        allegro_message("../image/arriver.bmp");
        exit(EXIT_FAILURE);
    }
    if(!note){
        allegro_message("../image/note.bmp");
        exit(EXIT_FAILURE);
    }
    if(!fond){
        allegro_message("../image/fondguitar0.bmp ");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    buffer=create_bitmap(WIDTH,HEIGHT);

    for (int tour = 0; tour < nbjoueur; ++tour) {
        joueurs[tour].nbTickets-=1;
        stop_sample(musique);
        play_sample(musique, 255, 128, 1000, 1);
        memo=0;
        for (int j = 0; j < batt; ++j) {
            for(int i=0;i<nbnote/batt;i++){
                xnote[i+j*(nbnote/batt)]=i*155+WIDTH*0.34;
                ynote[i+j*(nbnote/batt)]=(j+1)*(-200*(i+1));
            }
        }
        vitesse=60;
        score=0;
        rest(150); // Pause de 10 ms pour rafraîchir l'écran
        while (!key[KEY_ESC] && memo ==0) {
            clear_bitmap(buffer);
            clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc

            stretch_blit(fond,buffer,0,0,fond->w,fond->h,0,0,WIDTH,HEIGHT);

            for (int i=0; i<nbnote; i++) {

                ynote[i] += nombreAleatoire;
                draw_sprite(buffer,note,xnote[i],ynote[i]);
                draw_sprite(buffer,note,note1,notey);
                draw_sprite(buffer,note,note2,notey);
                draw_sprite(buffer,note,note3,notey);
                draw_sprite(buffer,note,note4,notey);

                if (ynote[i] >= HEIGHT ){
                    memo=1;
                    // Collision détectée !
                }
            }
            if (key[KEY_G] && ok[0] == 0) {
                if (xnote[0] <= (note1 + note->w) && (note1) <= (xnote[0] + note->w) &&
                    ynote[0] <= (notey + note->h) && (notey) <= (ynote[0] + note->h)) {
                    ynote[0] = -200;
                    score += 1;
                    vitesse -= 1;
                    ok[0] = 1;
                    // Collision détectée !
                } else {
                    memo = 1;
                }
            }
            if (key[KEY_H] && ok[1] == 0) {
                if (xnote[1] <= (note2 + note->w) && (note2) <= (xnote[1] + note->w) &&
                    ynote[1] <= (notey + note->h) && (notey) <= (ynote[1] + note->h)) {
                    ynote[1] = -200;
                    score += 1;
                    vitesse -= 1;
                    ok[1] = 1;
                    // Collision détectée !
                } else {
                    memo = 1;
                }
            }

            if (key[KEY_J] && ok[2] == 0) {
                if (xnote[2] <= (note3 + note->w) && (note3) <= (xnote[2] + note->w) &&
                    ynote[2] <= (notey + note->h) && (notey) <= (ynote[2] + note->h)) {
                    ynote[2] = -200;
                    score += 1;
                    vitesse -= 1;
                    // Collision détectée !
                    ok[2] = 1;
                } else {
                    memo = 1;
                }
            }
            if (key[KEY_K] && ok[3] == 0) {
                if (xnote[3] <= (note4 + note->w) && (note4) <= (xnote[3] + note->w) &&
                    ynote[3] <= (notey + note->h) && (notey) <= (ynote[3] + note->h)) {
                    ynote[3] = -200;
                    score += 1;
                    vitesse -= 1;
                    // Collision détectée !
                    ok[3] = 1;
                } else {
                    memo = 1;
                }
            }
            if (!key[KEY_G]) {
                ok[0] = 0;
            }
            if (!key[KEY_H]) {
                ok[1] = 0;
            }
            if (!key[KEY_J]) {
                ok[2] = 0;
            }
            if (!key[KEY_K]) {
                ok[3] = 0;
            }
            textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "score: %d", score);
            blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
            rest(vitesse); // Pause de 10 ms pour rafraîchir l'écran
        }
        while (!key[KEY_ENTER]) {
            draw_sprite(buffer,enterkey,xenter,yenter);
            stop_sample(musique);
            sprintf(message,"Perdu enculé");
            joueurs[tour].score_guitare[joueurs[tour].nb_essaie_guitare]=score;
            textout_centre_ex(buffer, font, message, WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
            blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
            rest(100); // Pause de 10 ms pour rafraîchir l'écran
        }
        joueurs[tour].nb_essaie_guitare+=1;
    }
    rest(150); // Pause de 10 ms pour rafraîchir l'écran
    clear_bitmap(buffer);
    clear_to_color(buffer, makecol(255, 255, 255)); // Effacer l'écran en blanc
    while (!key[KEY_ESC]) {
        if (joueurs[0].score_guitare[joueurs[0].nb_essaie_guitare-1]<joueurs[1].score_guitare[joueurs[1].nb_essaie_guitare-1]){
            sprintf(message,"%s a gagné 1 ticket",joueurs[1].nom);
            if(ticket==0){
                joueurs[1].nbTickets+=2;
                ticket=1;
            }
        }
        else if(joueurs[0].score_guitare[joueurs[0].nb_essaie_guitare-1]>joueurs[1].score_guitare[joueurs[1].nb_essaie_guitare-1]){
            sprintf(message,"%s a gagné 1 ticket",joueurs[0].nom);
            if(ticket==0){
                joueurs[0].nbTickets+=2;
                ticket=1;
            }
        }
        else {
            sprintf(message,"egalite");
            if(ticket==0){
                joueurs[0].nbTickets+=1;
                joueurs[1].nbTickets+=1;
                ticket=1;
            }
        }
        textout_centre_ex(buffer, font, message, WIDTH / 2, HEIGHT / 2, makecol(255, 0, 0), -1);
        blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
        rest(100); // Pause de 10 ms pour rafraîchir l'écran
    }
    rest(150); // Pause de 10 ms pour rafraîchir l'écran
}